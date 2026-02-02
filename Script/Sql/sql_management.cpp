#include "sql_management.h"

QScopedPointer<SQLManagement> SQLManagement::m_pInstance;

SQLManagement::SQLManagement(QObject *parent)
    : QObject{parent}
{

}

SQLManagement::~SQLManagement()
{

}

void SQLManagement::Init()
{
    // Connect to SQLite database
    m_bIsConnected = false;
    m_Database = QSqlDatabase::addDatabase("QSQLITE");
    m_Database.setDatabaseName(ConfigApplication::instance()->m_strDBFile);

    if (!m_Database.open()) {
        qWarning() << "Error: Unable to open database:" << m_Database.lastError().text();
        return;
    }
    m_bIsConnected = true;
    // Create a table
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS InspectionData ("
                    "dateTime DATETIME PRIMARY KEY, "
                    "lotID TEXT, "
                    "job TEXT, "
                    "moldNumber TEXT, "
                    "codeNumber TEXT, "
                    "height TEXT, "
                    "weight TEXT, "
                    "bodyR TEXT, "
                    "recShrt TEXT, "
                    "recLong TEXT, "
                    "recDiag TEXT, "
                    "sqrSide TEXT, "
                    "sqrDiag TEXT, "
                    "ovlShrt TEXT, "
                    "ovlLong TEXT, "
                    "tilt TEXT, "
                    "lean TEXT, "
                    "dimensionF TEXT, "
                    "dimensionA TEXT, "
                    "dimensionT TEXT, "
                    "dimensionE TEXT, "
                    "dimensionD TEXT, "
                    "dimensionB TEXT, "
                    "dimensionS TEXT, "
                    "dimensionH TEXT, "
                    "dimensionLugT TEXT, "
                    "dimensionLugT1 TEXT, "
                    "dAngle TEXT, "
                    "pushup TEXT, "
                    "flange TEXT, "
                    "knockout TEXT)")) {
        qWarning() << "Error: Unable to create table:" << query.lastError().text();
        // return;
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS ValidationData ("
                    "dateTime DATETIME PRIMARY KEY, "
                    "height TEXT, "
                    "bodyR TEXT)")) {
        qWarning() << "Error: Unable to create table:" << query.lastError().text();
        // return;
    }

    // check table exit code number or not and add it
    AddColumnIfNotExists("InspectionData", "codeNumber", "TEXT");

    // // Define the date range
    // QDateTime startDate = QDateTime::fromString("2024-10-20 00:00:00", Qt::ISODate);
    // QDateTime endDate = QDateTime::fromString("2024-11-02 23:59:59", Qt::ISODate);
    // LoadInspectionData(startDate, endDate);
}

void SQLManagement::Close()
{
    m_bIsConnected = false;
    m_Database.close();
}

void SQLManagement::AddInspectionData(InspectionInfoItem &item)
{
    if(!m_bIsConnected)
        return;

    // add data to table
    QSqlQuery query;

    // Insert data into the table
    query.prepare("INSERT INTO InspectionData ("
                  "dateTime, "
                  "lotID, "
                  "job, "
                  "moldNumber, "
                  "codeNumber, "
                  "height, "
                  "weight, "
                  "bodyR, "
                  "recShrt, "
                  "recLong, "
                  "recDiag, "
                  "sqrSide, "
                  "sqrDiag, "
                  "ovlShrt, "
                  "ovlLong, "
                  "tilt, "
                  "lean, "
                  "dimensionF, "
                  "dimensionA, "
                  "dimensionT, "
                  "dimensionE, "
                  "dimensionD, "
                  "dimensionB, "
                  "dimensionS, "
                  "dimensionH, "
                  "dimensionLugT, "
                  "dimensionLugT1, "
                  "dAngle, "
                  "pushup, "
                  "flange, "
                  "knockout) "
                  "VALUES ("
                  ":dateTime, "
                  ":lotID, "
                  ":job, "
                  ":moldNumber, "
                  ":codeNumber, "
                  ":height, "
                  ":weight, "
                  ":bodyR, "
                  ":recShrt, "
                  ":recLong, "
                  ":recDiag, "
                  ":sqrSide, "
                  ":sqrDiag, "
                  ":ovlShrt, "
                  ":ovlLong, "
                  ":tilt, "
                  ":lean, "
                  ":dimensionF, "
                  ":dimensionA, "
                  ":dimensionT, "
                  ":dimensionE, "
                  ":dimensionD, "
                  ":dimensionB, "
                  ":dimensionS, "
                  ":dimensionH, "
                  ":dimensionLugT, "
                  ":dimensionLugT1, "
                  ":dAngle, "
                  ":pushup, "
                  ":flange, "
                  ":knockout)");

    query.bindValue(":dateTime", item.getDateTime().getValue());
    query.bindValue(":lotID", item.getLotID().getValue());
    query.bindValue(":job", item.getJob().getValue());
    query.bindValue(":moldNumber", item.getMoldNumber().getValue());
    query.bindValue(":codeNumber", item.getCodeNumber().getValue());
    query.bindValue(":height", QString("%1%2")
                                   .arg(item.getHeight().getValue().toString())
                                   .arg(item.getHeight().getIsPass() ? "" : "$"));
    query.bindValue(":weight", QString("%1%2")
                                   .arg(item.getWeight().getValue().toString())
                                   .arg(item.getWeight().getIsPass() ? "" : "$"));

    QString bodyR;
    for (int i = 0; i < item.getBodyR().count(); ++i) {
        bodyR += (item.getBodyR()[i].getValue().toString() +
                  (item.getBodyR()[i].getIsPass() ? "" : "$") +
                  (i < item.getBodyR().count() - 1 ? ";" : ""));
    }
    query.bindValue(":bodyR", bodyR);

    QString recShrt;
    for (int i = 0; i < item.getRecShrt().count(); ++i) {
        recShrt += (item.getRecShrt()[i].getValue().toString() +
                    (item.getRecShrt()[i].getIsPass() ? "" : "$") +
                    (i < item.getRecShrt().count() - 1 ? ";" : ""));
    }
    query.bindValue(":recShrt", recShrt);

    QString recLong;
    for (int i = 0; i < item.getRecLong().count(); ++i) {
        recLong += (item.getRecLong()[i].getValue().toString() +
                    (item.getRecLong()[i].getIsPass() ? "" : "$") +
                    (i < item.getRecLong().count() - 1 ? ";" : ""));
    }
    query.bindValue(":recLong", recLong);

    QString recDiag;
    for (int i = 0; i < item.getRecDiag().count(); ++i) {
        recDiag += (item.getRecDiag()[i].getValue().toString() +
                    (item.getRecDiag()[i].getIsPass() ? "" : "$") +
                    (i < item.getRecDiag().count() - 1 ? ";" : ""));
    }
    query.bindValue(":recDiag", recDiag);

    QString sqrSide;
    for (int i = 0; i < item.getSqrSide().count(); ++i) {
        sqrSide += (item.getSqrSide()[i].getValue().toString() +
                    (item.getSqrSide()[i].getIsPass() ? "" : "$") +
                    (i < item.getSqrSide().count() - 1 ? ";" : ""));
    }
    query.bindValue(":sqrSide", sqrSide);

    QString sqrDiag;
    for (int i = 0; i < item.getSqrDiag().count(); ++i) {
        sqrDiag += (item.getSqrDiag()[i].getValue().toString() +
                    (item.getSqrDiag()[i].getIsPass() ? "" : "$") +
                    (i < item.getSqrDiag().count() - 1 ? ";" : ""));
    }
    query.bindValue(":sqrDiag", sqrDiag);

    QString ovlShrt;
    for (int i = 0; i < item.getOvlShrt().count(); ++i) {
        ovlShrt += (item.getOvlShrt()[i].getValue().toString() +
                    (item.getOvlShrt()[i].getIsPass() ? "" : "$") +
                    (i < item.getOvlShrt().count() - 1 ? ";" : ""));
    }
    query.bindValue(":ovlShrt", ovlShrt);

    QString ovlLong;
    for (int i = 0; i < item.getOvlLong().count(); ++i) {
        ovlLong += (item.getOvlLong()[i].getValue().toString() +
                    (item.getOvlLong()[i].getIsPass() ? "" : "$") +
                    (i < item.getOvlLong().count() - 1 ? ";" : ""));
    }
    query.bindValue(":ovlLong", ovlLong);

    query.bindValue(":tilt", QString("%1%2")
                                 .arg(item.getTilt().getValue().toString())
                                 .arg(item.getTilt().getIsPass() ? "" : "$"));
    query.bindValue(":lean", QString("%1%2")
                                 .arg(item.getLean().getValue().toString())
                                 .arg(item.getLean().getIsPass() ? "" : "$"));
    query.bindValue(":dimensionF", QString("%1%2")
                                       .arg(item.getDimensionF().getValue().toString())
                                       .arg(item.getDimensionF().getIsPass() ? "" : "$"));
    query.bindValue(":dimensionA", QString("%1%2")
                                       .arg(item.getDimensionA().getValue().toString())
                                       .arg(item.getDimensionA().getIsPass() ? "" : "$"));
    query.bindValue(":dimensionT", QString("%1%2")
                                       .arg(item.getDimensionT().getValue().toString())
                                       .arg(item.getDimensionT().getIsPass() ? "" : "$"));
    query.bindValue(":dimensionE", QString("%1%2")
                                       .arg(item.getDimensionE().getValue().toString())
                                       .arg(item.getDimensionE().getIsPass() ? "" : "$"));
    query.bindValue(":dimensionD", QString("%1%2")
                                       .arg(item.getDimensionD().getValue().toString())
                                       .arg(item.getDimensionD().getIsPass() ? "" : "$"));
    query.bindValue(":dimensionB", QString("%1%2")
                                       .arg(item.getDimensionB().getValue().toString())
                                       .arg(item.getDimensionB().getIsPass() ? "" : "$"));
    query.bindValue(":dimensionS", QString("%1%2")
                                       .arg(item.getDimensionS().getValue().toString())
                                       .arg(item.getDimensionS().getIsPass() ? "" : "$"));
    query.bindValue(":dimensionH", QString("%1%2")
                                       .arg(item.getDimensionH().getValue().toString())
                                       .arg(item.getDimensionH().getIsPass() ? "" : "$"));
    query.bindValue(":dimensionLugT", QString("%1%2")
                                          .arg(item.getDimensionLugT().getValue().toString())
                                          .arg(item.getDimensionLugT().getIsPass() ? "" : "$"));
    query.bindValue(":dimensionLugT1", QString("%1%2")
                                           .arg(item.getDimensionLugT1().getValue().toString())
                                           .arg(item.getDimensionLugT1().getIsPass() ? "" : "$"));
    query.bindValue(":dAngle", QString("%1%2")
                                   .arg(item.getDAngle().getValue().toString())
                                   .arg(item.getDAngle().getIsPass() ? "" : "$"));

    query.bindValue(":pushup", QString("%1%2")
                                   .arg(item.getPushup().getValue().toString())
                                   .arg(item.getPushup().getIsPass() ? "" : "$"));
    query.bindValue(":flange", QString("%1%2")
                                   .arg(item.getFlange().getValue().toString())
                                   .arg(item.getFlange().getIsPass() ? "" : "$"));
    query.bindValue(":knockout", QString("%1%2")
                                     .arg(item.getKnockout().getValue().toString())
                                     .arg(item.getKnockout().getIsPass() ? "" : "$"));


    if (!query.exec()) {
        qWarning() << "Error: Unable to insert data:" << query.lastError().text();
    }

}

QList<InspectionInfoItem> SQLManagement::LoadInspectionData(const QDateTime &startDate, const QDateTime &endDate)
{
    QList<InspectionInfoItem> values;
    if(!m_bIsConnected)
        return values;


    // Prepare a query to retrieve data within a date range
    QSqlQuery query;
    query.prepare("SELECT "
                  "dateTime, "
                  "lotID, "
                  "job, "
                  "moldNumber, "
                  "codeNumber, "
                  "height, "
                  "weight, "
                  "bodyR, "
                  "recShrt, "
                  "recLong, "
                  "recDiag, "
                  "sqrSide, "
                  "sqrDiag, "
                  "ovlShrt, "
                  "ovlLong, "
                  "tilt, "
                  "lean, "
                  "dimensionF, "
                  "dimensionA, "
                  "dimensionT, "
                  "dimensionE, "
                  "dimensionD, "
                  "dimensionB, "
                  "dimensionS, "
                  "dimensionH, "
                  "dimensionLugT, "
                  "dimensionLugT1, "
                  "dAngle, "
                  "pushup, "
                  "flange, "
                  "knockout "
                  "FROM InspectionData WHERE dateTime BETWEEN :start_date AND :end_date");
    query.bindValue(":start_date", startDate);
    query.bindValue(":end_date", endDate);

    if (!query.exec()) {
        qWarning() << "Error: Unable to execute query:" << query.lastError().text();
        return values;
    }

    // Read and display the results
    while (query.next()) {
        QString temp, temp1;
        InspectionInfoItem item;
        item.setDateTime(InspectionInfoChildItem(query.value("dateTime").toString(), true));
        item.setLotID(InspectionInfoChildItem(query.value("lotID").toString(), true));
        item.setJob(InspectionInfoChildItem(query.value("job").toString(), true));
        item.setMoldNumber(InspectionInfoChildItem(query.value("moldNumber").toString(), true));
        item.setCodeNumber(InspectionInfoChildItem(query.value("codeNumber").toString(), true));

        temp = query.value("height").toString();
        temp1 = query.value("height").toString();
        item.setHeight(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("weight").toString();
        temp1 = query.value("weight").toString();
        item.setWeight(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("tilt").toString();
        temp1 = query.value("tilt").toString();
        item.setTilt(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("lean").toString();
        temp1 = query.value("lean").toString();
        item.setLean(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("dimensionF").toString();
        temp1 = query.value("dimensionF").toString();
        item.setDimensionF(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("dimensionA").toString();
        temp1 = query.value("dimensionA").toString();
        item.setDimensionA(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("dimensionT").toString();
        temp1 = query.value("dimensionT").toString();
        item.setDimensionT(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("dimensionE").toString();
        temp1 = query.value("dimensionE").toString();
        item.setDimensionE(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("dimensionD").toString();
        temp1 = query.value("dimensionD").toString();
        item.setDimensionD(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("dimensionB").toString();
        temp1 = query.value("dimensionB").toString();
        item.setDimensionB(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("dimensionS").toString();
        temp1 = query.value("dimensionS").toString();
        item.setDimensionS(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("dimensionH").toString();
        temp1 = query.value("dimensionH").toString();
        item.setDimensionH(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("dimensionLugT").toString();
        temp1 = query.value("dimensionLugT").toString();
        item.setDimensionLugT(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("dimensionLugT1").toString();
        temp1 = query.value("dimensionLugT1").toString();
        item.setDimensionLugT1(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("dAngle").toString();
        temp1 = query.value("dAngle").toString();
        item.setDAngle(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("pushup").toString();
        temp1 = query.value("pushup").toString();
        item.setPushup(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("flange").toString();
        temp1 = query.value("flange").toString();
        item.setFlange(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        temp = query.value("knockout").toString();
        temp1 = query.value("knockout").toString();
        item.setKnockout(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        QStringList dataString = query.value("bodyR").toString().split(";");
        QList<InspectionInfoChildItem> bodyR;
        for (int i = 0; i < dataString.count(); ++i) {
            temp = dataString[i];
            temp1 = dataString[i];
            bodyR.append(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));
            item.setBodyR(bodyR);
        }

        dataString = query.value("recShrt").toString().split(";");
        QList<InspectionInfoChildItem> recShrt;
        for (int i = 0; i < dataString.count(); ++i) {
            temp = dataString[i];
            temp1 = dataString[i];
            recShrt.append(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));
            item.setRecShrt(recShrt);
        }

        dataString = query.value("recLong").toString().split(";");
        QList<InspectionInfoChildItem> recLong;
        for (int i = 0; i < dataString.count(); ++i) {
            temp = dataString[i];
            temp1 = dataString[i];
            recLong.append(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));
            item.setRecLong(recLong);
        }

        dataString = query.value("recDiag").toString().split(";");
        QList<InspectionInfoChildItem> recDiag;
        for (int i = 0; i < dataString.count(); ++i) {
            temp = dataString[i];
            temp1 = dataString[i];
            recDiag.append(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));
            item.setRecDiag(recDiag);
        }

        dataString = query.value("sqrSide").toString().split(";");
        QList<InspectionInfoChildItem> sqrSide;
        for (int i = 0; i < dataString.count(); ++i) {
            temp = dataString[i];
            temp1 = dataString[i];
            sqrSide.append(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));
            item.setSqrSide(sqrSide);
        }

        dataString = query.value("sqrDiag").toString().split(";");
        QList<InspectionInfoChildItem> sqrDiag;
        for (int i = 0; i < dataString.count(); ++i) {
            temp = dataString[i];
            temp1 = dataString[i];
            sqrDiag.append(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));
            item.setSqrDiag(sqrDiag);
        }

        dataString = query.value("ovlShrt").toString().split(";");
        QList<InspectionInfoChildItem> ovlShrt;
        for (int i = 0; i < dataString.count(); ++i) {
            temp = dataString[i];
            temp1 = dataString[i];
            ovlShrt.append(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));
            item.setOvlShrt(ovlShrt);
        }

        dataString = query.value("ovlLong").toString().split(";");
        QList<InspectionInfoChildItem> ovlLong;
        for (int i = 0; i < dataString.count(); ++i) {
            temp = dataString[i];
            temp1 = dataString[i];
            ovlLong.append(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));
            item.setOvlLong(ovlLong);
        }

        values.append(item);
    }

    return values;

}

void SQLManagement::AddValidationData(InspectionInfoItem &item)
{
    if(!m_bIsConnected)
        return;

    // add data to table
    QSqlQuery query;

    // Insert data into the table
    query.prepare("INSERT INTO ValidationData ("
                  "dateTime, "
                  "height, "
                  "bodyR) "
                  "VALUES ("
                  ":dateTime, "
                  ":height, "
                  ":bodyR)");

    query.bindValue(":dateTime", item.getDateTime().getValue());
    query.bindValue(":height", QString("%1%2")
                                   .arg(item.getHeight().getValue().toString())
                                   .arg(item.getHeight().getIsPass() ? "" : "$"));

    QString bodyR;
    for (int i = 0; i < item.getBodyR().count(); ++i) {
        bodyR += (item.getBodyR()[i].getValue().toString() +
                  (item.getBodyR()[i].getIsPass() ? "" : "$") +
                  (i < item.getBodyR().count() - 1 ? ";" : ""));
    }
    query.bindValue(":bodyR", bodyR);

    if (!query.exec()) {
        qWarning() << "Error: Unable to insert data:" << query.lastError().text();
    }
}

QList<InspectionInfoItem> SQLManagement::LoadValidationData()
{
    QList<InspectionInfoItem> values;
    if(!m_bIsConnected)
        return values;


    // Prepare a query to retrieve data within a date range
    QSqlQuery query;
    query.prepare("SELECT "
                  "dateTime, "
                  "height, "
                  "bodyR "
                  "FROM ValidationData ORDER BY dateTime ASC");


    if (!query.exec()) {
        qWarning() << "Error: Unable to execute query:" << query.lastError().text();
        return values;
    }

    // Read and display the results
    while (query.next()) {
        QString temp, temp1;
        InspectionInfoItem item;
        item.setDateTime(InspectionInfoChildItem(query.value("dateTime").toString(), true));

        temp = query.value("height").toString();
        temp1 = query.value("height").toString();
        item.setHeight(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));

        QStringList dataString = query.value("bodyR").toString().split(";");
        QList<InspectionInfoChildItem> bodyR;
        for (int i = 0; i < dataString.count(); ++i) {
            temp = dataString[i];
            temp1 = dataString[i];
            bodyR.append(InspectionInfoChildItem(temp.replace("$", ""), !temp1.contains("$")));
            item.setBodyR(bodyR);
        }

        values.append(item);
    }

    return values;
}

bool SQLManagement::ColumnExists(const QString &tableName, const QString &columnName)
{
    QSqlQuery query(m_Database);
    query.prepare(QString("PRAGMA table_info(%1)").arg(tableName));
    if (!query.exec()) {
        qWarning() << "PRAGMA failed:" << query.lastError().text();
        return false;
    }

    while (query.next()) {
        if (query.value(1).toString() == columnName) {
            return true;
        }
    }
    return false;
}

void SQLManagement::AddColumnIfNotExists(const QString &tableName, const QString &columnName, const QString &columnType)
{
    if (!ColumnExists(tableName, columnName)) {
        QSqlQuery query(m_Database);
        QString alterStmt = QString("ALTER TABLE %1 ADD COLUMN %2 %3").arg(tableName, columnName, columnType);
        if (!query.exec(alterStmt)) {
            qWarning() << "Failed to add column" << columnName << ":" << query.lastError().text();
        } else {
            qDebug() << "Added column" << columnName;
        }
    }
}
