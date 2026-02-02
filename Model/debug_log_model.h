#ifndef DEBUGLOGMODEL_H
#define DEBUGLOGMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "../ViewModel/Main/debug_log_vm.h"
#include "../Script/Config/config_application.h"

class DebugLogVM;

class DebugLogModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(DebugLogVM *list READ list WRITE setList NOTIFY listChanged)

public:
    explicit DebugLogModel(QObject *parent = nullptr);
    ~DebugLogModel();

    // Enum for custom roles in the list model // Перечисление для пользовательских ролей в модели списка
    enum{
        InfoRole = Qt::UserRole,
    };

    void ChangeLanguage();

    // Returns the number of rows in the model // Возвращает количество  рядов в модели
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

    // Getter for the DebugLogVM // Средство получения для DebugLogVM
    DebugLogVM *list() const;

    // Setter for the DebugLogVM // Установщик для DebugLogVM
    void setList(DebugLogVM *list);

private:
    // Pointer to the DebugLogVM // Указатель на DebugLogVM
    DebugLogVM *mList;

signals:
    // Signal emitted when the list changes // Сигнал, подаваемый при изменении списка
    void listChanged();

};

#endif // DEBUGLOGMODEL_H
