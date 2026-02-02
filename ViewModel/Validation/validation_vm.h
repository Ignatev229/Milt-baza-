#ifndef VALIDATIONVM_H
#define VALIDATIONVM_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "../../Script/Define/struct_def.h"

class MasterApp;
class ValidationVM : public QThread
{
    Q_OBJECT
    Q_PROPERTY(QString lastValidationTime READ lastValidationTime WRITE setLastValidationTime NOTIFY lastValidationTimeChanged FINAL)


public:
    explicit ValidationVM(QObject *parent = nullptr);
    ~ValidationVM();

    inline static ValidationVM* GetInstance() {

        if (m_pInstance.isNull())
            m_pInstance.reset(new ValidationVM());

        return m_pInstance.data();
    }

    void run();
    void Resume();
    void Pause();

    void Init(QObject *parent = nullptr);
    void LoadOldData();

    // property //  Собственность
    QString lastValidationTime();
    // end // конец

    void AddInspectionData(InspectionInfoItem data);
    void ClearInspectionData();

    // bool m_bIsValidation;



    QHash<INSPECT_SEQUENCE_CAMERA_POSITION, QImage> m_hashSequencePosImages;

private:
    // property //  Собственность
    QString _lastValidationTime;
    // end // конец
    MasterApp* m_pParentObject;
    static QScopedPointer<ValidationVM> m_pInstance;

    QMutex sync;
    QWaitCondition pauseCond;
    bool pause;
    bool isRun;

    VALIDATION_SEQUENCE m_nValidationStep;

signals:
    // property //  Собственность
    void lastValidationTimeChanged();

    //end // конец

    void validationSequenceLog_Signal(QString);
    void moveTable_Signal(double);
    void moveTableHome_Signal();

    // to qml

    void addInspectionData_Signal(InspectionInfoItem);


    void clearInspectionData_Signal();
    void updateVisionParamNumber_Signal(int bodyRNumber);


public slots:
    // property //  Собственность
    void setLastValidationTime(QString value);

    //end // конец

    void validationSequenceLog_Slot(QString);
    void moveTable_Slot(double);
    void moveTableHome_Slot();

    // qml slot // qml слот
    void run_Qml_Slot();
};

#endif // VALIDATIONVM_H
