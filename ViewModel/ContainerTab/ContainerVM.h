#ifndef CONTAINERVM_H
#define CONTAINERVM_H

#include <QObject>


struct containerItem {
    int index;
    QString item;
    float height;
    float weight;
    float eMin;
    float eMax;
    float tMin;
    float tMax;

    containerItem(int _index, QString _item, float _height, float _weight, float _eMin,
        float _eMax, float _tMin, float _tMax)
        : index(_index)
        , item(_item)
        , height(_height)
        , weight(_weight)
        , eMin(_eMin)
        , eMax(_eMax)
        , tMin(_tMin)
        , tMax(_tMax)
    {
    }
};

class ContainerVM : public QObject
{
    Q_OBJECT
public:
    explicit ContainerVM(QObject *parent = nullptr);
    QVector<containerItem> m_vectorListContainerData;
    void PopulateData();
public slots:
    void loadCompleted();
    void saveDataContainer();

signals:
    void addData(int index, QString item, QString height, QString weight, QString eMin, QString eMax, QString tMin, QString tMax);
};

#endif // CONTAINERVM_H
