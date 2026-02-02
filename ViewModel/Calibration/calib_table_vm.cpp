#include "calib_table_vm.h"
#include "../master_app.h"

QScopedPointer<CalibTableVM> CalibTableVM::m_pInstance;

CalibTableVM::CalibTableVM(QObject *parent)
    : QThread{parent}
{


}

CalibTableVM::~CalibTableVM()
{
    isRun = false;
    Resume();
    this->quit();
    this->wait();
}


void CalibTableVM::run()
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

        switch (m_nCalibrationStep) {
        case VALIDATION_SEQUENCE::INITIAL:
            emit validationSequenceLog_Signal("Initial Calibration");
            m_nCalibrationStep = VALIDATION_SEQUENCE::MOVE_BOTTOM1;
            break;
        case VALIDATION_SEQUENCE::MOVE_BOTTOM1:
            // send move to bottom pos
            // dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1);
            dValue = ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1];
            emit moveTable_Signal(dValue);
            emit validationSequenceLog_Signal(QString("Move Table to Bottom 1: %1").arg(dValue));
            m_nCalibrationStep = VALIDATION_SEQUENCE::MOVE_BOTTOM1_COMPLETE;
            break;
        case VALIDATION_SEQUENCE::MOVE_BOTTOM1_COMPLETE:
            // while until finish move
            // dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1);
            dValue = ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1];
            if(m_pParentObject->scopedTableVM.data()->tableElevationValue() == dValue)
            {
                emit validationSequenceLog_Signal("Move Table to Bottom 1 complete");
                emit validationSequenceLog_Signal("Call Bottom 1 Camera snap");

                // call snap
                m_pParentObject->scopedMainHomeVM.data()->Snap(
                    m_pParentObject->GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1));
                m_hashSequencePosImages[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1] =
                    m_pParentObject->hashTrackVM[m_pParentObject->GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1)]->GetDocImage(0).copy();
                m_nCalibrationStep = VALIDATION_SEQUENCE::MOVE_BOTTOM2;
            }
            break;

        case VALIDATION_SEQUENCE::MOVE_BOTTOM2:
            // send move to bottom pos
            // dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2);
            dValue = ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2];
            emit moveTable_Signal(dValue);
            emit validationSequenceLog_Signal(QString("Move Table to Bottom 2: %1").arg(dValue));
            m_nCalibrationStep = VALIDATION_SEQUENCE::MOVE_BOTTOM2_COMPLETE;
            break;
        case VALIDATION_SEQUENCE::MOVE_BOTTOM2_COMPLETE:
            // while until finish move
            // dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2);
            dValue = ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2];
            if(m_pParentObject->scopedTableVM.data()->tableElevationValue() == dValue)
            {
                emit validationSequenceLog_Signal("Move Table to Bottom 2 complete");
                emit validationSequenceLog_Signal("Call Bottom 2 Camera snap");

                // call snap
                m_pParentObject->scopedMainHomeVM.data()->Snap(
                    m_pParentObject->GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2));
                m_hashSequencePosImages[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2] =
                    m_pParentObject->hashTrackVM[m_pParentObject->GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2)]->GetDocImage(0).copy();
                m_nCalibrationStep = VALIDATION_SEQUENCE::MOVE_TOP;
            }
            break;

        case VALIDATION_SEQUENCE::MOVE_TOP:
            // send move to top pos
            // dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::TOP);
            dValue = ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::TOP];

            emit moveTable_Signal(dValue);
            emit validationSequenceLog_Signal(QString("Move Table to Top: %1").arg(dValue));
            m_nCalibrationStep = VALIDATION_SEQUENCE::MOVE_TOP_COMPLETE;
            break;
        case VALIDATION_SEQUENCE::MOVE_TOP_COMPLETE:

            // while until finish move
            // dValue = m_pParentObject->GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION::TOP);
            dValue = ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::TOP];
            if(m_pParentObject->scopedTableVM.data()->tableElevationValue() == dValue)
            {
                emit validationSequenceLog_Signal("Move Table to Top complete");
                emit validationSequenceLog_Signal("Call Top Camera snap");

                // call snap
                m_pParentObject->scopedMainHomeVM.data()->Snap(
                    m_pParentObject->GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION::TOP));

                m_hashSequencePosImages[INSPECT_SEQUENCE_CAMERA_POSITION::TOP] =
                    m_pParentObject->hashTrackVM[m_pParentObject->GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION::TOP)]->GetDocImage(0).copy();

                m_nCalibrationStep = VALIDATION_SEQUENCE::VALIDATION;
            }

            break;
        case VALIDATION_SEQUENCE::VALIDATION:

            emit validationSequenceLog_Signal("Call inspection");
            m_nCalibrationStep = VALIDATION_SEQUENCE::INITIAL;

            // call calibration inspection
            m_pParentObject->scopedMainHomeVM.data()->Inspect(BACKEND_FUNCTION::CALIBRATION_INSPECT);

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

void CalibTableVM::Resume()
{
    sync.lock();
    pause = false;
    sync.unlock();
    pauseCond.wakeAll();
}

void CalibTableVM::Pause()
{
    sync.lock();
    pause = true;
    sync.unlock();
}

double CalibTableVM::tableElevationValue()
{
    return _tableElevationValue;
}

double CalibTableVM::tableAngleValue()
{
    return _tableAngleValue;
}

void CalibTableVM::Init(QObject *parent)
{
    m_pParentObject = reinterpret_cast<MasterApp*>(parent);
    m_nCalibrationStep = VALIDATION_SEQUENCE::INITIAL;
    start();

    connect(this, SIGNAL(validationSequenceLog_Signal(QString)), this, SLOT(validationSequenceLog_Slot(QString)));
    connect(this, SIGNAL(moveTable_Signal(double)), this, SLOT(moveTable_Slot(double)));
    connect(this, SIGNAL(moveTableHome_Signal()), this, SLOT(moveTableHome_Slot()));

    emit updateCalibCameraPos_Signal(
        ConfigApplication::instance()->m_strCalibCameraPosData.toolHeight,
        ConfigApplication::instance()->m_strCalibCameraPosData.toolWidth,
        ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1],
        ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2],
        ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::TOP]);
}

void CalibTableVM::setTableElevationValue(double value)
{
    if(_tableElevationValue != value){_tableElevationValue = value; emit tableElevationValueChanged();}
}

void CalibTableVM::setTableAngleValue(double value)
{
    if(_tableAngleValue != value){_tableAngleValue = value; emit tableAngleValueChanged();}
}

void CalibTableVM::validationSequenceLog_Slot(QString info)
{
    PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Validation sequence", info, tr(""));
}

void CalibTableVM::moveTable_Slot(double dValue)
{
    MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_TABLE_ELEVATION_VALUE, dValue);
    QThread::msleep(60);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ELEVATION_COMMAND_GO, true);
}

void CalibTableVM::moveTableHome_Slot()
{
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ELEVATION_COMMAND_HOME, true);
    QThread::msleep(60);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ELEVATION_COMMAND_HOME, true);
}

void CalibTableVM::cameraCalibIndexChanged_Qml_Slot(int value)
{
    qDebug() << "[CalibTableVM]" << "Camera calib index: " << value;
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::CALIB_TABLE_STATUS), value + 1);
}

void CalibTableVM::combineImage_Qml_Slot()
{
    qDebug() << "[CalibTableVM]" << "Combine image";
}

void CalibTableVM::saveCameraCalib_Qml_Slot()
{
    qDebug() << "[CalibTableVM]" << "Save camera calib";
    //MBCommunication::GetInstance()->WriteData(MT_COIL, int(MB_COIL_ITEMS::SAVE_TABLE_ELEVATION_ANGLE), 1);
}

void CalibTableVM::tableElevationUp_Qml_Slot(QString value)
{
    qDebug() << "[CalibTableVM]" << "Table elevation up: " << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);
    if(!ok)
        return;
    int iValue = dvalue*1000;
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TABLE_ELEVATION_VALUE), iValue);
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TABLE_ELEVATION_ACTION), 2);
}

void CalibTableVM::tableElevationDown_Qml_Slot(QString value)
{
    qDebug() << "[CalibTableVM]" << "Table elevation down: " << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);
    if(!ok)
        return;
    int iValue = dvalue*1000;
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TABLE_ELEVATION_VALUE), iValue);
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TABLE_ELEVATION_ACTION), 3);
}

void CalibTableVM::tableElevationHome_Qml_Slot(QString value)
{
    qDebug() << "[CalibTableVM]" << "Table elevation home: " << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);
    if(!ok)
        return;
    int iValue = dvalue*1000;
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TABLE_ELEVATION_VALUE), iValue);
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TABLE_ELEVATION_ACTION), 4);
}

void CalibTableVM::tableAngle_Qml_Slot(QString value)
{
    qDebug() << "[CalibTableVM]" << "Table angle: " << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);
    if(!ok)
        return;
    int iValue = dvalue;
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TABLE_ANGLE_VALUE), iValue);
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TABLE_ANGLE_ACTION), 2);

}

void CalibTableVM::tableAngle45_Qml_Slot(QString value)
{
    qDebug() << "[CalibTableVM]" << "Table angle 45: " << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);
    if(!ok)
        return;
    int iValue = dvalue;
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TABLE_ANGLE_VALUE), iValue);
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TABLE_ANGLE_ACTION), 3);
}

void CalibTableVM::tableAngleHome_Qml_Slot(QString value)
{
    qDebug() << "[CalibTableVM]" << "Table home: " << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);
    if(!ok)
        return;
    int iValue = dvalue;
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TABLE_ANGLE_VALUE), iValue);
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TABLE_ANGLE_ACTION), 4);
}

void CalibTableVM::calibCameraPos_Qml_Slot(bool isCalib, double toolHeight, double toolWidth,
                                           double bottomPos1, double bottomPos2, double topPos)
{
    qDebug() << "[CalibTableVM]" << "Calib camera position: " << isCalib << bottomPos1 << bottomPos2 << topPos;
    if(isCalib)
    {
        ConfigApplication::instance()->m_strCalibCameraPosData.toolHeight = toolHeight;
        ConfigApplication::instance()->m_strCalibCameraPosData.toolWidth = toolWidth;
        ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1] = bottomPos1;
        ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2] = bottomPos2;
        ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::TOP] = topPos;

        // process sequence for snap image at bottom1, bottom2 and top position
        // call backend to calculate parameter
        // update to CalibCameraPosition.json file
        // update to CalculateLiftingMechanismPos()
        // update camera resolution and write config.json and resolution to UI
        // trigger backend load recipe

        m_nCalibrationStep = VALIDATION_SEQUENCE::INITIAL;
        Resume();

    }

}

void CalibTableVM::confirmSaveCalib_Qml_Slot(bool isSave)
{
    if(isSave)
    {
        // update to CalibCameraPosition.json file
        // update camera resolution and write config.json
        ConfigApplication::instance()->m_strCalibCameraPosData.saveToFile(ConfigApplication::instance()->m_strCalibCameraPosFile);
        ConfigApplication::instance()->WriteAppSetting();
    }
    else
    {
        // update to CalibCameraPosition.json file
        // update camera resolution and write config.json
        ConfigApplication::instance()->m_strCalibCameraPosData.loadFromFile(ConfigApplication::instance()->m_strCalibCameraPosFile);
        ConfigApplication::instance()->ReadAppSetting();
    }

    // send backend load recipe
    m_pParentObject->scopedInspectionCore.data()->RecipeChanged();
    EditRecipeVM::GetInstance()->CalculateLiftingMechanismPos();
    // update resolutio to UI
    m_pParentObject->scopedMainHomeVM.data()->UpdateResolutionToUI();
}


















