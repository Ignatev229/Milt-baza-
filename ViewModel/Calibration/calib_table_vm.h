#ifndef CALIB_TABLE_VM_H
#define CALIB_TABLE_VM_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "../../Script/Define/struct_def.h"
#include "../../Script/Modbus/MBcommunication.h"
#include "../../Script/Modbus/MBdefine.h"
#include "../../Script/Modbus/MBDLL.h"
#include "../../Script/Config/config_application.h"

class MasterApp;
class CalibTableVM : public QThread
{
    Q_OBJECT
    Q_PROPERTY(double tableElevationValue READ tableElevationValue WRITE setTableElevationValue NOTIFY tableElevationValueChanged FINAL)
    Q_PROPERTY(double tableAngleValue READ tableAngleValue WRITE setTableAngleValue NOTIFY tableAngleValueChanged FINAL)



public:
    explicit CalibTableVM(QObject *parent = nullptr);
    ~CalibTableVM();

    inline static CalibTableVM* GetInstance() {

        if (m_pInstance.isNull())
            m_pInstance.reset(new CalibTableVM());

        return m_pInstance.data();
    }

    // property //  Собственность
    double tableElevationValue();
    double tableAngleValue();

    // end // конец

    void run();
    void Resume();
    void Pause();

    void Init(QObject *parent = nullptr);

    QHash<INSPECT_SEQUENCE_CAMERA_POSITION, QImage> m_hashSequencePosImages;

private:
    // property //  Собственность
    double _tableElevationValue;
    double _tableAngleValue;

    // end // конец

    MasterApp* m_pParentObject;
    static QScopedPointer<CalibTableVM> m_pInstance;

    QMutex sync;
    QWaitCondition pauseCond;
    bool pause;
    bool isRun;

    VALIDATION_SEQUENCE m_nCalibrationStep; // calibration step and validation step are same

signals:
    // property //  Собственность
    void tableElevationValueChanged();
    void tableAngleValueChanged();
    // end // конец

    void validationSequenceLog_Signal(QString);
    void moveTable_Signal(double);
    void moveTableHome_Signal();

    void updateCalibCameraPos_Signal(double toolHeight, double toolWidth,
                                     double bottomPos1, double bottomPos2, double topPos);
    void isShowWaitingCalib(bool isShow);
    void openConfirmSaveDialog();
    //

public slots:
    // property //  Собственность
    void setTableElevationValue(double);
    void setTableAngleValue(double);
    // end // конец

    void validationSequenceLog_Slot(QString);
    void moveTable_Slot(double);
    void moveTableHome_Slot();

    // qml slot // qml слот
    void cameraCalibIndexChanged_Qml_Slot(int);
    void combineImage_Qml_Slot();
    void saveCameraCalib_Qml_Slot();
    void tableElevationUp_Qml_Slot(QString);
    void tableElevationDown_Qml_Slot(QString);
    void tableElevationHome_Qml_Slot(QString);
    void tableAngle_Qml_Slot(QString);
    void tableAngle45_Qml_Slot(QString);
    void tableAngleHome_Qml_Slot(QString);
    void calibCameraPos_Qml_Slot(bool isCalib, double toolHeight, double toolWidth,
                                 double bottomPos1, double bottomPos2, double topPos);
    void confirmSaveCalib_Qml_Slot(bool);



};

#endif // CALIB_TABLE_VM_H
