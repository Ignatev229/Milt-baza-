#include "debug_log_model.h"

DebugLogModel::DebugLogModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{

}

DebugLogModel::~DebugLogModel()
{

}

void DebugLogModel::ChangeLanguage()
{
    // if (mList == nullptr) return;

    // int s = mList->items().size();
    // for (int i = 0; i < s; i++)
    // {
    //     QString t = QString("%1").arg(QCoreApplication::translate(mList->items()[i].className.toStdString().c_str(), mList->items()[i].originalInfo.toStdString().c_str()));
    //     DebugLogItem current = mList->items().at(i);
    //     mList->setItemAt(i, DebugLogItem(current.className, current.originalInfo, current.time, current.time + t));

    //     emit dataChanged(index(i), index(i), { InfoRole });

    // }
}

int DebugLogModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all  // Для моделей списков только корневой узел (недопустимый родительский узел) должен возвращать размер списка. Для всех
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model. // при других (допустимых) родительских параметрах функция rowCount() должна возвращать 0, чтобы она не превратилась в древовидную модель.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant DebugLogModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const DebugLogItem item = mList->items().at(index.row());
    switch (role) {
        case InfoRole:
            return QVariant(item.info);
        default:
            break;
    }

    return QVariant();
}

bool DebugLogModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    DebugLogItem item = mList->items().at(index.row());
    switch (role) {
        case InfoRole:
            item.info = value.toString();
            break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

void DebugLogModel::setDataImp(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return;

    DebugLogItem item = mList->items().at(index.row());
    switch (role) {
        case InfoRole:
            item.info = value.toString();
            break;
        default:
            break;
    }
    emit dataChanged(index, index, QVector<int>() << role);
    return;
}

Qt::ItemFlags DebugLogModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me! // FIXME:  Реализуйте меня!
}

QHash<int, QByteArray> DebugLogModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[InfoRole] = "info";
    return names;

}

DebugLogVM *DebugLogModel::list() const
{
    return mList;
}

void DebugLogModel::setList(DebugLogVM *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &DebugLogVM::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &DebugLogVM::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &DebugLogVM::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &DebugLogVM::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(mList, &DebugLogVM::preItemInserted, this, [=](int index) {
//            const int index = 0;
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &DebugLogVM::postItemInserted, this, [=]() {
            endInsertRows();
        });

        connect(mList, &DebugLogVM::changeLanguageSignal, this, [&]() {
            ChangeLanguage();
        });
    }

    endResetModel();
}


