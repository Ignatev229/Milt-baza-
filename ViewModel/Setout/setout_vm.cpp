#include "setout_vm.h"
#include "../../ViewModel/master_app.h"

QScopedPointer<SetoutVM> SetoutVM::m_pInstance;

SetoutVM::SetoutVM(QObject *parent)
    : QObject{parent}
{

}

SetoutVM::~SetoutVM()
{

}

int SetoutVM::highPressureStatus()
{
    return _highPressureStatus;
}

int SetoutVM::safetyRelayStatus()
{
    return _safetyRelayStatus;
}

void SetoutVM::Init(QQmlApplicationEngine &appEngine, QObject *parent)
{
    setHighPressureStatus(0); // 0: false, 1: true
    setSafetyRelayStatus(0);
    m_pParentObject = reinterpret_cast<MasterApp*>(parent);
}

void SetoutVM::UpdateMoldUI(int column, int row, int header, int result)
{
    // emit updateMoldListUI_Signal(column, row, header, result);
}

void SetoutVM::InitSetoutMoldNumber()
{
    QString path = ConfigApplication::instance()->GetReportFilePath(ConfigApplication::instance()->m_strSetoutMoldFileName);
    m_pParentObject->m_strcSetoutMoldsData.loadFromFile(path);
    // get current mold index of this report
    m_pParentObject->m_strcSetoutMoldsData.GetMoldNumberInspectionSequence(m_pParentObject->m_strcSetoutMoldsData.m_nCurrentMoldIndex);
    // update to UI
    emit initSetoutMoldNumber_Signal(m_pParentObject->m_strcSetoutMoldsData.m_ListMoldNumbers,
                                     m_pParentObject->m_strcSetoutMoldsData.m_ListMoldResults);
}

void SetoutVM::UpdateMoldSerialNumberResult(MOLD_RESULT result, int moldIndex)
{
    QString path = ConfigApplication::instance()->GetReportFilePath(ConfigApplication::instance()->m_strSetoutMoldFileName);
    m_pParentObject->m_strcSetoutMoldsData.UpdateResult(result, moldIndex);
    m_pParentObject->m_strcSetoutMoldsData.saveToFile(path);
    emit updateMoldNumberResult_Signal(result, moldIndex);
}

void SetoutVM::setHighPressureStatus(int value)
{
    if(_highPressureStatus != value){_highPressureStatus = value; emit highPressureStatusChanged();}
}
void SetoutVM::setSafetyRelayStatus(int value)
{
    if(_safetyRelayStatus != value){_safetyRelayStatus = value; emit safetyRelayStatusChanged();}
}



void SetoutVM::runStopStatus_Qml_Slot(bool value, QString currentJobText)
{
    // qDebug() << "[SetoutVM]" << "Run Stop status: " << value;
    // setCurrentJob(listJobModel.items()[currentJobIndex].value);

    // load recipe // Загружаем рецепт
    // if(value && currentJobText != "")
    // {
    //     RecipeManagementVM::GetInstance()->doLoadRecipe(currentJobText, false);
    // }

    // ConfigApplication::instance()->m_appStatus = value ? APP_STATUS::RUNNING : APP_STATUS::STOP;

    // // write to status bit
    // MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_1000,
    //                                              (int)REGISTER_1000_PROFILE::AUTOMATIC_CYCLE, value);

    // write to control bit
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_0,
                                                value ? (int)REGISTER_0_PROFILE::START_AUTOMATIC_CYCLE : (int)REGISTER_0_PROFILE::STOP_AUTOMATIC_CYCLE, true);
    PLCCommunicationLogVM::GetInstance()->WriteDebugLog("SetoutVM", value ? "Set START_AUTOMATIC_CYCLE" : "Set STOP_AUTOMATIC_CYCLE", "");
}

void SetoutVM::clearAllContainers_Qml_Slot()
{
    qDebug() << "[SetoutVM]" << "Clear all containers";
    m_pParentObject->m_strcSetoutMoldsData.Clear();
    QString path = ConfigApplication::instance()->GetReportFilePath(ConfigApplication::instance()->m_strSetoutMoldFileName);
    m_pParentObject->m_strcSetoutMoldsData.saveToFile(path);

    // clear report tab // очистить вкладку отчета
    ReportVM::GetInstance()->ClearInspectionData();

}

void SetoutVM::columnHeaderMoldChanged_Qml_Slot(int column, int value)
{
    qDebug() << "[SetoutVM]" << "Header Mold changed: " << column << value;
}

void SetoutVM::resetAlarm_Qml_Slot()
{
    qDebug() << "[SetoutVM]" << "Reset alarm";
    PLCCommunicationLogVM::GetInstance()->WriteDebugLog("SetoutVM", "Reset PLC alarm");
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_0, (int)REGISTER_0_PROFILE::RESET_ERROR_STATE, true);
}

void SetoutVM::safetyRelayReset_Qml_Slot()
{
    qDebug() << "[SetoutVM]" << "Safety Relay Reset";
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_0, (int)REGISTER_0_PROFILE::SAFETY_RELAY_RESET_STATE, true);
}

void SetoutVM::saveMoldNumbers(QList<QVariant> data)
{
    QList<QString> strList;
    for (const QVariant &variant : data) {
        strList.append(variant.toString());
    }
    m_pParentObject->m_strcSetoutMoldsData.UpdateMoldNumber(strList);
    QString path = ConfigApplication::instance()->GetReportFilePath(ConfigApplication::instance()->m_strSetoutMoldFileName);
    m_pParentObject->m_strcSetoutMoldsData.saveToFile(path);

    // for update current result // для обновления текущего результата
    emit initSetoutMoldNumber_Signal(m_pParentObject->m_strcSetoutMoldsData.m_ListMoldNumbers,
                                     m_pParentObject->m_strcSetoutMoldsData.m_ListMoldResults);
}

void SetoutVM::loadRecipe_Qml_Slot(QString currentJobText)
{
    // load recipe // Загружаем рецепт
    if(currentJobText != "")
    {
        RecipeManagementVM::GetInstance()->doLoadRecipe(currentJobText, false);
    }
}







