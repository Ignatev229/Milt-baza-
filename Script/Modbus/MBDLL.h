#ifndef MBDLL_H
#define MBDLL_H

#include <QVector>

#define MT_SERVER_MODE 0
#define MT_CLIENT_MODE 1

#define MT_DISCRETE_INPUT 1
#define MT_COIL 2
#define MT_INPUT_REGISTER 3
#define MT_HOLDING_REGISTER 4

#define MT_UnconnectedState 0
#define MT_ConnectingState 1
#define MT_ConnectedState 2
#define MT_ClosingState 4


//-- Function callback --// //-- Обратный вызов функции --//
typedef void  (*onMTConnectStateChanged)(int);
typedef void (*onMTErrorOccured)(int);
typedef void (*onMTDataWriteCompletely)(int table, int address, int size, bool isSuccess);
typedef void (*onMTDataReadCompletely)(int table, int address, int totalCount, const QVector<quint16>& val, bool isSuccess);


// Allow read/write up to x item at time // Разрешить чтение / запись до x элементов
#define MT_MAX_ALLOWANCE_READ_ITEM 10
#define MT_MAX_ALLOWNACE_WRITE_ITEM 20

//-- DLL --//
typedef bool (*MTCreateFactoryFunc)(void** device, int mode);
typedef bool (*MTDestroyFactoryFunc)(void* device);

typedef bool (*MTSetUpConnectionParameterFunc)(void* device, const char* ip, const char* port, const char* serverAddress);

typedef bool (*MTSetUpUnitDataFunc)(void* device,
    int coilStart, int coilCount,
    int discreteInputStart, int discreteInputCount,
    int inputRegisterStart, int inputRegisterCount,
    int holdingRegisterStart, int holdingRegisterCount);


typedef bool (*MTSetUpCallbackFunc)(void* device, 
    onMTConnectStateChanged connectionChanged,
    onMTErrorOccured errorOccured,
    onMTDataReadCompletely dataReadCompletely,
    onMTDataWriteCompletely dataWriteCompletely);

typedef bool (*MTInitFunc)(void* device);
typedef bool (*MTStartFunc)(void* device);
typedef bool (*MTStopFunc)(void* device);

typedef bool (*MTGetDataUnitInforFunc)(void* device, int table, int& startAdd, int& total);

typedef bool (*MTWriteDataUnitFunc)(void* device, int table, int address, const QVector<quint16>& val);

typedef bool (*MTReadDataUnitFunc)(void* device, int table, int address, int totalCount, QVector<quint16>& val);

typedef bool (*MTIsConnectedFunc)(void* device);
//----//

class MBDLLControl
{
public:
    
    /// <summary>
    /// Must call this one first
    /// Avoid call mutiple time to avoid unwanted issue
    /// </summary>
    /// <param name="dllName"></param>
    /// <returns></returns>
    static bool RegisterDLL(const char* dllName);

    static inline  bool IsRegistedDLL() { return m_isInit; }

    /// <summary>
    /// Entry function
    /// </summary>
    /// <param name="device"></param>
    /// <param name="mode"></param>
    /// <returns></returns>
    static inline bool CreateFactory(void** device, int mode) { return m_pMTCreateFactoryFunc(device, mode); }

    /// <summary>
    /// Exit function
    /// </summary>
    /// <param name="device"></param>
    /// <returns></returns>
    static inline bool DestroyFactory(void* device) { return m_pMTDestroyFactoryFunc(device); }

    /// <summary>
    /// Init function type
    /// </summary>
    /// <param name="device"></param>
    /// <param name="ip"></param>
    /// <param name="port"></param>
    /// <param name="serverAddress"></param>
    /// <returns></returns>
    static inline bool SetUpConnectionParameter(void* device, const char* ip, const char* port, const char* serverAddress) { return m_pMTSetUpConnectionParameterFunc(device, ip, port, serverAddress); }

    /// <summary>
    /// Init function type
    /// </summary>
    /// <param name="device"></param>
    /// <param name="coilStart"></param>
    /// <param name="coilCount"></param>
    /// <param name="discreteInputStart"></param>
    /// <param name="discreteInputCount"></param>
    /// <param name="inputRegisterStart"></param>
    /// <param name="inputRegisterCount"></param>
    /// <param name="holdingRegisterStart"></param>
    /// <param name="holdingRegisterCount"></param>
    /// <returns></returns>
    static inline bool SetUpUnitData(void* device, int coilStart, int coilCount, int discreteInputStart, int discreteInputCount, int inputRegisterStart, int inputRegisterCount, int holdingRegisterStart, int holdingRegisterCount) {
        return m_pMTSetUpUnitDataFunc(device, coilStart, coilCount, discreteInputStart, discreteInputCount, inputRegisterStart, inputRegisterCount, holdingRegisterStart, holdingRegisterCount);
    }

    /// <summary>
    /// Init function type
    /// </summary>
    /// <param name="device"></param>
    /// <param name="connectionChanged"></param>
    /// <param name="errorOccured"></param>
    /// <param name="dataReadCompletely"></param>
    /// <param name="dataWriteCompletely"></param>
    /// <returns></returns>
    static inline bool SetUpCallback(void* device, onMTConnectStateChanged connectionChanged, onMTErrorOccured errorOccured, onMTDataReadCompletely dataReadCompletely, onMTDataWriteCompletely dataWriteCompletely) {
        return m_pMTSetUpCallbackFunc(device, connectionChanged, errorOccured, dataReadCompletely, dataWriteCompletely);
    }

    /// <summary>
    /// Init function type
    /// </summary>
    /// <param name="device"></param>
    /// <returns></returns>
    static inline bool Init(void* device) { return m_pMTInitFunc(device); }

    /// <summary>
    /// Start connection
    /// </summary>
    /// <param name="device"></param>
    /// <returns></returns>
    static inline bool Start(void* device) { return m_pMTStartFunc(device); }

    /// <summary>
    /// Stop connection
    /// </summary>
    /// <param name="device"></param>
    /// <returns></returns>
    static inline bool Stop(void* device) { return m_pMTStopFunc(device); }

    /// <summary>
    /// Get the range of data memory and table of currently using
    /// </summary>
    /// <param name="device"></param>
    /// <param name="table"></param>
    /// <param name="startAdd"></param>
    /// <param name="total"></param>
    /// <returns></returns>
    static inline bool GetDataUnitInfor(void* device, int table, int& startAdd, int& total) { return m_pMTGetDataUnitInforFunc(device, table, startAdd, total); }

    /// <summary>
    /// Read Write function
    /// Only allow write 1 data unit at a time
    /// </summary>
    /// <param name="device"></param>
    /// <param name="table"></param>
    /// <param name="address"></param>
    /// <param name="val"></param>
    /// <returns></returns>
    static inline bool WriteDataUnit(void* device, int table, int address, const QVector<quint16>& val) { return m_pMTWriteDataUnitFunc(device, table, address, val); }


    /// <summary>
    /// Read Write function
    /// </summary>
    /// <param name="device"></param>
    /// <param name="table"></param>
    /// <param name="address"></param>
    /// <param name="totalCount"></param>
    /// <param name="val"></param>
    /// <returns></returns>
    static inline bool ReadDataUnit(void* device, int table, int address, int totalCount, QVector<quint16>& val) { return m_pMTReadDataUnitFunc(device, table, address, totalCount, val); }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="device"></param>
    /// <returns></returns>
    static inline bool IsDeviceConnected(void* device) { return m_pMTIsConnectedFunc(device); }
    
    //
private:
    static bool m_isInit;


    // DLL function Ptr// // DLL-функция Ptr//
    static MTCreateFactoryFunc m_pMTCreateFactoryFunc;
    static MTDestroyFactoryFunc m_pMTDestroyFactoryFunc;
    static MTSetUpConnectionParameterFunc m_pMTSetUpConnectionParameterFunc;
    static MTSetUpUnitDataFunc m_pMTSetUpUnitDataFunc;
    static MTSetUpCallbackFunc m_pMTSetUpCallbackFunc;

    static MTInitFunc m_pMTInitFunc;
    static MTStartFunc m_pMTStartFunc;
    static MTStopFunc m_pMTStopFunc;

    static MTGetDataUnitInforFunc m_pMTGetDataUnitInforFunc;
    static MTWriteDataUnitFunc m_pMTWriteDataUnitFunc;
    static MTReadDataUnitFunc m_pMTReadDataUnitFunc;
    static MTIsConnectedFunc m_pMTIsConnectedFunc;

};

#endif // MBDLL_H
