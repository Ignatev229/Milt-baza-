#include "save_image_thread.h"

SaveImageThread::SaveImageThread(QObject *parent)
    : QThread{parent}
{
    isRun = true;
    isExit = false;
}

SaveImageThread::~SaveImageThread()
{
    isRun = false;
    Resume();
    this->quit();
    this->wait();
}

void SaveImageThread::Exit()
{
     sync.lock();
     isExit = true;
     sync.unlock();
     pauseCond.wakeAll();
}

void SaveImageThread::run()
{
    while(isRun)
    {
        if(saveImageQueues.isEmpty())
        {
            Pause();
            sync.lock();
            if(pause)
                pauseCond.wait(&sync);
            sync.unlock();
        }

        if (isExit) return;

        SaveImageInfo item = saveImageQueues.dequeue();
        QDir d = QFileInfo(item.path).absoluteDir();
        if(!d.exists())
        {
            QDir().mkdir(d.absolutePath());
        }
        if(item.path.contains(ConfigApplication::instance()->m_strOperatorImageName))
            item.image.save(item.path, "JPG", 80);
        else
            item.image.save(item.path, "JPG", 100);
        QThread::msleep(1);
    }
}

void SaveImageThread::Resume()
{
    sync.lock();
    pause = false;
    sync.unlock();
    pauseCond.wakeAll();
}

void SaveImageThread::Pause()
{
    sync.lock();
    pause = true;
    sync.unlock();
}

void SaveImageThread::AddSaveImage(SaveImageInfo &item)
{
    // if(ConfigApplication::instance()->m_bIsLowDisk)
    //     return;
    saveImageQueues.enqueue(item);
    Resume();
}

void SaveImageThread::SaveMultiInspectImage(OutputBackendInfo &result)
{
    // if(ConfigApplication::instance()->m_bIsLowDisk)
    //     return;
    for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i) {
        SaveImageInfo item;
        item.image = result.images[(TRACK_INDEX)i].copy();
        item.path = result.operatorImagePaths[(TRACK_INDEX)i];
        item.path = item.path.replace(ConfigApplication::instance()->m_strOperatorImageName,
                                      ConfigApplication::instance()->m_strInspectImageName);
        AddSaveImage(item);
    }

    for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i) {
        SaveImageInfo item;
        item.image = result.operatorImages[(TRACK_INDEX)i].copy();
        item.path = result.operatorImagePaths[(TRACK_INDEX)i];
        item.path = item.path.replace(ConfigApplication::instance()->m_strInspectImageName,
                                      ConfigApplication::instance()->m_strOperatorImageName);
        AddSaveImage(item);
    }
}


























