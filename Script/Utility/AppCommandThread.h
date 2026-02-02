#ifndef APPCOMMANDTHREAD_H
#define APPCOMMANDTHREAD_H

#include <QObject>
#include <QThread>
#include <QMutexLocker>
#include <QWaitCondition>

class MasterApp;

class AppCommandThread : public QThread
{
public:
    explicit AppCommandThread(QObject *parent = nullptr);

    void Exit();
    void run() override;
public slots:
    void ReceiveCommand(int command, int imageIndex);
private:
    QWaitCondition m_waitCommandCondition;
    QMutex m_mutexCommand;
    
    int m_nImageIndex;
    bool m_bExit;
    bool m_bIsCommandReady;
    int m_nCommand;

    MasterApp* m_pParentObject;
};

#endif // APPCOMMANDTHREAD_H
