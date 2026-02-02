#include "limit_table_model.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

limit_table_model::limit_table_model(QObject *parent)
    : QAbstractTableModel{parent}
{

    // default data // данные по умолчанию
    tableData.append({
            limitTableData("Height", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("Weight", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("Tilt", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("Lean", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("BentNeck", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("ExternalBody", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("F", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("A", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("T", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("E", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("B", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("D", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("S", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("H", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("LugT", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("LugT1", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("Pushup", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("Flange", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("Knockout", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("InsideNeck", 0, 0, 303.2, 303.25, 306.8, 306.8),
            limitTableData("DAngle", 0, 0, 303.2, 303.25, 306.8, 306.8),

            // limitTableData("OvlLong1", 0, 0, 303.2, 303.25, 306.8, 306.8),
            // limitTableData("OvlShrt1", 0, 0, 303.2, 303.25, 306.8, 306.8),
            // limitTableData("OvlLong3", 0, 0, 303.2, 303.25, 306.8, 306.8),
            // limitTableData("OvlShrt3", 0, 0, 303.2, 303.25, 306.8, 306.8),
            // limitTableData("Lean2", 0, 0, 303.2, 303.25, 306.8, 306.8),
        });


}

int limit_table_model::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return tableData.size(); // Number of rows in the data // Количество строк в данных
}

int limit_table_model::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (tableData.isEmpty())
        return 0;

    return tableData.at(0).totalItem; // Number of columns in the first row // Количество столбцов в первой строке

}

QVariant limit_table_model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();

    if (row >= tableData.size() || col >= tableData[row].totalItem)
        return QVariant();


    const limitTableData& data = tableData[index.row()];  // Get the struct at the current row // Получить структуру в текущей строке

    switch (role) {
    case NameRole:
        return data.name;
    case DifferenceWarningRole:
        return data.differenceWarning;
    case DifferenceAlarmRole:
        return data.differenceAlarm;
    case MinimumWarningRole:
        return data.minimumWarning;
    case MinimumAlarmRole:
        return data.minimumAlarm;
    case MaximumWarningRole:
        return data.maximumWarning;
    case MaximumAlarmRole:
        return data.maximumAlarm;
    default:
        return QVariant();
    }


}

bool limit_table_model::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if (!index.isValid())
        return false;

    int row = index.row();
    int col = index.column();

    if (row >= tableData.size() || col >= tableData[row].totalItem)
        return false;

    // Update the data based on the role // Обновите данные в зависимости от роли
    switch (role) {
    case NameRole:
        tableData[row].name = value.toString();
        break;
    case DifferenceWarningRole:
        tableData[row].differenceWarning = value.toDouble();
        break;
    case DifferenceAlarmRole:
        tableData[row].differenceAlarm = value.toDouble();
        break;
    case MinimumWarningRole:
        tableData[row].minimumWarning = value.toDouble();
        break;
    case MinimumAlarmRole:
        tableData[row].minimumAlarm = value.toDouble();
        break;
    case MaximumWarningRole:
        tableData[row].maximumWarning = value.toDouble();
        break;
    case MaximumAlarmRole:
        tableData[row].maximumAlarm = value.toDouble();
        break;
    default:
        return false;  // Unknown role // Неизвестная роль
    }

    emit dataChanged(index, index, {role});

    return true;
}

Qt::ItemFlags limit_table_model::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractTableModel::flags(index); // Make the items editable // Сделайте элементы доступными для редактирования
}

QHash<int, QByteArray> limit_table_model::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[DifferenceWarningRole] = "diffWarning";
    roles[DifferenceAlarmRole] = "diffAlarm";
    roles[MinimumWarningRole] = "minWarning";
    roles[MinimumAlarmRole] = "minAlarm";
    roles[MaximumWarningRole] = "maxWarning";
    roles[MaximumAlarmRole] = "maxAlarm";
    return roles;

}

bool limit_table_model::loadDataFromFile(const QString& filePath)
{
    QFile f(filePath);

    if (!f.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open file for reading:" << filePath;
        return false;
    }

    // Read the file content into a QByteArray // Считывает содержимое файла в QByteArray
    QByteArray jsonData = f.readAll();
    f.close();

    // Parse the JSON document // Разобрать документ в формате JSON
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
    if (jsonDoc.isNull() || !jsonDoc.isArray()) {
        qWarning() << "Invalid JSON file";
        return false;
    }

  


    // Convert the JSON array to QVector<CustomData> // Преобразовать массив JSON в вектор<Пользовательские данные>

    QVector<limitTableData> infor;
    QJsonArray jsonArray = jsonDoc.array();
    for (const QJsonValue& value : jsonArray) {
        QJsonObject jsonObject = value.toObject();

        limitTableData row;
        row.name = jsonObject["name"].toString();
        row.differenceWarning = jsonObject["differenceWarning"].toDouble();
        row.differenceAlarm = jsonObject["differenceAlarm"].toDouble();
        row.minimumWarning = jsonObject["minimumWarning"].toDouble();
        row.minimumAlarm = jsonObject["minimumAlarm"].toDouble();
        row.maximumWarning = jsonObject["maximumWarning"].toDouble();
        row.maximumAlarm = jsonObject["maximumAlarm"].toDouble();

        // Append the row to the QVector // Добавить строку к вектору
        infor.append(row);
    }

    // Start to notify to update data // Начать уведомлять об обновлении данных
    beginResetModel();
    tableData = infor;
    endResetModel();

    return true;
}

bool limit_table_model::saveDataToFile(const QString& filePath)
{
    QJsonArray jsonArray;

    for (const auto& row : tableData)
    {
        QJsonObject jsonObject;

        jsonObject["name"] = row.name;
        jsonObject["differenceWarning"] = row.differenceWarning;
        jsonObject["differenceAlarm"] = row.differenceAlarm;
        jsonObject["minimumWarning"] = row.minimumWarning;
        jsonObject["minimumAlarm"] = row.minimumAlarm;
        jsonObject["maximumWarning"] = row.maximumWarning;
        jsonObject["maximumAlarm"] = row.maximumAlarm;

        // Add the object to the array // Добавить объект в массив
        jsonArray.append(jsonObject);
    }

    // Create a QJsonDocument and set the array as the root // Создайте QJsonDocument и задайте массив в качестве корневого
    QJsonDocument jsonDoc(jsonArray);

    // Save the JSON to a file // Сохраните JSON-файл в файл
    QFile jsonFile(filePath);
    if (!jsonFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open file for writing: " << filePath;
        return false;
    }

    jsonFile.write(jsonDoc.toJson(QJsonDocument::Indented));  // Pretty-print with indentation // Красивый принт с отступом
    jsonFile.close();

    return true;
}


