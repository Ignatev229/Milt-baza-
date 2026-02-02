#ifndef SAVE_IMAGE_THREAD_H
#define SAVE_IMAGE_THREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QElapsedTimer>
#include <QFileInfo>
#include <QDir>
#include <QQueue>
#include <QImage>

#include "../Define/struct_def.h"
#include "../Config/config_application.h"

struct SaveImageInfo
{
    SaveImageInfo(QImage _image, QString _path)
        : image(_image)
        , path(_path)
    {
    }

    SaveImageInfo()
    {
    }

    QImage image;
    QString path;
};

class SaveImageThread : public QThread
{
    Q_OBJECT
public:
    explicit SaveImageThread(QObject *parent = nullptr);
    ~SaveImageThread();

    bool isRun;
    void run();
    void Resume();
    void Pause();
    void Exit();

    void AddSaveImage(SaveImageInfo &item);
    void SaveMultiInspectImage(OutputBackendInfo& result);

private:
    QMutex sync;
    QWaitCondition pauseCond;
    bool pause;
    bool isExit;
    QQueue<SaveImageInfo> saveImageQueues;

signals:

};

#endif // SAVE_IMAGE_THREAD_H
