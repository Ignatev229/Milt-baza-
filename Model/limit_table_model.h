#ifndef LIMIT_TABLE_MODEL_H
#define LIMIT_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QObject>


 struct limitTableData {
    QString name;
    double differenceWarning;
    double differenceAlarm;
    double minimumWarning;
    double minimumAlarm;
    double maximumWarning;
    double maximumAlarm;

    const int totalItem = 7;

    limitTableData() {}
    limitTableData& operator=(const limitTableData& other)
    {
        name = other.name;
        differenceWarning = other.differenceWarning;
        differenceAlarm = other.differenceAlarm;
        minimumWarning = other.minimumWarning;
        maximumWarning = other.maximumWarning;
        minimumAlarm = other.minimumAlarm;
        maximumAlarm = other.maximumAlarm;

        return *this;
    }

    limitTableData(QString _name,
        double _differenceWarning,
        double _differenceAlarm,
        double _minimumWarning,
        double _minimumAlarm,
        double _maximumWarning,
        double _maximumAlarm)
        : name(_name)
        , differenceWarning(_differenceWarning)
        , differenceAlarm(_differenceAlarm)
        , minimumWarning(_minimumWarning)
        , maximumWarning(_maximumWarning)
        , minimumAlarm(_minimumAlarm)
        , maximumAlarm(_maximumAlarm)
    {

    }
};


class limit_table_model : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit limit_table_model(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
protected:
    QHash<int, QByteArray> roleNames() const override;
public:
    bool loadDataFromFile(const QString& filePath);
    bool saveDataToFile(const QString& filePath);

private:

    enum LimitTabDataRoles {
        NameRole = Qt::UserRole + 1,
        DifferenceWarningRole,
        DifferenceAlarmRole,
        MinimumWarningRole,
        MinimumAlarmRole,
        MaximumWarningRole,
        MaximumAlarmRole
    };

    // store as row/column // хранить в виде  ряда/столбца
    QVector<limitTableData> tableData;
};

#endif // LIMIT_TABLE_MODEL_H
