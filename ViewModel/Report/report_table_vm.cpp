#include "report_table_vm.h"

// QScopedPointer<ReportTableVM> ReportTableVM::m_pInstance;

ReportTableVM::ReportTableVM(QObject *parent)
    : QObject{parent}
{}

ReportTableVM::~ReportTableVM()
{

}

QVector<InspectionInfoItem> ReportTableVM::items() const
{
    return m_Items;
}
bool ReportTableVM::setItemAt(int index, const InspectionInfoItem &item)
{
    if(index < 0 || index >= m_Items.size()) return false;

    m_Items[index] = item;

    emit dataContexDataChangedSignal(index);
    return true;
}

bool ReportTableVM::appendItem(InspectionInfoItem &item)
{
    emit preItemAppended();
    m_Items.append(item);
    emit postItemAppended();
    return true;
}

bool ReportTableVM::insertItem(int index, InspectionInfoItem item)
{
    emit preItemInserted(index);
    m_Items.insert(index, item);
    emit postItemInserted();
    return true;
}

bool ReportTableVM::removeItems(int index)
{
    if (index < 0 || index >= m_Items.size())
        return false;
    emit preItemRemoved(index);
    m_Items.removeAt(index);
    emit postItemRemoved();
    return true;
}

bool ReportTableVM::removeCompletedItems()
{
    while(m_Items.size() > 0){
        for (int i = 0; i < m_Items.size(); i++) {
            emit preItemRemoved(i);
            m_Items.removeAt(i);
            emit postItemRemoved();
        }
    }
    return true;
}

