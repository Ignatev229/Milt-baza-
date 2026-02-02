#include "main_vm.h"

#include "Model/modbus_list_model.h"
#include "Script/Modbus/MBcommunication.h"
#include "Script/Modbus/MBdiagnosticitems.h"
#include "Script/Hardware/Camera/CameraDLL.h"
#include "Script/Modbus/MBDLL.h"
#include "Script/Modbus/MBdiagnosticitems.h"
#include "Model/limit_table_model.h"

MainVM::MainVM()
    : m_pMainApp(nullptr)
    , m_pMainQMLEngine(nullptr)
    , m_bIsAppClosing(false)
{

}

MainVM::~MainVM()
{

    ConfigApplication::instance()->WriteDebugLog("Application", "Application End");

    //EventLogVM::instance()->AddEventLog("Close Application");
    delete this->masterApp;
}

void MainVM::Init(QQmlApplicationEngine &appEngine, QApplication* appMain)
{
    QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));

    setHomePath(ConfigApplication::instance()->m_strConfigPath);

    m_pMainApp = appMain;
    m_pMainQMLEngine = &appEngine;

    // Default rusia language
    switchLanguage(1);

    ConfigApplication::instance()->WriteDebugLog("Application", "Application Start");

    m_modbusDiagnosticDataContext.reset(new MBDiagnosticItems());

    //Register meta variable custom //Зарегистрировать пользовательскую мета-переменную
    // qRegisterMetaType<Mat>("Mat");
    qRegisterMetaType<QObject*>("QObject*");
    qRegisterMetaType<QWidget*>("QWidget*");
    qRegisterMetaType<QImage*>("QImage*");

    qRegisterMetaType<TrackVM*>("TrackVM*");
    qRegisterMetaType<ImageViewVM*>("ImageViewVM*");
    qRegisterMetaType<ImageModel*>("ImageModel*");
    qRegisterMetaType<MainHomeVM*>("MainHomeVM*");
    qRegisterMetaType<ReviewVM*>("ReviewVM*");
    qRegisterMetaType<SingleReviewVM*>("SingleReviewVM*");
    qRegisterMetaType<MainHomeVM*>("MainHomeVM*");

    qRegisterMetaType<TRACK_INDEX>("TRACK_INDEX");
    qRegisterMetaType<CAMERA_TYPE>("CAMERA_TYPE");
    qRegisterMetaType<CAMERA_PIXEL_FORMAT>("CAMERA_PIXEL_FORMAT");
    qRegisterMetaType<CameraSettingData>("CameraSettingData");
    qRegisterMetaType<CommonSettingData>("CommonSettingData");
    qRegisterMetaType<ACCOUNT_LEVEL>("ACCOUNT_LEVEL");
    qRegisterMetaType<InputBackendInfo>("InputBackendInfo&");
    qRegisterMetaType<InputBackendInfo>("InputBackendInfo");
    qRegisterMetaType<OutputBackendInfo>("OutputBackendInfo&");
    qRegisterMetaType<OutputBackendInfo>("OutputBackendInfo");
    qRegisterMetaType<InspectionInfoItem>("InspectionInfoItem");
    qRegisterMetaType<InspectionInfoChildItem>("InspectionInfoChildItem");
    qRegisterMetaType<QList<InspectionInfoChildItem>>("QList<InspectionInfoChildItem>");
    qRegisterMetaType<BACKEND_FUNCTION>("BACKEND_FUNCTION");

    // Register type custom //  Регистр пользовательского типа
    qmlRegisterType<ImageWriter>("ImageWriter", 1, 0, "ImageWriter");
    // qmlRegisterType<InspectionInfoItem>("InspectionInfoItemData", 1, 0, "InspectionInfoItem");
    // qmlRegisterType<InspectionInfoChildItem>("InspectionInfoChildItemData", 1, 0, "InspectionInfoChildItem");


    qmlRegisterSingletonType( QUrl("qrc:/ConfigView.qml"), "ConfigView", 1, 0, "ConfigView" );

    //
    qmlRegisterType<ListStringModel>("DataListString", 1, 0, "ListStringModel");
    qmlRegisterUncreatableType<ListStringVM>("DataListString", 1, 0, "ListStringVM", QStringLiteral("ListString should not be created in QML"));

    //Modbus
    qmlRegisterType<modbus_list_model>("BI.modbus.Modbus_list_model", 1, 0, "Modbus_list_model");
    qmlRegisterUncreatableType<MBItemList>("MBItemList", 1, 0, "MBItemList",
                                           QStringLiteral("MBItemList should not be created in QML"));
    qmlRegisterSingletonInstance<MBItemList>("BI.modbus.MBDiagnosticDataContext", 1, 0, "MBDiagnosticDataContext", m_modbusDiagnosticDataContext.data());

    qmlRegisterType<MBDiagnosticItems>("BI.modbus.MBDiagnosticDataContext", 1, 0, "DiagnosticItemStatus");

    qmlRegisterType<limit_table_model>("BI.tableData.LimitTableData", 1, 0, "LimitTableData");


    // Camera dll init // Инициализация dll камеры
    bool isSuccessLoadDLLCam = true;
    bool isSuccessLoadDLLMT = true;

#ifdef Q_OS_WIN
    isSuccessLoadDLLCam = CameraDLLControl::RegisterDLL("CC.dll");
#elif defined(Q_OS_LINUX)
    isSuccessLoadDLLCam = CameraDLLControl::RegisterDLL("libCC.so");
#endif

    // if register dll, will create device object // если зарегистрировать dll, то будет создан объект устройства
    if(isSuccessLoadDLLCam)
    {
        ConfigApplication::instance()->WriteDebugLog("DLL", "Register DLL Camera Succeed");
        qDebug() << "Register DLL Camera Succeed";
    }

// MB dll init
#ifdef Q_OS_WIN
    isSuccessLoadDLLMT = MBDLLControl::RegisterDLL("MT.dll");
#elif defined(Q_OS_LINUX)
    isSuccessLoadDLLMT = MBDLLControl::RegisterDLL("libMT.so");
#endif

    // if register dll, will create device object // если зарегистрировать dll, то будет создан объект устройства
    if (isSuccessLoadDLLMT)
    {
        ConfigApplication::instance()->WriteDebugLog("DLL", "Register DLL Modbus Succeed");
        qDebug() << "Register DLL Modbus Succeed";
    }

    // create master app // создать главное приложение
    masterApp = new MasterApp(appEngine);
    appEngine.rootContext()->setContextProperty(QStringLiteral("masterApp"), masterApp);

    //create connect when load dll success // создать подключение при успешной загрузке  dll
    if (isSuccessLoadDLLMT)
    {
     

        connect(MBCommunication::GetInstance(), &MBCommunication::populateDataSignal, m_modbusDiagnosticDataContext.data(), &MBDiagnosticItems::StartToUpdateData);

        connect(MBCommunication::GetInstance(), &MBCommunication::populateDataSignal, masterApp, &MasterApp::StartToUpdateMTData);

        connect(this, &MainVM::propagateChangeLanguageSignal,
                m_modbusDiagnosticDataContext.data(), &MBItemList::StartToChangeLanguage);


    }

}

QString MainVM::homePath()
{
    return _homePath;
}

void MainVM::setHomePath(QString value)
{
    if(_homePath != value)
    {
        _homePath = value;
        emit homePathChanged();
    }
}

void MainVM::switchLanguage(int languageSelected)
{
    if(m_pMainApp == nullptr) return;

    // set default to -1 so at first time, it can translate // установите значение по умолчанию равным -1, чтобы в первый раз оно могло переводить
    static int languageSelect = -1;

    // avoid loading multiple time for same language // избегайте многократной загрузки для одного и того же языка
    if (languageSelect == languageSelected) return;

    // directory will be .exe/translations //  Директория будет с расширением .exe/переводы
    QString translationPath = QCoreApplication::applicationDirPath() + "/translations";

    if(!m_translator.isEmpty())
        m_pMainApp->removeTranslator(&m_translator);

    QString appName = QCoreApplication::applicationName();
    QLocale country = QLocale::English;

    // assume 1 is russian // предположим, что 1 русский
    if(languageSelected == 1)
    {
        country = QLocale::Russian;
    }

    if (m_translator.load(country, QLatin1String("BottleInsp"), QLatin1String("_"), translationPath)) {
        m_pMainApp->installTranslator(&m_translator);
    }

    m_pMainQMLEngine->retranslate();

    emit propagateChangeLanguageSignal();

    languageSelect = languageSelected;
    qDebug() << "[MainVM]" << "switchLanguage" << country << appName << translationPath;
}


void MainVM::allComponentLoaded()
{

    qDebug() << "[MainVM]" << "All Component Loaded";
    ReportVM::GetInstance()->Init(masterApp);

    qDebug() << "[MainVM]" << "Modbus establish connection";
    MBCommunication::GetInstance()->Start();

    RecipeManagementVM::GetInstance()->InitRecipe();
    // masterApp->loadRecipe_RecipeManagementVM_Slots();

    masterApp->scopedMainHomeVM.data()->UpdateResolutionToUI();

    //
    masterApp->scopedSystemSettingVM.data()->Init();

    // update report table // обновить таблицу отчетов
    emit ReportVM::GetInstance()->updateVisionParamNumber_Signal(EditRecipeVM::GetInstance()->bodyRInspect.numberDimension,
                                                                 EditRecipeVM::GetInstance()->noneRoundShapeInspect.numberDimension,
                                                                 EditRecipeVM::GetInstance()->noneRoundShapeInspect.shape);
    emit ReportVM::GetInstance()->updateCurrentReport(ConfigApplication::instance()->m_commonInfo.appSetting.m_nCurrentReport);

    // update history tab
    emit HistoryVM::GetInstance()->updateVisionParamNumber_Signal(EditRecipeVM::GetInstance()->bodyRInspect.numberDimension,
                                                                 EditRecipeVM::GetInstance()->noneRoundShapeInspect.numberDimension,
                                                                 EditRecipeVM::GetInstance()->noneRoundShapeInspect.shape);
    // update validation tab
    emit ValidationVM::GetInstance()->updateVisionParamNumber_Signal(EditRecipeVM::GetInstance()->bodyRInspect.numberDimension);
    ValidationVM::GetInstance()->LoadOldData();

    // update calibration tab
    CalibTableVM::GetInstance()->Init(masterApp);

    // // setout // // установка
    // masterApp->scopedSetoutVM.data()->InitSetoutMoldNumber();
    // masterApp->StartToUpdateMachineStatusData();

}


void MainVM::appClose()
{
    m_bIsAppClosing = true;
}
