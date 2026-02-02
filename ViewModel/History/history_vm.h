#ifndef HISTORY_VM_H
#define HISTORY_VM_H

#include <QObject>
#include "Script/Define/struct_def.h"

class MasterApp;

class HistoryVM : public QObject
{
    Q_OBJECT
public:
    explicit HistoryVM(QObject *parent = nullptr);

    inline static HistoryVM* GetInstance() {

        if (m_pInstance.isNull())
            m_pInstance.reset(new HistoryVM());

        return m_pInstance.data();
    }

    void Init(QObject *parent = nullptr);

private:
    MasterApp* m_pParentObject;
    static QScopedPointer<HistoryVM> m_pInstance;

signals:

    // to qml
    void addInspectionData_Signal(InspectionInfoItem);
    void clearInspectionData_Signal();
    void updateVisionParamNumber_Signal(int bodyRNumber, int nonRoundShapeNumber, int nonRoundShape);

public slots:
    // qml slots // qml cлоты
    void dateChanged_Qml_Slot(QString startDate, QString endDate);

signals:
};

#endif // HISTORY_VM_H
