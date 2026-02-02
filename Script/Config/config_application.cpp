#include "config_application.h"
#include <QDebug>
#define VAR_TO_STRING(var) (#var)

static ConfigApplication * p_instance = 0;

ConfigApplication::ConfigApplication()
{

    m_listDocNames = QList<QStringList>{
        QStringList{tr("Camera 1")},
        QStringList{tr("Camera 2")},
        QStringList{tr("Camera 3")},
        };
    m_listInspectInfoState = QStringList{ tr("Inspecting"), tr("Not Connect Backend"), ""};
    m_listBackendFunctions = QStringList{
        "",
        "",
        "",
    };

    m_hashExtendImageName[TRACK_INDEX::CAMERA_1] = "_B";
    m_hashExtendImageName[TRACK_INDEX::CAMERA_2] = "_T";
    m_strImageExtension = ".jpg";

    m_strAppName = "Bottle";
    m_strAppVersion = "V1.0 DL1.0";
    // get app version from file // получить версию приложения из файла
    QString versionFile = QDir::currentPath() + "/AppVersion.txt";

    m_nServerPort = 27025;
    m_strServerName = "BottleServer";

    // cam // кам
    m_nCamNum = 2;
    m_nReviewDoc = 2;
    m_nReviewTrack = 4;
    m_nMaxSingleReviewReloaded = 12;

    // backend // бэкэнд
    m_nBackendPort = 27015;

    // create path config // создайте конфигурацию пути
    m_strConfigPath = QDir::homePath() + "/Bottle-Config";
    m_strAccountPath = m_strConfigPath + "/account.txt";
    m_strConfigFile = m_strConfigPath + "/config.json";
    m_strPLCSettingFileName = m_strConfigPath + "/PLCSetting.json";
    m_strReportPath = m_strConfigPath + "/Report";
    m_strSetoutMoldFileName = "DataSetoutMold";
    m_strReportFileName = "DataReport";
    m_strDBFile = m_strConfigPath + "/BottleInspDB.db";
    m_strCalibCameraPosFile = m_strConfigPath + "/CalibCameraPosition.json";

    m_strConfigRecipePath = m_strConfigPath + "/ConfigRecipe";
    m_strConfigRecipeDefaultName = "Default";
    m_strConfigRecipeName = m_strConfigRecipeDefaultName;
    m_strValidationRecipeName = "CalToolTest";
    m_strVisionParamName = "vision_parameter.vp";
    // m_strConfigCommonName = "config_common.json";
    // m_strConfigCameraName = "config_camera.json";
    m_strSaveImageDefaultPath = m_strConfigPath + "/SavedImages";
    m_strInspectImageName = "InspectImage";
    m_strOperatorImageName = "OperatorImage";
    // statistic // статистика
    m_strStatisticsPath = m_strConfigPath + "/Statistics";
    m_strStatisticsName = "";

    m_strLogPath = m_strConfigPath + "/Log";
    m_strLogName = QDateTime::currentDateTime().toString("yyyyMMdd") + "/" + QDateTime::currentDateTime().toString("hh-mm-ss") + ".txt";

    // license // лицензия
    m_strSoftwareName = "demoinspection";
    m_strLicenseKey = "demoinspection.key";

    // debug log // журнал отладки
    m_nMaxDebugLogLineNumber = 10000;

    // set common setting default value // установить общее значение настройки по умолчанию
    m_commonInfo.tcp_server_info.ip = "192.168.1.100";
    m_commonInfo.tcp_server_info.port = 1000;
    m_commonInfo.saving_image_info.save_dir = m_strSaveImageDefaultPath;

    // machine status // состояние машины
    // priority error, warning, info
    m_nCurrentMachineStatusIndex = -1;
    m_hashNumberBitStatusRegisterUsed[(int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START] = 6;       //1000
    m_hashNumberBitStatusRegisterUsed[(int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START+1] = 16;    //1001
    m_hashNumberBitStatusRegisterUsed[(int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START+2] = 16;    //1002
    m_hashNumberBitStatusRegisterUsed[(int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START+3] = 12;    //1003
    m_hashNumberBitStatusRegisterUsed[(int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS2_START] = 10;     //1025

    m_lRegusterStatus.append((int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START + 2);    //1002
    m_lRegusterStatus.append((int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START + 3);    //1003
    m_lRegusterStatus.append((int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START + 1);    //1001
    m_lRegusterStatus.append((int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS2_START);       //1025
    m_lRegusterStatus.append((int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START);        //1000

    m_hashStatusRegisterIndex[(int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START] = 0;       //1000
    m_hashStatusRegisterIndex[(int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START+1] = 1;    //1001
    m_hashStatusRegisterIndex[(int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START+2] = 2;    //1002
    m_hashStatusRegisterIndex[(int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START+3] = 3;    //1003
    m_hashStatusRegisterIndex[(int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS2_START] = 4;      //1025


    // app status // статус приложения
    m_appStatus = APP_STATUS::STOP;

    CreateFolderConfigApplication();
    ReadAppSetting();
    ReadPLCSetting();
    m_strCalibCameraPosData.loadFromFile(m_strCalibCameraPosFile);
    LoadRecipe();
}

ConfigApplication::~ConfigApplication()
{
    this->deleteLater();
}
ConfigApplication * ConfigApplication::instance()
{
    if(!p_instance) p_instance = new ConfigApplication();
    return p_instance;
}


void ConfigApplication::CreateFolderConfigApplication()
{
    if(!QDir(m_strConfigPath).exists())
    {
        QDir().mkdir(m_strConfigPath);
    }

    CreateFolderSaveImage(m_strSaveImageDefaultPath);

    CreateFolderSaveImage(m_commonInfo.saving_image_info.save_dir);

    if(!QDir(m_strLogPath).exists())
    {
        QDir().mkdir(m_strLogPath);
    }
    if(!QDir(m_strReportPath).exists())
    {
        QDir().mkdir(m_strReportPath);
    }
    if(!QDir(m_strLogPath + "/" + QDateTime::currentDateTime().toString("yyyyMMdd")).exists())
    {
        QDir().mkdir(m_strLogPath + "/" + QDateTime::currentDateTime().toString("yyyyMMdd"));
    }
    if(!QDir(m_strConfigRecipePath).exists())
    {
        QDir().mkdir(m_strConfigRecipePath);
    }
    if(!QDir(m_strStatisticsPath).exists())
    {
        QDir().mkdir(m_strStatisticsPath);
    }
    if(!QDir(m_strStatisticsPath + "/" + QDateTime::currentDateTime().toString("yyyyMMdd")).exists())
    {
        QDir().mkdir(m_strStatisticsPath + "/" + QDateTime::currentDateTime().toString("yyyyMMdd"));
    }
}

void ConfigApplication::CreateFolderSaveImage(QString path)
{
    if(!QDir(path).exists())
    {
        QDir().mkdir(path);
    }
    if(!QDir(path + "/" + m_strInspectImageName).exists())
    {
        QDir().mkdir(path + "/" + m_strInspectImageName);
    }
    if(!QDir(path + "/" + m_strOperatorImageName).exists())
    {
        QDir().mkdir(path + "/" + m_strOperatorImageName);
    }
}

void ConfigApplication::ReadAppSetting()
{
    try{
        QFile file(m_strConfigFile);
        if(!file.exists())
        {
            WriteAppSetting();
            return;
        }

        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << QString("fail to open the file: %1, %2, %3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
            return;
        }
        QByteArray allData = file.readAll();
        file.close();
        if(allData == "")
        {
            WriteAppSetting();
            return;
        }
        QJsonParseError json_error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(allData, &json_error);
        QJsonObject rootObj = jsonDoc.object();

        QJsonValue recipeSetting = rootObj.value("Recipe");
        m_strConfigRecipeName = recipeSetting.toVariant().toHash().value("Recipe Name").toString();

        QJsonValue cameraSetting = rootObj.value("Camera");
        for (int i = 0; i < m_nCamNum; ++i) {
            m_commonInfo.appSetting.cameraConfig[(TRACK_INDEX)i].resolution = cameraSetting.toVariant().toHash().value(QString("Camera %1 Resolution").arg(i+1)).toDouble();
            m_commonInfo.appSetting.cameraConfig[(TRACK_INDEX)i].oldLoadImagePath = cameraSetting.toVariant().toHash().value(QString("Camera %1 Load Image Path").arg(i + 1)).toString();
            m_commonInfo.appSetting.cameraConfig[(TRACK_INDEX)i].serial = cameraSetting.toVariant().toHash().contains(QString("Camera %1 Serial Numer").arg(i + 1)) ? cameraSetting.toVariant().toHash().value(QString("Camera %1 Serial Numer").arg(i + 1)).toString() : m_commonInfo.appSetting.cameraConfig[(TRACK_INDEX)i].serial;
        }

        // machine name, distance, weight unit // название машины, расстояние, единица измерения веса
        m_commonInfo.appSetting.m_strMachineName = rootObj.contains("Machine Name") ? rootObj.value("Machine Name").toString() : m_commonInfo.appSetting.m_strMachineName;
        m_commonInfo.appSetting.m_nDistanceUnit = rootObj.contains("Distance Unit") ? rootObj.value("Distance Unit").toInt() : m_commonInfo.appSetting.m_nDistanceUnit;
        m_commonInfo.appSetting.m_nWeightUnit = rootObj.contains("Weight Unit") ? rootObj.value("Weight Unit").toInt() : m_commonInfo.appSetting.m_nWeightUnit;

        // for current report from 0-3 max 4 report
        m_commonInfo.appSetting.m_nCurrentReport = rootObj.contains("Current Report") ? rootObj.value("Current Report").toInt() : m_commonInfo.appSetting.m_nCurrentReport;


        WriteAppSetting();
    }
    catch (const std::exception& e)
    {
        qDebug() << "Read App Setting Error: " << QString::fromStdString(e.what());
    }

}

void ConfigApplication::WriteAppSetting()
{
    try {
        QFile file(m_strConfigFile);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << QString("fail to open the file: %1, %2, %3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
            return;
        }
        QJsonObject rootObj;

        QJsonObject recipeSetting;
        recipeSetting.insert("Recipe Name", QString::fromUtf8(m_strConfigRecipeName.toUtf8()));
        rootObj.insert("Recipe", recipeSetting);

        QJsonObject cameraSetting;
        for (int i = 0; i < m_nCamNum; ++i) {
            cameraSetting.insert(QString("Camera %1 Resolution").arg(i+1), m_commonInfo.appSetting.cameraConfig[(TRACK_INDEX)i].resolution);
            cameraSetting.insert(QString("Camera %1 Serial Numer").arg(i + 1), m_commonInfo.appSetting.cameraConfig[(TRACK_INDEX)i].serial);
            cameraSetting.insert(QString("Camera %1 Load Image Path").arg(i + 1), m_commonInfo.appSetting.cameraConfig[(TRACK_INDEX)i].oldLoadImagePath);
        }
        rootObj.insert("Camera", cameraSetting);

        rootObj.insert("Machine Name", m_commonInfo.appSetting.m_strMachineName);
        rootObj.insert("Distance Unit", m_commonInfo.appSetting.m_nDistanceUnit);
        rootObj.insert("Weight Unit", m_commonInfo.appSetting.m_nWeightUnit);
        rootObj.insert("Current Report", m_commonInfo.appSetting.m_nCurrentReport);

        QJsonDocument jsonDoc;
        jsonDoc.setObject(rootObj);
        QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Indented);
        QTextStream out(&file);
        out.setCodec("UTF-8");
        out << byteArray;
        file.close();
    }
    catch (const std::exception& e)
    {
        qDebug() << "Write App Setting Error: " << QString::fromStdString(e.what());
    }
}

// void ConfigApplication::ReadCommonSetting()
// {
//     QString path = m_strConfigRecipePath + "/" +
//                    m_strConfigRecipeName + "/" + m_strConfigCommonName;
//     try{
//         QFile file(path);
//         if(!file.exists())
//         {
//             WriteCommonSetting();
//             return;
//         }

//         if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//         {
//             qDebug() << QString("fail to open the file: %1, %2, %3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
//             return;
//         }
//         QByteArray allData = file.readAll();
//         file.close();
//         if(allData == "")
//         {
//             WriteCommonSetting();
//             return;
//         }

//         QJsonParseError json_error;
//         QJsonDocument jsonDoc = QJsonDocument::fromJson(allData, &json_error);
//         QJsonObject rootObj = jsonDoc.object();

//         QJsonValue tcpServer = rootObj.value("TCP Server");
//         m_commonInfo.tcp_server_info.ip = tcpServer.toVariant().toHash().value("Ip").toString();
//         m_commonInfo.tcp_server_info.port = tcpServer.toVariant().toHash().value("Port").toInt();

//         QJsonValue systemIPSetting = rootObj.value("System IP Settings");
//         if (!systemIPSetting.isUndefined())
//         {
//             m_commonInfo.systemIPSetting.ip = systemIPSetting.toVariant().toHash().value("IP Address").toString();
//             m_commonInfo.systemIPSetting.subnet = systemIPSetting.toVariant().toHash().value("Subnet").toString();
//             m_commonInfo.systemIPSetting.gateway = systemIPSetting.toVariant().toHash().value("Gateway").toString();
//             m_commonInfo.systemIPSetting.isUseDHCP = systemIPSetting.toVariant().toHash().value("Use DHCP").toBool();
//         }





//         QJsonValue saveVideo = rootObj.value("Saving Image");
//         m_commonInfo.saving_image_info.save_dir = saveVideo.toVariant().toHash().value("Dir").toString();


//         // check exist and initial value for variable // проверьте наличие и Исходное значение для переменной
//         if(!QDir(m_commonInfo.saving_image_info.save_dir).exists())
//         {
//             m_commonInfo.saving_image_info.save_dir = m_strSaveImageDefaultPath;
//         }
//         CreateFolderSaveImage(m_commonInfo.saving_image_info.save_dir);
//         WriteCommonSetting();
//     }
//     catch (const std::exception& e)
//     {
//         qDebug() << "Read Common Setting Error: " << QString::fromStdString(e.what());
//     }
// }

// void ConfigApplication::ReadCameraSetting()
// {
   

// }

void ConfigApplication::ReadPLCSetting()
{
    QFile file(m_strPLCSettingFileName);
    if (!file.exists())
    {
        // Store default setting // Сохранить настройки по умолчанию
        m_commonInfo.plcSetting.saveToFile(m_strPLCSettingFileName);
        return;
    }

    m_commonInfo.plcSetting.loadFromFile(m_strPLCSettingFileName);

}

// void ConfigApplication::WriteCommonSetting()
// {
//     QString path = m_strConfigRecipePath + "/" +
//                    m_strConfigRecipeName + "/" + m_strConfigCommonName;
//     try {
//         QFile file(path);
//         if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
//         {
//             qDebug() << QString("fail to open the file: %1, %2, %3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
//             return;
//         }
//         QJsonObject rootObj;

//         QJsonObject tcpServer;
//         tcpServer.insert("Ip", m_commonInfo.tcp_server_info.ip);
//         tcpServer.insert("Port", m_commonInfo.tcp_server_info.port);
//         rootObj.insert("TCP Server", tcpServer);

//         QJsonObject systemIPSetting;
//         systemIPSetting.insert("IP Address", m_commonInfo.systemIPSetting.ip);
//         systemIPSetting.insert("Subnet", m_commonInfo.systemIPSetting.subnet);
//         systemIPSetting.insert("Gateway", m_commonInfo.systemIPSetting.gateway);
//         systemIPSetting.insert("Use DHCP", m_commonInfo.systemIPSetting.isUseDHCP);
//         rootObj.insert("System IP Settings", systemIPSetting);


//         QJsonObject saveImage;
//         saveImage.insert("Dir", m_commonInfo.saving_image_info.save_dir);
//         rootObj.insert("Saving Image", saveImage);

//         QJsonDocument jsonDoc;
//         jsonDoc.setObject(rootObj);
//         QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Indented);
//         QTextStream out(&file);
//         out << byteArray;
//         file.close();
//     }
//     catch (const std::exception& e)
//     {
//         qDebug() << "Write Camera Setting Error: " << QString::fromStdString(e.what());
//     }
// }

void ConfigApplication::LoadRecipe()
{
    QString defaultPath = m_strConfigRecipePath + "/" + m_strConfigRecipeName;
    if(!QDir(defaultPath).exists())
    {
        QDir().mkdir(defaultPath);
    }
    // ReadCommonSetting();
    // for(int i = 0; i < m_nCamNum; i++)
    // {
    //     ReadSingleCameraSetting(TRACK_INDEX(i));
    // }
}

void ConfigApplication::SaveRecipe()
{
    // WriteCommonSetting();
    // for(int i = 0; i < m_nCamNum; i++)
    // {
    //     WriteSingleCameraSetting(TRACK_INDEX(i));
    // }
}

QString ConfigApplication::GetReportFilePath(QString name)
{
    return QString("%1/%2%3.json")
        .arg(m_strReportPath)
        .arg(name)
        .arg(m_commonInfo.appSetting.m_nCurrentReport + 1);
}


QString ConfigApplication::ConvertTrackIndexToString(TRACK_INDEX value)
{
    if(value == TRACK_INDEX::CAMERA_1)
    {
        return tr("CAMERA 1");
    }
    else if(value == TRACK_INDEX::CAMERA_2)
    {
        return tr("CAMERA 2");
    }
    else
    {
        return tr("N/A");
    }
}

QString ConfigApplication::ConvertAccountLevelToString(ACCOUNT_LEVEL value)
{
    if(value == ACCOUNT_LEVEL::ADMINISTRATOR)
    {
        return tr("Administrator");
    }
    else if(value == ACCOUNT_LEVEL::ENGINEER)
    {
        return tr("Engineer");
    }
    else if(value == ACCOUNT_LEVEL::OPERATOR)
    {
        return tr("Operator");
    }
    else
    {
        return tr("None");
    }
}

BACKEND_RESULT ConfigApplication::ConvertStringToDefectCode(QString value)
{
    if(value == "Process Error")
    {
        return BACKEND_RESULT::PROCESS_ERROR;
    }
    else if(value == "Pass")
    {
        return BACKEND_RESULT::PASS;
    }
    else if(value == "Height")
    {
        return BACKEND_RESULT::HEIGHT;
    }
    else if(value == "Weight")
    {
        return BACKEND_RESULT::WEIGHT;
    }
    else if(value == "Non-round Shape")
    {
        return BACKEND_RESULT::NON_ROUND_SHAPE;
    }
    else if(value == "BodyR Dimension")
    {
        return BACKEND_RESULT::BODYR_DIMENSION;
    }
    else if(value == "Lean")
    {
        return BACKEND_RESULT::LEAN;
    }
    else if(value == "Tilt")
    {
        return BACKEND_RESULT::TILT;
    }
    else if(value == "F Dimension")
    {
        return BACKEND_RESULT::F_DIMENSION;
    }
    else if(value == "A Dimension")
    {
        return BACKEND_RESULT::A_DIMENSION;
    }
    else if(value == "T Dimension")
    {
        return BACKEND_RESULT::T_DIMENSION;
    }
    else if(value == "E Dimension")
    {
        return BACKEND_RESULT::E_DIMENSION;
    }
    else if(value == "D Dimension")
    {
        return BACKEND_RESULT::D_DIMENSION;
    }
    else if(value == "B Dimension")
    {
        return BACKEND_RESULT::B_DIMENSION;
    }
    else if(value == "S Dimension")
    {
        return BACKEND_RESULT::S_DIMENSION;
    }
    else if(value == "H Dimension")
    {
        return BACKEND_RESULT::H_DIMENSION;
    }
    else if(value == "LugT Dimension")
    {
        return BACKEND_RESULT::LUGT_DIMENSION;
    }
    else if(value == "LugT1 Dimension")
    {
        return BACKEND_RESULT::LUGT1_DIMENSION;
    }
    else if(value == "D Angle")
    {
        return BACKEND_RESULT::D_ANGLE_DIMENSION;
    }
    else if(value == "Flange Dimension")
    {
        return BACKEND_RESULT::FLANGE_DIMENSION;
    }
    else if(value == "Knockout Dimension")
    {
        return BACKEND_RESULT::KNOCKOUT_DIMENSION;
    }
    else if(value == "Pushup Dimension")
    {
        return BACKEND_RESULT::PUSHUP_DIMENSION;
    }
    else if(value == "Inside Neck")
    {
        return BACKEND_RESULT::INSIDE_NECK;
    }
    else if(value == "Wall Thickness")
    {
        return BACKEND_RESULT::WALL_THICKNESS;
    }
    else if(value == "Code Number")
    {
        return BACKEND_RESULT::CODE_NUMBER;
    }
    // else if(value == "Seam")
    // {
    //     return BACKEND_RESULT::SEAM;
    // }

    return BACKEND_RESULT::PASS;
}

BACKEND_RESULT ConfigApplication::ConvertBEStringToDefectCode(QString value)
{
    if(value == VAR_TO_STRING(PROCESS_ERROR))
    {
        return BACKEND_RESULT::PROCESS_ERROR;
    }
    else if(value == VAR_TO_STRING(PASS))
    {
        return BACKEND_RESULT::PASS;
    }
    else if(value == VAR_TO_STRING(HEIGHT))
    {
        return BACKEND_RESULT::HEIGHT;
    }
    else if(value == VAR_TO_STRING(WEIGHT))
    {
        return BACKEND_RESULT::WEIGHT;
    }
    else if(value == VAR_TO_STRING(NON_ROUND_SHAPE))
    {
        return BACKEND_RESULT::NON_ROUND_SHAPE;
    }
    else if(value == VAR_TO_STRING(BODYR_DIMENSION))
    {
        return BACKEND_RESULT::BODYR_DIMENSION;
    }
    else if(value == VAR_TO_STRING(LEAN))
    {
        return BACKEND_RESULT::LEAN;
    }
    else if(value == VAR_TO_STRING(TILT))
    {
        return BACKEND_RESULT::TILT;
    }
    else if(value == VAR_TO_STRING(F_DIMENSION))
    {
        return BACKEND_RESULT::F_DIMENSION;
    }
    else if(value == VAR_TO_STRING(A_DIMENSION))
    {
        return BACKEND_RESULT::A_DIMENSION;
    }
    else if(value == VAR_TO_STRING(T_DIMENSION))
    {
        return BACKEND_RESULT::T_DIMENSION;
    }
    else if(value == VAR_TO_STRING(E_DIMENSION))
    {
        return BACKEND_RESULT::E_DIMENSION;
    }
    else if(value == VAR_TO_STRING(D_DIMENSION))
    {
        return BACKEND_RESULT::D_DIMENSION;
    }
    else if(value == VAR_TO_STRING(B_DIMENSION))
    {
        return BACKEND_RESULT::B_DIMENSION;
    }
    else if(value == VAR_TO_STRING(S_DIMENSION))
    {
        return BACKEND_RESULT::S_DIMENSION;
    }
    else if(value == VAR_TO_STRING(H_DIMENSION))
    {
        return BACKEND_RESULT::H_DIMENSION;
    }
    else if(value == VAR_TO_STRING(LUGT_DIMENSION))
    {
        return BACKEND_RESULT::LUGT_DIMENSION;
    }
    else if(value == VAR_TO_STRING(LUGT1_DIMENSION))
    {
        return BACKEND_RESULT::LUGT1_DIMENSION;
    }
    else if(value == VAR_TO_STRING(D_ANGLE_DIMENSION))
    {
        return BACKEND_RESULT::D_ANGLE_DIMENSION;
    }
    else if(value == VAR_TO_STRING(FLANGE_DIMENSION))
    {
        return BACKEND_RESULT::FLANGE_DIMENSION;
    }
    else if(value == VAR_TO_STRING(KNOCKOUT_DIMENSION))
    {
        return BACKEND_RESULT::KNOCKOUT_DIMENSION;
    }
    else if(value == VAR_TO_STRING(PUSHUP_DIMENSION))
    {
        return BACKEND_RESULT::PUSHUP_DIMENSION;
    }
    else if(value == VAR_TO_STRING(INSIDE_NECK))
    {
        return BACKEND_RESULT::INSIDE_NECK;
    }
    else if(value == VAR_TO_STRING(WALL_THICKNESS))
    {
        return BACKEND_RESULT::WALL_THICKNESS;
    }
    else if(value == VAR_TO_STRING(CODE_NUMBER))
    {
        return BACKEND_RESULT::CODE_NUMBER;
    }
    // else if(value == VAR_TO_STRING(SEAM))
    // {
    //     return BACKEND_RESULT::SEAM;
    // }

    return BACKEND_RESULT::PASS;
}

QString ConfigApplication::ConvertDefectCodeToString(BACKEND_RESULT value)
{
    if(value == BACKEND_RESULT::PROCESS_ERROR)
    {
        return "Process Error";
    }
    else if(value == BACKEND_RESULT::PASS)
    {
        return "Pass";
    }
    else if(value == BACKEND_RESULT::HEIGHT)
    {
        return "Height";
    }
    else if(value == BACKEND_RESULT::WEIGHT)
    {
        return "Weight";
    }
    else if(value == BACKEND_RESULT::NON_ROUND_SHAPE)
    {
        return "Non-round Shape";
    }
    else if(value == BACKEND_RESULT::BODYR_DIMENSION)
    {
        return "BodyR Dimension";
    }
    else if(value == BACKEND_RESULT::LEAN)
    {
        return "Lean";
    }
    else if(value == BACKEND_RESULT::TILT)
    {
        return "Tilt";
    }
    else if(value == BACKEND_RESULT::F_DIMENSION)
    {
        return "F Dimension";
    }
    else if(value == BACKEND_RESULT::A_DIMENSION)
    {
        return "A Dimension";
    }
    else if(value == BACKEND_RESULT::T_DIMENSION)
    {
        return "T Dimension";
    }
    else if(value == BACKEND_RESULT::E_DIMENSION)
    {
        return "E Dimension";
    }
    else if(value == BACKEND_RESULT::D_DIMENSION)
    {
        return "D Dimension";
    }
    else if(value == BACKEND_RESULT::B_DIMENSION)
    {
        return "B Dimension";
    }
    else if(value == BACKEND_RESULT::S_DIMENSION)
    {
        return "S Dimension";
    }
    else if(value == BACKEND_RESULT::H_DIMENSION)
    {
        return "H Dimension";
    }
    else if(value == BACKEND_RESULT::LUGT_DIMENSION)
    {
        return "LugT Dimension";
    }
    else if(value == BACKEND_RESULT::LUGT1_DIMENSION)
    {
        return "LugT1 Dimension";
    }
    else if(value == BACKEND_RESULT::D_ANGLE_DIMENSION)
    {
        return "D Angle";
    }
    else if(value == BACKEND_RESULT::FLANGE_DIMENSION)
    {
        return "Flange Dimension";
    }
    else if(value == BACKEND_RESULT::KNOCKOUT_DIMENSION)
    {
        return "Knockout Dimension";
    }
    else if(value == BACKEND_RESULT::PUSHUP_DIMENSION)
    {
        return "Pushup Dimension";
    }
    else if(value == BACKEND_RESULT::INSIDE_NECK)
    {
        return "Inside Neck";
    }
    else if(value == BACKEND_RESULT::WALL_THICKNESS)
    {
        return "Wall Thickness";
    }
    else if(value == BACKEND_RESULT::CODE_NUMBER)
    {
        return "Code Number";
    }
    // else if(value == BACKEND_RESULT::SEAM)
    // {
    //     return "Seam";
    // }
    return "";
}

QString ConfigApplication::GetRootImagePath(QString path)
{
    path.chop(6);
    return path;
}

void ConfigApplication::WriteDebugLog(QString title, QString logInfo)
{
    // create new folder if new day and create new file if go next hour // создайте новую папку, если новый день, и создайте новый файл, если следующий час
    QString currentDay = QDateTime::currentDateTime().toString("yyyyMMdd");
    if(!QDir(m_strLogPath + "/" + currentDay).exists())
    {
        QDir().mkdir(m_strLogPath + "/" + currentDay);
    }
    QString logNameTemp = currentDay + "/" + QDateTime::currentDateTime().toString("hh-mm-ss") + ".txt";
    if(m_strLogName.mid(0, 11) != logNameTemp.mid(0, 11))
    {
        m_strLogName = logNameTemp;
    }

    QString time = QDateTime::currentDateTime().toString("hh:mm:ss:zzz");
    QFile file(m_strLogPath + "/" + m_strLogName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QTextStream stream( &file );
        stream << QString(time + "      [" + title + "]     " + logInfo) + "\n";
    }
    file.close();
}


