#ifndef FEEDERANDPUSHERSVM_H
#define FEEDERANDPUSHERSVM_H

#include <QObject>
#include <QDebug>
#include "../../Script/Modbus/MBcommunication.h"
#include "../../Script/Modbus/MBdefine.h"
#include "../../Script/Modbus/MBDLL.h"
#include "../Main/debug_log_vm.h"

class FeederAndPushersVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double scalePusherDistance READ scalePusherDistance WRITE setScalePusherDistance NOTIFY scalePusherDistanceChanged FINAL)
    Q_PROPERTY(double tablePusherDistance READ tablePusherDistance WRITE setTablePusherDistance NOTIFY tablePusherDistanceChanged FINAL)
    Q_PROPERTY(double pushupDistance READ pushupDistance WRITE setPushupDistance NOTIFY pushupDistanceChanged FINAL)
    Q_PROPERTY(double testBottleDiameter READ testBottleDiameter WRITE setTestBottleDiameter NOTIFY testBottleDiameterChanged FINAL)
    Q_PROPERTY(double scaleValue READ scaleValue WRITE setScaleValue NOTIFY scaleValueChanged FINAL)
    Q_PROPERTY(double motorCameraValue READ motorCameraValue WRITE setMotorCameraValue NOTIFY motorCameraValueChanged FINAL)

public:
    explicit FeederAndPushersVM(QObject *parent = nullptr);
    ~FeederAndPushersVM();

    // property //  Собственность
    double scalePusherDistance();
    double tablePusherDistance();
    double pushupDistance();
    double testBottleDiameter();
    double scaleValue();
    double motorCameraValue();
    // end // конец

private:

    // property //  Собственность
    double _scalePusherDistance;
    double _tablePusherDistance;
    double _pushupDistance;
    double _testBottleDiameter;
    double _scaleValue;
    double _motorCameraValue;
    // end // конец


signals:
    // property //  Собственность
    void scalePusherDistanceChanged();
    void tablePusherDistanceChanged();
    void pushupDistanceChanged();
    void testBottleDiameterChanged();
    void scaleValueChanged();
    void motorCameraValueChanged();
    // end // конец

    // qml
    void conveyorStartStop_Qml_Signal(bool);

public slots:
    // property //  Собственность
    void setScalePusherDistance(double);
    void setTablePusherDistance(double);
    void setPushupDistance(double);
    void setTestBottleDiameter(double);
    void setScaleValue(double);
    void setMotorCameraValue(double);
    // end // конец


    // qml slot // qml слот
    void conveyorStartStop_Qml_Slot(bool);
    void infeedCylinder1OpenClose_Qml_Slot(bool);
    void infeedCylinder2OpenClose_Qml_Slot(bool);
    void outfeedCylinder2OpenClose_Qml_Slot(bool);
    void rotateCylinderOpenClose_Qml_Slot(bool);
    void scalePusherInOut_Qml_Slot(bool, QString);
    void tablePusherInOut_Qml_Slot(bool, QString);
    void resetPushupDistance_Qml_Slot();
    void resetScale_Qml_Slot();
    void test_Qml_Slot(QString);
    void motorCameraMove_Qml_Slot(bool, QString);
    void airCompressorChanged_Qml_Slot(bool);
    void vaccumEjectorChanged_Qml_Slot(bool);


    void pushHome_Qml_Slot(QString);
    void save_Qml_Slot(QString, QString, QString, QString);
    void autoManualModeChanged_Qml_Slot(bool value);
    void machineHomePosition_Qml_Slot();
    void stopAllCommand_Qml_Slot();
    void resetDrives_Qml_Slot();



};

#endif // FEEDERANDPUSHERSVM_H
