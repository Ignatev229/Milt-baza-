#ifndef DEBUGLOGVM_H
#define DEBUGLOGVM_H

#include <QObject>

#include "../../Script/Config/config_application.h"

struct DebugLogItem
{
    DebugLogItem(QString _className, QString _originalInfo, QString _time, QString _info)
        : className(_className)
        , originalInfo(_originalInfo)
        , time(_time)
        , info(_info)
    {
    }
    DebugLogItem()
    {
    }
    // to store the class which debug log // для сохранения класса, который ведет журнал отладки
    QString className;
    // to store the time // для сохранения времени
    QString time;
    // original content for know translate key // оригинальный контент для получения ключа перевод
    QString originalInfo;
    QString info;
};


class DebugLogVM : public QObject
{
    Q_OBJECT
public:
    explicit DebugLogVM(QObject *parent = nullptr);
    ~DebugLogVM();
    static DebugLogVM * instance();

    QVector<DebugLogItem> items() const;
    bool setItemAt(int index, const DebugLogItem &item);
    int getLength();

public:
    void appendItem(DebugLogItem item);
    void insertItem(DebugLogItem item, int index);
    void removeCompletedItems();
    void WriteDebugLog(QString className, QString orgInfo, QString info = "");


signals:
    void preItemAppended();
    void postItemAppended();

    void preItemInserted(int index);
    void postItemInserted();

    void preItemRemoved(int index);
    void postItemRemoved();

    void changeLanguageSignal();

public slots:


private:
    QVector<DebugLogItem> mItems;
    void removeItems(int index);



};

#endif // DEBUGLOGVM_H
