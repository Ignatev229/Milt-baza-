#ifndef CORRECTION_VM_H
#define CORRECTION_VM_H

#include <QObject>

#include "../RecipeManagement/vision_parameters.h"


class MasterApp;
class CorrectionVM : public QObject
{
    Q_OBJECT
public:
    explicit CorrectionVM(QObject *parent = nullptr);
    ~CorrectionVM();

    inline static CorrectionVM* GetInstance() {

        if (m_pInstance.isNull())
            m_pInstance.reset(new CorrectionVM());

        return m_pInstance.data();
    }

    void Init(QObject *parent = nullptr);
    void UpdateCurrentRecipeToCorrection();

    BACKEND_RESULT currentDefectCorrection;
    QString currentDefectParameter;

private:
    MasterApp* m_pParentObject;
    static QScopedPointer<CorrectionVM> m_pInstance;

    // vision parameter
    NonRoundShapeInspect noneRoundShapeInspect;
    BodyRInspect bodyRInspect;
    GroupFinishDimensionInspect groupFinishDimensionInspect;

    bool isWaitTableMoveComplete;

    void UpdateCurrentDefectParameter(FinishDimensionInspect &vp);


signals:

    void sequenceLog_Signal(QString);
    void moveTable_Signal(double);
    void moveTableHome_Signal();

    // qml
    void updateDataUI(double min, double max, double goal, double distanceBottomRegion, double heightRegion);
    void closeWaitTableMoveComplete();
public slots:

    void sequenceLog_Slot(QString);
    void moveTable_Slot(double);
    void moveTableHome_Slot();

    // qml slot // qml слот
    void currentDefectChanged_Qml_Slot(int);
    void test_Qml_Slot(QList<int> defectIdx);
    void parameterChanged_Qml_Slot(double goal, double distanceBottomRegion, double heightRegion);
    void saveSetting_Qml_Slot(bool);
    void cancelWaitTableMoveComplete();

};

#endif // CORRECTION_VM_H
