#ifndef SQL_MANAGEMENT_H
#define SQL_MANAGEMENT_H

#include <QObject>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include "../Config/config_application.h"

class SQLManagement: public QObject
{
    Q_OBJECT
public:
    SQLManagement(QObject *parent = nullptr);
    virtual ~SQLManagement();

    inline static SQLManagement* GetInstance() {

        if (m_pInstance.isNull())
            m_pInstance.reset(new SQLManagement());

        return m_pInstance.data();
    }

    void Init();
    void Close();
    void AddInspectionData(InspectionInfoItem &item);
    QList<InspectionInfoItem> LoadInspectionData(const QDateTime& startDate, const QDateTime& endDate);

    void AddValidationData(InspectionInfoItem &item);
    QList<InspectionInfoItem> LoadValidationData();


private:
    static QScopedPointer<SQLManagement> m_pInstance;
    QSqlDatabase m_Database;

    bool m_bIsConnected;
    bool ColumnExists(const QString &tableName, const QString &columnName);
    void AddColumnIfNotExists(const QString &tableName, const QString &columnName, const QString &columnType);


};

#endif // SQL_MANAGEMENT_H
