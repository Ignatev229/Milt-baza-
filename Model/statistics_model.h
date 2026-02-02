#ifndef STATISTICSMODEL_H
#define STATISTICSMODEL_H

#include <QAbstractListModel>
#include "../ViewModel/Main/statistics_vm.h"

class StatisticsVM;


class StatisticsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(StatisticsVM* list READ list WRITE setList NOTIFY listChange)


public:
    explicit StatisticsModel(QObject *parent = nullptr);
    ~StatisticsModel();

    // Enum for custom roles in the list model
    enum{
        ContentRole = Qt::UserRole,
        ValueRole = Qt::UserRole + 1
    };

    void ChangeLanguage();

    // Basic functionality: returns the number of rows in the model // Основные функциональные: возвращает количество рядов в модели
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

    // Getter for the statistics view model // Средство получения для режима просмотра статистики
    StatisticsVM *list() const;

    // Setter for the statistics view model //  Установщик для модели просмотра статистики
    void setList(StatisticsVM *list);

private:
    StatisticsVM *mList;

signals:
    // Signal emitted when the list changes // Сигнал, подаваемый при изменении списка
    void listChange();

};

#endif // STATISTICSMODEL_H
