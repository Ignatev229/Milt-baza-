#include "main_home_vm.h"
#include "../../ViewModel/master_app.h"

MainHomeVM::MainHomeVM(QQmlApplicationEngine &appEngine,
                       QHash<TRACK_INDEX, TrackVM*> hashTrackVM,
                       QObject *parent)
{

    m_pParentObject = reinterpret_cast<MasterApp*>(parent);
    this->hashTrackVM = hashTrackVM;
    currentTrackIndex = TRACK_INDEX::CAMERA_1;
    currentDocIndex = 0;

    // initial //исходный
    // ribbon //Лента
    scopedRibbonVM.reset(new RibbonVM(appEngine, hashTrackVM, this));
    appEngine.rootContext()->setContextProperty(QStringLiteral("ribbonVM"), scopedRibbonVM.data());
    QList<TrackVM*> Tracks;
    QList<int> numHorizontalCell;
    QList<int> numVerticalCell;
    for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
    {
        Tracks.append(hashTrackVM[(TRACK_INDEX)i]);
        numHorizontalCell.append(1);
        numVerticalCell.append(1);
    }


    this->setNumHorizontalCell(numHorizontalCell);
    this->setNumVerticalCell(numVerticalCell);
    this->setListTrackVM(Tracks);

    // create connect // создать соединение
    this->CreateConnection();
    SetCurrentTrackDoc(currentTrackIndex, currentDocIndex);

    for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i) {
        Tracks[i]->scopedCameraInterface.data()->RegisterCamera();
        Tracks[i]->scopedCameraInterface.data()->start();
    }

    // debug log // журнал отладки
    qmlRegisterType<DebugLogModel>("DataDebugLog", 1, 0, "DebugLogModel");
    qmlRegisterUncreatableType<DebugLogVM>("DataDebugLog", 1, 0, "DebugLogVM", QStringLiteral("DebugLog should not be created in QML"));
    appEngine.rootContext()->setContextProperty(QStringLiteral("debugLogVM"), DebugLogVM::instance());

    // statistic // статистика

    scopedStatisticsVM.reset(new StatisticsVM());
    qmlRegisterType<StatisticsModel>("DataStatistics", 1, 0, "StatisticsModel");
    qmlRegisterUncreatableType<StatisticsVM>("DataStatistics", 1, 0, "StatisticsVM",
                                             QStringLiteral("Statistics should not be created in QML"));
    appEngine.rootContext()->setContextProperty(QStringLiteral("statisticsVM"), scopedStatisticsVM.data());
    scopedStatisticsVM.data()->InitStatisticsTable();

    // inspect cycle // цикл проверки
    inspectCycleTimer.reset(new QTimer());
    connect(inspectCycleTimer.data(), SIGNAL(timeout()), this, SLOT(inspectCyleTimeout()));
}

MainHomeVM::~MainHomeVM()
{
    scopedRibbonVM.data()->deleteLater();
    scopedStatisticsVM.data()->deleteLater();
    inspectCycleTimer.data()->deleteLater();
}

// property //собственность

QList<TrackVM *> MainHomeVM::listTrackVM()
{
    return _listTrackVM;
}

QList<double> MainHomeVM::resolutions()
{
    return _resolutions;
}

QList<int> MainHomeVM::numHorizontalCell()
{
    return _numHorizontalCell;
}

QList<int> MainHomeVM::numVerticalCell()
{
    return _numVerticalCell;
}

void MainHomeVM::setListTrackVM(QList<TrackVM *> &value)
{
    if(_listTrackVM != value)
    {
        _listTrackVM = value;
        emit listTrackVMChanged();
    }
}

void MainHomeVM::setNumHorizontalCell(QList<int> value)
{
    if(_numHorizontalCell != value)
    {
        _numHorizontalCell = value;
        emit numHorizontalCellChanged();
    }
}

void MainHomeVM::setNumVerticalCell(QList<int> value)
{
    if(_numVerticalCell != value)
    {
        _numVerticalCell = value;
        emit numVerticalCellChanged();
    }
}

void MainHomeVM::setResolutions(QList<double> value)
{
    if(_resolutions != value)
    {
        _resolutions = value;
        emit resolutionsChanged();
    }
}

// end property // конечное свойство

QObject *MainHomeVM::trackListAt(int index) const
{
    if (index<0 || index>= _listTrackVM.size())
        return nullptr;
    return _listTrackVM[index];
}

void MainHomeVM::SetCurrentTrackDoc(TRACK_INDEX camID, int docID)
{
    currentTrackIndex = camID;
    currentDocIndex = docID;
    scopedRibbonVM.data()->currentTrackIndex = camID;
    scopedRibbonVM.data()->currentDocIndex = docID;
    // set default path // установить путь по умолчанию
    scopedRibbonVM.data()->setOldLoadImagePath(ConfigApplication::instance()->m_commonInfo.appSetting.cameraConfig[currentTrackIndex].oldLoadImagePath);
}

void MainHomeVM::SetDocName(TRACK_INDEX camID, int docID, QString name)
{
    this->hashTrackVM[camID]->SetDocName(docID, name);
}

void MainHomeVM::UpdateDisconnectImage(TRACK_INDEX camID)
{
    this->hashTrackVM[camID]->UpdateDisconnectImage(0);
}

void MainHomeVM::StreamAllCam(bool isStream)
{
    for(int i = 0; i < ConfigApplication::instance()->m_nCamNum; i++)
        this->hashTrackVM[(TRACK_INDEX)i]->scopedCameraInterface.data()->Stream(isStream);
}

void MainHomeVM::SetDLModelVersion()
{

}

void MainHomeVM::StartToChangeLanguage()
{
    emit scopedStatisticsVM.data()->changeLanguageSignal();
    emit DebugLogVM::instance()->changeLanguageSignal();
    emit startToChangeLanguage_Signal();
}

void MainHomeVM::AddDefectInfos(QList<DefectInfoItem> defectInfos)
{
    emit clearDataToDefectInforSignal();
    for (int i = 0; i < defectInfos.count(); ++i)
    {
        emit addDataToDefectInforSignal(defectInfos[i].trackIndex,
                                        ConfigApplication::instance()->ConvertDefectCodeToString(defectInfos[i].defect),
                                        defectInfos[i].parameter,
                                        QString::number(defectInfos[i].pixelValue, 'f', 2),
                                        QString::number(defectInfos[i].mmValue, 'f', 2));
    }
}

void MainHomeVM::UpdateResolutionToUI()
{
    QList<double> resolutions;
    for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i) {
        resolutions.append(ConfigApplication::instance()->
                           m_commonInfo.appSetting.cameraConfig[(TRACK_INDEX)i].resolution);
    }
    setResolutions(resolutions);
}

void MainHomeVM::Snap(TRACK_INDEX trackIndex)
{
    if(trackIndex < 0 || trackIndex >= TRACK_INDEX::TRACK_COUNT)
        return;
    hashTrackVM[trackIndex]->Snap();
}

void MainHomeVM::InspectCycle(bool value)
{
    if(value)
    {
        inspectCycleTimer.data()->start(1500);
    }
    else
    {
        inspectCycleTimer.data()->stop();
    }
}

void MainHomeVM::Inspect(BACKEND_FUNCTION function)
{
    InputBackendInfo input;
    input.function = function;
    input.correctionData = "";

    if(function == BACKEND_FUNCTION::INSPECT)
    {
        if(m_pParentObject->m_strcInspectionSequenceData.m_hashSequencePosImages.count() ==
            INSPECT_SEQUENCE_CAMERA_POSITION::TOTAL_POS)
        {
            // inspect online // проверять онлайн
            for (int i = 0; i < INSPECT_SEQUENCE_CAMERA_POSITION::TOTAL_POS; ++i) {
                input.images[(INSPECT_SEQUENCE_CAMERA_POSITION)i] =
                    m_pParentObject->m_strcInspectionSequenceData.m_hashSequencePosImages[(INSPECT_SEQUENCE_CAMERA_POSITION)i].copy();
            }
        }
        else
        {
            // inspect offline // проверять в  Оффлайне
            for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i) {
                QImage image = hashTrackVM[(TRACK_INDEX)i]->GetDocImage(0);
                if(image.width()%4 != 0)
                {
                    DialogVM::instance()->ShowDialog(tr("Wrong Image Size"), \
                        tr("Image width need divisible by 4"), 2);
                    return;
                }
                input.images[(INSPECT_SEQUENCE_CAMERA_POSITION)(i+1)] = image;
            }
        }
        hashTrackVM[TRACK_INDEX::CAMERA_1]->setInspectionInfo(ConfigApplication::instance()->m_listInspectInfoState[0]);
    }
    else if(function == BACKEND_FUNCTION::NON_ROUND_SHAPE_INSPECT ||
               function == BACKEND_FUNCTION::NON_ROUND_SHAPE_INSPECT_START)
    {
        // shape (bottom2) //форма ( Корпуса (bottom2)
        input.images[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2] = hashTrackVM[TRACK_INDEX::CAMERA_1]->GetDocImage(0);
        hashTrackVM[TRACK_INDEX::CAMERA_1]->setInspectionInfo(ConfigApplication::instance()->m_listInspectInfoState[0]);
    }
    else if(function == BACKEND_FUNCTION::TOP_INSPECT ||
             function == BACKEND_FUNCTION::TOP_INSPECT_START)
    {
        // knockout (top) // нокаут (вверху)
        input.images[INSPECT_SEQUENCE_CAMERA_POSITION::TOP] = hashTrackVM[TRACK_INDEX::CAMERA_2]->GetDocImage(0);
        hashTrackVM[TRACK_INDEX::CAMERA_2]->setInspectionInfo(ConfigApplication::instance()->m_listInspectInfoState[0]);
    }
    else if(function == BACKEND_FUNCTION::VALIDATION_INSPECT)
    {
        // validation inspect
        // input.images[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1] = hashTrackVM[TRACK_INDEX::CAMERA_1]->GetDocImage(0);
        // input.images[INSPECT_SEQUENCE_CAMERA_POSITION::TOP] = hashTrackVM[TRACK_INDEX::CAMERA_2]->GetDocImage(0);

        if(ValidationVM::GetInstance()->m_hashSequencePosImages.count() ==
            INSPECT_SEQUENCE_CAMERA_POSITION::TOTAL_POS)
        {
            // validation
            for (int i = 0; i < INSPECT_SEQUENCE_CAMERA_POSITION::TOTAL_POS; ++i) {
                input.images[(INSPECT_SEQUENCE_CAMERA_POSITION)i] =
                    ValidationVM::GetInstance()->m_hashSequencePosImages[(INSPECT_SEQUENCE_CAMERA_POSITION)i].copy();
            }
        }

        hashTrackVM[TRACK_INDEX::CAMERA_1]->setInspectionInfo(ConfigApplication::instance()->m_listInspectInfoState[0]);
    }
    else if(function == BACKEND_FUNCTION::CALIBRATION_INSPECT)
    {
        // calibration
        if(CalibTableVM::GetInstance()->m_hashSequencePosImages.count() ==
            INSPECT_SEQUENCE_CAMERA_POSITION::TOTAL_POS)
        {
            for (int i = 0; i < INSPECT_SEQUENCE_CAMERA_POSITION::TOTAL_POS; ++i) {
                input.images[(INSPECT_SEQUENCE_CAMERA_POSITION)i] =
                    CalibTableVM::GetInstance()->m_hashSequencePosImages[(INSPECT_SEQUENCE_CAMERA_POSITION)i].copy();
            }
        }

        hashTrackVM[TRACK_INDEX::CAMERA_1]->setInspectionInfo(ConfigApplication::instance()->m_listInspectInfoState[0]);
    }
    else if(function == BACKEND_FUNCTION::CORRECTION_FIRST_INSPECT ||
               function == BACKEND_FUNCTION::CORRECTION_INSPECT)
    {
        // correction
        if(hashTrackVM[TRACK_INDEX::CAMERA_2]->GetDocImage(0).width()%4 != 0)
        {
            return;
        }
        input.images[INSPECT_SEQUENCE_CAMERA_POSITION::TOP] = hashTrackVM[TRACK_INDEX::CAMERA_2]->GetDocImage(0);


        hashTrackVM[TRACK_INDEX::CAMERA_2]->setInspectionInfo(ConfigApplication::instance()->m_listInspectInfoState[0]);

        // correction info
        // defect index, vp
        input.correctionData = QString("%1,%2")
                                .arg(CorrectionVM::GetInstance()->currentDefectCorrection)
                                .arg(CorrectionVM::GetInstance()->currentDefectParameter);
    }


    // get plc info // получить информацию о плк
    input.weight = m_pParentObject->m_strcInspectionSequenceData.m_dWeight;
    input.depth = m_pParentObject->m_strcInspectionSequenceData.m_dDepth;




    emit inspect_Signal(input);
}

void MainHomeVM::CreateConnection()
{
    for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
    {
        if(hashTrackVM[(TRACK_INDEX)i]->scopedCameraInterface.data() == nullptr || !ConfigApplication::instance()->m_commonInfo.appSetting.cameraConfig.contains((TRACK_INDEX)i))
            continue;
        connect(this->hashTrackVM[(TRACK_INDEX)i]->scopedCameraInterface.data(), SIGNAL(cameraConnectedStatusChanged_Signal(TRACK_INDEX, bool)), this,
                SLOT(cameraConnectedStatusChanged_CameraInterface_Slots(TRACK_INDEX, bool)));
        connect(this->hashTrackVM[(TRACK_INDEX)i]->scopedCameraInterface.data(), SIGNAL(sendImageCamToMain_Signal(TRACK_INDEX, QImage, bool, QString)), this,
                SLOT(updateImage_CameraInterface_Slot(TRACK_INDEX, QImage, bool, QString)));
    }

    // ribbon //Лента
    connect(scopedRibbonVM.data(), SIGNAL(inspect_Signal(BACKEND_FUNCTION)), this, SLOT(Inspect(BACKEND_FUNCTION)));
}

void MainHomeVM::updateImage_CameraInterface_Slot(TRACK_INDEX camID, QImage image, bool isInspect, QString imageResultName)
{
    QImage img_in_thread = image.copy();

    this->hashTrackVM[camID]->UpdateImage(img_in_thread, 0);
    // inspect online // проверять онлайн
    if(isInspect)
    {
        this->hashTrackVM[camID]->Inspect();
    }

}


void MainHomeVM::cameraConnectedStatusChanged_CameraInterface_Slots(TRACK_INDEX camID, bool isConnected)
{
    if(isConnected)
    {
        hashTrackVM[camID]->Snap();
    }
    else
    {
        hashTrackVM[camID]->UpdateDisconnectImage(0);
    }
    hashTrackVM[camID]->SetCameraSerialNumber(0);

}

void MainHomeVM::currentTrackChanged_Qml_Slot(TRACK_INDEX currentTrackIndex)
{
    SetCurrentTrackDoc(currentTrackIndex, 0);
}

void MainHomeVM::inspectCyleTimeout()
{
    qDebug() << "[MainHomeVM]" << "Inspect cycle";

    // call inspect //вызовите Проверку
    Inspect(BACKEND_FUNCTION::INSPECT);
}




