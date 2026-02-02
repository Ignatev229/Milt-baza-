#ifndef TCPBACKENDCLIENT_H
#define TCPBACKENDCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QBuffer>
#include <QImageWriter>
#include <QtEndian>
#include <QThread>
#include <QPixmap>

#include "../Script/Config/config_application.h"
#include "../Script/Define/struct_def.h"

class TCPBackendClient : public QObject
{
    Q_OBJECT
public:
    explicit TCPBackendClient(QObject *parent = nullptr);
    ~TCPBackendClient();


    bool Send(InputBackendInfo &inputBackendInfo);
    void Disconnect();
    void DLModelPathChanged(TRACK_INDEX trackID);
    void RecipeChanged();
    bool isConnected;

private:
    QScopedPointer<QTcpSocket> scopedSocket;
    void ReceiveMessage();
    int sizeRequired;

private slots:
    void ReadyRead_Slots();
    void Disconnected_Slots();
    void Connected_Slots();


signals:
    void receiveMessage_Signal(OutputBackendInfo&);

};

#endif // TCPBACKENDCLIENT_H
