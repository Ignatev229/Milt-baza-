#include "debug_log_vm.h"
DebugLogVM * p_instance = 0;

DebugLogVM::DebugLogVM(QObject *parent)
    : QObject{parent}
{

}

DebugLogVM::~DebugLogVM()
{
    this->deleteLater();
}

DebugLogVM *DebugLogVM::instance()
{
    if(!p_instance) p_instance = new DebugLogVM();
    return p_instance;
}

QVector<DebugLogItem> DebugLogVM::items() const
{
    return mItems;
}

bool DebugLogVM::setItemAt(int index, const DebugLogItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    removeItems(index);
    insertItem(item, index);
    return true;
}

int DebugLogVM::getLength()
{
    return mItems.size();
}

void DebugLogVM::appendItem(DebugLogItem item)
{
    emit preItemAppended();
    mItems.append(item);
    emit postItemAppended();
    return;
}

void DebugLogVM::insertItem(DebugLogItem item, int index)
{
    emit preItemInserted(index);
    mItems.insert(index, item);
    emit postItemInserted();
    return;

}

void DebugLogVM::removeCompletedItems()
{
    while(mItems.size() > 0){
        for (int i = 0; i < mItems.size(); i++) {
            emit preItemRemoved(i);
            mItems.removeAt(i);
            emit postItemRemoved();
        }
    }
    return;
}

void DebugLogVM::WriteDebugLog(QString className, QString orgInfo, QString info)
{
    while(getLength() > ConfigApplication::instance()->m_nMaxDebugLogLineNumber)
        removeItems(0);
    DebugLogItem item;
    item.className = className;
    item.time = QDateTime::currentDateTime().toString("hh:mm:ss") + " :  ";
    item.originalInfo = orgInfo;
    if(info == "")
    {
        item.info = item.time + item.originalInfo;
    }
    else
    {
        item.info = item.time + info;
    }
    appendItem(item);
}

void DebugLogVM::removeItems(int index)
{
    if (index < 0 || index >= mItems.size())
        return;
    emit preItemRemoved(index);
    mItems.removeAt(index);
    emit postItemRemoved();
}
