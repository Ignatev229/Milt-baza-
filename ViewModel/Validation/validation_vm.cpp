#include "validation_vm.h"
#include "../master_app.h"
#include "../../Script/Sql/sql_management.h"
#include "../Setout/plc_communication_log_vm.h"

QScopedPointer<ValidationVM> ValidationVM::m_pInstance;

ValidationVM::ValidationVM(QObject *parent)
    : QThread{parent}
{

}

ValidationVM::~ValidationVM()
{
    isRun = false;
    Resume();
    this->quit();
    this->wait();
}

void ValidationVM::run()
{
    isRun = true;
    Pause();
    double dValue = 0;
    while (isRun)
    {
        sync.lock();
        if(pause)
            pauseCond.wait(&sync);
        sync.unlock();

        switch (m_nValidationStep) {
        case VALIDATION_SEQUENCE::INITIAL:
            emit validationSequenceLog_Signal("Initial Validation");
            m_nValidationStep = VALIDATION_SEQUENCE::MOVE_BOTTOM1;
            break;
        case VALIDATION_SEQUENCE::MOVE_BOTTOM1:
            // send move to bottom pos
            dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1);
            emit moveTable_Signal(dValue);
            emit validationSequenceLog_Signal(QString("Move Table to Bottom 1: %1").arg(dValue));
            m_nValidationStep = VALIDATION_SEQUENCE::MOVE_BOTTOM1_COMPLETE;
            break;
        case VALIDATION_SEQUENCE::MOVE_BOTTOM1_COMPLETE:
            // while until finish move
            dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1);
            if(m_pParentObject->scopedTableVM.data()->tableElevationValue() == dValue)
            {
                emit validationSequenceLog_Signal("Move Table to Bottom 1 complete");
                emit validationSequenceLog_Signal("Call Bottom 1 Camera snap");

                // call snap
                m_pParentObject->scopedMainHomeVM.data()->Snap(
                    m_pParentObject->GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1));
                m_hashSequencePosImages[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1] =
                    m_pParentObject->hashTrackVM[m_pParentObject->GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1)]->GetDocImage(0).copy();
                m_nValidationStep = VALIDATION_SEQUENCE::MOVE_BOTTOM2;
            }
            break;

        case VALIDATION_SEQUENCE::MOVE_BOTTOM2:
            // send move to bottom pos
            dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2);
            emit moveTable_Signal(dValue);
            emit validationSequenceLog_Signal(QString("Move Table to Bottom 2: %1").arg(dValue));
            m_nValidationStep = VALIDATION_SEQUENCE::MOVE_BOTTOM2_COMPLETE;
            break;
        case VALIDATION_SEQUENCE::MOVE_BOTTOM2_COMPLETE:
            // while until finish move
            dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2);
            if(m_pParentObject->scopedTableVM.data()->tableElevationValue() == dValue)
            {
                emit validationSequenceLog_Signal("Move Table to Bottom 2 complete");
                emit validationSequenceLog_Signal("Call Bottom 2 Camera snap");

                // call snap
                m_pParentObject->scopedMainHomeVM.data()->Snap(
                    m_pParentObject->GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2));
                m_hashSequencePosImages[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2] =
                    m_pParentObject->hashTrackVM[m_pParentObject->GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2)]->GetDocImage(0).copy();
                m_nValidationStep = VALIDATION_SEQUENCE::MOVE_TOP;
            }
            break;

        case VALIDATION_SEQUENCE::MOVE_TOP:
            // send move to top pos
            dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::TOP);

            emit moveTable_Signal(dValue);
            emit validationSequenceLog_Signal(QString("Move Table to Top: %1").arg(dValue));
            m_nValidationStep = VALIDATION_SEQUENCE::MOVE_TOP_COMPLETE;
            break;
        case VALIDATION_SEQUENCE::MOVE_TOP_COMPLETE:

            // while until finish move
            dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::TOP);
            if(m_pParentObject->scopedTableVM.data()->tableElevationValue() == dValue)
            {
                emit validationSequenceLog_Signal("Move Table to Top complete");
                emit validationSequenceLog_Signal("Call Top Camera snap");

                // call snap
                m_pParentObject->scopedMainHomeVM.data()->Snap(
                    m_pParentObject->GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION::TOP));

                m_hashSequencePosImages[INSPECT_SEQUENCE_CAMERA_POSITION::TOP] =
                    m_pParentObject->hashTrackVM[m_pParentObject->GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION::TOP)]->GetDocImage(0).copy();

                m_nValidationStep = VALIDATION_SEQUENCE::VALIDATION;
            }

            break;
        case VALIDATION_SEQUENCE::VALIDATION:

            emit validationSequenceLog_Signal("Call inspection");
            m_nValidationStep = VALIDATION_SEQUENCE::INITIAL;

            // call validation inspection
            m_pParentObject->scopedMainHomeVM.data()->Inspect(BACKEND_FUNCTION::VALIDATION_INSPECT);

            // go home
            // MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ELEVATION_COMMAND_HOME, true);
            emit moveTableHome_Signal();
            emit validationSequenceLog_Signal("Move Table to Home");

            // pause for next validation
            Pause();
            break;
        default:
            break;
        }

        QThread::msleep(20);
    }
}

void ValidationVM::Resume()
{
    sync.lock();
    pause = false;
    sync.unlock();
    pauseCond.wakeAll();
}

void ValidationVM::Pause()
{
    sync.lock();
    pause = true;
    sync.unlock();
}

void ValidationVM::Init(QObject *parent)
{
    m_pParentObject = reinterpret_cast<MasterApp*>(parent);
    m_nValidationStep = VALIDATION_SEQUENCE::INITIAL;
    start();


    connect(this, SIGNAL(validationSequenceLog_Signal(QString)), this, SLOT(validationSequenceLog_Slot(QString)));
    connect(this, SIGNAL(moveTable_Signal(double)), this, SLOT(moveTable_Slot(double)));
    connect(this, SIGNAL(moveTableHome_Signal()), this, SLOT(moveTableHome_Slot()));


    // m_bIsValidation = false;
}

void ValidationVM::LoadOldData()
{
    // load old data
    setLastValidationTime("");
    QList<InspectionInfoItem> data = SQLManagement::GetInstance()->LoadValidationData();
    for (int i = 0; i < data.count(); ++i) {
        setLastValidationTime(data[i].getDateTime().getValue().toDateTime().toString("yyyy.MM.dd hh:mm:ss"));
        data[i].setDateTime(InspectionInfoChildItem(data[i].getDateTime().getValue().toDateTime().toString("yyyy.MM.dd hh:mm:ss"), true));
        emit addInspectionData_Signal(data[i]);
    }
}

QString ValidationVM::lastValidationTime()
{
    return _lastValidationTime;
}

void ValidationVM::AddInspectionData(InspectionInfoItem data)
{
    // store and record data // хранение и запись данных
    SQLManagement::GetInstance()->AddValidationData(data);
    setLastValidationTime(data.getDateTime().getValue().toDateTime().toString("yyyy.MM.dd hh:mm:ss"));
    data.setDateTime(InspectionInfoChildItem(data.getDateTime().getValue().toDateTime().toString("yyyy.MM.dd hh:mm:ss"), true));
    emit addInspectionData_Signal(data);
}

void ValidationVM::ClearInspectionData()
{
    // emit clearInspectionData_Signal();
}

void ValidationVM::setLastValidationTime(QString value)
{
    if(_lastValidationTime != value){_lastValidationTime = value; emit lastValidationTimeChanged();}
}

void ValidationVM::validationSequenceLog_Slot(QString info)
{
    PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Validation sequence", info, tr(""));
}

void ValidationVM::moveTable_Slot(double dValue)
{
    MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_TABLE_ELEVATION_VALUE, dValue);
    QThread::msleep(60);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ELEVATION_COMMAND_GO, true);

}

void ValidationVM::moveTableHome_Slot()
{
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ELEVATION_COMMAND_HOME, true);
    QThread::msleep(60);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ELEVATION_COMMAND_HOME, true);
}

void ValidationVM::run_Qml_Slot()
{
    qDebug() << "[ValidationVM]" << "Run";
    m_nValidationStep = VALIDATION_SEQUENCE::INITIAL;
    Resume();
    // m_pParentObject->DoValidation();
    // m_bIsValidation = true;
}
