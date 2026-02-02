#include "track_vm.h"

TrackVM::TrackVM(QQmlApplicationEngine &appEngine, TRACK_INDEX trackID, QStringList listDocName)
{
    appEngine.isWindowType();

    // create track // создать трек
    this->trackID = trackID;
    this->numDoc = listDocName.size();
    this->isInspecFolder = false;
    for(int i = 0; i < numDoc; i++)
    {
        this->imageViewFeature.imageViewVM = new ImageViewVM(trackID, i, listDocName[i]);
        this->imageViewFeatures.append(this->imageViewFeature);

        connect(this->imageViewFeature.imageViewVM, &ImageViewVM::doSnapImageSignal, this, &TrackVM::doSnapImageDoc);
    }
    this->_imageModel = new ImageModel();
    this->_imageModel->createData(this->imageViewFeatures);

    // create connect // создать подключение
    CreateConnection();
    if(ConfigApplication::instance()->m_commonInfo.appSetting.cameraConfig.contains(trackID))
    {
        scopedCameraInterface.reset(new CameraInterface(trackID,
            ConfigApplication::instance()->m_commonInfo.appSetting.cameraConfig[trackID].serial, trackID));
    }

    // inspect cycle // цикл проверки
    inspectCycleTimer.reset(new QTimer());
    connect(inspectCycleTimer.data(), SIGNAL(timeout()), this, SLOT(inspectCyleTimeout()));
}

TrackVM::~TrackVM()
{
    scopedCameraInterface.data()->isStream = false;
    scopedCameraInterface.data()->deleteLater();
    inspectCycleTimer.data()->deleteLater();
}
// Property //  Собственность
ImageModel* TrackVM::imageModel()
{
    return _imageModel;
}

QString TrackVM::inspectFolderInfo()
{
    return _inspectFolderInfo;
}

int TrackVM::inspectCycleInfo()
{
    return _inspectCycleInfo;
}


void TrackVM::setImageModel(ImageModel* value)
{

    _imageModel = value;
    emit imageModelChanged();

}

void TrackVM::setInspectFolderInfo(QString value)
{
    if(_inspectFolderInfo != value){_inspectFolderInfo = value; emit inspectFolderInfoChanged();}

}

void TrackVM::setInspectCycleInfo(int value)
{
    if(_inspectCycleInfo != value){_inspectCycleInfo = value; emit inspectCycleInfoChanged();}
}

void TrackVM::doSnapImageDoc()
{
    Snap();
}

void TrackVM::inspectCyleTimeout()
{
    qDebug() << "[TRACK]" << "Inspect cycle" << trackID;
    inspectCycleCount++;
    imageViewFeatures[0].imageViewVM->setInspectionCycleInfo(inspectCycleCount);

    // call inspect // вызовите проверку
    QImage image = GetDocImage(0);
    UpdateImageOverlay(image, 0);
    Inspect();
}

// end property // конечное свойство

void TrackVM::UpdateImage(QImage &image, int docIndex)
{
    ClearOverlay();
    if(docIndex >= imageViewFeatures.size())
    {
        qDebug() << "Doc index bigger than num doc of this track";
        return;
    }
    imageViewFeatures[docIndex].imageViewVM->setImage(image);
    imageViewFeatures[docIndex].imageViewVM->setImageOverlay(image);
    SetProcessTime(docIndex, 0);
}

void TrackVM::UpdateImageOverlay(QImage &image, int docIndex)
{
    if(docIndex >= imageViewFeatures.size())
    {
        qDebug() << "Doc index bigger than num doc of this track";
        return;
    }
    imageViewFeatures[docIndex].imageViewVM->setImageOverlay(image);
}

void TrackVM::UpdateImageFromFile(QString &imagePath, int docIndex)
{
    if(!QFile::exists(imagePath))
    {

        QImage image = QImage(QString(":/Resources/NoneCamera" + QString::number(trackID + 1) + ".png"));
        UpdateImage(image, docIndex);
        imageViewFeatures[docIndex].imageViewVM->setIsShowBelowImage(true);
        return;
    }
    QImage image(imagePath);
    UpdateImage(image, docIndex);
}

void TrackVM::UpdateImageOverlayFromFile(QString &imagePath, int docIndex)
{
    if(!QFile::exists(imagePath))
        return;
    QImage image(imagePath);
    UpdateImageOverlay(image, docIndex);
}

void TrackVM::UpdateOverlayLeftString(QString value, int docIndex)
{
    imageViewFeatures[docIndex].imageViewVM->setInspectResult(value);
}

QImage TrackVM::GetDocImage(int docIndex)
{
    if(docIndex >= imageViewFeatures.size())
    {
        qDebug() << "Doc index bigger than num doc of this track";
        return QImage();
    }
    return imageViewFeatures[docIndex].imageViewVM->image();
}

void TrackVM::UpdateDisconnectImage(int docIndex)
{
    if(docIndex >= imageViewFeatures.size())
    {
        qDebug() << "Doc index bigger than num doc of this track";
        return;
    }
    imageViewFeatures[docIndex].imageViewVM->UpdateDisconnectImage();
}

void TrackVM::UpdateAllImage(QList<QImage> &images)
{
    if(images.size() != imageViewFeatures.size())
    {
        qDebug() << "Num images diff num doc of this track";
        return;
    }
    for(int i = 0; i < images.size(); i++)
    {
        imageViewFeatures[i].imageViewVM->setImage(images[i]);
    }
}

void TrackVM::UpdateCameraConnect(bool isConnect)
{
    isConnectCam = isConnect;
    for(int i = 0; i < numDoc; i++)
    {
        imageViewFeatures[i].imageViewVM->setIsConnectCam(isConnect);
    }
}

void TrackVM::SetDocName(int docIndex, QString name)
{
    if(docIndex >= imageViewFeatures.size())
    {
        qDebug() << "Doc index bigger than num doc of this track";
        return;
    }
    imageViewFeatures[docIndex].imageViewVM->setDocName(name);
}

void TrackVM::setInspectionInfo(QString value)
{
    imageViewFeatures[0].imageViewVM->setInspectionInfo(value);
}

void TrackVM::ClearOverlay()
{
    UpdateOverlayLeftString("", 0);
}

void TrackVM::Inspect() // inspect // проверить
{
    QImage image = GetDocImage(0);
    Inspect(image);
}

void TrackVM::Inspect(QString imagePath) // inspect from file // проверить из файла
{
    if(!QFile::exists(imagePath))
        return;
    QImage image(imagePath);
    UpdateImage(image, 0);
    Inspect(image);
}

void TrackVM::Inspect(QImage &image) // inspect from image // проверка  из изображения
{
    // if(image.width()%4 != 0)
    // {
    //     DialogVM::instance()->ShowDialog("Wrong Image Size", \
    //         "Image width in camera " + QString::number(trackID + 1) + " need divisible by 4", 2);
    //     return;
    // }
    // InputBackendInfo input;
    // input.function = BACKEND_FUNCTION::INSPECT;
    // input.image = image;

    // QString ImageFolder = ConfigApplication::instance()->m_commonInfo.saving_image_info.save_dir + "/" +\
    //         ConfigApplication::instance()->m_strInspectImageName + "/" +\
    //         QDateTime::currentDateTime().toString("yyyy_MM_dd");

    // if(!QDir(ImageFolder).exists())
    // {
    //    QDir().mkdir(ImageFolder);
    // }
    // input.inputStr = ImageFolder + "/" + QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
    // this->setInspectionInfo(ConfigApplication::instance()->m_listInspectInfoState[0]);
    // emit inspect_Signal(input);
}

void TrackVM::InspectFolder(bool isStart, QString path) // inspect folder
{
    return;
    isInspecFolder = isStart;
    inspectFolderPath = path;
    if(isStart)
    {
        currentInspectFolderIndex = 0;
        QDir directory(inspectFolderPath);
        listImageInspectFolder = directory.entryList(QStringList() << "*.png" << "*.PNG" << "*.bmp" << "*.jpg", QDir::Files);
        GetNextInspectFolder();
    }
    else
    {
        isInspecFolder = false;
        currentInspectFolderIndex = 0;
        imageViewFeatures[0].imageViewVM->setInspectionFolderInfo("");
        listImageInspectFolder.clear();
    }
}

void TrackVM::GetNextInspectFolder()
{
    if(!isInspecFolder) // inspect folder //  Проверка папки
        return;
    if(currentInspectFolderIndex < listImageInspectFolder.length())
    {
        Inspect(inspectFolderPath + "/" + listImageInspectFolder[currentInspectFolderIndex]);
        currentInspectFolderIndex++;
        imageViewFeatures[0].imageViewVM->setInspectionFolderInfo(QString::number(currentInspectFolderIndex) + "/" + QString::number(listImageInspectFolder.length()));
        //        setInspectFolderInfo(QString::number(currentInspectFolderIndex) + "/" + QString::number(listImageInspectFolder.length()));
    }
    else
    {
        emit inspectFolderStatusChanged_Signal(false);
        imageViewFeatures[0].imageViewVM->setInspectionFolderInfo("");
        // complete inspect folder // завершить проверку папки
    }
}

void TrackVM::InspectCycle(bool value)
{
    if(value)
    {
        inspectCycleCount = 0;
        inspectCycleTimer.data()->start(1000);
    }
    else
    {
        inspectCycleTimer.data()->stop();
        imageViewFeatures[0].imageViewVM->setInspectionCycleInfo(0);
    }
}

void TrackVM::SnapAndInspect()
{
    Snap();
    Inspect();
}

void TrackVM::Snap()
{
    ClearOverlay();
    QImage image;
    if(scopedCameraInterface.data()->Snap(image))
        UpdateImage(image, 0);
}

void TrackVM::Stream(bool isStream)
{
    scopedCameraInterface.data()->Stream(isStream);
}

void TrackVM::SetProcessTime(int docIndex, float time)
{
    if(docIndex >= imageViewFeatures.size())
    {
        qDebug() << "Doc index bigger than num doc of this track";
        return;
    }
    imageViewFeatures[docIndex].imageViewVM->setProcessedTime(time);
}

void TrackVM::SetDLModelVersion(QString version)
{
    //    QString ver = version;
    //    imageViewFeatures[0].imageViewVM->setDlModelVersion(ver);
}

void TrackVM::SetCameraSerialNumber(int docIndex)
{

    imageViewFeatures[docIndex].imageViewVM->setSerialNumber(ConfigApplication::instance()->m_commonInfo.appSetting.cameraConfig[trackID].isConnected ?
                                                ConfigApplication::instance()->m_commonInfo.appSetting.cameraConfig[trackID].serial : "N/A");

}

void TrackVM::initialVariable()
{

}

void TrackVM::CreateConnection()
{
    for(int i = 0; i < this->imageViewFeatures.size(); i++)
    {

    }
}

