#ifndef CAMERAINTERFACE_H
#define CAMERAINTERFACE_H

#include <QObject>
#include <QThread>
#include <QImage>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QDir>
#include <QDirIterator>
#include <QFuture>
#include <QtConcurrent>
#include <QElapsedTimer>
#include <QQueue>

#ifdef Q_OS_WIN
    #include <Windows.h>
#endif

// #include <opencv2/opencv.hpp>
// #include <opencv2/core/core.hpp>
// #include <opencv2/highgui/highgui.hpp>
// #include <opencv2/imgcodecs.hpp>
// #include <opencv2/videoio.hpp>
#include "../../Define/struct_def.h"
#include "../../Config/config_application.h"
#include "../../../ViewModel/Main/debug_log_vm.h"

// using namespace cv;

class CameraInterface : public QThread
{
    Q_OBJECT
public:
    explicit CameraInterface(TRACK_INDEX camID, QString camSerial, int camIndex, QObject *parent = nullptr);
    ~CameraInterface();

    void run() override;
    void Resume();
    void Pause();
    void Destroy();

    void RegisterCamera();
    bool Snap(QImage& image);
    bool Snap(QString &imageResultName);
    bool Stream(bool isStart);
    void Disconnect();
    void SetCameraParameter(CameraSetting &value);
    void SetAutoWhiteBalance(double &red, double &green, double &blue);

    void* m_pCameraDevice;

    TRACK_INDEX camID; // camera name // название камеры
    QString camSerial; //....
    QString camIDStr;
    int camIndex;


    bool isStream;
    bool isRun;
    bool isInspect;
    QString imageInspectName;

private:
    QMutex sync;
    QWaitCondition pauseCond;
    bool pause;

    int camWidth;
    int camHeight;



private slots:


signals:
    void cameraConnectedStatusChanged_Signal(TRACK_INDEX, bool);
    void sendImageCamToMain_Signal(TRACK_INDEX, QImage, bool, QString);

};

#endif // CAMERAINTERFACE_H
