#ifndef TRACKVM_H
#define TRACKVM_H

#include <QObject>
#include <QImage>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <thread>
#include <QTimer>

#include "../Script/Define/struct_def.h"
#include "../Model/image_model.h"
#include "../Script/Hardware/Camera/camera_interface.h"
#include "Dialog/dialog_vm.h"
//#include "EventLog/event_log_vm.h"


class TrackVM : public QObject
{
    Q_OBJECT

public:
    TrackVM(QQmlApplicationEngine &appEngine, TRACK_INDEX trackID, QStringList listDocName);
    ~TrackVM();


    Q_PROPERTY(ImageModel* imageModel READ imageModel WRITE setImageModel NOTIFY imageModelChanged)
    Q_PROPERTY(QString inspectFolderInfo READ inspectFolderInfo WRITE setInspectFolderInfo NOTIFY inspectFolderInfoChanged)
    Q_PROPERTY(int inspectCycleInfo READ inspectCycleInfo WRITE setInspectCycleInfo NOTIFY inspectCycleInfoChanged)

    //
    ImageModel* imageModel();
    QString inspectFolderInfo();
    int inspectCycleInfo();
    //

    void UpdateImage(QImage &image, int docIndex);
    void UpdateImageOverlay(QImage &image, int docIndex);
    void UpdateImageFromFile(QString &imagePath, int docIndex);
    void UpdateImageOverlayFromFile(QString &imagePath, int docIndex);
    void UpdateOverlayLeftString(QString value, int docIndex);
    QImage GetDocImage(int docIndex);
    void UpdateDisconnectImage(int docIndex);
    void UpdateAllImage(QList<QImage> &images);
    void UpdateCameraConnect(bool isConnect);
    void SetDocName(int docIndex, QString name);
    void setInspectionInfo(QString value);
    void ClearOverlay();
    void Inspect();
    void Inspect(QString);
    void Inspect(QImage&);
    void InspectFolder(bool isStart, QString path);
    void GetNextInspectFolder();
    void InspectCycle(bool value);
    void SnapAndInspect();
    void Snap();
    void Stream(bool isStream);
    void SetProcessTime(int docIndex, float time);
    void SetDLModelVersion(QString version);
    void SetCameraSerialNumber(int docIndex);


    ImageViewFeature imageViewFeature;
    QList<ImageViewFeature> imageViewFeatures;

    QScopedPointer<CameraInterface> scopedCameraInterface;

    TRACK_INDEX trackID;
    int numDoc;
    bool isConnectCam;

    // inspect folder param //  Проверка параметров папки
    bool isInspecFolder;
    int currentInspectFolderIndex;
    QString inspectFolderPath;
    QStringList listImageInspectFolder;


private:
    // Property //Собственность
    ImageModel* _imageModel;
    QString _inspectFolderInfo;
    QString _oldLoadImagePath;
    int _inspectCycleInfo;
    // End property // Конечное свойство

    QScopedPointer<QTimer> inspectCycleTimer;
    int inspectCycleCount;

    void initialVariable();
    void CreateConnection();


signals:
    // Property //Собственность
    void imageModelChanged();
    void inspectFolderInfoChanged();
    void inspectCycleInfoChanged();
    // End property // Конечное свойство

    void inspect_Signal(InputBackendInfo&);
    void inspectFolderStatusChanged_Signal(bool);


public slots:
    // Property //Собственность
    void setImageModel(ImageModel* value);
    void setInspectFolderInfo(QString value);
    void setInspectCycleInfo(int value);
    // End property // Конечное свойство
    void doSnapImageDoc();

    //
    void inspectCyleTimeout();

};

#endif // TRACKVM_H
