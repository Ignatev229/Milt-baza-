#include "ribbon_vm.h"
#include "../../ViewModel/Main/main_home_vm.h"
RibbonVM::RibbonVM(QQmlApplicationEngine &appEngine,
                   QHash<TRACK_INDEX, TrackVM*> hashTrackVM,
                   QObject *parent)
{
    m_pParentObject = reinterpret_cast<MainHomeVM*>(parent);
    this->hashTrackVM = hashTrackVM;
    isGlassContainerShapeInspect = false;
    isTopInspect = false;
    CreateConnection();
}

QString RibbonVM::oldLoadImagePath()
{
    return _oldLoadImagePath;
}

void RibbonVM::CreateConnection()
{
    foreach (TRACK_INDEX key, hashTrackVM.keys()) {
        //        if(hashTrackVM[key]->scopedCameraVM.data() == nullptr || !ConfigApplication::instance()->m_hashConfigCameras.contains(key))
        //            continue;
        connect(this->hashTrackVM.value(key), SIGNAL(inspectFolderStatusChanged_Signal(bool)), this,
                SLOT(inspectFolderStatusChanged_TrackVM_Slot(bool)));
    }
}

void RibbonVM::InspectGlassContainerShapeFolder(QString path)
{
    // only inspect bottom image // просматривайте только нижнее (корпус) изображение
    QFuture<void> future = QtConcurrent::run([=]() {
        if(isGlassContainerShapeInspect)
        {
            QDir directory(path);
            QStringList listImageInspectFolder = directory.entryList(QStringList() << "*.png" << "*.PNG" << "*.bmp" << "*.jpg", QDir::Files);
            for (int i = 0; i < listImageInspectFolder.count(); ++i)
            {
                // load image // загрузить изображение
                QString imagePath = QString("%1/%2")
                                        .arg(path)
                                        .arg(listImageInspectFolder[i]);
                hashTrackVM[TRACK_INDEX::CAMERA_1]->UpdateImageFromFile(imagePath, 0);
                // call inspect // вызовите  Проверку
                emit inspect_Signal(i == 0 ? BACKEND_FUNCTION::NON_ROUND_SHAPE_INSPECT_START :
                                        BACKEND_FUNCTION::NON_ROUND_SHAPE_INSPECT);
                QThread::msleep(1000);
            }
            emit inspectGlassContainerShapeStatusChanged_Signal(false);
        }
    });
}

void RibbonVM::InspectTopFolder(QString path)
{
    // only inspect top image // просматривайте только верхнее изображение
    QFuture<void> future = QtConcurrent::run([=]() {
        if(isTopInspect)
        {
            QDir directory(path);
            QStringList listImageInspectFolder = directory.entryList(QStringList() << "*.png" << "*.PNG" << "*.bmp" << "*.jpg", QDir::Files);
            for (int i = 0; i < listImageInspectFolder.count(); ++i)
            {
                // load image // загрузить изображение
                QString imagePath = QString("%1/%2")
                                        .arg(path)
                                        .arg(listImageInspectFolder[i]);
                hashTrackVM[TRACK_INDEX::CAMERA_2]->UpdateImageFromFile(imagePath, 0);
                // call inspect // вызовите  Проверку
                emit inspect_Signal(i == 0 ? BACKEND_FUNCTION::TOP_INSPECT_START :
                                        BACKEND_FUNCTION::TOP_INSPECT);
                QThread::msleep(1000);
            }
            emit inspectTopStatusChanged_Signal(false);
        }
    });
}

void RibbonVM::setOldLoadImagePath(QString value)
{
    QFileInfo fi(value);
    if(_oldLoadImagePath != fi.dir().absolutePath()){_oldLoadImagePath = fi.dir().absolutePath(); emit oldLoadImagePathChanged();}
}


void RibbonVM::loadImage_Qml_Slot(QString path)
{
    // ConfigApplication::instance()->WriteDebugLog("UI", QString("Click LoadImage Camera %1").arg(currentTrackIndex));
    ConfigApplication::instance()->WriteDebugLog("UI", "Click LoadImage");
    QString rootPath = ConfigApplication::instance()->GetRootImagePath(path);
    for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
    {
        QString imagePath = QString("%1%2%3")
                                .arg(rootPath)
                                .arg(ConfigApplication::instance()->m_hashExtendImageName[(TRACK_INDEX)i])
                                .arg(ConfigApplication::instance()->m_strImageExtension);
        hashTrackVM[(TRACK_INDEX)i]->UpdateImageFromFile(imagePath, 0);
        ConfigApplication::instance()->m_commonInfo.appSetting.cameraConfig[(TRACK_INDEX)i].oldLoadImagePath = path;
        ConfigApplication::instance()->WriteAppSetting();
        setOldLoadImagePath(path);
    }

}

void RibbonVM::snap_Qml_Slot()
{
    ConfigApplication::instance()->WriteDebugLog("UI", QString("Click Snap Camera %1").arg(currentTrackIndex));
    hashTrackVM[currentTrackIndex]->Snap();
    // ConfigApplication::instance()->WriteDebugLog("UI", QString("Click Snap"));
    // for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
    // {
    //     hashTrackVM[(TRACK_INDEX)i]->Snap();
    // }
}

void RibbonVM::stream_Qml_Slot(bool value)
{
    ConfigApplication::instance()->WriteDebugLog("UI", QString("Click Stream Camera %1").arg(currentTrackIndex));
    hashTrackVM[currentTrackIndex]->Stream(value);
    // ConfigApplication::instance()->WriteDebugLog("UI", QString("Click Stream"));
    // for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
    // {
    //     hashTrackVM[(TRACK_INDEX)i]->Stream(value);
    // }
}

void RibbonVM::saveImage_Qml_Slot(QString path)
{
    // ConfigApplication::instance()->WriteDebugLog("UI", QString("Click SaveImage Camera %1").arg(currentTrackIndex));
    ConfigApplication::instance()->WriteDebugLog("UI", QString("Click SaveImage"));

    // if(path.contains(".png") || path.contains(".jpg") || path.contains(".bmp"))
    //     hashTrackVM[currentTrackIndex]->imageViewFeatures[0].imageViewVM->image().save(path);
    // else
    //     hashTrackVM[currentTrackIndex]->imageViewFeatures[0].imageViewVM->image().save(path + ".bmp");

    for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
    {
        QString imagePath = QString("%1%2%3")
                                .arg(path)
                                .arg(ConfigApplication::instance()->m_hashExtendImageName[(TRACK_INDEX)i])
                                .arg(ConfigApplication::instance()->m_strImageExtension);
        hashTrackVM[(TRACK_INDEX)i]->imageViewFeatures[0].imageViewVM->image().save(imagePath, "JPG", 100);
    }
}

void RibbonVM::inspect_Qml_Slot()
{
    // ConfigApplication::instance()->WriteDebugLog("UI", QString("Click Inspect Camera %1").arg(currentTrackIndex));
    // hashTrackVM[currentTrackIndex]->Inspect();
    ConfigApplication::instance()->WriteDebugLog("UI", QString("Click Inspect"));
    emit inspect_Signal(BACKEND_FUNCTION::INSPECT);
}

void RibbonVM::inspectCycle_Qml_Slot(bool value)
{
    // ConfigApplication::instance()->WriteDebugLog("UI", QString("Click InspectCycle Camera %1").arg(currentTrackIndex));
    // hashTrackVM[currentTrackIndex]->InspectCycle(value);

    ConfigApplication::instance()->WriteDebugLog("UI", QString("Click InspectCycle"));
    m_pParentObject->InspectCycle(value);
}

void RibbonVM::inspectFolder_Qml_Slot(bool value, QString path)
{
    ConfigApplication::instance()->WriteDebugLog("UI", QString("Click InspectFolder Camera %1").arg(currentTrackIndex));

    hashTrackVM[currentTrackIndex]->InspectFolder(value, path);
}

void RibbonVM::inspectGlassContainerShape_Qml_Slot(bool isInspect, QString path)
{
    ConfigApplication::instance()->WriteDebugLog("UI", QString("Click Inspect Glass Container Shape"));
    qDebug() << isInspect << path;
    isGlassContainerShapeInspect = isInspect;
    if(isInspect)
        InspectGlassContainerShapeFolder(path);
    // emit inspect_Signal(BACKEND_FUNCTION::INSPECT);
}

void RibbonVM::inspectTop_Qml_Slot(bool isInspect, QString path)
{
    ConfigApplication::instance()->WriteDebugLog("UI", QString("Click Inspect Top"));
    qDebug() << isInspect << path;
    isTopInspect = isInspect;
    if(isInspect)
        InspectTopFolder(path);
}

void RibbonVM::inspectFolderStatusChanged_TrackVM_Slot(bool value)
{
    emit inspectFolderStatusChanged_Signal(value);
}
















