#include "list_string_model.h"

ListStringModel::ListStringModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{}


ListStringModel::~ListStringModel()
{

}

int ListStringModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all // Для моделей списков только корневой узел (недопустимый родительский узел) должен возвращать размер списка. Для всех
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model. // при других (допустимых) родительских параметрах функция rowCount() должна возвращать 0, чтобы она не превратилась в древовидную модель.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant ListStringModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const ListStringItem item = mList->items().at(index.row());
    switch (role) {
    case ValueRole:
        return QVariant(item.value);
    default:
        break;
    }

    return QVariant();
}

bool ListStringModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    ListStringItem item = mList->items().at(index.row());
    switch (role) {
    case ValueRole:
        item.value = value.toString();
        break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

void ListStringModel::setDataImp(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return;

    ListStringItem item = mList->items().at(index.row());
    switch (role) {
    case ValueRole:
        item.value = value.toString();
        break;
    default:
        break;
    }
    emit dataChanged(index, index, QVector<int>() << role);
    return;
}

Qt::ItemFlags ListStringModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me! // FIXME:  Реализуйте меня!
}

QHash<int, QByteArray> ListStringModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[ValueRole] = "value";
    return names;

}

ListStringVM *ListStringModel::list() const
{
    return mList;
}

void ListStringModel::setList(ListStringVM *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &ListStringVM::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &ListStringVM::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &ListStringVM::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &ListStringVM::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(mList, &ListStringVM::preItemInserted, this, [=](int index) {
            //            const int index = 0;
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &ListStringVM::postItemInserted, this, [=]() {
            endInsertRows();
        });
    }

    endResetModel();
}
