#include "feeder_and_pushers_vm.h"

FeederAndPushersVM::FeederAndPushersVM(QObject *parent)
    : QObject{parent}
{
    setScalePusherDistance(0.1);
    setTablePusherDistance(0.1);
    setPushupDistance(0.1);
    setTestBottleDiameter(0.1);
    setScaleValue(0.1);
    setMotorCameraValue(0.1);
    // emit conveyorStartStop_Qml_Signal(true); //  Эмитировать conveyorStartStop_Qml_Signal(значение true);
}

FeederAndPushersVM::~FeederAndPushersVM()
{

}

double FeederAndPushersVM::scalePusherDistance()
{
    return _scalePusherDistance;
}

double FeederAndPushersVM::tablePusherDistance()
{
    return _tablePusherDistance;
}

double FeederAndPushersVM::pushupDistance()
{
    return _pushupDistance;
}

double FeederAndPushersVM::testBottleDiameter()
{
    return _testBottleDiameter;
}

double FeederAndPushersVM::scaleValue()
{
    return _scaleValue;
}


double FeederAndPushersVM::motorCameraValue()
{
    return _motorCameraValue;
}

void FeederAndPushersVM::setScalePusherDistance(double value)
{
    if(_scalePusherDistance != value){_scalePusherDistance = value; emit scalePusherDistanceChanged();}
}

void FeederAndPushersVM::setTablePusherDistance(double value)
{
    if(_tablePusherDistance != value){_tablePusherDistance = value; emit tablePusherDistanceChanged();}
}

void FeederAndPushersVM::setPushupDistance(double value)
{
    if(_pushupDistance != value){_pushupDistance = value; emit pushupDistanceChanged();}
}

void FeederAndPushersVM::setTestBottleDiameter(double value)
{
    if(_testBottleDiameter != value){_testBottleDiameter = value; emit testBottleDiameterChanged();}
}

void FeederAndPushersVM::setScaleValue(double value)
{
    if(_scaleValue != value){_scaleValue = value; emit scaleValueChanged();}
}

void FeederAndPushersVM::setMotorCameraValue(double value)
{
    if(_motorCameraValue != value){_motorCameraValue = value; emit motorCameraValueChanged();}
}

void FeederAndPushersVM::conveyorStartStop_Qml_Slot(bool value)
{
    qDebug() << "[FeederAndPushersVM]" << "Conveyor Start Stop: " << value;

    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_1, value == true ? (int)REGISTER_1_PROFILE::CONVEYOR_COMMAND_RUN : (int)REGISTER_1_PROFILE::CONVEYOR_COMMAND_STOP, true);
}

void FeederAndPushersVM::infeedCylinder1OpenClose_Qml_Slot(bool value)
{
    qDebug() << "[FeederAndPushersVM]" << "Infeed Cylinder 1: " << value;

    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_1, value == true ? (int)REGISTER_1_PROFILE::INFEED_CYCLINDER_1_COMMAND_OPEN : (int)REGISTER_1_PROFILE::INFEED_CYCLINDER_1_COMMAND_CLOSE, true);
}

void FeederAndPushersVM::infeedCylinder2OpenClose_Qml_Slot(bool value)
{
    qDebug() << "[FeederAndPushersVM]" << "Infeed Cylinder 2: " << value;

    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_1, value == true ? (int)REGISTER_1_PROFILE::INFEED_CYCLINDER_2_COMMAND_OPEN : (int)REGISTER_1_PROFILE::INFEED_CYCLINDER_2_COMMAND_CLOSE, true);
}

void FeederAndPushersVM::outfeedCylinder2OpenClose_Qml_Slot(bool value)
{
    qDebug() << "[FeederAndPushersVM]" << "Outfeed Cylinder 2: " << value;


    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_1, value == true ? (int)REGISTER_1_PROFILE::OUTFEED_CYCLINDER_COMMAND_OPEN : (int)REGISTER_1_PROFILE::OUTFEED_CYCLINDER_COMMAND_CLOSE, true);
}

void FeederAndPushersVM::rotateCylinderOpenClose_Qml_Slot(bool value)
{
    qDebug() << "[FeederAndPushersVM]" << "Rotate Cylinder: " << value;

    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_1, value == true ? (int)REGISTER_1_PROFILE::ROTATE_CYCLINDER_COMMAND_OPEN : (int)REGISTER_1_PROFILE::ROTATE_CYCLINDER_COMMAND_CLOSE, true);
}

void FeederAndPushersVM::scalePusherInOut_Qml_Slot(bool isIn, QString value)
{
    qDebug() << "[FeederAndPushersVM]" << "Scale Pusher: " << isIn << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);
    if(!ok)
        return;

    MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_SCALE_PUSHER_VALUE, dvalue);
    
    QThread::msleep(20);

    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_1, isIn == true ? (int)REGISTER_1_PROFILE::SCALE_PUSHER_COMMAND_GO : (int)REGISTER_1_PROFILE::SCALE_PUSHER_COMMAND_HOME, true);
}

void FeederAndPushersVM::tablePusherInOut_Qml_Slot(bool isIn, QString value)
{
    qDebug() << "[FeederAndPushersVM]" << "Table Pusher: " << isIn << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);

    if(!ok)
        return;


    MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_TABLE_PUSHER_VALUE, dvalue);
    QThread::msleep(20);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_1, isIn == true ? (int)REGISTER_1_PROFILE::TABLE_PUSHER_COMMAND_GO : (int)REGISTER_1_PROFILE::TABLE_PUSHER_COMMAND_HOME, true);
}

void FeederAndPushersVM::resetPushupDistance_Qml_Slot()
{
    qDebug() << "[FeederAndPushersVM]" << "Reset Pushup";
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::PUSHUP_COMMAND_RESET, true);
}

void FeederAndPushersVM::resetScale_Qml_Slot()
{
    qDebug() << "[FeederAndPushersVM]" << "Reset Scale";
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::SCALE_COMMAND_RESET, true);
}

void FeederAndPushersVM::test_Qml_Slot(QString value)
{
    qDebug() << "[FeederAndPushersVM]" << "Test: " << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);

    if(!ok)
        return;
    int iValue = dvalue*1000;
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TEST_BOTTLE_DIAMETER_VALUE), iValue);
    //MBCommunication::GetInstance()->WriteData(MT_COIL, int(MB_COIL_ITEMS::TEST_BOTTLE_DIAMETER), 1);
}

void FeederAndPushersVM::motorCameraMove_Qml_Slot(bool isIn, QString value)
{
    qDebug() << "[FeederAndPushersVM]" << "Motor Move: " << isIn << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);

    if(!ok)
        return;
    MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_CAMERA_ADJUSTMENT_VALUE, dvalue);
    QThread::msleep(20);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, isIn == true ? (int)REGISTER_2_PROFILE::CAMERA_ADJUSTMENT_COMMAND_GO : (int)REGISTER_2_PROFILE::CAMERA_ADJUSTMENT_COMMAND_HOME, true);
}

void FeederAndPushersVM::airCompressorChanged_Qml_Slot(bool value)
{
    qDebug() << "[FeederAndPushersVM]" << "Air Compressor: " << value;
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, value == true ? (int)REGISTER_2_PROFILE::HIGH_PRESSURE_AIR_COMMAND_OPEN : (int)REGISTER_2_PROFILE::HIGH_PRESSURE_AIR_COMMAND_CLOSE, true);
}

void FeederAndPushersVM::vaccumEjectorChanged_Qml_Slot(bool value)
{
    qDebug() << "[FeederAndPushersVM]" << "Vaccum Ejector: " << value;
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_14, value == true ? (int)REGISTER_14_PROFILE::VACCUM_COMMAND_OPEN : (int)REGISTER_14_PROFILE::VACCUM_COMMAND_CLOSE, true);

}

void FeederAndPushersVM::pushHome_Qml_Slot(QString value)
{
    qDebug() << "[FeederAndPushersVM]" << "Push Home: " << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);
    if(!ok)
        return;
    int iValue = dvalue*1000;
    //MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, int(MB_HOLDING_REGISTER_ITEMS::TEST_BOTTLE_DIAMETER_VALUE), iValue);
    //MBCommunication::GetInstance()->WriteData(MT_COIL, int(MB_COIL_ITEMS::TEST_BOTTLE_DIAMETER), 0);
}

void FeederAndPushersVM::save_Qml_Slot(QString scalePusherDistance, QString tablePusherDistance, QString pusherDistance, QString testBottleDistance)
{
    // double value;
    // bool ok;
    // value = scalePusherDistance.toDouble(&ok);
    // if(ok)
    // {
    //     setScalePusherDistance(value);
    // }
    // value = tablePusherDistance.toDouble(&ok);
    // if(ok)
    // {
    //     setTablePusherDistance(value);
    // }
    // value = pusherDistance.toDouble(&ok);
    // if(ok)
    // {
    //     setPushupDistance(value);
    // }
    // value = testBottleDistance.toDouble(&ok);
    // if(ok)
    // {
    //     setTestBottleDiameter(value);
    // }
    // qDebug() << "[FeederAndPushersVM]" << "Save: " << scalePusherDistance << tablePusherDistance << pusherDistance << testBottleDistance;
}

void FeederAndPushersVM::autoManualModeChanged_Qml_Slot(bool value)
{
    // true: auto mode // true: автоматический режим
    // false: manual mode // false: ручной режим
    qDebug() << "[FeederAndPushersVM]" << "IsAuto mode change: " << value;
    DebugLogVM::instance()->WriteDebugLog("FeederAndPushersVM", value ? "Switch to Auto Mode" : "Switch to Manual Mode");
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_0, value == true ? (int)REGISTER_0_PROFILE::MACHINE_COMMAND_CHANGE_AUTO_MODE : (int)REGISTER_0_PROFILE::MACHINE_COMMAND_CHANGE_MANUAL_MODE, true);
}

void FeederAndPushersVM::machineHomePosition_Qml_Slot()
{
    qDebug() << "[FeederAndPushersVM]" << "Machine Home Position";
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_0, (int)REGISTER_0_PROFILE::MACHINE_COMMAND_CHANGE_TO_ORIGINAL_STATE, true);
}

void FeederAndPushersVM::stopAllCommand_Qml_Slot()
{
    qDebug() << "[FeederAndPushersVM]" << "Stop all command";
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::SCALE_PUSHER_COMMAND_STOP, true);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_PUSHER_COMMAND_STOP, true);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ANGLE_COMMAND_STOP, true);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ELEVATION_COMMAND_STOP, true);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::CAMERA_ADJUSTMENT_COMMAND_STOP, true);
}

void FeederAndPushersVM::resetDrives_Qml_Slot()
{
    qDebug() << "[FeederAndPushersVM]" << "Reset drivers";
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_0, (int)REGISTER_0_PROFILE::STEP_DRIVE_POWER_RESET, true);

}















