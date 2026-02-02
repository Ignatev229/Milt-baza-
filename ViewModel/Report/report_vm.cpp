#include "report_vm.h"
#include <QPdfWriter>
#include <QPainter>
#include "../Setout/setout_vm.h"
#include "../master_app.h"

QScopedPointer<ReportVM> ReportVM::m_pInstance;

ReportVM::ReportVM(QObject *parent)
    : QObject{parent}
{

}

void ReportVM::Init(QObject *parent)
{
    m_pParentObject = reinterpret_cast<MasterApp*>(parent);

    PopulateInspectionDataFromFile();
    // setLastReportTime("2024.04.21 12:50:30"); // Установить время последнего отчета("2024.04.21 12:50:30");
    setMaxPageNumber(10);
    emit reportNumberChanged_Signal(4);
}

void ReportVM::StartToChangeLanguage()
{
    emit reportNumberChanged_Signal(4);
}

void ReportVM::PopulateInspectionDataFromFile()
{
    QString path = ConfigApplication::instance()->GetReportFilePath(ConfigApplication::instance()->m_strReportFileName);

    QString filePath = QDir::cleanPath(path);

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        file.close();

        DeserilizeListInspectionInfor(doc.array());
    }

    // Record its back in order to have value if file not exist // Запишите его обратно, чтобы иметь значение, если файл не существует
    RecordInspectionDataToFile();


    // push data to UI // передача данных в пользовательский интерфейс

    for (int i = 0; i < m_listInspectionInfor.count(); ++i) {
        emit addInspectionData_Signal(m_listInspectionInfor[i]);
    }

}

InspectionInfoItem ReportVM::CreateInspectionData(QList<DefectInfoItem> defectInfos, QList<BACKEND_RESULT> defectCodes)
{

    InspectionInfoItem item;

    for (int i = 0; i < defectInfos.count(); ++i) {
        if(defectInfos[i].defect == BACKEND_RESULT::HEIGHT &&
            defectInfos[i].parameter == "Height")
        {
            item.setHeight(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::WEIGHT &&
                   defectInfos[i].parameter == "Weight")
        {
            item.setWeight(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::TILT &&
                 defectInfos[i].parameter == "Height")
        {
            item.setTilt(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));

        }
        else if(defectInfos[i].defect == BACKEND_RESULT::LEAN &&
                 defectInfos[i].parameter == "Deviation")
        {
            item.setLean(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));

        }
        else if(defectInfos[i].defect == BACKEND_RESULT::F_DIMENSION &&
                 defectInfos[i].parameter == "Dimension")
        {
            item.setDimensionF(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));

        }
        else if(defectInfos[i].defect == BACKEND_RESULT::A_DIMENSION &&
                 defectInfos[i].parameter == "Dimension")
        {
            item.setDimensionA(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::T_DIMENSION &&
                 defectInfos[i].parameter == "Dimension")
        {
            item.setDimensionT(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::E_DIMENSION &&
                 defectInfos[i].parameter == "Dimension")
        {
            item.setDimensionE(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::B_DIMENSION &&
                 defectInfos[i].parameter == "Dimension")
        {
            item.setDimensionB(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::D_DIMENSION &&
                 defectInfos[i].parameter == "Dimension")
        {
            item.setDimensionD(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::S_DIMENSION &&
                 defectInfos[i].parameter == "Dimension")
        {
            item.setDimensionS(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::H_DIMENSION &&
                 defectInfos[i].parameter == "Dimension")
        {
            item.setDimensionH(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::LUGT_DIMENSION &&
                 defectInfos[i].parameter == "Dimension")
        {
            item.setDimensionLugT(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::LUGT1_DIMENSION &&
                 defectInfos[i].parameter == "Dimension")
        {
            item.setDimensionLugT1(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::D_ANGLE_DIMENSION &&
                 defectInfos[i].parameter == "Angle")
        {
            item.setDAngle(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }

        else if(defectInfos[i].defect == BACKEND_RESULT::BODYR_DIMENSION &&
                   defectInfos[i].parameter.startsWith("Dimension"))
        {
            QList<InspectionInfoChildItem> k = item.getBodyR();
            k.append(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
            item.setBodyR(k);
        }

        else if(defectInfos[i].defect == BACKEND_RESULT::PUSHUP_DIMENSION &&
                 defectInfos[i].parameter == "Pushup")
        {
            item.setPushup(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }

        else if(defectInfos[i].defect == BACKEND_RESULT::NON_ROUND_SHAPE &&
                 defectInfos[i].parameter.startsWith("RecShrt"))
        {
            QList<InspectionInfoChildItem> k = item.getRecShrt();
            k.append(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
            item.setRecShrt(k);
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::NON_ROUND_SHAPE &&
                 defectInfos[i].parameter.startsWith("RecLong"))
        {
            QList<InspectionInfoChildItem> k = item.getRecLong();
            k.append(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
            item.setRecLong(k);
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::NON_ROUND_SHAPE &&
                 defectInfos[i].parameter.startsWith("RecDiag"))
        {
            QList<InspectionInfoChildItem> k = item.getRecDiag();
            k.append(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
            item.setRecDiag(k);
        }

        else if(defectInfos[i].defect == BACKEND_RESULT::NON_ROUND_SHAPE &&
                 defectInfos[i].parameter.startsWith("SqrSide"))
        {
            QList<InspectionInfoChildItem> k = item.getSqrSide();
            k.append(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
            item.setSqrSide(k);
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::NON_ROUND_SHAPE &&
                 defectInfos[i].parameter.startsWith("SqrDiag"))
        {
            QList<InspectionInfoChildItem> k = item.getSqrDiag();
            k.append(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
            item.setSqrDiag(k);
        }

        else if(defectInfos[i].defect == BACKEND_RESULT::NON_ROUND_SHAPE &&
                 defectInfos[i].parameter.startsWith("OvlShrt"))
        {
            QList<InspectionInfoChildItem> k = item.getOvlShrt();
            k.append(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
            item.setOvlShrt(k);
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::NON_ROUND_SHAPE &&
                 defectInfos[i].parameter.startsWith("OvlLong"))
        {
            QList<InspectionInfoChildItem> k = item.getOvlLong();
            k.append(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
            item.setOvlLong(k);
        }

        else if(defectInfos[i].defect == BACKEND_RESULT::FLANGE_DIMENSION &&
                 defectInfos[i].parameter == "Max Knockout")
        {
            item.setFlange(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }
        else if(defectInfos[i].defect == BACKEND_RESULT::KNOCKOUT_DIMENSION &&
                 defectInfos[i].parameter == "Max Knockout")
        {
            item.setKnockout(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }

        else if(defectInfos[i].defect == BACKEND_RESULT::CODE_NUMBER &&
                 defectInfos[i].parameter == "Code Number")
        {
            item.setCodeNumber(InspectionInfoChildItem(defectInfos[i].mmValue, defectInfos[i].isPass));
        }
    }
    return item;
}

void ReportVM::AddInspectionData(InspectionInfoItem data)
{
    m_listInspectionInfor.append(data);

    // store and record data // хранение и запись данных
    RecordInspectionDataToFile();

    emit addInspectionData_Signal(data);

}

void ReportVM::ClearInspectionData()
{
    emit clearInspectionData_Signal();
    m_listInspectionInfor.clear();
    // store and record data // хранение и запись данных
    RecordInspectionDataToFile();
}

QString ReportVM::lastReportTime()
{
    return _lastReportTime;
}

int ReportVM::maxPageNumber()
{
    return _maxPageNumber;
}

void ReportVM::setLastReportTime(QString value)
{
    if(_lastReportTime != value){_lastReportTime = value; emit lastReportTimeChanged();}
}

void ReportVM::setMaxPageNumber(int value)
{
    if(_maxPageNumber != value){_maxPageNumber = value; emit maxPageNumberChanged();}
}

void ReportVM::saveReportTableCSV(const QString& path, const QString& infor)
{
    QFile f(path);

    if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {  // Open the file for writing // Открыть файл для записи
        QTextStream out(&f);  // Create a stream to write to the file // Создайте поток для записи в файл
        out << infor;
        f.close();  // Close the file when done // Закройте файл, когда  завершите

        qDebug() << "[ReportVM]" << "saveReportTable Success";
    }
}

void ReportVM::saveReportTablePDF(const QString& path, const QString& infor, const QString& header)
{

    QPdfWriter writer(path);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setResolution(300);

    static QString title = "TABLE REPORT";

    QPainter painter(&writer);

    // Set font for the title // Установить шрифт для заголовка
    static QFont titleFont("Arial", 16, QFont::Bold);
    int titleHeight = QFontMetrics(titleFont).height();

    painter.setFont(titleFont);

    // Get the page width and height // Получить ширину и высоту страницы
    int pageWidth = writer.width();
    int pageHeight = writer.height();

    QFontMetrics metrics(titleFont);


    int textWidth = metrics.horizontalAdvance(title);
    int x = (pageWidth - textWidth) / 2; // Center x position // Центральное положение x
    int y = 100; // Fixed Y position for title // Исправлена позиция Y для названия

    // Title // Название
    painter.drawText(x, y, title);


    // Content // Содержание
    static QFont contentFont(QFont("Arial", 12));
    painter.setFont(contentFont);

    QStringList rowInfors = infor.split("------\n");
    int lineHeight = QFontMetrics(contentFont).height();

    static const int offsetTitle2Content = 10;
    int yPos = y + titleHeight + offsetTitle2Content;
    QStringList headerText = header.split("\n");

    int pageCount = 0;

    for (const QString& rowInfor : rowInfors)
    {
        if (rowInfor.isEmpty()) continue;

        // increase a page, except first case // увеличить страницу, за исключением первого случая
        if (pageCount > 0)
        {
            writer.newPage();
        }

        // split to get each item // разделить, чтобы получить каждый предмет
        // now all item size must be equal header size // теперь размер всего элемента должен быть равен размеру заголовка
        QStringList infor = rowInfor.split("\n");

        yPos = y + titleHeight + offsetTitle2Content;
        int countItem = 0;
        for (const QString& item : infor)
        {
            //Draw header //Нарисовать заголовок
            painter.drawText(100, yPos, headerText.at(countItem));

            // Draw item // Нарисовать элемент
            painter.drawText(800, yPos, item);

            yPos += 80;
            countItem++;
        }

        pageCount++;
    }

    //int countItem = 0;

    //for (int i = 0; i < parts.size(); i++)
    //{

    //    QString textHeader = headerText.at(i);
    //    QString textContent = 

    //}
    //for (const QString& p : parts)
    //{
    //    // store header
    //    if (p == "HEADER")
    //    {
    //        headerText.append(p);
    //    }



    //    //if (yPos > pageHeight)
    //    //{
    //    //    writer.newPage();  // Finish current page
    //    //    yPos = y + titleHeight + offsetTitle2Content;
    //    //    page++;
    //    //}

    //    //painter.drawText(100, yPos, p);

    //    //yPos += 100;
    //}
    //

    painter.end();
    
}

void ReportVM::export_Qml_Slot(int reportIndex, int pageIndex)
{
    qDebug() << "[ReportVM]" << "Export: " << reportIndex << pageIndex;
}

void ReportVM::print_Qml_Slot(int reportIndex, int pageIndex)
{
    qDebug() << "[ReportVM]" << "Print: " << reportIndex << pageIndex;
}

void ReportVM::currentReportIndexChanged_Qml_Slot(int reportIndex)
{
    qDebug() << "[ReportVM]" << "Current Report: " << reportIndex;
    // write to config file
    ConfigApplication::instance()->m_commonInfo.appSetting.m_nCurrentReport = reportIndex;
    ConfigApplication::instance()->WriteAppSetting();

    // load old report data
    emit clearInspectionData_Signal();
    m_listInspectionInfor.clear();
    PopulateInspectionDataFromFile();

    // load old setout data
    SetoutVM::GetInstance()->InitSetoutMoldNumber();
}


QJsonArray ReportVM::SerializeListInspectionInfor()
{
    QJsonArray jsonArray;
    for ( auto& item : m_listInspectionInfor) {

        jsonArray.append(item.SerializeData());
    }
    return jsonArray;
}

void ReportVM::DeserilizeListInspectionInfor(const QJsonArray& jsonArray)
{
    m_listInspectionInfor.clear();

    for (const auto& jsonValue : jsonArray) {
        InspectionInfoItem infor;
        infor.DeserializeData(jsonValue.toObject());
        m_listInspectionInfor.append(infor);
    }
}

void ReportVM::RecordInspectionDataToFile()
{
    QString path = ConfigApplication::instance()->GetReportFilePath(ConfigApplication::instance()->m_strReportFileName);

    QString filePath = QDir::cleanPath(path);

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(SerializeListInspectionInfor()); // Convert QList to QJsonArray and wrap in QJsonDocument // Конвертировать QList в QJsonArray и обернуть в QJsonDocument
        file.write(doc.toJson());
        file.close();
    }
}


