#ifndef REPORTVM_H
#define REPORTVM_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include "Script/Define/struct_def.h"
#include "Script/Config/config_application.h"

class MasterApp;

class ReportVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString lastReportTime READ lastReportTime WRITE setLastReportTime NOTIFY lastReportTimeChanged FINAL)
    Q_PROPERTY(int maxPageNumber READ maxPageNumber WRITE setMaxPageNumber NOTIFY maxPageNumberChanged FINAL)
public:
    explicit ReportVM(QObject *parent = nullptr);

    inline static ReportVM* GetInstance() {

        if (m_pInstance.isNull())
            m_pInstance.reset(new ReportVM());

        return m_pInstance.data();
    }

    void Init(QObject *parent = nullptr);
    void StartToChangeLanguage();
    InspectionInfoItem CreateInspectionData(QList<DefectInfoItem>, QList<BACKEND_RESULT>);
    void AddInspectionData(InspectionInfoItem data);
    void ClearInspectionData();

    // property //  Собственность
    QString lastReportTime();
    int maxPageNumber();
    // end // конец

    void RecordInspectionDataToFile();
    void PopulateInspectionDataFromFile();
private:

    // property //  Собственность
    QString _lastReportTime;
    int _maxPageNumber;
    // end // конец
    MasterApp* m_pParentObject;
    static QScopedPointer<ReportVM> m_pInstance;

    QList<InspectionInfoItem> m_listInspectionInfor;
    QJsonArray SerializeListInspectionInfor();
    void DeserilizeListInspectionInfor(const QJsonArray& jsonArray);

signals:

    // property //  Собственность
    void lastReportTimeChanged();
    void maxPageNumberChanged();
    // end // конец

    // qml signal
    void reportNumberChanged_Signal(int);
    void updateCurrentReport(int);

    // to qml

    void addInspectionData_Signal(InspectionInfoItem);


    void clearInspectionData_Signal();
    void updateVisionParamNumber_Signal(int bodyRNumber, int nonRoundShapeNumber, int nonRoundShape);

public slots:
    // property //  Собственность
    void setLastReportTime(QString value);
    void setMaxPageNumber(int value);
    void saveReportTableCSV(const QString& path, const QString& infor);
    void saveReportTablePDF(const QString& path, const QString& infor, const QString& header);
    // end // конец


    // qml slots // qml cлоты
    void export_Qml_Slot(int reportIndex, int pageIndex);
    void print_Qml_Slot(int reportIndex, int pageIndex);
    void currentReportIndexChanged_Qml_Slot(int reportIndex);

};

#endif // REPORTVM_H
