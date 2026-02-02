#ifndef LISTSTRINGMODEL_H
#define LISTSTRINGMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "../ViewModel/list_string_vm.h"

class ListStringVM;

class ListStringModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ListStringVM *list READ list WRITE setList NOTIFY listChanged)
public:
    explicit ListStringModel(QObject *parent = nullptr);
    ~ListStringModel();

    enum{
        ValueRole = Qt::UserRole,
    };

    // Returns the number of rows in the model // Возвращает количество рядов в модели
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Returns data for a given index and role // Возвращает данные для заданного индекса и роли
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable: sets data for a given index and role // Редактируемый: задает данные для заданного индекса и роли
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    // Helper function to set data for a given index and role // Вспомогательная функция для установки данных для заданного индекса и роли
    void setDataImp(const QModelIndex &index, const QVariant &value,
                    int role = Qt::EditRole);

    // Returns item flags for a given index // Возвращает флаги элементов для заданного индекса
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Returns a hash of role names used in the model // Возвращает хэш имен ролей, используемых в модели
    virtual QHash<int, QByteArray> roleNames() const override;

    // Getter for the ListStringVM // Средство получения для ListStringVM
    ListStringVM *list() const;

    // Setter for the ListStringVM // Установщик для ListStringVM
    void setList(ListStringVM *list);

private:
    // Pointer to the ListStringVM // Указатель для ListStringVM
    ListStringVM *mList;

signals:
    // Signal emitted when the list changes // Сигнал, подаваемый при изменении списка
    void listChanged();
};

#endif // LISTSTRINGMODEL_H
