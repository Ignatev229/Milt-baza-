#ifndef SYSTEMSETTINGVM_H
#define SYSTEMSETTINGVM_H

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <QProcess>
#include <zlib.h>
#include <quazip.h>
#include <quazipfile.h>
#include <quazipdir.h>

#include "../Dialog/dialog_vm.h"

class SystemSettingVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString machineName READ machineName WRITE setMachineName NOTIFY machineNameChanged FINAL)
    Q_PROPERTY(QString ipAddress READ ipAddress WRITE setIpAddress NOTIFY ipAddressChanged FINAL)
    Q_PROPERTY(QString subnet READ subnet WRITE setSubnet NOTIFY subnetChanged FINAL)
    Q_PROPERTY(QString gateway READ gateway WRITE setGateway NOTIFY gatewayChanged FINAL)
    Q_PROPERTY(bool useDHCP READ useDHCP WRITE setUseDHCP NOTIFY useDHCPChanged FINAL)
    Q_PROPERTY(int distanceUnit READ distanceUnit WRITE setDistanceUnit NOTIFY distanceUnitChanged FINAL)
    Q_PROPERTY(int weightUnit READ weightUnit WRITE setWeightUnit NOTIFY weightUnitChanged FINAL)
    Q_PROPERTY(int masterHost READ masterHost WRITE setMasterHost NOTIFY masterHostChanged FINAL)
    Q_PROPERTY(bool enableSerial READ enableSerial WRITE setEnableSerial NOTIFY enableSerialChanged FINAL)
    Q_PROPERTY(bool enableNetwork READ enableNetwork WRITE setEnableNetwork NOTIFY enableNetworkChanged FINAL)
public:
    explicit SystemSettingVM(QObject *parent = nullptr);
    ~SystemSettingVM();

    // property //  Собственность
    QString machineName();
    QString ipAddress();
    QString subnet();
    QString gateway();
    bool useDHCP();
    int distanceUnit();
    int weightUnit();
    int masterHost();
    bool enableSerial();
    bool enableNetwork();
    // end // конец

    void Init();

private:
    // property //  Собственность
    QString _machineName;
    QString _ipAddress;
    QString _subnet;
    QString _gateway;
    bool _useDHCP;
    int _distanceUnit;
    int _weightUnit;
    int _masterHost;
    bool _enableSerial;
    bool _enableNetwork;
    // end // конец
    // QuaZip zip;
    bool ZipFolderRecursive(QuaZip &zip, const QString &folderPath, const QString &baseFolder);
    bool ZipConfigFolder(const QString &folderPath, const QString &zipFilePath);
    bool UnzipFile(const QString &zipFilePath, const QString &destFolderPath);


signals:
    // property //  Собственность
    void machineNameChanged();
    void ipAddressChanged();
    void subnetChanged();
    void gatewayChanged();
    void useDHCPChanged();
    void distanceUnitChanged();
    void weightUnitChanged();
    void masterHostChanged();
    void enableSerialChanged();
    void enableNetworkChanged();
    //end // конец

public slots:

    // property //  Собственность
    void setMachineName(QString);
    void setIpAddress(QString);
    void setSubnet(QString);
    void setGateway(QString);
    void setUseDHCP(bool);
    void setDistanceUnit(int);
    void setWeightUnit(int);
    void setMasterHost(int);
    void setEnableSerial(bool);
    void setEnableNetwork(bool);
    //end // конец


    // qml slot // qml слот
    void saveMachineName_Qml_Slot(QString);
    void saveIPSetting_Qml_Slot(QString, QString, QString, bool);
    void saveDistanceUnit_Qml_Slot(int);
    void saveWeightUnit_Qml_Slot(int);
    void saveCommunication_Qml_Slot(int, bool, bool);

    // archive
    void zipFolder_Qml_Slot(QString);
    void unZipFolder_Qml_Slot(QString);

    // Restart tab // Вкладка Перезапуск
    void exitSoftware();
    void restartSoftware();
    void rebootSystem();
    void shutdownSystem();



};

#endif // SYSTEMSETTINGVM_H
