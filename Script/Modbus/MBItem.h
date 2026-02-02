#ifndef MBITEM_H
#define MBITEM_H
#include <QString>
#include <QObject>

struct MBItem
{
    MBItem(QString des,
        QString originalDes,
        int add,
        int table,
        const QVector<int>& bitPositions = QVector<int>(),
        quint16 initResult = 0)
        : m_description(des)
        , m_address(add)
        , m_table(table)
        , m_vectorBitPositonValue(bitPositions)
        , m_result(initResult)
        , m_originalDescription(originalDes)
    {
    }

    MBItem()
    {
    }
    // original description for know translate key // оригинальное описание для получения ключа перевод
    QString m_originalDescription;
    // name to display // имя для отображения
    QString m_description;
    // address in order to send to modbus // адрес для отправки в  Модбус
    int m_address;
    // table type // тип таблицы
    int m_table;

    // optional //  Опционально
    QVector<int> m_vectorBitPositonValue;

    // result // результат
    quint16 m_result;
};

class MBItemList : public QObject{
    Q_OBJECT
public:
    explicit MBItemList(QObject *parent = nullptr);
    virtual ~MBItemList();

    QVector<MBItem> item() const;
    bool setItemAt(int index, const MBItem& item);


    // public data to UI //  Публичные данные для пользовательского интерфейса

signals:
    // signal from ItemList to UI // сигнал из списка элементов в пользовательский интерфейс
    void dataContexDataChangedSignal(int index);
    void changeLanguageSignal();
public slots:
    void StartToChangeLanguage();
protected:
    QVector<MBItem> m_Items;

};


#endif // MBITEM_H
