#ifndef STATISTICVM_H
#define STATISTICVM_H

#include <QObject>
#include "../../Script/Config/config_application.h"

#define DEFECT_START_INDEX 3 // total, fail

struct StatisticsItem
{
    StatisticsItem(QString _originalContent, QString _content, int _value)
        : originalContent(_originalContent)
        , content(_content)
        , value(_value)
    {
    }
    StatisticsItem()
    {

    }

    // original content for know translate key // оригинальный контент для получения ключа перевод
    QString originalContent;
    // name to content //  Название к  содержанию
    QString content;
    int value;
};


class StatisticsVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double yieldPass READ yieldPass WRITE setYeilPass NOTIFY yieldPassChanged FINAL)

public:
    explicit StatisticsVM(QObject *parent = nullptr);


    QVector<StatisticsItem> items() const;


    void InitStatisticsTable();
    void ResetStatisticsTable();
    void UpdateStatisticsTable(BACKEND_RESULT defectCode);

    bool setItemAt(int index, const StatisticsItem &item);
    int getLength();

    //
    double yieldPass();



public:
    void appendItem(StatisticsItem &item);
    void insertItem(int index, StatisticsItem item);
    void removeItems(int index);
    void removeCompletedItems();

    //
    double _yieldPass;

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemInserted(int index);
    void postItemInserted();

    void preItemRemoved(int index);
    void postItemRemoved();

    void dataContexDataChangedSignal(int index);

    void changeLanguageSignal();

    //
    void yieldPassChanged();

public slots:
    void resetStatistics_Qml_Slot();

    //
    void setYeilPass(double value);

private:
    QVector<StatisticsItem> mItems;

    QString ConvertDefectCodeToStringTranslate(BACKEND_RESULT);


};

#endif // STATISTICVM_H
