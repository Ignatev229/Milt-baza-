#include "list_string_vm.h"

ListStringVM::ListStringVM(QObject *parent)
    : QObject{parent}
{}

ListStringVM::~ListStringVM()
{
    this->deleteLater();
}


QVector<ListStringItem> ListStringVM::items() const
{
    return mItems;
}

bool ListStringVM::setItemAt(int index, const ListStringItem &item)
{
    if (index < 0 || index >= mItems.size())
        return false;

    removeItems(index);
    insertItem(item, index);
    return true;
}

int ListStringVM::getLength()
{
    return mItems.size();
}

int ListStringVM::getItemIndex(QString value)
{
    for (int i = 0; i < mItems.size(); i++) {
        if(value == mItems[i].value)
            return i;
    }
    return -1;
}

void ListStringVM::appendItem(ListStringItem item)
{
    emit preItemAppended();
    mItems.append(item);
    emit postItemAppended();
    return;
}

void ListStringVM::insertItem(ListStringItem item, int index)
{
    emit preItemInserted(index);
    mItems.insert(index, item);
    emit postItemInserted();
    return;

}

void ListStringVM::removeCompletedItems()
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

void ListStringVM::AppendValue(QString value)
{
    ListStringItem item;
    item.value = value;
    appendItem(item);
}

void ListStringVM::removeItems(int index)
{
    if (index < 0 || index >= mItems.size())
        return;
    emit preItemRemoved(index);
    mItems.removeAt(index);
    emit postItemRemoved();
}
