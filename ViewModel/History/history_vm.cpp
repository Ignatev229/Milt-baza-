#include "history_vm.h"
#include "../master_app.h"
#include "../../Script/Sql/sql_management.h"

QScopedPointer<HistoryVM> HistoryVM::m_pInstance;

HistoryVM::HistoryVM(QObject *parent)
    : QObject{parent}
{}

void HistoryVM::Init(QObject *parent)
{
    m_pParentObject = reinterpret_cast<MasterApp*>(parent);

}

void HistoryVM::dateChanged_Qml_Slot(QString startDate, QString endDate)
{
    startDate += " 00:00:00";
    endDate += " 23:59:59";
    QDateTime startD = QDateTime::fromString(startDate, Qt::ISODate);
    QDateTime endD = QDateTime::fromString(endDate, Qt::ISODate);
    qDebug() << "[HistoryVM]" << "Date selected: " << startDate << endDate << startD << endD;

    QList<InspectionInfoItem> value = SQLManagement::GetInstance()->LoadInspectionData(startD, endD);
    emit clearInspectionData_Signal();
    for (int i = 0; i < value.count(); ++i) {
        emit addInspectionData_Signal(value[i]);
    }
}
