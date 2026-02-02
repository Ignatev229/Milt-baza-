#ifndef LISTSTRINGVM_H
#define LISTSTRINGVM_H

#include <QObject>

struct ListStringItem
{
    QString value;
};

class ListStringVM : public QObject
{
    Q_OBJECT
public:
    explicit ListStringVM(QObject *parent = nullptr);
    ~ListStringVM();

    QVector<ListStringItem> items() const;
    bool setItemAt(int index, const ListStringItem &item);
    int getLength();
    int getItemIndex(QString value);
public:
    void appendItem(ListStringItem item);
    void insertItem(ListStringItem item, int index);
    void removeCompletedItems();
    void AppendValue(QString value);



signals:
    void preItemAppended();
    void postItemAppended();

    void preItemInserted(int index);
    void postItemInserted();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:


private:
    QVector<ListStringItem> mItems;
    void removeItems(int index);
};

#endif // LISTSTRINGVM_H
