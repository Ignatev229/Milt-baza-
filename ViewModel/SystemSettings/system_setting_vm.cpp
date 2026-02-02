#include "system_setting_vm.h"
#include "Script/Config/config_application.h"

SystemSettingVM::SystemSettingVM(QObject *parent)
    : QObject{parent}
{

}

SystemSettingVM::~SystemSettingVM()
{

}

QString SystemSettingVM::machineName()
{
    return _machineName;
}

QString SystemSettingVM::ipAddress()
{
    return _ipAddress;
}

QString SystemSettingVM::subnet()
{
    return _subnet;
}

QString SystemSettingVM::gateway()
{
    return _gateway;
}

bool SystemSettingVM::useDHCP()
{
    return _useDHCP;
}

int SystemSettingVM::distanceUnit()
{
    return _distanceUnit;
}

int SystemSettingVM::weightUnit()
{
    return _weightUnit;
}

int SystemSettingVM::masterHost()
{
    return _masterHost;
}

bool SystemSettingVM::enableSerial()
{
    return _enableSerial;
}

bool SystemSettingVM::enableNetwork()
{
    return _enableNetwork;
}

void SystemSettingVM::Init()
{
    setMachineName(ConfigApplication::instance()->m_commonInfo.appSetting.m_strMachineName);
    setIpAddress(ConfigApplication::instance()->m_commonInfo.plcSetting.strIPAddress);
    setDistanceUnit(ConfigApplication::instance()->m_commonInfo.appSetting.m_nDistanceUnit);
    setWeightUnit(ConfigApplication::instance()->m_commonInfo.appSetting.m_nWeightUnit);
}

bool SystemSettingVM::ZipFolderRecursive(QuaZip &zip, const QString &folderPath, const QString &baseFolder)
{
    QDir dir(folderPath.toUtf8());
    if (!dir.exists()) {
        qWarning() << "Directory does not exist:" << folderPath;
        return false;
    }

    // Get all files and subdirectories
    QStringList files = dir.entryList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
    QStringList subDirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);

    // Zip the files
    for (const QString &fileName : files) {
        QFile file(dir.absoluteFilePath(fileName).toUtf8());
        if (file.open(QIODevice::ReadOnly)) {
            QuaZipFile zipFile(&zip);
            QString zipPath = baseFolder.toUtf8() + "/" + fileName.toUtf8();

            if(baseFolder == "")
                zipPath = fileName.toUtf8();

            qDebug() << zipPath;

            zipFile.open(QIODevice::WriteOnly, QuaZipNewInfo(zipPath.toUtf8()));
            zipFile.write(file.readAll());
            zipFile.close();
        } else {
            qWarning() << "Failed to open file:" << fileName;
        }
    }

    // Recursively zip subdirectories

    for (const QString &subDir : subDirs) {
        if(subDir == "SavedImages" || subDir == "Statistics")
            continue;
        QString subDirPath = dir.absoluteFilePath(subDir.toUtf8());
        QString subFolder = baseFolder.toUtf8() + "/" + subDir.toUtf8();
        if(baseFolder == "")
            subFolder = subDir;

        ZipFolderRecursive(zip, subDirPath.toUtf8(), subFolder.toUtf8());  // Recursion with base path
    }
    return zip.getZipError() == UNZ_OK;
}

bool SystemSettingVM::ZipConfigFolder(const QString &folderPath, const QString &zipFilePath)
{
    QuaZip zip(zipFilePath);
    if (!zip.open(QuaZip::mdCreate)) {
        qWarning() << "Could not open zip file for writing:" << zipFilePath;
        return false;
    }
    ZipFolderRecursive(zip, folderPath, "");  // Start from base folder path

    zip.close();
    return zip.getZipError() == UNZ_OK;
}

bool SystemSettingVM::UnzipFile(const QString &zipFilePath, const QString &destFolderPath)
{
    QuaZip zip(zipFilePath);
    if (!zip.open(QuaZip::mdUnzip)) {
        qWarning() << "Could not open zip file for reading:" << zipFilePath;
        return false;
    }

    QDir destDir(destFolderPath);
    if (!destDir.exists()) {
        destDir.mkpath(".");
    }

    // Iterate through the files in the zip
    for (bool more = zip.goToFirstFile(); more; more = zip.goToNextFile()) {
        // QString fileName = zip.getCurrentFileName();
        QString fileName = QString::fromUtf8(zip.getCurrentFileName().toUtf8());

        // Check if the file is a directory or a regular file
        if (fileName.contains("/")) {
            // It's a directory, create it in the destination folder
            QStringList fileItems = fileName.split("/");
            fileItems.removeLast();
            QString subfolder = fileItems.join("/");
            QDir dir(destFolderPath + "/" + subfolder);
            if (!dir.exists()) {
                dir.mkpath(".");
            }
        }

        // It's a regular file, extract it
        QuaZipFile zipFile(&zip);
        if (zipFile.open(QIODevice::ReadOnly)) {
            QFile outputFile(destFolderPath + "/" + fileName);
            if (outputFile.open(QIODevice::WriteOnly)) {
                outputFile.write(zipFile.readAll());
                outputFile.close();
            } else {
                // qWarning() << "Failed to write file:" << outputFile.fileName();
            }
        } else {
            // qWarning() << "Failed to open file in zip:" << fileName;
        }

    }

    zip.close();
    return zip.getZipError() == UNZ_OK;
}

void SystemSettingVM::setMachineName(QString value)
{
    if(_machineName != value){_machineName = value; emit machineNameChanged();}
}

void SystemSettingVM::setIpAddress(QString value)
{
    if(_ipAddress != value){_ipAddress = value; emit ipAddressChanged();}
}

void SystemSettingVM::setSubnet(QString value)
{
    if(_subnet != value){_subnet = value; emit subnetChanged();}
}

void SystemSettingVM::setGateway(QString value)
{
    if(_gateway != value){_gateway = value; emit gatewayChanged();}
}

void SystemSettingVM::setUseDHCP(bool value)
{
    if(_useDHCP != value){_useDHCP = value; emit useDHCPChanged();}
}

void SystemSettingVM::setDistanceUnit(int value)
{
    if(_distanceUnit != value){_distanceUnit = value; emit distanceUnitChanged();}
}

void SystemSettingVM::setWeightUnit(int value)
{
    if(_weightUnit != value){_weightUnit = value; emit weightUnitChanged();}
}

void SystemSettingVM::setMasterHost(int value)
{
    if(_masterHost != value){_masterHost = value; emit masterHostChanged();}
}

void SystemSettingVM::setEnableSerial(bool value)
{
    if(_enableSerial != value){_enableSerial = value; emit enableSerialChanged();}
}

void SystemSettingVM::setEnableNetwork(bool value)
{
    if(_enableNetwork != value){_enableNetwork = value; emit enableNetworkChanged();}
}

void SystemSettingVM::saveMachineName_Qml_Slot(QString value)
{
    setMachineName(value);
    ConfigApplication::instance()->m_commonInfo.appSetting.m_strMachineName = value;
    ConfigApplication::instance()->WriteAppSetting();
    qDebug() << "[SystemSettingVM]" << "Save machine name: " << value;
}

void SystemSettingVM::saveIPSetting_Qml_Slot(QString ipAddress, QString subnet, QString gateway, bool useDHCP)
{
    setIpAddress(ipAddress);
    // setSubnet(subnet);
    // setGateway(gateway);
    // setUseDHCP(useDHCP);

    // ConfigApplication::instance()->m_commonInfo.systemIPSetting.ip = _ipAddress;
    // ConfigApplication::instance()->m_commonInfo.systemIPSetting.subnet = _subnet;
    // ConfigApplication::instance()->m_commonInfo.systemIPSetting.gateway = _gateway;
    // ConfigApplication::instance()->m_commonInfo.systemIPSetting.isUseDHCP = _useDHCP;
    // ConfigApplication::instance()->WriteCommonSetting();

    ConfigApplication::instance()->m_commonInfo.plcSetting.strIPAddress = ipAddress;
    ConfigApplication::instance()->m_commonInfo.plcSetting.saveToFile(ConfigApplication::instance()->m_strPLCSettingFileName);
    qDebug() << "[SystemSettingVM]" << "Save IP setting: " << ipAddress;
}

void SystemSettingVM::saveDistanceUnit_Qml_Slot(int value)
{
    qDebug() << "[SystemSettingVM]" << "Save distance unit: " << value;
    setDistanceUnit(value);
    ConfigApplication::instance()->m_commonInfo.appSetting.m_nDistanceUnit = value;
    ConfigApplication::instance()->WriteAppSetting();
}

void SystemSettingVM::saveWeightUnit_Qml_Slot(int value)
{
    qDebug() << "[SystemSettingVM]" << "Save weight unit: " << value;
    setWeightUnit(value);
    ConfigApplication::instance()->m_commonInfo.appSetting.m_nWeightUnit = value;
    ConfigApplication::instance()->WriteAppSetting();
}

void SystemSettingVM::saveCommunication_Qml_Slot(int masterHost, bool serial, bool network)
{
    setMasterHost(masterHost);
    setEnableSerial(serial);
    setEnableNetwork(network);
    qDebug() << "[SystemSettingVM]" << "Save communication: " << masterHost << serial << network;
}

void SystemSettingVM::zipFolder_Qml_Slot(QString path)
{
    qDebug() << "[SystemSettingVM]" << "Zip: " << path;
    // ZipConfigFolder("C:/Users/hadai/Bottle-Config/123", path);

    // return;
    if(ZipConfigFolder(ConfigApplication::instance()->m_strConfigPath, path))
    {
        // popup dialog
        DialogVM::instance()->ShowDialog(tr("Archive"), \
                                         tr("Config folder archived successfully"), 1);
    }
    else
    {
        DialogVM::instance()->ShowDialog(tr("Archive"), \
                                         tr("Failed to archive the config folder."), 1);
    }
}

void SystemSettingVM::unZipFolder_Qml_Slot(QString path)
{
    qDebug() << "[SystemSettingVM]" << "Unzip: " << path;
    QString destFolder = path;
    destFolder = destFolder.replace(".zip", "");
    if(!QDir(destFolder).exists())
    {
        QDir().mkdir(destFolder);
    }
    destFolder += "/Bottle-Config";



    if(UnzipFile(path, destFolder))
    {
        // popup dialog
        DialogVM::instance()->ShowDialog(tr("Archive"), \
                                         tr("Config folder unarchived successfully"), 1);
    }
    else
    {
        DialogVM::instance()->ShowDialog(tr("Archive"), \
                                         tr("Failed to unarchive the config folder."), 1);
    }
}

void SystemSettingVM::exitSoftware()
{
    qDebug() << "[SystemSettingVM]" << "Exit Software";
    QCoreApplication::quit();
}

void SystemSettingVM::restartSoftware()
{
    qDebug() << "[SystemSettingVM]" << "Restart Software";

    QString program = QCoreApplication::applicationFilePath();
    QStringList arguments = QCoreApplication::arguments();

    QCoreApplication::quit();
    QProcess::startDetached(program, arguments);
}

void SystemSettingVM::rebootSystem()
{
    qDebug() << "[SystemSettingVM]" << "Reboot System";
#ifdef Q_OS_WIN
    QProcess::execute("shutdown /r /t 0");
#elif defined(Q_OS_LINUX)
    QProcess::execute("reboot");
#endif
}

void SystemSettingVM::shutdownSystem()
{
    qDebug() << "[SystemSettingVM]" << "Shutdown System";
#ifdef Q_OS_WIN
    QProcess::execute("shutdown /s /t 0");
#elif defined(Q_OS_LINUX)
    QProcess::execute("shutdown -h now");
#endif
}



