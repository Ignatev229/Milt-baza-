#include "camera_interface.h"
#include "CameraDLL.h"
#include "qpixmap.h"
CameraInterface::CameraInterface(TRACK_INDEX camID, QString camSerial, int camIndex, QObject *parent)
    : QThread{parent}
    , m_pCameraDevice(nullptr)
{
    this->camID = camID;
    this->camSerial = camSerial;
    this->camIndex = camIndex;
    camIDStr = "camid" + QString::number(camID + 1);
    ConfigApplication::instance()->m_commonInfo.appSetting.cameraConfig[camID].isConnected = false;

    m_pCameraDevice = CameraDLLControl::CreateDevice();

    isStream = false;
    isInspect = false;
    imageInspectName = "";
}

CameraInterface::~CameraInterface()
{
    Destroy();
    Disconnect();

    CameraDLLControl::StopGrabbing(m_pCameraDevice);
    CameraDLLControl::DestroyDevice(m_pCameraDevice);
}

void CameraInterface::run()
{
    // camera stream //  Трансляция с камеры
    isStream = false;
    isRun = true;
    if (CameraDLLControl::IsDeviceOpened(m_pCameraDevice))
    {
        ConfigApplication::instance()->WriteDebugLog("CameraInterface", "Start Streaming " + QString::number(camID + 1) + ": " + camSerial);

        QElapsedTimer timer;
        while(isRun)
        {
            timer.start();
            if(!isStream)
            {
                Pause();
                sync.lock();
                if(pause)
                    pauseCond.wait(&sync);
                sync.unlock();
            }

            // View // Просмотр
            QImage q_image;

            if(!Snap(q_image))
            {
                q_image = QImage(QString(":/Resources/NoneCamera" + QString::number(camID + 1) + ".png"));
            }

            emit sendImageCamToMain_Signal(camID, q_image, isInspect, imageInspectName);
            isInspect = false;

            // delay // задержка
            if(timer.elapsed() < 40)
            {
                QThread::msleep(40 - timer.elapsed());
            }
            QThread::msleep(5);
        }
    }
    else
    {
        ConfigApplication::instance()->WriteDebugLog("CameraInterface", "Can not Streaming " + QString::number(camID + 1) + ": " + camSerial);
    }
    this->quit();
    this->wait();
}

void CameraInterface::Resume()
{
    if (!CameraDLLControl::IsDeviceOpened(m_pCameraDevice))
        return;
    sync.lock();
    pause = false;
    sync.unlock();
    pauseCond.wakeAll();
}

void CameraInterface::Pause()
{
    if (!CameraDLLControl::IsDeviceOpened(m_pCameraDevice))
        return;
    sync.lock();
    pause = true;
    sync.unlock();
}

void CameraInterface::Destroy()
{
    isRun = false;
    isStream = false;
    Resume();
    this->quit();
    this->wait();
}

void CameraInterface::RegisterCamera()
{
    if (m_pCameraDevice == nullptr) return;

    // Register camera when it is disconnected // Зарегистрировать камеру, когда она отключена
    if (CameraDLLControl::IsDeviceOpened(m_pCameraDevice)) return;

    // Camera infor // Информация о камере
    int width = 0;
    int height = 0;
    int maxWidth = 0;
    int maxHeight = 0;
    int gain = 0;
    int expose = 0;

    ConfigApplication::instance()->m_commonInfo.appSetting.cameraConfig[camID].isConnected = false;
    int isOk = CameraDLLControl::OpenDevice(m_pCameraDevice, camSerial.toStdString().c_str());
    if (isOk != 0)
    {
        qDebug() << "[CameraInterface]" << QString("Connection failed: %1").arg(isOk);
        return;
    }

    if (CameraDLLControl::GetDeviceWidthHeight(m_pCameraDevice, width, height, maxWidth, maxHeight) == false)
    {
        // action fail // Действие завершилось неудачей
        qDebug() << "[CameraInterface]" << QString("GetDeviceWidthHeight failed");
        return;
    }

    isOk = CameraDLLControl::GetGain(m_pCameraDevice, gain);
    if (isOk != 0)
    {
        // action fail // Действие завершилось неудачей
        qDebug() << QString("GetGain failed: %1").arg(isOk);
        return;
    }


    isOk = CameraDLLControl::GetExposure(m_pCameraDevice, expose);
    if (isOk != 0)
    {
        // action fail // Действие завершилось неудачей
        qDebug() << QString("GetExpose failed: %1").arg(isOk);
        return;
    }

    isOk = CameraDLLControl::SetTriggerSouce(m_pCameraDevice, CC_TRIGGER_SOURCE_SOFTWARE);
    if (isOk != 0)
    {
        // action fail // Действие завершилось неудачей
        qDebug() << QString("SetTriggerSouce failed: %1").arg(isOk);
        return;
    }

    isOk = CameraDLLControl::SetTriggerMode(m_pCameraDevice, CC_TRIGGER_MODE_ON);
    if (isOk != 0)
    {
        // action fail // Действие завершилось неудачей
        qDebug() << QString("SetTriggerMode failed: %1").arg(isOk);
        return;
    }

    // enter grab mode // войти в режим захвата
    isOk = CameraDLLControl::StartGrabbing(m_pCameraDevice);
    if (isOk != 0)
    {
        // action fail // Действие завершилось неудачей
        qDebug() << QString("SetTriggerMode failed: %1").arg(isOk);
        return;
    }





    qDebug() << "[CameraInterface]" << "Register Success Camera";
    qDebug() << QString("Width: %1, Height: %2, Gain: %3, Expose: %4").arg(width).arg(height).arg(gain).arg(expose);

    ConfigApplication::instance()->WriteDebugLog("CameraInterface", "Register Success Camera");
    ConfigApplication::instance()->m_commonInfo.appSetting.cameraConfig[camID].isConnected = true;

    emit cameraConnectedStatusChanged_Signal(camID, ConfigApplication::instance()->m_commonInfo.appSetting.cameraConfig[camID].isConnected);
}

bool CameraInterface::Snap(QImage &image)
{
   /* if (isStream) return false;*/

    auto start = std::chrono::high_resolution_clock::now();

    if (CameraDLLControl::ExecuteSoftwareTrigger(m_pCameraDevice) == false)
    {
        ConfigApplication::instance()->WriteDebugLog("CameraInterface", "ExecuteSoftwareTrigger Failed " + QString::number(camID + 1) + ": " + camSerial);

        image = QImage(QString(":/Resources/NoneCamera" + QString::number(camID + 1) + ".png"));

        return false;
    }

    unsigned char* pBuffer = nullptr;
    int bufferWidth = 0;
    int bufferHeight = 0;
    int stride = 0;


    auto isOk = CameraDLLControl::GetDeviceBuffer(m_pCameraDevice, pBuffer, bufferWidth, bufferHeight, stride);
    if (isOk != 0)
    {
        ConfigApplication::instance()->WriteDebugLog("CameraInterface", "GetDeviceBuffer Failed " + QString::number(camID + 1) + ": " + camSerial);

        if (pBuffer != nullptr) delete[] pBuffer;

        image = QImage(QString(":/Resources/NoneCamera" + QString::number(camID + 1) + ".png"));

        return false;
    }


    // ASSUME FORMAT BGR888 or MONO8 from camera config //  Предположим, ЧТО формат BGR888 или MONO8 указан в конфигурации камеры
    image = QImage(pBuffer, bufferWidth, bufferHeight, bufferWidth * stride, stride == 1 ? QImage::Format_Indexed8 : QImage::Format_BGR888);
    QPixmap pixmap = QPixmap::fromImage(image);
    image = pixmap.toImage();

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    ConfigApplication::instance()->WriteDebugLog("CameraInterface", "Snap Success" + QString::number(camID + 1) + ": " + camSerial + " --- " + QString::number(elapsed.count()));

    delete[] pBuffer;
    return true;
}

bool CameraInterface::Snap(QString &imageResultName) // snap in thread and inspection //защелкивание резьбы и проверка
{
    // if((ConfigApplication::instance()->m_hashConfigCameras[camID].type == CAMERA_TYPE::BASLER && !cameraBaslerInterface.data()->isConnected) ||
    //    (ConfigApplication::instance()->m_hashConfigCameras[camID].type == CAMERA_TYPE::NORMAL_USB && !cameraUsbInterface.data()->isConnected))
    // {
    //     ConfigApplication::instance()->WriteDebugLog("CameraInterface", "Can not Snap " + QString::number(camID + 1) + ": " + camSerial);
    //     return false;
    // }
    // imageInspectName = imageResultName;
    // isStream = false;
    // isInspect = true;
    // Resume();
    return true;
}



bool CameraInterface::Stream(bool isStart)
{
    if (!CameraDLLControl::IsDeviceOpened(m_pCameraDevice))
    {
        ConfigApplication::instance()->WriteDebugLog("CameraInterface", "Can not start streaming " + QString::number(camID + 1) + ": " + camSerial);
        return false;
    }
    if(isStart)
    {
        isStream = true;
        Resume();
    }
    else
    {
        isStream = false;
    }

    return true;
}


void CameraInterface::Disconnect()
{
    CameraDLLControl::CloseDevice(m_pCameraDevice);
}

void CameraInterface::SetCameraParameter(CameraSetting &value)
{
    CameraDLLControl::SetExposure(m_pCameraDevice, value.exposure);
    CameraDLLControl::SetGain(m_pCameraDevice, value.gain);
}

void CameraInterface::SetAutoWhiteBalance(double &red, double &green, double &blue)
{
   //cameraBaslerInterface.data()->SetAutoWhiteBalance(red, green, blue);
}
















