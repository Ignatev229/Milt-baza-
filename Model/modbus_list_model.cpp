#include "modbus_list_model.h"
#include "Script/Modbus/MBItem.h"
#include "qcoreapplication.h"

modbus_list_model::modbus_list_model(QObject *parent)
    : QAbstractListModel(parent)
    , m_pMBList(nullptr)
{
}

modbus_list_model::~modbus_list_model()
{
    
}

void modbus_list_model::ChangeLanguage()
{

    if (m_pMBList == nullptr) return;

    int s = m_pMBList->item().size();
    for (int i = 0; i < s; i++)
    {
        QString t = QString("%1").arg(QCoreApplication::translate("MBDiagnosticItems", m_pMBList->item()[i].m_originalDescription.toStdString().c_str()));

        MBItem current = m_pMBList->item().at(i);
        
        
        m_pMBList->setItemAt(i, MBItem(t, current.m_originalDescription, current.m_address, current.m_table, current.m_vectorBitPositonValue, current.m_result));


        emit dataChanged(index(i), index(i), { DescriptionRole });

    }

}

int modbus_list_model::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all // Для моделей списков только корневой узел (недопустимый родительский узел) должен возвращать размер списка. Для всех
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model. // при других (допустимых) родительских параметрах функция rowCount() должна возвращать 0, чтобы она не превратилась в древовидную модель.
    if (parent.isValid())
        return 0;

    if(m_pMBList == nullptr) return 0;

    return m_pMBList->item().size();
}

QVariant modbus_list_model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const auto item = m_pMBList->item().at(index.row());

    switch (role) {
    case DescriptionRole:
        return QVariant(item.m_description);
        break;
    case ValueRole:
        return QVariant(item.m_result);
        break;
    default:
        break;
    }
    return QVariant();
}

bool modbus_list_model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(m_pMBList == nullptr) return false;

    auto item = m_pMBList->item().at(index.row());

    switch (role) {
    case DescriptionRole:

        item.m_description = value.toString();
        break;
    case ValueRole:
        item.m_result = value.toUInt();
        break;
    default:
        break;
    }

    if(!m_pMBList->setItemAt(index.row(), item)) return false;

    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags modbus_list_model::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

QHash<int, QByteArray> modbus_list_model::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DescriptionRole] = "description";
    names[ValueRole] = "value";
    return names;
}

MBItemList *modbus_list_model::pMBList() const
{
    return m_pMBList;
}

void modbus_list_model::setPMBList(MBItemList *newPMBList)
{
    beginResetModel();

    if (m_pMBList == newPMBList)
        return;

    if(m_pMBList)
        m_pMBList->disconnect(this);

    m_pMBList = newPMBList;

    connect(m_pMBList, &MBItemList::dataContexDataChangedSignal, this, [&](int i) {
        emit dataChanged(index(i), index(i));
        });

    connect(m_pMBList, &MBItemList::changeLanguageSignal, this, [&]() {
        
        ChangeLanguage();

        });

    endResetModel();
}








