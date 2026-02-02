#include "image_view_vm.h"

ImageViewVM::ImageViewVM(TRACK_INDEX trackID, int docID, QString docName, QObject *parent)
    : QObject(parent)
{
    _trackID = trackID;
    _docID = docID;
    _docName = docName;

    setSerialNumber("N/A");
    setInspectFunctionName(ConfigApplication::instance()->m_listBackendFunctions[trackID]);
    setIsConnectCam(true);
    setInspectResult("");
    setDocName(ConfigApplication::instance()->ConvertTrackIndexToString(trackID));
    setDlModelVersion("");
    setProcessedTime(0);
    setInspectionCycleInfo(0);
    setInspectionFolderInfo("");
    setIsShowBelowImage(false);
}

ImageViewVM::~ImageViewVM()
{

}


QImage ImageViewVM::image()
{
    return _image;
}

QImage ImageViewVM::imageOverlay()
{
    return _imageOverlay;
}

bool ImageViewVM::isShowBelowImage()
{
    return _isShowBelowImage;
}

QString ImageViewVM::docName()
{
    return _docName;
}

QString ImageViewVM::serialNumber()
{
    return _serialNumber;
}

QString ImageViewVM::inspectFunctionName()
{
    return _inspectFunctionName;
}

QString ImageViewVM::inspectResult()
{
    return _inspectResult;
}


int ImageViewVM::docID()
{
    return _docID;
}

int ImageViewVM::trackID()
{
    return _trackID;
}

bool ImageViewVM::isConnectCam()
{
    return _isConnectCam;
}

QString ImageViewVM::inspectionInfo()
{
    return _inspectionInfo;
}

float ImageViewVM::processedTime()
{
    return _processedTime;
}

QString ImageViewVM::dlModelVersion()
{
    return _dlModelVersion;
}

int ImageViewVM::inspectionCycleInfo()
{
    return _inspectionCycleInfo;
}

QString ImageViewVM::inspectionFolderInfo()
{
    return _inspectionFolderInfo;
}

void ImageViewVM::UpdateDisconnectImage()
{
    QImage image = QImage(QString(":/Resources/NoneCamera" + QString::number(_trackID + 1) + ".png"));
    setImage(image);
    setIsShowBelowImage(true);
}

void ImageViewVM::setImage(QImage &image)
{
    setIsShowBelowImage(false);
    _image = image;
    emit imageChanged();
}

void ImageViewVM::setImageOverlay(QImage &image)
{
    _imageOverlay = image.copy();
    emit imageOverlayChanged();

}

void ImageViewVM::setIsShowBelowImage(bool value)
{
    _isShowBelowImage = value;
    emit isShowBelowImageChanged();

}

void ImageViewVM::setDocName(QString value)
{
    if(_docName == value)
        return;
    _docName = value;
    emit docNameChanged();
}

void ImageViewVM::setSerialNumber(QString value)
{
    if(_serialNumber == value)
        return;
    _serialNumber = value;
    emit serialNumberChanged();
}

void ImageViewVM::setInspectFunctionName(QString value)
{
    if(_inspectFunctionName == value)
        return;
    _inspectFunctionName = value;
    emit inspectFunctionNameChanged();
}

void ImageViewVM::setInspectResult(QString value)
{
    if(_inspectResult == value)
        return;
    _inspectResult = value;
    emit inspectResultChanged();
}

void ImageViewVM::setDocID(int &value)
{
    if(_docID == value)
        return;
    _docID = value;
    emit docIDChanged();
}

void ImageViewVM::setTrackID(int &value)
{
    if(_trackID == value)
        return;
    _trackID = value;
    emit trackIDChanged();
}

void ImageViewVM::setIsConnectCam(bool value)
{
    if(_isConnectCam == value)
        return;
    _isConnectCam = value;
    emit isConnectCamChanged();
}

void ImageViewVM::setInspectionInfo(QString value)
{
    if(_inspectionInfo != value){_inspectionInfo = value; emit inspectionInfoChanged();}
}

void ImageViewVM::setProcessedTime(float value)
{
    if(_processedTime != value){_processedTime = value; emit processedTimeChanged();}
}

void ImageViewVM::setDlModelVersion(QString value)
{
    if(_dlModelVersion != value){_dlModelVersion = value; emit dlModelVersionChanged();}
}

void ImageViewVM::setInspectionCycleInfo(int value)
{
    if(_inspectionCycleInfo != value){_inspectionCycleInfo = value; emit inspectionCycleInfoChanged();}
}

void ImageViewVM::setInspectionFolderInfo(QString value)
{
    if(_inspectionFolderInfo != value){_inspectionFolderInfo = value; emit inspectionFolderInfoChanged();}
}


int ImageViewVM::imageWidth()
{
    return _image.width();
}

int ImageViewVM::imageHeight()
{
    return _image.height();
}

void ImageViewVM::doSnapImage()
{
    emit doSnapImageSignal();
}

void ImageViewVM::doSaveImage(QString path)
{
    QString imagePath = QString("%1%2%3")
                            .arg(path)
                            .arg(ConfigApplication::instance()->m_hashExtendImageName[(TRACK_INDEX)trackID()])
                            .arg(ConfigApplication::instance()->m_strImageExtension);
    image().save(imagePath, "BMP");
}


