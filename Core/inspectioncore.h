#ifndef INSPECTIONCORE_H
#define INSPECTIONCORE_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QElapsedTimer>

#include "../TCPServer/tcp_backend_client.h"

class InspectionCore : public QThread
{
    Q_OBJECT
public:
    explicit InspectionCore(QObject *parent = nullptr);
    ~InspectionCore();
    bool isRun;

    void run();
    void Resume();
    void Pause();

    void ResetOutputBackendInfo();
    void RecipeChanged();

    QScopedPointer<TCPBackendClient> scopedTCPBackendClient; // backend client

private:
    QMutex sync;
    QWaitCondition pauseCond;
    bool pause;

    bool isTotalEmptyQueue();

    QString defaultResultFlags;
    QQueue<InputBackendInfo> inputBackendQueues;
    InputBackendInfo currentInputBackend;
    bool isReadyCamInspectProcess;
    QElapsedTimer processedTimes;
    OutputBackendInfo outputBackendInfo;


signals:
    void sendInputInspect_Signal(InputBackendInfo&);
    void sendFinishInspect_Signal(OutputBackendInfo&);
    void sendRecipeLoaded_Signal(bool);

private slots:
    void receiveInspResult_TCPBackendClient_Slot(OutputBackendInfo&);
    void sendInputInspect_Slot(InputBackendInfo&);
public slots:
    void inspect_MainHomeVM_Slot(InputBackendInfo &input);

};

#endif // INSPECTIONCORE_H
