#include "MBcommunication.h"
#include "MBdefine.h"
#include <QDebug>
#include "ViewModel/main_vm.h"
#include "MBDLL.h"

QScopedPointer<MBCommunication> MBCommunication::m_pInstance;

MBCommunication::MBCommunication(QObject *parent)
    : QObject{parent}
    , m_ipAddress("192.168.1.100")
    , m_port("502")
    , m_serverAddress("1")
    , m_isConnectedState(false)
    , m_mode(MT_CLIENT_MODE)
    , m_pDevice(nullptr)
    , m_groupAdressIndex(0)
{
    m_pPollingDataUpdate.reset(new QTimer(this));
    connect(m_pPollingDataUpdate.data(), &QTimer::timeout, this, &MBCommunication::ReadData);
    m_pPollingDataUpdate.data()->setInterval(200);


    if(Setup() == false)
    {
        qDebug() << "MBCommunication Setup failed";
    }
}

MBCommunication::~MBCommunication()
{
    StopPollingTimer();

    if (MBDLLControl::IsRegistedDLL() == true)
        MBDLLControl::DestroyFactory(m_pDevice);
}


// to avoid any unwanted issue, should not call this function multiple time // чтобы избежать каких-либо нежелательных   Неисправностей, не следует вызывать эту функцию несколько раз
bool MBCommunication::Setup()
{
    bool isOk = false;

    if (MBDLLControl::IsRegistedDLL() == false) return isOk;

    isOk = MBDLLControl::CreateFactory(&m_pDevice, m_mode);
    if (isOk == false) return isOk;

    m_ipAddress = ConfigApplication::instance()->m_commonInfo.plcSetting.strIPAddress;
    m_port = ConfigApplication::instance()->m_commonInfo.plcSetting.strPort;
    m_serverAddress = ConfigApplication::instance()->m_commonInfo.plcSetting.strServerAddress;

 
    isOk = MBDLLControl::SetUpConnectionParameter(m_pDevice, 
                               m_ipAddress.toStdString().c_str(),
                               m_port.toStdString().c_str(),
                               m_serverAddress.toStdString().c_str());

    if(isOk == false) return isOk;

    isOk = MBDLLControl::SetUpUnitData(m_pDevice,
                (int)MB_COIL_ITEMS::START, (int)MB_COIL_ITEMS::END - (int)MB_COIL_ITEMS::START,
                    (int)MB_DISCRETE_INPUT_ITEMS::START, (int)MB_DISCRETE_INPUT_ITEMS::END - (int)MB_DISCRETE_INPUT_ITEMS::START,
                    (int)MB_INPUT_REGISTER_ITEMS::START, (int)MB_INPUT_REGISTER_ITEMS::END - (int)MB_INPUT_REGISTER_ITEMS::START,
                    (int)MB_HOLDING_REGISTER_ITEMS::START, (int)MB_HOLDING_REGISTER_ITEMS::END - (int)MB_HOLDING_REGISTER_ITEMS::START);

    if(isOk == false) return isOk;


    isOk = MBDLLControl::SetUpCallback(m_pDevice, 
        ConnectionChangedCallback, 
        ErrorOccurCallback, 
        DataReadCompleteCallback, 
        DataWriteCompleteCallback);

    if(isOk == false) return isOk;

    isOk = MBDLLControl::Init(m_pDevice);

    return isOk;
}

bool MBCommunication::Start()
{
    if (MBDLLControl::IsRegistedDLL() == false) return false;

    if(!MBDLLControl::Start(m_pDevice))
    {
        qDebug() << "MBCommunication Start failed";
    }
    return true;
}

void MBCommunication::StartPollingTimer()
{
    if (MBDLLControl::IsRegistedDLL() == false) return;

    // only client mode need to have timer // таймер должен быть установлен только в клиентском режиме
    if (m_mode == MT_SERVER_MODE) return;

    if (!m_pPollingDataUpdate.data()->isActive())
        m_pPollingDataUpdate.data()->start();
}

void MBCommunication::StopPollingTimer()
{
    if (MBDLLControl::IsRegistedDLL() == false) return;

    // only client mode need to have timer // таймер должен быть установлен только в клиентском режиме
    if (m_mode == MT_SERVER_MODE) return;

    if (m_pPollingDataUpdate.data()->isActive())
        m_pPollingDataUpdate.data()->stop();
}

void MBCommunication::WriteData(int table, int address, int val)
{
    if (MBDLLControl::IsRegistedDLL() == false) return;

    auto v = static_cast<quint16>(val);

    if (!MBDLLControl::WriteDataUnit(m_pDevice, table, address, QVector<quint16>{v})) {
        qDebug() << "Write data failed";
    }
}

void MBCommunication::WriteBitData(int table, int address, int bitValue, bool val)
{
    if (MBDLLControl::IsRegistedDLL() == false) return;

    MBKeyData key(address, table);
    quint16 currentVal = MBCommunication::GetInstance()->m_mbDataAggregation[key];

    currentVal = val ? (currentVal | bitValue) : (currentVal & ~(bitValue));

    if (!MBDLLControl::WriteDataUnit(m_pDevice, table, address, QVector<quint16>{currentVal})) {
        qDebug() << "Write data failed";
    }
}

void MBCommunication::WriteFloatData(int table, int address, float val)
{
    if (MBDLLControl::IsRegistedDLL() == false) return;

    quint16 reg1, reg2;
    MBCommunication::ConvertFloatTo2Registers(val, reg1, reg2);
    QVector<quint16> reg = {reg1, reg2};
    int regCount = reg.count();

    if (!MBDLLControl::WriteDataUnit(m_pDevice, table, address, reg)) {
        qDebug() << "Write data failed";
    }
}

void MBCommunication::WriteUint32Data(int table, int address, quint32 val)
{
    uint16_t low = static_cast<uint16_t>(val & 0xFFFF);         // Lower 16 bits
    uint16_t high = static_cast<uint16_t>((val >> 16) & 0xFFFF);  // Upper 16 bits

    if (!MBDLLControl::WriteDataUnit(m_pDevice, table, address, QVector<quint16>{low, high})) {
        qDebug() << "Write data failed";
    }
}

void MBCommunication::ReadFloatData(int table, int address, float &val)
{
    MBKeyData key1(address, table);
    quint16 currentVal1 = MBCommunication::GetInstance()->m_mbDataAggregation[key1];
    MBKeyData key2(address + 1, table);
    quint16 currentVal2 = MBCommunication::GetInstance()->m_mbDataAggregation[key2];

    uint32_t combined = (static_cast<uint32_t>(currentVal2) << 16) | currentVal1;
#ifdef Q_OS_WIN
    std::memcpy(&val, &combined, sizeof(val));
#elif defined(Q_OS_LINUX)
    memcpy(&val, &combined, sizeof(val));
#endif
    //val = static_cast<float>(combined) / (1 << 16);
}

void MBCommunication::ReadUnit16Data(int table, int address, quint16& val)
{
    MBKeyData key(address, table);
    val = MBCommunication::GetInstance()->m_mbDataAggregation[key];
}

void MBCommunication::ReadUint32Data(int table, int address, quint32& val)
{
    val = 0;

    MBKeyData key1(address, table);
    quint16 currentVal1 = MBCommunication::GetInstance()->m_mbDataAggregation[key1];
    MBKeyData key2(address + 1, table);
    quint16 currentVal2 = MBCommunication::GetInstance()->m_mbDataAggregation[key2];

    val = (static_cast<uint32_t>(currentVal2) << 16) | currentVal1;
}

void MBCommunication::ConvertFloatTo2Registers(float value, quint16 &reg1, quint16 &reg2)
{
    /*uint32_t intValue = static_cast<uint32_t>(value * (1 << 16));*/
    quint32 intValue = 0;
    memcpy(&intValue, &value, sizeof(float)); // Copy the float bits to an integer
    reg1 = static_cast<quint16>(intValue & 0xFFFF);         // Lower 16 bits
    reg2 = static_cast<quint16>((intValue >> 16) & 0xFFFF); // Upper 16 bits
}



void MBCommunication::ConnectionChangedCallback(int connectState)
{
    void* pDevice = MBCommunication::GetInstance()->m_pDevice;

    if (connectState == MT_ConnectingState) return;

    // when go to unconnected state will automatically connect // при переходе в неподключенное состояние произойдет автоматическое подключение
    if (connectState == MT_UnconnectedState)
    {
        MBCommunication::GetInstance()->Start();
    }

    if(theMainVM.m_bIsAppClosing == false)
        PLCCommunicationLogVM::GetInstance()->WriteDebugLog("MBCommunication", connectState ? "Connect PLC success" : "Connect PLC failed",
                                                            connectState ? tr("Connect PLC success") : tr("Connect PLC failed"));

    bool isAlive = MBDLLControl::IsDeviceConnected(pDevice);

    // return if not changing in state // вернуть, если состояние не меняется
    if (isAlive == MBCommunication::GetInstance()->m_isConnectedState) return;

    MBCommunication::GetInstance()->m_isConnectedState = isAlive;

    if (isAlive == true) {
        MBCommunication::GetInstance()->StartPollingTimer();
    }
    else {
        MBCommunication::GetInstance()->StopPollingTimer();

        // reset all modbus value when disconnect // сбросить все значения modbus при отключении
        auto& data = MBCommunication::GetInstance()->m_mbDataAggregation;
        for (auto& val : data.values()) val = 0;
  
    } 

}

void MBCommunication::ErrorOccurCallback(int error)
{
    qDebug() << "MBCommunicate Error: " << error;

}

void MBCommunication::DataWriteCompleteCallback(int table, int startAddress, int count, bool isSuccess)
{
    qDebug() << QString("MBCommunicate DataWriteCompleteCallback. Table: %1, Starting address: %2, Item count: %3, IsSucess: %4 ").arg(table).arg(startAddress).arg(count).arg(isSuccess);
    int a = 2;
}

void MBCommunication::DataReadCompleteCallback(int table, int address, int totalCount, const QVector<quint16> &val, bool isSuccess)
{
    if (address == -1) return;
    if (table <= 0 || table > MT_HOLDING_REGISTER) return;
    if (totalCount == 0) return;
    if (isSuccess == false) return;
    if (totalCount != val.count()) return;


    for (int i = 0; i < totalCount; i++)
    {
        MBCommunication::GetInstance()->AccumulateData(table, address + i, val.at(i));
    }

    // emit signal to other side to update data // отправить сигнал на другую сторону для обновления данных
    emit MBCommunication::GetInstance()->populateDataSignal();
}

void MBCommunication::ReadData()
{
    // Try to read all data type // Попробуйте прочитать все типы данных
    
    if (MBDLLControl::IsRegistedDLL() == false) return;

    if (theMainVM.m_bIsAppClosing) return;

    int startAddress = 0;
    int totalAddress = 0;
    int totalItemSendToMB = 0;

    // not use, just passing to function call for this case // не использовать, просто перейти к вызову функции для этого случая
    QVector<quint16> val;

    ////-- Read Discrete Input --//
    //if (MBDLLControl::GetDataUnitInfor(m_pDevice, MT_DISCRETE_INPUT, startAddress, totalAddress) == false)
    //{
    //    qDebug() << "Get data unit failed";
    //    return;
    //}
    //// or access directly in current application to get register information
    //for (int i = 0; i < totalAddress; i += MT_MAX_ALLOWANCE_READ_ITEM)
    //{
    //    totalItemSendToMB = qMin(MT_MAX_ALLOWANCE_READ_ITEM, totalAddress - i);
    //    val.clear();
    //    // data will be update in callback function, not at here
    //    if (MBDLLControl::ReadDataUnit(m_pDevice, MT_DISCRETE_INPUT, i + startAddress, totalItemSendToMB, val) == false) {
    //        qDebug() << "MTReadDataUnit Discrete failed";
    //    }
    //}

    ////-- Read Coil --//
    //startAddress = 0;
    //totalAddress = 0;
    //if (MBDLLControl::GetDataUnitInfor(m_pDevice, MT_COIL, startAddress, totalAddress) == false)
    //{
    //    qDebug() << "Get data unit failed";
    //    return;
    //}
    //for (int i = 0; i < totalAddress; i += MT_MAX_ALLOWANCE_READ_ITEM)
    //{
    //    totalItemSendToMB = qMin(MT_MAX_ALLOWANCE_READ_ITEM, totalAddress - i);
    //    // data will be update in callback function, not at here
    //    val.clear();
    //    if (MBDLLControl::ReadDataUnit(m_pDevice, MT_COIL, i + startAddress, totalItemSendToMB, val) == false) {
    //        qDebug() << "MTReadDataUnit Coil failed";
    //    }
    //}

    ////-- Read Input Register --//
    //startAddress = 0;
    //totalAddress = 0;
    //if (MBDLLControl::GetDataUnitInfor(m_pDevice, MT_INPUT_REGISTER, startAddress, totalAddress) == false)
    //{
    //    qDebug() << "Get data unit failed";
    //    return;
    //}
    //for (int i = 0; i < totalAddress; i += MT_MAX_ALLOWANCE_READ_ITEM)
    //{
    //    totalItemSendToMB = qMin(MT_MAX_ALLOWANCE_READ_ITEM, totalAddress - i);
    //    // data will be update in callback function, not at here
    //    val.clear();
    //    if (MBDLLControl::ReadDataUnit(m_pDevice, MT_INPUT_REGISTER, i + startAddress, totalItemSendToMB, val) == false) {
    //        qDebug() << "MTReadDataUnit Input Register failed";
    //    }
    //}


    //-- Read Holding Register --//
     //startAddress = 0;
     //totalAddress = 0;
     //if (MBDLLControl::GetDataUnitInfor(m_pDevice, MT_HOLDING_REGISTER, startAddress, totalAddress) == false)
     //{
     //    qDebug() << "Get data unit failed";
     //    return;
     //}


     //for (int i = 0; i < totalAddress; i += MT_MAX_ALLOWANCE_READ_ITEM)
     //{
     //    totalItemSendToMB = qMin(MT_MAX_ALLOWANCE_READ_ITEM, totalAddress - i);
     //    // data will be update in callback function, not at here
     //    val.clear();

     //    if (MBDLLControl::IsDeviceConnected(m_pDevice) == false) break;

     //    if (MBDLLControl::ReadDataUnit(m_pDevice, MT_HOLDING_REGISTER, i + startAddress, totalItemSendToMB, val) == false) {
     //        qDebug() << "MTReadDataUnit Holding Register failed";
     //    }
     //}


     // read amonut of memory
 /*    int totalRead = (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_CAMERA_ADJUSTMENT_VALUE - (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_0;

     for (int i = 0; i < totalRead; i += MT_MAX_ALLOWANCE_READ_ITEM)
     {
         auto totalItemSendToMB = qMin(MT_MAX_ALLOWANCE_READ_ITEM, totalRead - i);

         if (MBDLLControl::ReadDataUnit(m_pDevice, MT_HOLDING_REGISTER, i + (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_0, totalItemSendToMB, val) == false) {
             qDebug() << "MTReadDataUnit Holding Register failed";
         }

         QThread::msleep(100);
     }

     totalRead = (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_SCALE_CURRENT_VALUE - (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START;

     for (int j = 0; j < totalRead; j += MT_MAX_ALLOWANCE_READ_ITEM)
     {
         auto totalItemSendToMB = qMin(MT_MAX_ALLOWANCE_READ_ITEM, totalRead - j);

         if (MBDLLControl::ReadDataUnit(m_pDevice, MT_HOLDING_REGISTER, j + (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START, totalItemSendToMB, val) == false)
         {
             qDebug() << "MTReadDataUnit Holding Register failed";
         }

         QThread::msleep(100);
     }*/

  /*  int totalRead = (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_CAMERA_ADJUSTMENT_VALUE - (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_0;

     if (MBDLLControl::ReadDataUnit(m_pDevice, MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_0, totalRead, val) == false) {
         qDebug() << "MTReadDataUnit Holding Register failed";
     }
     QThread::msleep(10);

     totalRead = (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_SCALE_CURRENT_VALUE - (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START;

     if (MBDLLControl::ReadDataUnit(m_pDevice, MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START, totalRead, val) == false) {
         qDebug() << "MTReadDataUnit Holding Register failed";
     }*/

    if (m_groupAdressIndex % 3 == 0)
    {
        int totalRead = (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_14 - (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_0;

        if (MBDLLControl::ReadDataUnit(m_pDevice, MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_0, totalRead, val) == false) {
            qDebug() << "MTReadDataUnit Holding Register failed";
        }
    }
    else if (m_groupAdressIndex % 3 == 1)
    {
        int totalRead = (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_BOTTOM_DEPTH_ACK_VALUE + 1 - (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500;

        if (MBDLLControl::ReadDataUnit(m_pDevice, MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500, totalRead, val) == false) {
            qDebug() << "MTReadDataUnit Holding Register failed";
        }
    }
    else if (m_groupAdressIndex % 3 == 2)
    {
        int totalRead = (int)MB_HOLDING_REGISTER_ITEMS::END - (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START + 1;

        if (MBDLLControl::ReadDataUnit(m_pDevice, MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START, totalRead, val) == false) {
            qDebug() << "MTReadDataUnit Holding Register failed";
        }
    }
    m_groupAdressIndex++;
}

void MBCommunication::AccumulateData(int table, int address, quint16 value)
{
    MBKeyData k(address, table);

    if (m_mbDataAggregation.contains(k))
    {
        m_mbDataAggregation[k] = value;
    }
    else
    {
        m_mbDataAggregation.insert(k, value);
    }
}



MBKeyData::MBKeyData()
    : address(0)
    , table(0)
{
}

MBKeyData::MBKeyData(int _address, int _table)
    : address(_address)
    , table(_table)
{
}

MBKeyData::~MBKeyData()
{
}
