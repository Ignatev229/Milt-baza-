#include "table_vm.h"

TableVM::TableVM(QObject *parent)
    : QObject{parent}
{
    setTableElevationValue(0.1);
    setTableAngleValue(0.1);
    setLoadPosition(0.176);
    setUnloadPosition(0.257);
}

TableVM::~TableVM()
{

}

double TableVM::tableElevationValue()
{
    return _tableElevationValue;
}

double TableVM::tableAngleValue()
{
    return _tableAngleValue;
}

double TableVM::loadPosition()
{
    return _loadPosition;
}

double TableVM::unloadPosition()
{
    return _unloadPosition;
}

void TableVM::setTableElevationValue(double value)
{
    if(_tableElevationValue != value){_tableElevationValue = value; emit tableElevationValueChanged();}
}

void TableVM::setTableAngleValue(double value)
{
    if(_tableAngleValue != value){_tableAngleValue = value; emit tableAngleValueChanged();}
}

void TableVM::setLoadPosition(double value)
{
    if(_loadPosition != value){_loadPosition = value; emit loadPositionChanged();}
}

void TableVM::setUnloadPosition(double value)
{
    if(_unloadPosition != value){_unloadPosition = value; emit unloadPositionChanged();}
}

void TableVM::tableElevationGo_Qml_Slot(QString value)
{
    qDebug() << "[TableVM]" << "Table Elevation Go" << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);
    if(!ok)
        return;

    MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_TABLE_ELEVATION_VALUE, dvalue);
    QThread::msleep(20);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ELEVATION_COMMAND_GO, true);
}

void TableVM::tableElevationHome_Qml_Slot()
{
    qDebug() << "[TableVM]" << "Table Elevation Home";
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ELEVATION_COMMAND_HOME, true);

}

void TableVM::tableAngleRotateLeft_Qml_Slot(QString value)
{
    qDebug() << "[TableVM]" << "Table Angle Rotate Left" << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);
    if(!ok)
        return;

    MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_TABLE_ANGLE_VALUE, dvalue);
    QThread::msleep(20);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ANGLE_COMMAND_TURN_LEFT, true);

}

void TableVM::tableAngleRotateRight_Qml_Slot(QString value)
{
    qDebug() << "[TableVM]" << "Table Angle Rotate Right" << value;
    double dvalue;
    bool ok;
    dvalue = value.toDouble(&ok);
    if(!ok)
        return;

    MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_TABLE_ANGLE_VALUE, dvalue);
    QThread::msleep(20);
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_2, (int)REGISTER_2_PROFILE::TABLE_ANGLE_COMMAND_TURN_RIGHT, true);

}

void TableVM::tableAngleHome_Qml_Slot()
{
    qDebug() << "[TableVM]" << "Table Angle Home";
    MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_1, (int)REGISTER_1_PROFILE::TABLE_ANGLE_COMMAND_HOME, true);

}

void TableVM::testGotoLoad_Qml_Slot()
{
    qDebug() << "[TableVM]" << "Test go to load";
    //MBCommunication::GetInstance()->WriteData(MT_COIL, int(MB_COIL_ITEMS::GO_TO_LOAD), 1);
}

void TableVM::testGotoUnload_Qml_Slot()
{
    qDebug() << "[TableVM]" << "Test go to unload";
    //MBCommunication::GetInstance()->WriteData(MT_COIL, int(MB_COIL_ITEMS::GO_TO_UNLOAD), 1);
}

void TableVM::saveAsLoad_Qml_Slot()
{
    qDebug() << "[TableVM]" << "save as load";
    //MBCommunication::GetInstance()->WriteData(MT_COIL, int(MB_COIL_ITEMS::SAVE_AS_LOAD), 1);
}

void TableVM::saveAsUnload_Qml_Slot()
{
    qDebug() << "[TableVM]" << "save as unload";
    //MBCommunication::GetInstance()->WriteData(MT_COIL, int(MB_COIL_ITEMS::SAVE_AS_UNLOAD), 1);
}



