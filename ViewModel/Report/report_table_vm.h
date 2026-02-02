#ifndef REPORT_TABLE_VM_H
#define REPORT_TABLE_VM_H

#include <QObject>

struct InspectionInfoItem
{
    InspectionInfoItem(QString _moldNumber,
        double _height,
        double _weight,
        QList<double> _bodyR,
        double _tilt,
        double _lean,
        double _dimensionF,
        double _dimensionA,
        double _dimensionT,
        double _dimensionE,
        double _dimensionB,
        double _dimensionD,
        double _dimensionS,
        double _dimensionH)
        : moldNumber(_moldNumber)
        , height(_height)
        , weight(_weight)
        , bodyR(_bodyR)
        , tilt(_tilt)
        , lean(_lean)
        , dimensionF(_dimensionF)
        , dimensionA(_dimensionA)
        , dimensionT(_dimensionT)
        , dimensionE(_dimensionE)
        , dimensionB(_dimensionB)
        , dimensionD(_dimensionD)
        , dimensionS(_dimensionS)
        , dimensionH(_dimensionH)

    {
    }

    InspectionInfoItem()
    {
    }

    QString moldNumber;
    double height;
    double weight;
    QList<double> bodyR;
    double tilt;
    double lean;
    double dimensionF;
    double dimensionA;
    double dimensionT;
    double dimensionE;
    double dimensionB;
    double dimensionD;
    double dimensionS;
    double dimensionH;

};


class ReportTableVM : public QObject
{
    Q_OBJECT
public:
    explicit ReportTableVM(QObject *parent = nullptr);
    virtual ~ReportTableVM();

    // inline static ReportTableVM* GetInstance() {

    //     if (m_pInstance.isNull())
    //         m_pInstance.reset(new ReportTableVM());

    //     return m_pInstance.data();
    // }

    QVector<InspectionInfoItem> items() const;
    bool setItemAt(int index, const InspectionInfoItem& item);

    bool appendItem(InspectionInfoItem &item);
    bool insertItem(int index, InspectionInfoItem item);
    bool removeItems(int index);
    bool removeCompletedItems();

// private:
    // static QScopedPointer<ReportTableVM> m_pInstance;

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemInserted(int index);
    void postItemInserted();

    void preItemRemoved(int index);
    void postItemRemoved();

    // signal from ItemList to UI
    void dataContexDataChangedSignal(int index);
public slots:

protected:
    QVector<InspectionInfoItem> m_Items;



};

#endif // REPORT_TABLE_VM_H
