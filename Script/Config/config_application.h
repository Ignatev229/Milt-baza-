#ifndef CONFIGAPPLICATION_H
#define CONFIGAPPLICATION_H

#include <QObject>
#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDirIterator>
#include <QStandardPaths>
#include <QFuture>
#include <QtConcurrent>


#include "../Define/struct_def.h"
#include "Script/Modbus/MBdefine.h"

class ConfigApplication : public QObject
{
    Q_OBJECT
public:
    ConfigApplication();
    ~ConfigApplication();

    static ConfigApplication * instance();

    QString m_strAppName;
    QString m_strAppVersion;

    // config folder // конфигурационная папка
    QString m_strConfigPath;
    QString m_strAccountPath;
    QString m_strConfigFile;
    QString m_strConfigRecipePath;
    QString m_strConfigRecipeDefaultName;
    QString m_strConfigRecipeName;
    QString m_strValidationRecipeName;
    QString m_strVisionParamName;
    // QString m_strConfigCommonName;
    // QString m_strConfigCameraName;
    QString m_strLogPath;
    QString m_strLogName;
    QString m_strSaveImageDefaultPath;
    QString m_strOperatorImageName;
    QString m_strInspectImageName;
    QString m_strPLCSettingFileName;
    QString m_strReportPath;
    QString m_strSetoutMoldFileName;
    QString m_strReportFileName;
    QString m_strDBFile;
    QString m_strCalibCameraPosFile;

    // statistic // статистика
    QString m_strStatisticsName;
    QString m_strStatisticsPath;

    // Account // Учетная запись
    ACCOUNT_LEVEL m_strcCurrentAccountLevel;
    QString m_strCurrentAccountName;

    //
    QHash<TRACK_INDEX, QString> m_hashExtendImageName;
    QString m_strImageExtension;

    // camera // камера
    int m_nCamNum;
    int m_nReviewDoc;
    int m_nReviewTrack;

    // APP mode // Режим приложения
    APP_STATUS m_appStatus;

    // review tab // вкладка "обзор"
    int m_nMaxSingleReviewReloaded;

    // AI backend //  Бэкенд искусственного интеллекта
    int m_nBackendPort;

    // license // лицензия
    std::string m_strSoftwareName;
    std::string m_strLicenseKey;

    // config // конфигурация
    CommonInfo m_commonInfo;
    int m_nServerPort;
    std::string m_strServerName;

    // doc name for each track // название документа для каждого трека
    QList<QStringList> m_listDocNames ;
    QStringList m_listInspectInfoState;
    QStringList m_listBackendFunctions;


    // create folder // создать папку
    void CreateFolderConfigApplication();
    void CreateFolderSaveImage(QString path);

    // setting // настройка
    void ReadAppSetting();
    void WriteAppSetting();
    // void ReadCommonSetting();
    // void ReadCameraSetting();
    void ReadPLCSetting();
    // void WriteCommonSetting();
    void LoadRecipe();
    void SaveRecipe();
    QString GetReportFilePath(QString name);

    // convert enum to string // преобразовать перечисление в строку
    QString ConvertTrackIndexToString(TRACK_INDEX value);
    QString ConvertAccountLevelToString(ACCOUNT_LEVEL value);
    BACKEND_RESULT ConvertStringToDefectCode(QString);
    BACKEND_RESULT ConvertBEStringToDefectCode(QString);
    QString ConvertDefectCodeToString(BACKEND_RESULT);

    //
    QString GetRootImagePath(QString path);


    // write log file // запись лог-файла
    void WriteDebugLog(QString title, QString logInfo);

    // debug viewer // средство просмотра отладки
    int m_nMaxDebugLogLineNumber;

    // machine status // состояние машины
    int m_nCurrentMachineStatusIndex;
    QHash<int, quint16> m_hashStatusRegisterValues;
    QHash<int, int> m_hashNumberBitStatusRegisterUsed;
    QHash<int, int> m_hashStatusRegisterIndex;
    QList<int> m_lRegusterStatus;

    // calib camera postion when change the hardware position
    CalibCameraPosData m_strCalibCameraPosData;
};

#endif // CONFIGAPPLICATION_H
