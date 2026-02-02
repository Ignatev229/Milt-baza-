#ifndef IMAGEVIEWVM_H
#define IMAGEVIEWVM_H

#include <QtMath>
#include <QObject>
#include <QPainter>
#include <QQuickItem>
#include <QQuickPaintedItem>


#include "../Script/Define/struct_def.h"
#include "../Script/Config/config_application.h"


class ImageViewVM: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QImage image MEMBER _image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(QImage imageOverlay MEMBER _imageOverlay READ imageOverlay WRITE setImageOverlay NOTIFY imageOverlayChanged)
    Q_PROPERTY(bool isShowBelowImage READ isShowBelowImage WRITE setIsShowBelowImage NOTIFY isShowBelowImageChanged)
    Q_PROPERTY(QString docName READ docName WRITE setDocName NOTIFY docNameChanged)
    Q_PROPERTY(QString serialNumber READ serialNumber WRITE setSerialNumber NOTIFY serialNumberChanged)
    Q_PROPERTY(QString inspectFunctionName READ inspectFunctionName WRITE setInspectFunctionName NOTIFY inspectFunctionNameChanged)
    Q_PROPERTY(QString inspectResult READ inspectResult WRITE setInspectResult NOTIFY inspectResultChanged)
    Q_PROPERTY(int docID READ docID WRITE setDocID NOTIFY docIDChanged)
    Q_PROPERTY(int trackID READ trackID WRITE setTrackID NOTIFY trackIDChanged)
    Q_PROPERTY(bool isConnectCam READ isConnectCam WRITE setIsConnectCam NOTIFY isConnectCamChanged)
    Q_PROPERTY(QString inspectionInfo READ inspectionInfo WRITE setInspectionInfo NOTIFY inspectionInfoChanged)
    Q_PROPERTY(float processedTime READ processedTime WRITE setProcessedTime NOTIFY processedTimeChanged)
    Q_PROPERTY(QString dlModelVersion READ dlModelVersion WRITE setDlModelVersion NOTIFY dlModelVersionChanged)
    Q_PROPERTY(int inspectionCycleInfo READ inspectionCycleInfo WRITE setInspectionCycleInfo NOTIFY inspectionCycleInfoChanged)
    Q_PROPERTY(QString inspectionFolderInfo READ inspectionFolderInfo WRITE setInspectionFolderInfo NOTIFY inspectionFolderInfoChanged)
public:
    ImageViewVM(TRACK_INDEX trackID, int docID, QString docName, QObject *parent = nullptr);
    ~ImageViewVM();

    QImage image();
    QImage imageOverlay();
    bool isShowBelowImage();
    QString docName();
    QString serialNumber();
    QString inspectFunctionName();
    QString inspectResult();
    int docID();
    int trackID();
    bool isConnectCam();
    QString inspectionInfo();
    float processedTime();
    QString dlModelVersion();
    int inspectionCycleInfo();
    QString inspectionFolderInfo();

    void UpdateDisconnectImage();

private:
    // Property //  Собственность
    QImage _image;
    QImage _imageOverlay;
    bool _isShowBelowImage;
    QString _docName;
    QString _serialNumber;
    QString _inspectFunctionName;
    QString _inspectResult;
    int _docID;
    int _trackID;
    bool _isConnectCam;
    QString _inspectionInfo;
    float _processedTime;
    QString _dlModelVersion;
    int _inspectionCycleInfo;
    QString _inspectionFolderInfo;
    // End property // Конечное свойство

signals:
    // Property //  Собственность
    void imageChanged();
    void imageOverlayChanged();
    void isShowBelowImageChanged();
    void docNameChanged();
    void serialNumberChanged();
    void inspectFunctionNameChanged();
    void inspectResultChanged();
    void docIDChanged();
    void trackIDChanged();
    void isConnectCamChanged();
    void inspectionInfoChanged();
    void processedTimeChanged();
    void dlModelVersionChanged();
    void inspectionCycleInfoChanged();
    void inspectionFolderInfoChanged();
    void doSnapImageSignal();
    // End property // Конечное свойство


public slots:
    // Property //  Собственность
    void setImage(QImage &image);
    void setImageOverlay(QImage &image);
    void setIsShowBelowImage(bool value);
    void setDocName(QString value);
    void setSerialNumber(QString value);
    void setInspectFunctionName(QString value);
    void setInspectResult(QString value);
    void setDocID(int &value);
    void setTrackID(int &value);
    void setIsConnectCam(bool value);
    void setInspectionInfo(QString value);
    void setProcessedTime(float value);
    void setDlModelVersion(QString value);
    void setInspectionCycleInfo(int value);
    void setInspectionFolderInfo(QString value);
    // End property // Конечное свойство

    int imageWidth();
    int imageHeight();

    void doSnapImage();

    void doSaveImage(QString path);
};

#endif // IMAGEVIEWVM_H
