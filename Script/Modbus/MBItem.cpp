#include "MBItem.h"
#include "MBdefine.h"
#include "MBcommunication.h"

MBItemList::MBItemList(QObject *parent)
    : QObject{parent}
{
}

MBItemList::~MBItemList()
{
}

QVector<MBItem> MBItemList::item() const
{
    return m_Items;
}

bool MBItemList::setItemAt(int index, const MBItem &item)
{
    if(index < 0 || index >= m_Items.size()) return false;

    const MBItem& oldItem = m_Items.at(index);

    if(item.m_result == oldItem.m_result && item.m_description == oldItem.m_description) return false;

    m_Items[index] = item;

    return true;

}

void MBItemList::StartToChangeLanguage()
{
    emit changeLanguageSignal();
}


