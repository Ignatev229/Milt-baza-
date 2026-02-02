#include "statistics_model.h"

StatisticsModel::StatisticsModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{

}
StatisticsModel::~StatisticsModel()
{

}

void StatisticsModel::ChangeLanguage()
{
    if (mList == nullptr) return;

    int s = mList->items().size();
    for (int i = 0; i < s; i++)
    {
        QString t = QString("%1").arg(QCoreApplication::translate("StatisticsVM", mList->items()[i].originalContent.toStdString().c_str()));
        StatisticsItem current = mList->items().at(i);


        mList->setItemAt(i, StatisticsItem(current.originalContent, t, current.value));

        emit dataChanged(index(i), index(i), { ContentRole });

    }
}

int StatisticsModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all // Для моделей списков только корневой узел (недопустимый родительский узел) должен возвращать размер списка. Для всех
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.// при других (допустимых) родительских параметрах функция rowCount() должна возвращать 0, чтобы она не превратилась в древовидную модель.
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant StatisticsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const StatisticsItem item = mList->items().at(index.row());
    switch (role) {
        case ContentRole:
            return QVariant(item.content);
        case ValueRole:
            return QVariant(item.value);
        default:
            break;
    }

    return QVariant();
}

bool StatisticsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    StatisticsItem item = mList->items().at(index.row());
    switch (role) {
        case ContentRole:
            item.content = value.toString();
            break;
        case ValueRole:
            item.value = value.toInt();
            break;
    }

    if (mList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

void StatisticsModel::setDataImp(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return;

    StatisticsItem item = mList->items().at(index.row());
    switch (role) {
        case ContentRole:
            item.content = value.toString();
            break;
        case ValueRole:
            item.value = value.toInt();
            break;
        default:
            break;
    }
    emit dataChanged(index, index, QVector<int>() << role);
    return;
}

Qt::ItemFlags StatisticsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!// FIXME:  Реализуйте меня!
}

QHash<int, QByteArray> StatisticsModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[ContentRole] = "content";
    names[ValueRole] = "value";
    return names;
}

StatisticsVM *StatisticsModel::list() const
{
    return mList;
}

void StatisticsModel::setList(StatisticsVM *list)
{
    beginResetModel();

    if (mList)
        mList->disconnect(this);

    mList = list;

    if (mList) {
        connect(mList, &StatisticsVM::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &StatisticsVM::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &StatisticsVM::preItemInserted, this, [=](int index) {
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &StatisticsVM::postItemInserted, this, [=]() {
            endInsertRows();
        });

        connect(mList, &StatisticsVM::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(mList, &StatisticsVM::postItemRemoved, this, [=]() {
            endRemoveRows();
        });

        connect(mList, &StatisticsVM::dataContexDataChangedSignal, this, [&](int i) {
            emit dataChanged(index(i), index(i));
        });

        connect(mList, &StatisticsVM::changeLanguageSignal, this, [&]() {
            ChangeLanguage();
        });
    }

    endResetModel();
}
