#ifndef MODBUS_LIST_MODEL_H
#define MODBUS_LIST_MODEL_H

#include <QAbstractListModel>
class MBItemList;


class modbus_list_model : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(MBItemList *pMBList READ pMBList WRITE setPMBList)
public:
    explicit modbus_list_model(QObject *parent = nullptr);
    virtual ~modbus_list_model();

    enum {
        ValueRole = Qt::UserRole + 1,
        DescriptionRole
    };

    void ChangeLanguage();

    // Basic functionality: returns the number of rows in the model // Основные функциональные: возвращает количество рядов в модели
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Returns data for a given index and role // Возвращает данные для заданного индекса и роли
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable: sets data for a given index and role // Редактируемый: задает данные для заданного индекса и роли
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    // Returns item flags for a given index // Возвращает флаги элементов для заданного индекса
    Qt::ItemFlags flags(const QModelIndex &index) const override;
public:
    // Returns a hash of role names used in the model // Возвращает хэш имен ролей, используемых в модели
    virtual QHash<int, QByteArray> roleNames() const override;

    // Getter for the Modbus item list // Средство получения для список элементов Modbus
    MBItemList *pMBList() const;

    // Setter for the Modbus item list // Установщик для список элементов Modbus
    void setPMBList(MBItemList *newPMBList);

signals:

private:
    MBItemList* m_pMBList;


};

#endif // MODBUS_LIST_MODEL_H
