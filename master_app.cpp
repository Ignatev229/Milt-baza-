#include "master_app.h"
#include "main_vm.h"
#include "Script/Utility/AppCommandThread.h"



MasterApp::MasterApp(QQmlApplicationEngine &appEngine, QObject *parent)
    : QObject{parent}
    , m_pCommandThread(nullptr)
{
    // create track // создать трек
    for(int i = 0; i < ConfigApplication::instance()->m_nCamNum; i++)
    {
        TrackVM *track = new TrackVM(appEngine, (TRACK_INDEX)i, ConfigApplication::instance()->m_listDocNames.at(i));
        this->hashTrackVM.insert((TRACK_INDEX)i, track);
    }

    // Init Sql
    SQLManagement::GetInstance()->Init();

    // tab control // управление вкладками
    scopedTabControlVM.reset(new TabControlVM());
    appEngine.rootContext()->setContextProperty(QStringLiteral("tabControlVM"), scopedTabControlVM.data());

    scopedLoginVM.reset(new LoginVM());
    appEngine.rootContext()->setContextProperty(QStringLiteral("loginVM"), scopedLoginVM.data());

    // create home //создать Домашний
    scopedMainHomeVM.reset(new MainHomeVM(appEngine, hashTrackVM, this));
    appEngine.rootContext()->setContextProperty(QStringLiteral("mainHomeVM"), scopedMainHomeVM.data());

    // System Setting // Настройка системы
    scopedSystemSettingVM.reset(new SystemSettingVM());
    appEngine.rootContext()->setContextProperty(QStringLiteral("systemSettingVM"), scopedSystemSettingVM.data());

    // Review // Обзор
    scopedReviewVM.reset(new ReviewVM());
    appEngine.rootContext()->setContextProperty(QStringLiteral("reviewVM"), scopedReviewVM.data());

    // Feeder and pushers // Актуаторы
    scopedFeederAndPushersVM.reset(new FeederAndPushersVM());
    appEngine.rootContext()->setContextProperty(QStringLiteral("feederAndPushersVM"), scopedFeederAndPushersVM.data());

    // Table //  Стол
    scopedTableVM.reset(new TableVM());
    appEngine.rootContext()->setContextProperty(QStringLiteral("tableVM"), scopedTableVM.data());

    // setout // установка
    SetoutVM::GetInstance()->Init(appEngine, this);
    appEngine.rootContext()->setContextProperty(QStringLiteral("setoutVM"), SetoutVM::GetInstance());

    // container // контейнер
    scopedContainerVM.reset(new ContainerVM());
    appEngine.rootContext()->setContextProperty(QStringLiteral("containerVM"), scopedContainerVM.data());

    // system // система
    scopedSystemVM.reset(new SystemVM());
    appEngine.rootContext()->setContextProperty(QStringLiteral("systemVM"), scopedSystemVM.data());

    // validation // валидация
    ValidationVM::GetInstance()->Init(this);
    appEngine.rootContext()->setContextProperty(QStringLiteral("validationVM"), ValidationVM::GetInstance());

    // report // отчет
    // scopedReportVM.reset(new ReportVM());
    appEngine.rootContext()->setContextProperty(QStringLiteral("reportVM"), ReportVM::GetInstance());

    // recipe // рецепт
    // scopedRecipeManagementVM.reset(new RecipeManagementVM(appEngine));
    RecipeManagementVM::GetInstance()->Init(appEngine);
    appEngine.rootContext()->setContextProperty(QStringLiteral("recipeManagementVM"), RecipeManagementVM::GetInstance());

    // calib // калибр
    // scopedCalibTableVM.reset(new CalibTableVM());
    appEngine.rootContext()->setContextProperty(QStringLiteral("calibTableVM"), CalibTableVM::GetInstance());

    // save image thread // сохранить поток изображений
    scopedSaveImageThread.reset(new SaveImageThread());
    scopedSaveImageThread.data()->start();

    // dialog //  Диалог
    appEngine.rootContext()->setContextProperty(QStringLiteral("dialogVM"), DialogVM::instance());

    // plc communication log // журнал связи с плк
    appEngine.rootContext()->setContextProperty(QStringLiteral("plcCommunicationLogVM"), PLCCommunicationLogVM::GetInstance());

    // limit tab // вкладка Лимит
    // scopedLimitTabVM.reset(new LimitTabVM);
    appEngine.rootContext()->setContextProperty(QStringLiteral("limitTabVM"), LimitTabVM::GetInstance());

    // history tab
    HistoryVM::GetInstance()->Init(this);
    appEngine.rootContext()->setContextProperty(QStringLiteral("historyVM"), HistoryVM::GetInstance());

    // Correction tab
    CorrectionVM::GetInstance()->Init(this);
    appEngine.rootContext()->setContextProperty(QStringLiteral("correctionVM"), CorrectionVM::GetInstance());



    // infeed sensor sequence // последовательность действий датчика подачи
    m_nCurrentBottleTransferredInfeedSensorState = 0;

    // reset inspection sequence enum // сбросить перечисление последовательности проверки
    m_strcInspectionSequenceData.Reset();
    ResetInspectionSequenceEN();

    QTimer::singleShot(1000, this, &MasterApp::InitApp);

    connect(&theMainVM, &MainVM::propagateChangeLanguageSignal,
            this,
            &MasterApp::StartToChangeLanguage);
}

MasterApp::~MasterApp()
{
    if (m_pCommandThread)
    {
        m_pCommandThread->Exit();

        // wait thread exit completely // дождаться полного завершения потока
        m_pCommandThread->wait();
    }

    foreach (TrackVM * value, this->hashTrackVM)
    {
        value->deleteLater();
    }
    scopedTabControlVM.data()->deleteLater();
    scopedLoginVM.data()->deleteLater();
    scopedMainHomeVM.data()->deleteLater();
    scopedSystemSettingVM.data()->deleteLater();
    scopedFeederAndPushersVM.data()->deleteLater();
    scopedTableVM.data()->deleteLater();
    // scopedSetoutVM.data()->deleteLater();
    scopedSystemVM.data()->deleteLater();
    // scopedValidationVM.data()->deleteLater();
    // scopedReportVM.data()->deleteLater();
    // scopedRecipeManagementVM.data()->deleteLater();
    // scopedCalibTableVM.data()->deleteLater();

    scopedSaveImageThread.data()->Exit();
    scopedSaveImageThread.data()->wait();
    scopedSaveImageThread.data()->deleteLater();

    scopedInspectionCore.data()->deleteLater();

    if (scopedBackendProcess != nullptr)
    {
        scopedBackendProcess.data()->terminate();
        scopedBackendProcess.data()->waitForFinished(2000);
    }

}

void MasterApp::ExecuteCommandThread(int command)
{
}

void MasterApp::InitApp()
{
    //call backend process // вызвать  Бэкенд-процесс
    scopedBackendProcess.reset(new QProcess());
    scopedBackendProcess.data()->setWorkingDirectory(QDir::currentPath() + "/Backend");
    #ifdef Q_OS_WIN
        QString backendPath = QDir::currentPath() + "/Backend/main.py";
        if(!QFile(backendPath).exists())
        {
            scopedBackendProcess.data()->start("python main.pyc");
        }
        else
        {
            scopedBackendProcess.data()->start("python main.py");
        }
    #elif defined(Q_OS_LINUX)
        QString backendPath = QDir::currentPath() + "/Backend/main.py";
        if(!QFile(backendPath).exists())
        {
            scopedBackendProcess.data()->start("python3 main.pyc");
        }
        else
        {
            scopedBackendProcess.data()->start("python3 main.py");
        }
    #endif

    QThread::sleep(10);

    // inspection core //  Инспекционный сердечник
    scopedInspectionCore.reset(new InspectionCore());
    scopedInspectionCore.data()->start();

    //    // save image thread // сохранить поток изображений
    //    scopedSaveImage.reset(new SaveImage());
    //    scopedSaveImage.data()->start();

    // create connection // создать соединение
    CreateConnection();

    //    // create tcpip // создать tcpip
    //    scopedTcpServerInterface.data()->StartServer(ConfigApplication::instance()->m_strServerName,
    //                                                 ConfigApplication::instance()->m_nServerPort);


    if(!scopedInspectionCore.data()->scopedTCPBackendClient.data()->isConnected)
    {
        DebugLogVM::instance()->WriteDebugLog("MasterApp", "Can not connected Backend", tr("Can not connected Backend"));
        for(int i = 0; i < ConfigApplication::instance()->m_nCamNum; i++)
        {
            // this->hashTrackVM[(TRACK_INDEX)(i)]->setInspectionInfo(ConfigApplication::instance()->m_listInspectInfoState[1]);
            this->hashTrackVM[(TRACK_INDEX)(i)]->setInspectionInfo(QCoreApplication::translate("ConfigApplication", ConfigApplication::instance()->m_listInspectInfoState[1].toStdString().c_str()));

        }
    }
    else
    {
        DebugLogVM::instance()->WriteDebugLog("MasterApp", "Connected Backend", tr("Connected Backend"));
    }

    m_pCommandThread = new AppCommandThread(this);

    QObject::connect(this, &MasterApp::sendAppCommandSignal, m_pCommandThread, &AppCommandThread::ReceiveCommand);

    m_pCommandThread->start();

    for(int i = 0; i < ConfigApplication::instance()->m_nCamNum; i++)
    {
        QString empty = "";
        hashTrackVM[(TRACK_INDEX)(i)]->UpdateImageFromFile(empty, 0);
        scopedInspectionCore.data()->scopedTCPBackendClient.data()->DLModelPathChanged((TRACK_INDEX)i);
    }

    scopedMainHomeVM.data()->SetDLModelVersion();
    loadRecipe_RecipeManagementVM_Slots();

}

void MasterApp::CreateConnection()
{
    // tab control // управление вкладками
    connect(scopedTabControlVM.data(), SIGNAL(tabIndexChanged_Signal(int)),
            this, SLOT(tabIndexChanged_TabControlVM_Slots(int)));

    // login // войти в систему
    connect(scopedLoginVM.data(), SIGNAL(login_Signals(bool)), this, SLOT(login_LoginVM_Slots(bool)));

    // System setting // Настройка системы

    // Manage recipe // Управление рецептом
    connect(RecipeManagementVM::GetInstance(), SIGNAL(loadRecipe_Signal()), this, SLOT(loadRecipe_RecipeManagementVM_Slots()));
    connect(EditRecipeVM::GetInstance(), SIGNAL(editRecipe_Signal()), this, SLOT(editRecipe_EditRecipeVM_Slots()));
    connect(LimitTabVM::GetInstance(), SIGNAL(loadRecipe_Signal()), this, SLOT(loadRecipe_RecipeManagementVM_Slots()));


    // inspection core //  Инспекционный сердечник
    connect(scopedInspectionCore.data(), SIGNAL(sendFinishInspect_Signal(OutputBackendInfo&)),
            this, SLOT(inspectFinish_InspectionCore_Slots(OutputBackendInfo&)));
    // connect(scopedInspectionCore.data(), SIGNAL(sendModelLoaded_Signal(QStringList&)),
    //         this, SLOT(modelLoaded_InspectionCore_Slots(QStringList&)));
    connect(scopedInspectionCore.data(), SIGNAL(sendRecipeLoaded_Signal(bool)),
            this, SLOT(recipeLoaded_InspectionCore_Slots(bool)));

    connect(scopedMainHomeVM.data(), SIGNAL(inspect_Signal(InputBackendInfo&)),
            scopedInspectionCore.data(), SLOT(inspect_MainHomeVM_Slot(InputBackendInfo&)));

    // for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
    // {
    //     connect(hashTrackVM[(TRACK_INDEX)i], SIGNAL(inspect_Signal(InputBackendInfo&)),
    //             scopedInspectionCore.data(), SLOT(inspect_TrackVM_Slot(InputBackendInfo&)));
    // }



}

int MasterApp::GetFirstSetBitPosition(uint16_t num)
{
    if (num == 0) return -1; // If no bits are set

    // Check the lower 8 bits // Проверьте  Меньшие 8  Бит
    if (num & 0x00FF) {
        if (num & 0x000F) {
            return lookup[num & 0x000F];
        } else {
            return 4 + lookup[(num & 0x00F0) >> 4];
        }
    } else {
        // Check the upper 8 bits // Проверьте  Высших  8  Бит
        if (num & 0x0F00) {
            return 8 + lookup[(num & 0x0F00) >> 8];
        } else {
            return 12 + lookup[(num & 0xF000) >> 12];
        }
    }
}

void MasterApp::CalibrationHandler()
{
    // // receive plc trigger start inspect // получение триггера плк для Запуска проверки
    // quint16 plcVal = 0;
    // MBCommunication::GetInstance()->ReadUnit16Data(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_CALIBRATION_SEQUENCE_1, plcVal);

    // // // if is specing will return // если указано, то вернется
    // // if (plcVal & (int)REGISTER_CALIBRATION_SEQUENCE_1::TRIGER_INSPECT_STATUS_INSPECTING) return;

    // // == receive trigger inspect // == проверка получения триггера
    // if (plcVal & (int)REGISTER_CALIBRATION_SEQUENCE_1::TRIGER_INSPECT_STATUS_INSPECT)
    // {
    //     if(m_nCurrentInspectState == 0)
    //     {
    //         // announce to plc that sw inspecting // сообщить плк, что sw проверяет
    //         MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
    //             (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_CALIBRATION_SEQUENCE_1,
    //             (int)REGISTER_CALIBRATION_SEQUENCE_1::TRIGER_INSPECT_STATUS_INSPECTING, true);
    //     }

    //     // m_nCurrentInspectState: to know current step of inspect

    //     if((plcVal & (int)REGISTER_CALIBRATION_SEQUENCE_1::TRIGER_REQUEST_PLC_MOVEMENT) == 0 && m_nCurrentInspectState%2 == 0)
    //     {
    //         // set bit position corresponding move pos // установить положение бита, соответствующее позиции перемещения
    //         MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
    //             (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_CALIBRATION_SEQUENCE_2,
    //             m_arrayCalibrationStepInfor[m_nCurrentStepCalibration].bitPosValue, true);

    //         // request plc move // запросить перемещение плк
    //         MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
    //             (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_CALIBRATION_SEQUENCE_1,
    //             (int)REGISTER_CALIBRATION_SEQUENCE_1::TRIGER_REQUEST_PLC_MOVEMENT, true);
    //         m_nCurrentInspectState++;
    //     }
    //     else if (m_nCurrentInspectState%2 == 1 &&
    //         (plcVal & m_arrayCalibrationStepInfor[m_nCurrentStepCalibration].bitPosValue) == 0 &&
    //         (plcVal & (int)REGISTER_CALIBRATION_SEQUENCE_1::TRIGER_REQUEST_PLC_MOVEMENT) == 0)
    //     {
    //         // plc already stop and bit request position already set to 0 // плк уже остановлен, а позиция запроса бита уже установлена на 0
    //         // start to do snap // начните выполнять защелку

    //         // announce to plc that sw inspectiing // сообщить плк, что sw проверяет
    //         // MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
    //         //     (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_CALIBRATION_SEQUENCE_1,
    //         //     (int)REGISTER_CALIBRATION_SEQUENCE_1::TRIGER_INSPECT_STATUS_INSPECTING, true);
    //         // emit sendAppCommandSignal(COMMAND_CALIBRATION, m_arrayCalibrationStepInfor[m_nCurrentStepCalibration].imageIndex);

    //         scopedMainHomeVM.data()->hashTrackVM[(TRACK_INDEX)m_arrayCalibrationStepInfor[m_nCurrentStepCalibration].imageIndex]->Snap();
    //         m_nCurrentStepCalibration += 4;
    //         m_nCurrentInspectState++;
    //     }
    // }

    // // wait move finish // дождаться завершения перемещения

    // // check finish capture // проверьте завершение захвата
    // if(m_nCurrentStepCalibration == TOTAL_CALIBRATION_STEP)
    // {
    //     m_nCurrentStepCalibration = 0;
    //     m_nCurrentInspectState = 0;

    //     // call inspection // проверка вызова
    //     // scopedMainHomeVM.data()->Inspect();
    // }

}

void MasterApp::CalibrationInitData()
{
    // m_nCurrentStepCalibration = 0;
    // m_nCurrentInspectState = 0;
    
    // m_arrayCalibrationStepInfor = {
    //     CalibratioStepInfor((int)TRACK_INDEX::CAMERA_1, 1 << 0, "Rotate 0. Move Bottom"),
    //     CalibratioStepInfor((int)TRACK_INDEX::CAMERA_1, 1 << 1, "Rotate 90. Move Bottom"),
    //     CalibratioStepInfor((int)TRACK_INDEX::CAMERA_1, 1 << 2, "Rotate 180. Move Bottom"),
    //     CalibratioStepInfor((int)TRACK_INDEX::CAMERA_1, 1 << 3, "Rotate 270. Move Bottom"),

    //     CalibratioStepInfor((int)TRACK_INDEX::CAMERA_2, 1 << 4, "Rotate 0. Move Middle"),
    //     CalibratioStepInfor((int)TRACK_INDEX::CAMERA_2, 1 << 5, "Rotate 90. Move Middle"),
    //     CalibratioStepInfor((int)TRACK_INDEX::CAMERA_2, 1 << 6, "Rotate 180. Move Middle"),
    //     CalibratioStepInfor((int)TRACK_INDEX::CAMERA_2, 1 << 7, "Rotate 270. Move Middle"),

    //     CalibratioStepInfor((int)TRACK_INDEX::CAMERA_3, 1 << 8, "Rotate 0. Move Top"),
    //     CalibratioStepInfor((int)TRACK_INDEX::CAMERA_3, 1 << 9, "Rotate 90. Move Top"),
    //     CalibratioStepInfor((int)TRACK_INDEX::CAMERA_3, 1 << 10, "Rotate 180. Move Top"),
    //     CalibratioStepInfor((int)TRACK_INDEX::CAMERA_3, 1 << 11, "Rotate 270. Move Top"),
    // };
}

void MasterApp::BottleTransferredInfeedSensorHandler()
{
    // if(ConfigApplication::instance()->m_appStatus != APP_STATUS::RUNNING)
    // {
    //     if(m_nCurrentBottleTransferredInfeedSensorState > 0)
    //     {
    //         // reset
    //         MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
    //             (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
    //             (int)REGISTER_500_PROFILE::REQUEST_DATA_BIT_ACK, false);
    //         MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
    //             (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
    //             (int)REGISTER_500_PROFILE::RESPONSE_DATA_BIT, false);
    //     }
    //     m_nCurrentBottleTransferredInfeedSensorState = 0;
    //     return;
    // }
    // // only run in running mode
    // // receive plc trigger start inspect
    // quint16 plcVal = 0;
    // MBCommunication::GetInstance()->ReadUnit16Data(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500, plcVal);

    // switch (m_nCurrentBottleTransferredInfeedSensorState) {
    // case 0:
    //     if(plcVal & (int)REGISTER_500_PROFILE::REQUEST_DATA_BIT)
    //     {
    //         // send ack
    //         MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
    //                                                      (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
    //                                                      (int)REGISTER_500_PROFILE::REQUEST_DATA_BIT_ACK, true);

    //         m_nCurrentBottleTransferredInfeedSensorState++;
    //     }
    //     break;
    // case 1:
    //     if((plcVal & (int)REGISTER_500_PROFILE::REQUEST_DATA_BIT) == 0)
    //     {
    //         // send ack
    //         MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
    //                                                      (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
    //                                                      (int)REGISTER_500_PROFILE::REQUEST_DATA_BIT_ACK, false);
    //         m_nCurrentBottleTransferredInfeedSensorState++;
    //     }
    //     break;
    // case 2:
    //     // write operation type ack
    //     MBCommunication::GetInstance()->ReadUnit16Data(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::OPERATION_TYPE_VALUE, plcVal);
    //     MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::OPERATION_TYPE_ACK_VALUE, plcVal);
    //     m_nCurrentBottleTransferredInfeedSensorState++;
    //     break;
    // case 3:
    //     // write info: ex: bottle diameter
    //     MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_DIAMETER_VALUE, EditRecipeVM::GetInstance()->bottleDiameter.diameter);
    //     MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_DIAMETER_ACK_VALUE, EditRecipeVM::GetInstance()->bottleDiameter.diameter);
    //     QThread::msleep(20);
    //     // write response data bit
    //     MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
    //             (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
    //             (int)REGISTER_500_PROFILE::RESPONSE_DATA_BIT, true);
    //     m_nCurrentBottleTransferredInfeedSensorState++;
    //     break;
    // case 4:
    //     if(plcVal & (int)REGISTER_500_PROFILE::RESPONSE_DATA_BIT_ACK)
    //     {
    //         // send response
    //         MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
    //                                                      (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
    //                                                      (int)REGISTER_500_PROFILE::RESPONSE_DATA_BIT, false);
    //         m_nCurrentBottleTransferredInfeedSensorState++;
    //     }
    //     break;
    // case 5:
    //     // read response ack and finish
    //     if((plcVal & (int)REGISTER_500_PROFILE::RESPONSE_DATA_BIT_ACK) == 0)
    //     {
    //         m_nCurrentBottleTransferredInfeedSensorState = 0;
    //     }
    //     break;
    // default:
    //     m_nCurrentBottleTransferredInfeedSensorState = 0;
    //     break;
    // }


}

void MasterApp::InspectionSequence()
{
    if(ConfigApplication::instance()->m_appStatus != APP_STATUS::RUNNING)
    {
        // // set moldindex and serial index
        // m_strcInspectionSequenceData.m_nCurrentSerialNumber = 0;
        // // reset sequence flag // // флаг сброса последовательности
        // ResetInspectionSequenceEN();
        // reset variable // сбросить переменную
        m_strcInspectionSequenceData.Reset();
        return;
    }

    // if(!m_strcSetoutMoldsData.IsHaveSlotForInspectiSequence() &&
    //     m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep == WAIT_REQUEST_TRUE)
    // {
    //     return;
    // }

    // only run in running mode // запускается только в рабочем режиме
    // receive plc trigger start inspect, register 500 // получение триггера плк для  Запуска проверки, регистрация 500
    quint16 plcVal = 0;
    MBCommunication::GetInstance()->ReadUnit16Data(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500, plcVal);

    switch ((int)m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep) {
        case UNKNOW:
        m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::INITIALIZATION;
            break;
        case INITIALIZATION:
            // TODO: reset or queue for inspect // TODO: сброс или постановка в очередь для проверки
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_REQUEST_TRUE", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_REQUEST_TRUE;
            break;

        case WAIT_REQUEST_TRUE:
            if(plcVal & (int)REGISTER_500_PROFILE::REQUEST)
            {
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_REQUEST_ACK_TRUE", tr(""));
                m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_REQUEST_ACK_TRUE;
            }
            break;
        case SEND_REQUEST_ACK_TRUE:

            if(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceType == AT_TURNING_TABLE &&
                m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos == INSPECT_SEQUENCE_CAMERA_POSITION::TOTAL_POS)
            {

            }
            // send request ack true // отправить запрос ack true
            MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
                                                         (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
                                                         (int)REGISTER_500_PROFILE::REQUEST_ACK, true);
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_REQUEST_FALSE", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_REQUEST_FALSE;

            break;
        case WAIT_REQUEST_FALSE:
            if((plcVal & (int)REGISTER_500_PROFILE::REQUEST) == 0)
            {
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_REQUEST_ACK_FALSE", tr(""));
                m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_REQUEST_ACK_FALSE;
            }
            break;
        case SEND_REQUEST_ACK_FALSE:
            // send request ack false // отправить запрос ack false
            MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
                                                         (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
                                                         (int)REGISTER_500_PROFILE::REQUEST_ACK, false);
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_OPERATION_TYPE", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_OPERATION_TYPE;
            break;

            // branch //ветка
        case WAIT_OPERATION_TYPE:
            MBCommunication::GetInstance()->ReadUnit16Data(MT_HOLDING_REGISTER,
                                                    (int)MB_HOLDING_REGISTER_ITEMS::OPERATION_TYPE_VALUE, plcVal);
            if(plcVal > 0)
            {

                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_OPERATION_TYPE_ACK", tr(""));
                // write operation type ack // Операция записи тип ack
                MBCommunication::GetInstance()->WriteData(MT_HOLDING_REGISTER,
                                                        (int)MB_HOLDING_REGISTER_ITEMS::OPERATION_TYPE_ACK_VALUE, plcVal);

                // get current seuqence type // получить текущий тип  Последовательности
                m_strcInspectionSequenceData.m_nCurrentInspectionSequenceType = INSPECT_SEQUENCE_TYPE(plcVal);
                if(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceType == AT_INFEED)
                {
                    PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "Start Infeed sequence", tr(""));
                    PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_AT_INFEED_PARAMETER1", tr(""));
                    m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_AT_INFEED_PARAMETER1;
                }
                else if(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceType == AT_TURNING_TABLE)
                {
                    if(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceType == AT_TURNING_TABLE &&
                        m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos == INSPECT_SEQUENCE_CAMERA_POSITION::TOTAL_POS)
                    {
                        PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_OPERATION_ALL_COMPLETE_TRUE", tr(""));
                        m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_OPERATION_ALL_COMPLETE_TRUE;
                    }
                    else
                    {
                        PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "Start Turning table sequence", tr(""));
                        PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_AT_TURN_TABLE_SERIALNUMBER", tr(""));
                        m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_AT_TURN_TABLE_SERIALNUMBER;
                    }
                }
                else if(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceType == AT_OUTFEED)
                {
                    PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "Start Outfeed sequence", tr(""));
                    PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_AT_OUTFEED_SERIALNUMBER", tr(""));
                    m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_AT_OUTFEED_SERIALNUMBER;
                }
            }

            break;

        // Infeed sequence // Последовательность подачи
        case SEND_AT_INFEED_PARAMETER1:


            m_strcInspectionSequenceData.m_nCurrentSerialNumber++;
            MBCommunication::GetInstance()->WriteUint32Data(MT_HOLDING_REGISTER,
                                                            (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_SERIALNUMBER_VALUE,
                                                            (m_strcInspectionSequenceData.m_nCurrentSerialNumber));


            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", QString("Send Serial number %1")
                                                            .arg(m_strcInspectionSequenceData.m_nCurrentSerialNumber), tr(""));
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_AT_INFEED_PARAMETER2", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_AT_INFEED_PARAMETER2;
            break;

        case SEND_AT_INFEED_PARAMETER2:
            // send serial number, bottle height, bottle diameter, scale pusher, table pusher // отправить серийный номер, высоту бутылки, диаметр бутылки, толкатель весов, толкатель стола
            // MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER,
            //                                                (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_HEIGHT_VALUE,
            //                                                EditRecipeVM::GetInstance()->heightInspect.height);
            // PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", QString("Send Bottle Height %1")
            //                                         .arg(EditRecipeVM::GetInstance()->heightInspect.height), tr(""));

            MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER,
                                                           (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_DIAMETER_VALUE,
                                                           EditRecipeVM::GetInstance()->bottleDiameter.diameter);
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", QString("Send Bottle Diameter %1")
                                                    .arg(EditRecipeVM::GetInstance()->bottleDiameter.diameter), tr(""));

            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_AT_INFEED_PARAMETER3", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_AT_INFEED_PARAMETER3;
            break;

        case SEND_AT_INFEED_PARAMETER3:
            // send serial number, bottle height, bottle diameter, scale pusher, table pusher // отправить серийный номер, высоту бутылки, диаметр бутылки, толкатель весов, толкатель стола
            MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER,
                                                           (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_HEIGHT_VALUE,
                                                           EditRecipeVM::GetInstance()->heightInspect.height);
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", QString("Send Bottle Height %1")
                                                    .arg(EditRecipeVM::GetInstance()->heightInspect.height), tr(""));

            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_AT_INFEED_PARAMETER_ACK", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_AT_INFEED_PARAMETER_ACK;
            break;

        case WAIT_AT_INFEED_PARAMETER_ACK:
            // read serial number, bottle height ack, bottle diameter ack, scale pusher ack, table pusher ack // считывание серийного номера, высоты бутылки ack, диаметра бутылки ack, толкателя весов ack, толкателя стола ack
            quint32 serialNumberACK;
            float heightACK, diameterACK;
            MBCommunication::GetInstance()->ReadUint32Data(MT_HOLDING_REGISTER,
                        (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_SERIALNUMBER_ACK_VALUE, serialNumberACK);
            MBCommunication::GetInstance()->ReadFloatData(MT_HOLDING_REGISTER,
                    (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_HEIGHT_ACK_VALUE, heightACK);
            MBCommunication::GetInstance()->ReadFloatData(MT_HOLDING_REGISTER,
                    (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_DIAMETER_ACK_VALUE, diameterACK);

            if(m_strcInspectionSequenceData.m_nCurrentSerialNumber == serialNumberACK &&
                QString::number(EditRecipeVM::GetInstance()->bottleDiameter.diameter, 'f', 2) == QString::number(diameterACK, 'f', 2) &&
                QString::number(EditRecipeVM::GetInstance()->heightInspect.height, 'f', 2) == QString::number(heightACK, 'f', 2))
            {
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_RESPONSE_TRUE", tr(""));
                m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_RESPONSE_TRUE;
            }
            break;


        case SEND_RESPONSE_TRUE:
            // send reponse true // отправить ответ true
            MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
                                                    (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
                                                    (int)REGISTER_500_PROFILE::RESPONSE, true);
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_RESPONSE_ACK_TRUE", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_RESPONSE_ACK_TRUE;
            break;
        case WAIT_RESPONSE_ACK_TRUE:
            if(plcVal & (int)REGISTER_500_PROFILE::RESPONSE_ACK)
            {
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_RESPONSE_FALSE", tr(""));
                m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_RESPONSE_FALSE;
            }
            break;
        case SEND_RESPONSE_FALSE:
            // send respose false // отправить ответ false
            MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
                                                         (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
                                                         (int)REGISTER_500_PROFILE::RESPONSE, false);
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_RESPONSE_ACK_FALSE", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_RESPONSE_ACK_FALSE;
            break;
        case WAIT_RESPONSE_ACK_FALSE:
            if((plcVal & (int)REGISTER_500_PROFILE::RESPONSE_ACK) == 0)
            {
                if(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceType == AT_INFEED)
                {
                    // finish sequence infeed // завершите подачу последовательности
                    PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "End Infeed sequence", tr(""));
                    ResetInspectionSequenceEN();
                }
                else if(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceType == AT_TURNING_TABLE)
                {
                    PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_OPERATION_COMPLETE_TRUE", tr(""));
                    m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_OPERATION_COMPLETE_TRUE;
                }
                else if(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceType == AT_OUTFEED)
                {

                }
            }
            break;

        // Turning table // Поворотный стол

        case WAIT_AT_TURN_TABLE_SERIALNUMBER:
            // TODO: check serial number // TODO: проверьте серийный номер
            quint32 serialNumber;
            MBCommunication::GetInstance()->ReadUint32Data(MT_HOLDING_REGISTER,
                                                        (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_SERIALNUMBER_VALUE, serialNumber);
            if(serialNumber > 0)
            {
                MBCommunication::GetInstance()->WriteUint32Data(MT_HOLDING_REGISTER,
                                                        (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_SERIALNUMBER_ACK_VALUE, serialNumber);
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_AT_TURN_TABLE_SERIALNUMBER", tr(""));
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_AT_TURN_TABLE_PARAMETER_ACK", tr(""));
                m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_AT_TURN_TABLE_PARAMETER;
            }

            break;

        case SEND_AT_TURN_TABLE_PARAMETER:
            // send LiftingMechanism_Position // отправить подъемный механизм_позицию
            // TODO: calculate position // TODO: вычислить Позицию
            MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER,
                                                           (int)MB_HOLDING_REGISTER_ITEMS::LIFTING_MECHANISM_POSION_VALUE,
                                                           GetTablePositionNeedToMove(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos));
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_AT_TURN_TABLE_PARAMETER_ACK", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_AT_TURN_TABLE_PARAMETER_ACK;
            break;



        case WAIT_AT_TURN_TABLE_PARAMETER_ACK:
            // read LiftingMechanism_Position // прочитайте положение подъемного механизма
            // TODO
            float liftingMechanismPosition;
            MBCommunication::GetInstance()->ReadFloatData(MT_HOLDING_REGISTER,
                                    (int)MB_HOLDING_REGISTER_ITEMS::LIFTING_MECHANISM_POSION_ACK_VALUE,
                                    liftingMechanismPosition);
            if(QString::number(liftingMechanismPosition, 'f', 2) ==
                QString::number(GetTablePositionNeedToMove(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos), 'f', 2))
            {
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_RESPONSE_TRUE", tr(""));
                m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_RESPONSE_TRUE;
            }
            break;

        case WAIT_OPERATION_COMPLETE_TRUE:
            if(plcVal & (int)REGISTER_500_PROFILE::OPERATION_COMPLETE)
            {
                // if bottom position we will capture 40 times and inspect bottle container shape // при расположении перед камера корпус мы проведем cъемка 40 раз и проверим форму контейнера для бутылок
                // at bottom need to move 2 position for make sure see all bottle // перед камера корпус нужно передвинуть на 2 позиции, чтобы убедиться, что видна вся бутылка

                // Capture // снимков
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", QString("Call capture pos %1").arg((int)m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos + 1), tr(""));
                scopedMainHomeVM.data()->Snap(GetTablePositionCamera(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos));

                // store the image for inspect // сохраните изображение для проверки
                m_strcInspectionSequenceData.m_hashSequencePosImages[m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos] =
                    hashTrackVM[GetTablePositionCamera(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos)]->GetDocImage(0);


                // capture image with rotate table // Снимка изображения с поворотного стола
                m_strcInspectionSequenceData.m_hashCurrentPositionImageNumber[m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos]++;

                if(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos == INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1)
                {
                    // no inspect // нет проверки
                }
                else if(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos == INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2)
                {
                    // call bottle container shape inspect //  Вызовите проверку формы контейнера для бутылок
                    scopedMainHomeVM.data()->Inspect(m_strcInspectionSequenceData.m_hashCurrentPositionImageNumber[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2] == 1 ?
                                                         BACKEND_FUNCTION::NON_ROUND_SHAPE_INSPECT_START : BACKEND_FUNCTION::NON_ROUND_SHAPE_INSPECT);
                }
                else if(m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos == INSPECT_SEQUENCE_CAMERA_POSITION::TOP)
                {
                    // call flange & knockout inspection // Вызовите проверка  фланцевый & нокаут
                    scopedMainHomeVM.data()->Inspect(m_strcInspectionSequenceData.m_hashCurrentPositionImageNumber[INSPECT_SEQUENCE_CAMERA_POSITION::TOP] == 1 ?
                                                         BACKEND_FUNCTION::TOP_INSPECT_START : BACKEND_FUNCTION::TOP_INSPECT);
                }


                if(m_strcInspectionSequenceData.m_hashCurrentPositionImageNumber[m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos] >=
                    m_strcInspectionSequenceData.m_hashPositionImageNumber[m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos])
                {
                    // Increase current position // Увеличить текущую позицию
                    m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos = (INSPECT_SEQUENCE_CAMERA_POSITION)((int)m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos + 1);
                    PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_OPERATION_COMPLETE_ACK_TRUE", tr(""));
                    m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_OPERATION_COMPLETE_ACK_TRUE;
                }

            }
            break;
        case SEND_OPERATION_COMPLETE_ACK_TRUE:
            // send operation complete ack true //  Отправка завершена операция ack true
            MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
                                                         (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
                                                         (int)REGISTER_500_PROFILE::OPERATION_COMPLETE_ACK,
                                                         true);
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_OPERATION_COMPLETE_FALSE", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_OPERATION_COMPLETE_FALSE;
            break;
        case WAIT_OPERATION_COMPLETE_FALSE:
            if((plcVal & (int)REGISTER_500_PROFILE::OPERATION_COMPLETE) == 0)
            {
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_OPERATION_COMPLETE_ACK_FALSE", tr(""));
                m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_OPERATION_COMPLETE_ACK_FALSE;
            }
            break;
        case SEND_OPERATION_COMPLETE_ACK_FALSE:
            // send operation complete ack false //  Отправка завершена операция ack false
            MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
                                                         (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
                                                         (int)REGISTER_500_PROFILE::OPERATION_COMPLETE_ACK,
                                                         false);

            // go to WAIT_REQUEST_TRUE // перейти к WAIT_REQUEST_TRUE
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_REQUEST_TRUE", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_REQUEST_TRUE;
            break;


        case SEND_OPERATION_ALL_COMPLETE_TRUE:
            // send all operation complete true // отправить все операции завершенными true
            MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
                                                         (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
                                                         (int)REGISTER_500_PROFILE::OPERATION_ALL_COMPLETE, true);

            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_OPERATION_ALL_COMPLETE_ACK_TRUE", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_OPERATION_ALL_COMPLETE_ACK_TRUE;

            break;

        case WAIT_OPERATION_ALL_COMPLETE_ACK_TRUE:
            if(plcVal & (int)REGISTER_500_PROFILE::OPERATION_ALL_COMPLETE_ACK)
            {
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_OPERATION_ALL_COMPLETE_FALSE", tr(""));
                m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_OPERATION_ALL_COMPLETE_FALSE;
            }
            break;
        case SEND_OPERATION_ALL_COMPLETE_FALSE:
            // send operation all complete false // отправить все операции завершенными false
            MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
                                                         (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
                                                         (int)REGISTER_500_PROFILE::OPERATION_ALL_COMPLETE,
                                                         false);
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_OPERATION_ALL_COMPLETE_ACK_FALSE", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_OPERATION_ALL_COMPLETE_ACK_FALSE;
            break;
        case WAIT_OPERATION_ALL_COMPLETE_ACK_FALSE:
            if((plcVal & (int)REGISTER_500_PROFILE::OPERATION_ALL_COMPLETE_ACK) == 0)
            {
                // finish turning table sequence // завершите последовательность поворота стола
                ResetInspectionSequenceEN();
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "End Turning table sequence", tr(""));
            }
            break;

            // outfeed sequence // последовательность выгрузки

        case WAIT_AT_OUTFEED_SERIALNUMBER:
            quint32 serialNumber1;
            MBCommunication::GetInstance()->ReadUint32Data(MT_HOLDING_REGISTER,
                                            (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_SERIALNUMBER_VALUE, serialNumber1);
            if(serialNumber1 > 0)
            {
                MBCommunication::GetInstance()->WriteUint32Data(MT_HOLDING_REGISTER,
                                                (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_SERIALNUMBER_ACK_VALUE, serialNumber1);
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_OUTFEED_SERIALNUMBER", tr(""));
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_AT_OUTFEED_PARAMETER1", tr(""));
                m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_AT_OUTFEED_PARAMETER1;
            }
            break;

        case WAIT_AT_OUTFEED_PARAMETER1:
            // TODO: get serial, weight, depth // TODO: получить серийный номер, вес, глубину
            MBCommunication::GetInstance()->ReadFloatData(MT_HOLDING_REGISTER,
                                                          (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_WEIGHT_VALUE,
                                                          m_strcInspectionSequenceData.m_dWeight);

            MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER,
                                                           (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_WEIGHT_ACK_VALUE,
                                                           m_strcInspectionSequenceData.m_dWeight);
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", QString("Send Bottle Weight %1")
                                                            .arg(m_strcInspectionSequenceData.m_dWeight), tr(""));

            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_AT_OUTFEED_PARAMETER2", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_AT_OUTFEED_PARAMETER2;
            break;

        case WAIT_AT_OUTFEED_PARAMETER2:
            // TODO: get serial, weight, depth // TODO: получить серийный номер, вес, глубину
            MBCommunication::GetInstance()->ReadFloatData(MT_HOLDING_REGISTER,
                                                          (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_BOTTOM_DEPTH_VALUE,
                                                          m_strcInspectionSequenceData.m_dDepth);

            MBCommunication::GetInstance()->WriteFloatData(MT_HOLDING_REGISTER,
                                                           (int)MB_HOLDING_REGISTER_ITEMS::BOTTLE_BOTTOM_DEPTH_ACK_VALUE,
                                                           m_strcInspectionSequenceData.m_dDepth);
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", QString("Send Bottle Depth %1")
                                                            .arg(m_strcInspectionSequenceData.m_dDepth), tr(""));

            // call inspection // проверка вызова
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "Call inspection", tr(""));
            scopedMainHomeVM.data()->Inspect(BACKEND_FUNCTION::INSPECT);


            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_RESPONSE_TRUE", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_RESPONSE_TRUE;
            break;

        case WAIT_RESPONSE_TRUE:
            if(plcVal & (int)REGISTER_500_PROFILE::RESPONSE)
            {
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_RESPONSE_ACK_TRUE", tr(""));
                m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_RESPONSE_ACK_TRUE;
            }
            break;
        case SEND_RESPONSE_ACK_TRUE:
            // send response ack true // отправить ответ ack true
            MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
                                                         (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
                                                         (int)REGISTER_500_PROFILE::RESPONSE_ACK, true);
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "WAIT_RESPOSE_FALSE", tr(""));
            m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::WAIT_RESPOSE_FALSE;
            break;
        case WAIT_RESPOSE_FALSE:
            if((plcVal & (int)REGISTER_500_PROFILE::RESPONSE) == 0)
            {
                PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "SEND_RESPONSE_ACK_FALSE", tr(""));
                m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::SEND_RESPONSE_ACK_FALSE;
            }
            break;
        case SEND_RESPONSE_ACK_FALSE:
            // finish outfeed sequence // завершите последовательность выгрузки
            // send response ack true // отправить ответ ack true
            MBCommunication::GetInstance()->WriteBitData(MT_HOLDING_REGISTER,
                                                         (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_500,
                                                         (int)REGISTER_500_PROFILE::RESPONSE_ACK, false);
            ResetInspectionSequenceEN();
            m_strcInspectionSequenceData.m_hashSequencePosImages.clear();
            PLCCommunicationLogVM::GetInstance()->WriteDebugLog("Inspect sequence", "End Outfeed sequence", tr(""));
            break;



    }
}

void MasterApp::DoValidation()
{
    // m_strcInspectionSequenceData.Reset();
    // // simulate call validation offline
    // scopedMainHomeVM.data()->Inspect(BACKEND_FUNCTION::VALIDATION_INSPECT);
}

void MasterApp::ResetInspectionSequenceEN()
{
    m_strcInspectionSequenceData.m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::UNKNOW;
    m_strcInspectionSequenceData.m_nCurrentInspectionSequenceType = INSPECT_SEQUENCE_TYPE::NO_OPERATION;
    m_strcInspectionSequenceData.m_nCurrentInspectionSequenceCameraPos = INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1;
    for (int i = 0; i < INSPECT_SEQUENCE_CAMERA_POSITION::TOTAL_POS; ++i) {
        m_strcInspectionSequenceData.m_hashCurrentPositionImageNumber[(INSPECT_SEQUENCE_CAMERA_POSITION)i] = 0;
    }

    // Validation
    // ValidationVM::GetInstance()->m_bIsValidation = false;
}

double MasterApp::GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION pos)
{
    return EditRecipeVM::GetInstance()->heightInspect.liftingMechanismPos[pos];
}

TRACK_INDEX MasterApp::GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION pos)
{
    if(pos == INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1)
    {
        return TRACK_INDEX::CAMERA_1;
    }
    else if(pos == INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2)
    {
        return TRACK_INDEX::CAMERA_1;
    }
    else if(pos == INSPECT_SEQUENCE_CAMERA_POSITION::TOP)
    {
        return TRACK_INDEX::CAMERA_2;
    }
    return TRACK_INDEX::CAMERA_1;
}

void MasterApp::tabIndexChanged_TabControlVM_Slots(int value)
{
    // when tab recipe got selected will populate data to ui // когда будет выбрана вкладка  Рецепт, данные будут перенесены в пользовательский интерфейс
    if (value == 2)
    {
        RecipeManagementVM::GetInstance()->PopulateData();
    }
}

void MasterApp::login_LoginVM_Slots(bool value)
{
    EditRecipeVM::GetInstance()->UpdateVisionParamToUI();
    scopedTabControlVM.data()->SetEnableTab(ConfigApplication::instance()->m_strcCurrentAccountLevel != ACCOUNT_LEVEL::NONE);
    if(value)
    {
        DebugLogVM::instance()->WriteDebugLog("MasterApp",
                                              "Login " + ConfigApplication::instance()->m_strCurrentAccountName
                                                  + " " + ConfigApplication::instance()->ConvertAccountLevelToString(ConfigApplication::instance()->m_strcCurrentAccountLevel),
                                              tr("Login") + " " + ConfigApplication::instance()->m_strCurrentAccountName
                                                  + " " + ConfigApplication::instance()->ConvertAccountLevelToString(ConfigApplication::instance()->m_strcCurrentAccountLevel));

        // setout // установка
        SetoutVM::GetInstance()->InitSetoutMoldNumber();
        // set mold index and serial index // установите индекс формы и серийный номер
        m_strcSetoutMoldsData.GetMoldNumberInspectionSequence(m_strcSetoutMoldsData.m_nCurrentMoldIndex);
    }
    else
    {
        DebugLogVM::instance()->WriteDebugLog("MasterApp", "Logout", tr("Logout"));
    }



    return;

}

void MasterApp::loadRecipe_RecipeManagementVM_Slots()
{
    // Load new recipe // Загрузить новый рецепт

    // send load new recipe to backend // отправить загрузку нового рецепта в  Бэкенд
    scopedInspectionCore.data()->RecipeChanged();

    // update report table // обновить таблицу отчетов
    emit ReportVM::GetInstance()->updateVisionParamNumber_Signal(EditRecipeVM::GetInstance()->bodyRInspect.numberDimension,
                                                                 EditRecipeVM::GetInstance()->noneRoundShapeInspect.numberDimension,
                                                                 EditRecipeVM::GetInstance()->noneRoundShapeInspect.shape);

    // update history tab
    emit HistoryVM::GetInstance()->updateVisionParamNumber_Signal(EditRecipeVM::GetInstance()->bodyRInspect.numberDimension,
                                                                  EditRecipeVM::GetInstance()->noneRoundShapeInspect.numberDimension,
                                                                  EditRecipeVM::GetInstance()->noneRoundShapeInspect.shape);

    // update validation tab
    emit ValidationVM::GetInstance()->updateVisionParamNumber_Signal(EditRecipeVM::GetInstance()->bodyRInspect.numberDimension);

    // update to correction tab
    CorrectionVM::GetInstance()->UpdateCurrentRecipeToCorrection();
}

void MasterApp::editRecipe_EditRecipeVM_Slots()
{
    // send load new recipe to backend // отправить загрузку нового рецепта в  Бэкенд
    scopedInspectionCore.data()->RecipeChanged();
    emit ReportVM::GetInstance()->updateVisionParamNumber_Signal(EditRecipeVM::GetInstance()->bodyRInspect.numberDimension,
                                                                 EditRecipeVM::GetInstance()->noneRoundShapeInspect.numberDimension,
                                                                 EditRecipeVM::GetInstance()->noneRoundShapeInspect.shape);
    // update history tab
    emit HistoryVM::GetInstance()->updateVisionParamNumber_Signal(EditRecipeVM::GetInstance()->bodyRInspect.numberDimension,
                                                                  EditRecipeVM::GetInstance()->noneRoundShapeInspect.numberDimension,
                                                                  EditRecipeVM::GetInstance()->noneRoundShapeInspect.shape);

    // update validation tab
    emit ValidationVM::GetInstance()->updateVisionParamNumber_Signal(EditRecipeVM::GetInstance()->bodyRInspect.numberDimension);

    // update to correction tab
    CorrectionVM::GetInstance()->UpdateCurrentRecipeToCorrection();
}

void MasterApp::openDocumentFile_Qml_Slots(QString name)
{
QString path = QString("%1/%2").arg(ConfigApplication::instance()->m_strConfigPath).arg(name);
QProcess process;
process.setWorkingDirectory(ConfigApplication::instance()->m_strConfigPath);

#ifdef Q_OS_WIN
    bool success = process.startDetached("cmd.exe", QStringList() << "/C" << "start" << "" << path);
#elif defined(Q_OS_LINUX)
    bool success = process.startDetached("xdg-open", QStringList() << path);
#endif
}

void MasterApp::registerNewCamera_SettingVM_Slots(TRACK_INDEX camID)
{
    qDebug() << "[MasterApp]" << "Register new camera";
    hashTrackVM[camID]->scopedCameraInterface.data()->Disconnect();
    hashTrackVM[camID]->scopedCameraInterface.data()->RegisterCamera();
}

void MasterApp::dlModelPathChanged_SettingVM_Slots(TRACK_INDEX camID)
{
    qDebug() << "[MasterApp]" << "DL model path change";
    DebugLogVM::instance()->WriteDebugLog("MasterApp", "DL model file changed");
    scopedInspectionCore.data()->scopedTCPBackendClient.data()->DLModelPathChanged(camID);
}

void MasterApp::inspectFinish_InspectionCore_Slots(OutputBackendInfo &result)
{
    try {
        qDebug() << "[MasterApp]" << "Result inspection";

        if(result.function == BACKEND_FUNCTION::INSPECT_DONE ||
           result.function == BACKEND_FUNCTION::BODYR_INSPECT_DONE)
        {
            for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
            {
                hashTrackVM[(TRACK_INDEX)i]->UpdateImageOverlay(result.operatorImages[(TRACK_INDEX)i], 0);
                // hashTrackVM[(TRACK_INDEX)i]->UpdateOverlayLeftString(result.resultString, 0);
                hashTrackVM[(TRACK_INDEX)i]->SetProcessTime(0, result.processTime);
                hashTrackVM[(TRACK_INDEX)i]->setInspectionInfo(ConfigApplication::instance()->m_listInspectInfoState[2]);
            }

            // add defect info // добавить информацию о дефекте
            scopedMainHomeVM.data()->AddDefectInfos(result.defectInfos);

            // update statistic // обновить статистику
            if(result.defectCodes.count() > 0)
                scopedMainHomeVM.data()->scopedStatisticsVM.data()->UpdateStatisticsTable(result.defectCodes[0]);

            // call save image // вызов сохранения изображения
            scopedSaveImageThread.data()->SaveMultiInspectImage(result);

            // update review tab // вкладка  Обзора обновлений
            scopedReviewVM.data()->AddSingleReviewData(result.resultString, result.operatorImagePaths, result.operatorImages);
            DebugLogVM::instance()->WriteDebugLog("MasterApp", "Inspection Done " +  QString::number(result.processTime));


            // increase mold and serial number and update setout // увеличьте формы и серийный номер, а также обновите  Установку
            m_strcSetoutMoldsData.GetMoldNumberInspectionSequence(m_strcSetoutMoldsData.m_nCurrentMoldIndex); // increase mold and serial number

            // SetoutVM::GetInstance()->UpdateMoldSerialNumberResult(result.defectCodes.contains(BACKEND_RESULT::PASS) ?
            //                                     MOLD_RESULT::MOLD_PASS : MOLD_RESULT::MOLD_FAIL,
            //                                 m_strcSetoutMoldsData.m_nCurrentMoldIndex);

            SetoutVM::GetInstance()->UpdateMoldSerialNumberResult(result.moldResult,
                                                                  m_strcSetoutMoldsData.m_nCurrentMoldIndex);

            // update to report tab // обновить до на вкладку отчет
            InspectionInfoItem inspectionInfoItem = ReportVM::GetInstance()->CreateInspectionData(result.defectInfos, result.defectCodes);
            inspectionInfoItem.setDateTime(InspectionInfoChildItem(result.dateTime, true));
            inspectionInfoItem.setLotID(InspectionInfoChildItem(QString("%1")
                .arg(ConfigApplication::instance()->m_commonInfo.appSetting.m_nCurrentReport + 1), true));
            inspectionInfoItem.setJob(InspectionInfoChildItem(ConfigApplication::instance()->m_strConfigRecipeName, true));
            inspectionInfoItem.setMoldNumber(InspectionInfoChildItem(m_strcSetoutMoldsData.m_ListMoldNumbers[m_strcSetoutMoldsData.m_nCurrentMoldIndex], true));
            ReportVM::GetInstance()->AddInspectionData(inspectionInfoItem);

            // update system tab
            scopedSystemVM.data()->UpdateInspectInfo();

            // add to sql
            SQLManagement::GetInstance()->AddInspectionData(inspectionInfoItem);

            // Reset variable inspect
            scopedInspectionCore.data()->ResetOutputBackendInfo();




            // // inspect folder // //  Проверка папки
            // if(this->hashTrackVM[camIndex]->isInspecFolder) // inspect folder
            // {
            //     this->hashTrackVM[camIndex]->GetNextInspectFolder();
            // }
        }
        else if(result.function == BACKEND_FUNCTION::NON_ROUND_SHAPE_INSPECT_DONE)
        {
            hashTrackVM[TRACK_INDEX::CAMERA_1]->UpdateImageOverlay(result.operatorImages[TRACK_INDEX::CAMERA_1], 0);
            hashTrackVM[TRACK_INDEX::CAMERA_1]->SetProcessTime(0, result.processTime);
            hashTrackVM[TRACK_INDEX::CAMERA_1]->setInspectionInfo(ConfigApplication::instance()->m_listInspectInfoState[2]);

            // add defect info // добавить информацию о дефекте
            scopedMainHomeVM.data()->AddDefectInfos(result.defectInfos);
            scopedInspectionCore.data()->ResetOutputBackendInfo();
        }
        else if(result.function == BACKEND_FUNCTION::TOP_INSPECT_DONE ||
                   result.function == BACKEND_FUNCTION::CORRECTION_INSPECT_DONE)
        {
            hashTrackVM[TRACK_INDEX::CAMERA_2]->UpdateImageOverlay(result.operatorImages[TRACK_INDEX::CAMERA_2], 0);
            hashTrackVM[TRACK_INDEX::CAMERA_2]->SetProcessTime(0, result.processTime);
            hashTrackVM[TRACK_INDEX::CAMERA_2]->setInspectionInfo(ConfigApplication::instance()->m_listInspectInfoState[2]);

            // add defect info // добавить информацию о дефекте
            scopedMainHomeVM.data()->AddDefectInfos(result.defectInfos);
            scopedInspectionCore.data()->ResetOutputBackendInfo();
        }
        else if(result.function == BACKEND_FUNCTION::VALIDATION_INSPECT_DONE)
        {
            for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
            {
                hashTrackVM[(TRACK_INDEX)i]->UpdateImageOverlay(result.operatorImages[(TRACK_INDEX)i], 0);
                hashTrackVM[(TRACK_INDEX)i]->SetProcessTime(0, result.processTime);
                hashTrackVM[(TRACK_INDEX)i]->setInspectionInfo(ConfigApplication::instance()->m_listInspectInfoState[2]);
            }

            // add defect info // добавить информацию о дефекте
            scopedMainHomeVM.data()->AddDefectInfos(result.defectInfos);


            // update to validation tab
            InspectionInfoItem inspectionInfoItem = ReportVM::GetInstance()->CreateInspectionData(result.defectInfos, result.defectCodes);
            inspectionInfoItem.setDateTime(InspectionInfoChildItem(result.dateTime, true));
            ValidationVM::GetInstance()->AddInspectionData(inspectionInfoItem);


            // Reset variable inspect
            scopedInspectionCore.data()->ResetOutputBackendInfo();


            // popup dialog

            DialogVM::instance()->ShowDialog(tr("Validation"), \
                                             tr("Validation Test is completed"), 1);
        }
        else if(result.function == BACKEND_FUNCTION::CALIBRATION_INSPECT_DONE)
        {
            for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
            {
                hashTrackVM[(TRACK_INDEX)i]->UpdateImageOverlay(result.operatorImages[(TRACK_INDEX)i], 0);
                hashTrackVM[(TRACK_INDEX)i]->SetProcessTime(0, result.processTime);
                hashTrackVM[(TRACK_INDEX)i]->setInspectionInfo(ConfigApplication::instance()->m_listInspectInfoState[2]);
            }

            // add defect info // добавить информацию о дефекте
            scopedMainHomeVM.data()->AddDefectInfos(result.defectInfos);

            if(result.defectCodes[0] == BACKEND_RESULT::PASS)
            {
                // popup dialog
                emit CalibTableVM::GetInstance()->openConfirmSaveDialog();

            }
            else
            {
                CalibTableVM::GetInstance()->confirmSaveCalib_Qml_Slot(false);
                // popup dialog
                DialogVM::instance()->ShowDialog(tr("Calibration"), \
                                                 tr("Calibration failed\n"
                                                    "Please recalibrate"), 4);

            }



            // Reset variable inspect
            scopedInspectionCore.data()->ResetOutputBackendInfo();

            emit CalibTableVM::GetInstance()->isShowWaitingCalib(false);
        }

    } catch (const std::exception &e) {
        ConfigApplication::instance()->WriteDebugLog("Inspection", "Inspect: except" + QString::fromStdString(e.what()));
    }


}

void MasterApp::modelLoaded_InspectionCore_Slots(QStringList &listClassName)
{
    // qDebug() << "[MasterApp]" << "DL model loaded" << "Update statistics table";
    // scopedMainHomeVM.data()->scopedStatisticsVM.data()->InitStatisticsTable(listClassName);
}

void MasterApp::recipeLoaded_InspectionCore_Slots(bool value)
{
    ConfigApplication::instance()->WriteDebugLog("[Inspection Core]", QString("Backend load recipe: %1").arg(value ? "success" : "fail"));
    DebugLogVM::instance()->WriteDebugLog("MasterApp", QString("Backend load recipe: %1").arg(value ? "success" : "fail"), tr(""));
}

void MasterApp::StartToChangeLanguage()
{
    for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; i++)
    {
        if(!scopedInspectionCore.data()->scopedTCPBackendClient.data()->isConnected)
            this->hashTrackVM[(TRACK_INDEX)(i)]->setInspectionInfo(QCoreApplication::translate("ConfigApplication", ConfigApplication::instance()->m_listInspectInfoState[1].toStdString().c_str()));

        // one doc so set at doc 0 // один документ установлен на doc 0
        this->hashTrackVM[(TRACK_INDEX)(i)]->SetDocName(0, ConfigApplication::instance()->ConvertTrackIndexToString((TRACK_INDEX)i));
    }

    scopedMainHomeVM.data()->StartToChangeLanguage();
    ReportVM::GetInstance()->StartToChangeLanguage();
    emit PLCCommunicationLogVM::GetInstance()->changeLanguageSignal();
    emit EditRecipeVM::GetInstance()->changeLanguage_Signal();
    emit machineStatusChanged(ConfigApplication::instance()->m_nCurrentMachineStatusIndex);
}

void MasterApp::StartToUpdateMTData()
{
    // Find current status // Узнать текущее состояние
    int index = ConfigApplication::instance()->m_nCurrentMachineStatusIndex;

    // in status register group
    // when add more status bit need update m_hashNumberBitStatusRegisterUsed
    for (int k = 0; k < ConfigApplication::instance()->m_lRegusterStatus.count(); ++k)
    {
        int u = ConfigApplication::instance()->m_lRegusterStatus[k];
        // init status register values
        if(!ConfigApplication::instance()->m_hashStatusRegisterValues.contains(u))
        {
            ConfigApplication::instance()->m_hashStatusRegisterValues[u] = 0;
        }

        quint16 currentVal;
        MBCommunication::GetInstance()->ReadUnit16Data(MT_HOLDING_REGISTER, u, currentVal);

        // if(currentVal == ConfigApplication::instance()->m_hashStatusRegisterValues[u])
        // {
        //     continue;
        // }

        // uint16_t result = (currentVal ^ ConfigApplication::instance()->m_hashStatusRegisterValues[u]) & currentVal;

        index = GetFirstSetBitPosition(currentVal);
        ConfigApplication::instance()->m_hashStatusRegisterValues[u] = currentVal;

        if(u == 1025)
        {
            qDebug() << u << currentVal << index << index + (ConfigApplication::instance()->m_hashStatusRegisterIndex[u])*16;
        }

        if(index != -1 && index < ConfigApplication::instance()->m_hashNumberBitStatusRegisterUsed[u])
        {
            index += (ConfigApplication::instance()->m_hashStatusRegisterIndex[u])*16;
            break;
        }
    }



    if(index != -1 && ConfigApplication::instance()->m_nCurrentMachineStatusIndex != index)
    {
        qDebug() << "[MasterApp]" << "Change machine status: " << index;
        ConfigApplication::instance()->m_nCurrentMachineStatusIndex = index;
        emit machineStatusChanged(index);
    }

    // set running/stop button status

    quint16 currentVal;
    MBCommunication::GetInstance()->ReadUnit16Data(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_STATUS_START, currentVal);
    bool staus = (currentVal >> 4) & 1;
    if(ConfigApplication::instance()->m_appStatus == APP_STATUS::RUNNING && !staus)
    {
        // stop
        ConfigApplication::instance()->m_appStatus = APP_STATUS::STOP;
        emit scopedTabControlVM.data()->appStatusBtnChanged_Signal(false);
    }
    else if(ConfigApplication::instance()->m_appStatus == APP_STATUS::STOP && staus)
    {
        // running
        ConfigApplication::instance()->m_appStatus = APP_STATUS::RUNNING;
        emit scopedTabControlVM.data()->appStatusBtnChanged_Signal(true);
    }




    // feeder pusher tab //  Вкладка актуаторы
    float scalePusherDistance;
    MBCommunication::GetInstance()->ReadFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_SCALE_PUSHER_CURRENT_VALUE, scalePusherDistance);
    scopedFeederAndPushersVM.data()->setScalePusherDistance(scalePusherDistance);

    float tablePusherDistance;
    MBCommunication::GetInstance()->ReadFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_TABLE_PUSHER_CURRENT_VALUE, tablePusherDistance);
    scopedFeederAndPushersVM.data()->setTablePusherDistance(tablePusherDistance);

    float scaleValue;
    MBCommunication::GetInstance()->ReadFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_SCALE_CURRENT_VALUE, scaleValue);
    scopedFeederAndPushersVM.data()->setScaleValue(scaleValue);

    float motorCameraValue;
    MBCommunication::GetInstance()->ReadFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_CAMERA_POSITION_CURRENT_VALUE, motorCameraValue);
    scopedFeederAndPushersVM.data()->setMotorCameraValue(motorCameraValue);


    float pushupDistance;
    MBCommunication::GetInstance()->ReadFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_PUSHUP_DISTANCE_CURRENT_VALUE, pushupDistance);
    scopedFeederAndPushersVM.data()->setPushupDistance(pushupDistance);

    // table tab // вкладка стол
    float tableElevationValue;
    MBCommunication::GetInstance()->ReadFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_TABLE_LIFTING_CURRENT_VALUE, tableElevationValue);
    scopedTableVM.data()->setTableElevationValue(tableElevationValue);

    float tableAngleValue;
    MBCommunication::GetInstance()->ReadFloatData(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_TABLE_TURNING_CURRENT_VALUE, tableAngleValue);
    scopedTableVM.data()->setTableAngleValue(tableAngleValue);

    // setout // установка
    quint16 diagnostic3Value;
    MBCommunication::GetInstance()->ReadUnit16Data(MT_HOLDING_REGISTER, (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3, diagnostic3Value);
    SetoutVM::GetInstance()->setHighPressureStatus(((diagnostic3Value >> 7) & 1) ? 1 : 0);
    SetoutVM::GetInstance()->setSafetyRelayStatus(((diagnostic3Value >> 13) & 1) ? 1 : 0);

    // CalibrationHandler();

    // BottleTransferredIlnfeedSensorHandler();

    // call inspection
    InspectionSequence();
    // m_pCommandThread->ReceiveCommand(COMMAND_INSPECTION_SEQUENCE, 0);
}

