#ifndef STRUCT_DEF_H
#define STRUCT_DEF_H

#include <QObject>
#include <QVector>
#include <QImage>
#include <QHash>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>

enum ACCOUNT_LEVEL{
    NONE = 0,
    ADMINISTRATOR = 1,
    ENGINEER = 2,
    OPERATOR = 3,
};

enum TRACK_INDEX{
    CAMERA_1 = 0,  //Must be always started with index = 0 //Всегда должен начинаться с индекса = 0
    CAMERA_2 = 1,
    TRACK_COUNT,
};

enum CAMERA_TYPE
{
    MVS,
    NORMAL_USB,
};

enum CAMERA_PIXEL_FORMAT
{
    COLOR,
    MONO,
};

enum BACKEND_FUNCTION{
    DISCONNECT = 1,
    TEACH = 2,
    TEACH_DONE = 3,
    INSPECT = 4,
    INSPECT_DONE = 5,
    CHANGE_RECIPE = 6,
    CHANGE_RECIPE_DONE = 7,

    NON_ROUND_SHAPE_INSPECT_START = 8, // FIRST inspect //  Первый  Проверка
    NON_ROUND_SHAPE_INSPECT = 9,
    NON_ROUND_SHAPE_INSPECT_DONE = 10,

    TOP_INSPECT_START = 11, // FIRST inspect //  Первый  Проверка
    TOP_INSPECT = 12,
    TOP_INSPECT_DONE = 13,

    VALIDATION_INSPECT = 14,
    VALIDATION_INSPECT_DONE = 15,

    CALIBRATION_INSPECT = 16,
    CALIBRATION_INSPECT_DONE = 17,

    CORRECTION_FIRST_INSPECT = 18,
    CORRECTION_INSPECT = 19,
    CORRECTION_INSPECT_DONE = 20,

    BODYR_INSPECT_START = 21,
    BODYR_INSPECT = 22,
    BODYR_INSPECT_DONE = 23,
};

enum BACKEND_RESULT{
    PROCESS_ERROR = -1,
    PASS = 0,
    HEIGHT = 1,
    WEIGHT = 2,
    NON_ROUND_SHAPE = 3,
    BODYR_DIMENSION = 4,
    LEAN = 5,
    TILT = 6,
    F_DIMENSION = 7,
    A_DIMENSION = 8,
    T_DIMENSION = 9,
    E_DIMENSION = 10,
    D_DIMENSION = 11,
    B_DIMENSION = 12,
    S_DIMENSION = 13,
    H_DIMENSION = 14,
    LUGT_DIMENSION = 15,
    LUGT1_DIMENSION = 16,
    D_ANGLE_DIMENSION = 17,
    FLANGE_DIMENSION = 18,
    KNOCKOUT_DIMENSION = 19,
    PUSHUP_DIMENSION = 20,
    INSIDE_NECK = 21,
    WALL_THICKNESS = 22,
    CODE_NUMBER = 23,
    TOTAL_DEFECT,
};

enum MACHINE_STATUS {
    IDLE,
    MEASURING_CONTAINER,
    INITIALIZING,
    STARTING_MOTORS,
    CLOSE_DOOR,
    REMOVE_DOWN_CONTAINER,
    REMOVE_EXTRA_CONTAINER,
    VACUUM_FAILURE,
    TAKE_OUT_ASSEMBLY_FAILURE,

};

enum APP_STATUS {
    STOP,
    RUNNING,
};

enum INSPECT_SEQUENCE : int
{
    UNKNOW = 0,
    INITIALIZATION,

    WAIT_REQUEST_TRUE,
    SEND_REQUEST_ACK_TRUE,
    WAIT_REQUEST_FALSE,
    SEND_REQUEST_ACK_FALSE,

    WAIT_OPERATION_TYPE,
    SEND_OPERATION_TYPE_ACK_OR_OPERATION_ALL_COMPLETE,

    SEND_AT_INFEED_PARAMETER1,
    SEND_AT_INFEED_PARAMETER2,
    SEND_AT_INFEED_PARAMETER3,
    WAIT_AT_INFEED_PARAMETER_ACK,

    WAIT_AT_TURN_TABLE_SERIALNUMBER,
    SEND_AT_TURN_TABLE_PARAMETER,
    WAIT_AT_TURN_TABLE_PARAMETER_ACK,

    WAIT_AT_OUTFEED_SERIALNUMBER,
    WAIT_AT_OUTFEED_PARAMETER1,
    WAIT_AT_OUTFEED_PARAMETER2,

    WAIT_CAMERA_ACTION_COMPLETE,

    WAIT_OPERATION_COMPLETE_TRUE,
    SEND_OPERATION_COMPLETE_ACK_TRUE,
    WAIT_OPERATION_COMPLETE_FALSE,
    SEND_OPERATION_COMPLETE_ACK_FALSE,

    SEND_RESPONSE_TRUE,
    WAIT_RESPONSE_ACK_TRUE,
    SEND_RESPONSE_FALSE,
    WAIT_RESPONSE_ACK_FALSE,

    WAIT_RESPONSE_TRUE,
    SEND_RESPONSE_ACK_TRUE,
    WAIT_RESPOSE_FALSE,
    SEND_RESPONSE_ACK_FALSE,

    SEND_OPERATION_ALL_COMPLETE_TRUE,
    WAIT_OPERATION_ALL_COMPLETE_ACK_TRUE,
    SEND_OPERATION_ALL_COMPLETE_FALSE,
    WAIT_OPERATION_ALL_COMPLETE_ACK_FALSE,

    WAIT_OPERAITON_COMPLETE_COMMAND,
};

enum VALIDATION_SEQUENCE : int
{
    INITIAL=0,
    MOVE_BOTTOM1,
    MOVE_BOTTOM1_COMPLETE,
    MOVE_BOTTOM2,
    MOVE_BOTTOM2_COMPLETE,
    MOVE_TOP,
    MOVE_TOP_COMPLETE,
    VALIDATION,

};

enum INSPECT_SEQUENCE_TYPE : int
{
    NO_OPERATION = 0,
    AT_INFEED,
    AT_TURNING_TABLE,
    AT_OUTFEED,
};

enum INSPECT_SEQUENCE_CAMERA_POSITION : int
{
    BOTTOM1 = 0, // see the top bottle
    BOTTOM2,     // see the bottom bottle
    TOP,
    TOTAL_POS,
};

enum MOLD_RESULT : int
{
    NO_INSPECT = 0,
    MOLD_PASS,
    MOLD_WARNING,
    MOLD_FAIL,
};



struct InputBackendInfo
{
    BACKEND_FUNCTION function;
    QHash<INSPECT_SEQUENCE_CAMERA_POSITION, QImage> images;
    QString inputStr; // when change dl model imageName become dl model path // при изменении имени изображения модели DL имя изображения модели DL становится путем к модели DL

    // plc info // информация о плк
    double weight;
    double depth;

    // correction tab info inspect
    QString correctionData;
};

struct DefectInfoItem {
    DefectInfoItem(TRACK_INDEX _trackIndex,
                    BACKEND_RESULT _defect,
                    QString _parameter,
                    double _pixelValue,
                    double _mmValue, bool _isPass)
        : trackIndex(_trackIndex)
        , defect(_defect)
        , parameter(_parameter)
        , pixelValue(_pixelValue)
        , mmValue(_mmValue)
        , isPass(_isPass)
    {
    }

    DefectInfoItem()
    {
    }

    TRACK_INDEX trackIndex;
    BACKEND_RESULT defect;
    QString parameter;
    double pixelValue;
    double mmValue;
    bool isPass;
};

struct OutputBackendInfo
{
    BACKEND_FUNCTION function;
    QList<BACKEND_RESULT> defectCodes;
    QList<DefectInfoItem> defectInfos;
    QHash<TRACK_INDEX, QImage> images;
    QHash<TRACK_INDEX, QImage> operatorImages;
    QHash<TRACK_INDEX, QString> operatorImagePaths;
    MOLD_RESULT moldResult;
    QString resultString;
    int processTime;
    QDateTime dateTime;
};

struct CameraSetting
{
    double gain;
    double min_gain;
    double max_gain;
    double exposure;
    double min_exposure;
    double max_exposure;
    double red;
    double green;
    double blue;
    double min_balance;
    double max_balance;
};

struct SingleCameraConfig
{
    // CAMERA_TYPE type; // Basler or Nomal Usb Camera // CAMERA_TYPE тип; // Basler или обычная Usb-камера
    // CameraSetting camera_setting; // Настройка камеры
    QString serial;
    QString oldLoadImagePath;
    double resolution;
    bool isConnected;

    SingleCameraConfig()
        : serial("None")
        , oldLoadImagePath("")
        , resolution(0.05)
        , isConnected(false)
    {
    }
};

struct TCPServerInfo
{
    QString ip;
    int port;
};

struct SystemIPSetting
{
    QString ip;
    QString subnet;
    QString gateway;
    bool isUseDHCP;

    SystemIPSetting()
        : ip("192.168.1.100")
        , subnet("255.255.255.0")
        , gateway("192.168.1.1")
        , isUseDHCP(true)
    {
    }
};


struct SavingImageInfo
{
    QString save_dir;
};

struct PLCSetting
{
    QString strIPAddress;
    QString strPort;
    QString strServerAddress;

    PLCSetting()
    {
        strIPAddress = "192.168.1.100";
        strPort = "502";
        strServerAddress = "1";
    }

    QJsonObject toJson() const
    {
        QJsonObject jsonObj;
        jsonObj["IPAddress"] = strIPAddress;
        jsonObj["Port"] = strPort;
        jsonObj["ServerAddress"] = strServerAddress;
        return jsonObj;
    }

    void fromJson(const QJsonObject& jsonObj)
    {
        strIPAddress = jsonObj["IPAddress"].toString();
        strPort = jsonObj["Port"].toString();
        strServerAddress = jsonObj["ServerAddress"].toString();
    }

    bool saveToFile(const QString& fileName) const
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
            return false;

        QJsonDocument doc(toJson());
        file.write(doc.toJson());
        file.close();
        return true;
    }

    bool loadFromFile(const QString& fileName)
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
            return false;

        QByteArray data = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));
        if (doc.isNull())
            return false;

        fromJson(doc.object());
        return true;
    }
};

struct AppSetting
{
    // QString strConfigRecipeName;
    QString m_strMachineName;
    int m_nDistanceUnit;
    int m_nWeightUnit;
    int m_nCurrentReport;
    QHash<TRACK_INDEX, SingleCameraConfig> cameraConfig;

    AppSetting()
    {
        // strConfigRecipeName = "Default";
        m_strMachineName = "IsisDemo";
        m_nDistanceUnit = 1; // inches, mm, um
        m_nWeightUnit = 0; // grams, kgams
        m_nCurrentReport = 0;// from 0-3 max 4 report
        for (int i = 0; i < TRACK_INDEX::TRACK_COUNT; ++i) {
            cameraConfig[(TRACK_INDEX)i] = SingleCameraConfig();
        }
    }
};

struct CommonInfo
{
    TCPServerInfo tcp_server_info; // not use // не использовать
    SavingImageInfo saving_image_info; // not use // не использовать
    SystemIPSetting systemIPSetting; // not use // не использовать
    PLCSetting plcSetting;
    AppSetting appSetting;
};

struct CameraSettingData {
    Q_GADGET
    Q_PROPERTY(TRACK_INDEX camID MEMBER _camID)
    Q_PROPERTY(CAMERA_TYPE camType MEMBER _camType)
    Q_PROPERTY(QString camSerial MEMBER _camSerial)
    Q_PROPERTY(int camIndex MEMBER _camIndex)
    Q_PROPERTY(CAMERA_PIXEL_FORMAT pixelFormat MEMBER _pixelFormat)
    Q_PROPERTY(QString dlPath MEMBER _dlPath)
    Q_PROPERTY(int roiX MEMBER _roiX)
    Q_PROPERTY(int roiY MEMBER _roiY)
    Q_PROPERTY(int roiWidth MEMBER _roiWidth)
    Q_PROPERTY(int roiHeight MEMBER _roiHeight)

public:
    TRACK_INDEX _camID;
    CAMERA_TYPE _camType;
    QString _camSerial;
    int _camIndex;
    CAMERA_PIXEL_FORMAT _pixelFormat;
    QString _dlPath;
    int _roiX;
    int _roiY;
    int _roiWidth;
    int _roiHeight;
};

struct CommonSettingData {
    Q_GADGET
    Q_PROPERTY(QString savingFolder MEMBER _savingFolder)
    Q_PROPERTY(QString ipAddress MEMBER _ipAddress)
    Q_PROPERTY(int ipPort MEMBER _ipPort)

public:
    QString _savingFolder;
    QString _ipAddress;
    int _ipPort;
};

struct SingleReviewData
{
    QString info;
    QList<QString> imagePaths;
    QList<QImage> images;
};

struct CalibratioStepInfor
{
    int imageIndex;
    int bitPosValue;
    QString strDescription;

    CalibratioStepInfor() : bitPosValue(0), imageIndex(0) {};
    CalibratioStepInfor( int trackIndex,
        int bitVal, 
        QString des) :
        imageIndex(trackIndex), 
        bitPosValue(bitVal),
        strDescription(des) {};

};

// each cam rotate 0, 90, 180, 269 // каждая камера поворачивается на 0, 90, 180, 269
#define TOTAL_CALIBRATION_STEP 12
#define COMMAND_CALIBRATION 1
#define COMMAND_INSPECTION_SEQUENCE 2


#define LIMIT_FILE_NAME "limit_information.json"
// #define REPORT_FILE_NAME "data_report.json"
// inspection info // информация о проверке



class InspectionInfoChildItem{

    Q_GADGET
    Q_PROPERTY(QVariant value READ getValue WRITE setValue)
    Q_PROPERTY(bool isPass READ getIsPass WRITE setIsPass)

public:
    InspectionInfoChildItem(){
    }
    InspectionInfoChildItem(QVariant __value, bool __isPass){
        setValue(__value);
        setIsPass(__isPass);
    }
    QVariant getValue() const { return _value; }
    void setValue(QVariant value) { _value = value; }

    bool getIsPass() const { return _isPass; }
    void setIsPass(bool value) { _isPass = value; }


    QJsonObject SerializeData() const
    {
        QJsonObject jsonObj;

        jsonObj["value"] = _value.toString();
        jsonObj["isPass"] = _isPass;

        return jsonObj;
    }

    void DeseializeData(const QJsonObject& jsonObj)
    {
        _value =  jsonObj["value"].toString();
        _isPass = jsonObj["isPass"].toBool();
    }


private:
    bool _isPass;
    QVariant _value;
};

class InspectionInfoItem
{
    Q_GADGET
    Q_PROPERTY(InspectionInfoChildItem dateTime READ getDateTime WRITE setDateTime)
    Q_PROPERTY(InspectionInfoChildItem lotID READ getLotID WRITE setLotID)
    Q_PROPERTY(InspectionInfoChildItem job READ getJob WRITE setJob)
    Q_PROPERTY(InspectionInfoChildItem moldNumber READ getMoldNumber WRITE setMoldNumber)
    Q_PROPERTY(InspectionInfoChildItem height READ getHeight WRITE setHeight)
    Q_PROPERTY(InspectionInfoChildItem weight READ getWeight WRITE setWeight)
    Q_PROPERTY(QList<InspectionInfoChildItem> bodyR READ getBodyR WRITE setBodyR)
    Q_PROPERTY(InspectionInfoChildItem tilt READ getTilt WRITE setTilt)
    Q_PROPERTY(InspectionInfoChildItem lean READ getLean WRITE setLean)
    Q_PROPERTY(InspectionInfoChildItem dimensionF READ getDimensionF WRITE setDimensionF)
    Q_PROPERTY(InspectionInfoChildItem dimensionA READ getDimensionA WRITE setDimensionA)
    Q_PROPERTY(InspectionInfoChildItem dimensionT READ getDimensionT WRITE setDimensionT)
    Q_PROPERTY(InspectionInfoChildItem dimensionE READ getDimensionE WRITE setDimensionE)
    Q_PROPERTY(InspectionInfoChildItem dimensionB READ getDimensionB WRITE setDimensionB)
    Q_PROPERTY(InspectionInfoChildItem dimensionD READ getDimensionD WRITE setDimensionD)
    Q_PROPERTY(InspectionInfoChildItem dimensionS READ getDimensionS WRITE setDimensionS)
    Q_PROPERTY(InspectionInfoChildItem dimensionH READ getDimensionH WRITE setDimensionH)
    Q_PROPERTY(InspectionInfoChildItem dimensionLugT READ getDimensionLugT WRITE setDimensionLugT)
    Q_PROPERTY(InspectionInfoChildItem dimensionLugT1 READ getDimensionLugT1 WRITE setDimensionLugT1)
    Q_PROPERTY(InspectionInfoChildItem dAngle READ getDAngle WRITE setDAngle)
    Q_PROPERTY(InspectionInfoChildItem pushup READ getPushup WRITE setPushup)

    Q_PROPERTY(QList<InspectionInfoChildItem> recShrt READ getRecShrt WRITE setRecShrt)
    Q_PROPERTY(QList<InspectionInfoChildItem> recLong READ getRecLong WRITE setRecLong)
    Q_PROPERTY(QList<InspectionInfoChildItem> recDiag READ getRecDiag WRITE setRecDiag)
    Q_PROPERTY(QList<InspectionInfoChildItem> sqrSide READ getSqrSide WRITE setSqrSide)
    Q_PROPERTY(QList<InspectionInfoChildItem> sqrDiag READ getSqrDiag WRITE setSqrDiag)
    Q_PROPERTY(QList<InspectionInfoChildItem> ovlShrt READ getOvlShrt WRITE setOvlShrt)
    Q_PROPERTY(QList<InspectionInfoChildItem> ovlLong READ getOvlLong WRITE setOvlLong)

    Q_PROPERTY(InspectionInfoChildItem flange READ getFlange WRITE setFlange)
    Q_PROPERTY(InspectionInfoChildItem knockout READ getKnockout WRITE setKnockout)

    Q_PROPERTY(InspectionInfoChildItem codeNumber READ getCodeNumber WRITE setCodeNumber)

public:
    InspectionInfoItem(){
        setLotID(InspectionInfoChildItem("", true));
        setMoldNumber(InspectionInfoChildItem("", true));
        setJob(InspectionInfoChildItem("", true));
        setHeight(InspectionInfoChildItem("", true));
        setWeight(InspectionInfoChildItem("", true));
        setTilt(InspectionInfoChildItem("", true));
        setLean(InspectionInfoChildItem("", true));
        setDimensionF(InspectionInfoChildItem("", true));
        setDimensionA(InspectionInfoChildItem("", true));
        setDimensionT(InspectionInfoChildItem("", true));
        setDimensionE(InspectionInfoChildItem("", true));
        setDimensionB(InspectionInfoChildItem("", true));
        setDimensionD(InspectionInfoChildItem("", true));
        setDimensionS(InspectionInfoChildItem("", true));
        setDimensionH(InspectionInfoChildItem("", true));
        setDimensionLugT(InspectionInfoChildItem("", true));
        setDimensionLugT1(InspectionInfoChildItem("", true));
        setDAngle(InspectionInfoChildItem("", true));
        setPushup(InspectionInfoChildItem("", true));
        setFlange(InspectionInfoChildItem("", true));
        setKnockout(InspectionInfoChildItem("", true));
        setCodeNumber(InspectionInfoChildItem("", true));

    }
    InspectionInfoChildItem getDateTime() const { return _dateTime; }
    void setDateTime(InspectionInfoChildItem value) { _dateTime = value; }

    InspectionInfoChildItem getLotID() const { return _lotID; }
    void setLotID(InspectionInfoChildItem value) { _lotID = value; }

    InspectionInfoChildItem getJob() const { return _job; }
    void setJob(InspectionInfoChildItem value) { _job = value; }

    InspectionInfoChildItem getMoldNumber() const { return _moldNumber; }
    void setMoldNumber(InspectionInfoChildItem value) { _moldNumber = value; }

    InspectionInfoChildItem getHeight() const { return _height; }
    void setHeight(InspectionInfoChildItem value) { _height = value; }

    InspectionInfoChildItem getWeight() const { return _weight; }
    void setWeight(InspectionInfoChildItem value) { _weight = value; }

    QList<InspectionInfoChildItem> getBodyR() const { return _bodyR; }
    void setBodyR(QList<InspectionInfoChildItem> value) { _bodyR = value; }

    InspectionInfoChildItem getTilt() const { return _tilt; }
    void setTilt(InspectionInfoChildItem value) { _tilt = value; }

    InspectionInfoChildItem getLean() const { return _lean; }
    void setLean(InspectionInfoChildItem value) { _lean = value; }

    InspectionInfoChildItem getDimensionF() const { return _dimensionF; }
    void setDimensionF(InspectionInfoChildItem value) { _dimensionF = value; }

    InspectionInfoChildItem getDimensionA() const { return _dimensionA; }
    void setDimensionA(InspectionInfoChildItem value) { _dimensionA = value; }

    InspectionInfoChildItem getDimensionT() const { return _dimensionT; }
    void setDimensionT(InspectionInfoChildItem value) { _dimensionT = value; }

    InspectionInfoChildItem getDimensionE() const { return _dimensionE; }
    void setDimensionE(InspectionInfoChildItem value) { _dimensionE = value; }

    InspectionInfoChildItem getDimensionB() const { return _dimensionB; }
    void setDimensionB(InspectionInfoChildItem value) { _dimensionB = value; }

    InspectionInfoChildItem getDimensionD() const { return _dimensionD; }
    void setDimensionD(InspectionInfoChildItem value) { _dimensionD = value; }

    InspectionInfoChildItem getDimensionS() const { return _dimensionS; }
    void setDimensionS(InspectionInfoChildItem value) { _dimensionS = value; }

    InspectionInfoChildItem getDimensionH() const { return _dimensionH; }
    void setDimensionH(InspectionInfoChildItem value) { _dimensionH = value; }

    InspectionInfoChildItem getDimensionLugT() const { return _dimensionLugT; }
    void setDimensionLugT(InspectionInfoChildItem value) { _dimensionLugT = value; }

    InspectionInfoChildItem getDimensionLugT1() const { return _dimensionLugT1; }
    void setDimensionLugT1(InspectionInfoChildItem value) { _dimensionLugT1 = value; }

    InspectionInfoChildItem getDAngle() const { return _dAngle; }
    void setDAngle(InspectionInfoChildItem value) { _dAngle = value; }

    InspectionInfoChildItem getPushup() const { return _pushup; }
    void setPushup(InspectionInfoChildItem value) { _pushup = value; }


    QList<InspectionInfoChildItem> getRecShrt() const { return _recShrt; }
    void setRecShrt(QList<InspectionInfoChildItem> value) { _recShrt = value; }

    QList<InspectionInfoChildItem> getRecLong() const { return _recLong; }
    void setRecLong(QList<InspectionInfoChildItem> value) { _recLong = value; }

    QList<InspectionInfoChildItem> getRecDiag() const { return _recDiag; }
    void setRecDiag(QList<InspectionInfoChildItem> value) { _recDiag = value; }

    QList<InspectionInfoChildItem> getSqrSide() const { return _sqrSide; }
    void setSqrSide(QList<InspectionInfoChildItem> value) { _sqrSide = value; }

    QList<InspectionInfoChildItem> getSqrDiag() const { return _sqrDiag; }
    void setSqrDiag(QList<InspectionInfoChildItem> value) { _sqrDiag = value; }

    QList<InspectionInfoChildItem> getOvlShrt() const { return _ovlShrt; }
    void setOvlShrt(QList<InspectionInfoChildItem> value) { _ovlShrt = value; }

    QList<InspectionInfoChildItem> getOvlLong() const { return _ovlLong; }
    void setOvlLong(QList<InspectionInfoChildItem> value) { _ovlLong = value; }

    InspectionInfoChildItem getFlange() const { return _flange; }
    void setFlange(InspectionInfoChildItem value) { _flange = value; }

    InspectionInfoChildItem getKnockout() const { return _knockout; }
    void setKnockout(InspectionInfoChildItem value) { _knockout = value; }

    InspectionInfoChildItem getCodeNumber() const { return _codeNumber; }
    void setCodeNumber(InspectionInfoChildItem value) { _codeNumber = value; }

    QJsonObject SerializeData()
    {
        QJsonObject jsonObj;
        jsonObj["dateTime"] = _dateTime.SerializeData();
        jsonObj["lotID"] = _lotID.SerializeData();
        jsonObj["job"] = _job.SerializeData();
        jsonObj["moldNumber"] = _moldNumber.SerializeData();
        jsonObj["height"] = _height.SerializeData();
        jsonObj["weight"] = _weight.SerializeData();

        // Convert QList<InspectionInfoChildItem> to QJsonArray
        QJsonArray bodyArray;
        for (const auto& childItem : _bodyR) {
            bodyArray.append(childItem.SerializeData());
        }
        jsonObj["bodyR"] = bodyArray;
        jsonObj["tilt"] = _tilt.SerializeData();
        jsonObj["lean"] = _lean.SerializeData();
        jsonObj["dimensionF"] = _dimensionF.SerializeData();
        jsonObj["dimensionA"] = _dimensionA.SerializeData();
        jsonObj["dimensionT"] = _dimensionT.SerializeData();
        jsonObj["dimensionE"] = _dimensionE.SerializeData();
        jsonObj["dimensionB"] = _dimensionB.SerializeData();
        jsonObj["dimensionD"] = _dimensionD.SerializeData();
        jsonObj["dimensionS"] = _dimensionS.SerializeData();
        jsonObj["dimensionH"] = _dimensionH.SerializeData();
        jsonObj["dimensionLugT"] = _dimensionLugT.SerializeData();
        jsonObj["dimensionLugT1"] = _dimensionLugT1.SerializeData();
        jsonObj["dAngle"] = _dAngle.SerializeData();
        jsonObj["pushup"] = _pushup.SerializeData();

        QJsonArray recShrtArray;
        for (const auto& childItem : _recShrt) {
            recShrtArray.append(childItem.SerializeData());
        }
        jsonObj["recShrt"] = recShrtArray;

        QJsonArray recLongArray;
        for (const auto& childItem : _recLong) {
            recLongArray.append(childItem.SerializeData());
        }
        jsonObj["recLong"] = recLongArray;

        QJsonArray recDiagArray;
        for (const auto& childItem : _recDiag) {
            recDiagArray.append(childItem.SerializeData());
        }
        jsonObj["recDiag"] = recDiagArray;

        QJsonArray sqrSideArray;
        for (const auto& childItem : _sqrSide) {
            sqrSideArray.append(childItem.SerializeData());
        }
        jsonObj["sqrSide"] = sqrSideArray;

        QJsonArray sqrDiagArray;
        for (const auto& childItem : _sqrDiag) {
            sqrDiagArray.append(childItem.SerializeData());
        }
        jsonObj["sqrDiag"] = sqrDiagArray;

        QJsonArray bodyArrayOvlShrt;
        for (const auto& childItem : _ovlShrt) {
            bodyArrayOvlShrt.append(childItem.SerializeData());
        }
        jsonObj["ovlShrt"] = bodyArrayOvlShrt;

        QJsonArray ovlLongArray;
        for (const auto& childItem : _ovlLong) {
            ovlLongArray.append(childItem.SerializeData());
        }
        jsonObj["ovlLong"] = ovlLongArray;

        jsonObj["flange"] = _flange.SerializeData();
        jsonObj["knockout"] = _knockout.SerializeData();
        jsonObj["codeNumber"] = _codeNumber.SerializeData();

        return jsonObj;
    }

    void DeserializeData(const QJsonObject& jsonObj)
    {
        _dateTime.DeseializeData(jsonObj["dateTime"].toObject());
        _lotID.DeseializeData(jsonObj["lotID"].toObject());
        _job.DeseializeData(jsonObj["job"].toObject());
        _moldNumber.DeseializeData(jsonObj["moldNumber"].toObject());
        _height.DeseializeData(jsonObj["height"].toObject());
        _weight.DeseializeData(jsonObj["weight"].toObject());

        // Convert QJsonArray to QList<InspectionInfoChildItem>
        QJsonArray bodyArray = jsonObj["bodyR"].toArray();
        for (const auto& childVal : bodyArray) {
            InspectionInfoChildItem item;
            item.DeseializeData(childVal.toObject());
            _bodyR.append(item);
        }

        _tilt.DeseializeData(jsonObj["tilt"].toObject());
        _lean.DeseializeData(jsonObj["lean"].toObject());
        _dimensionF.DeseializeData(jsonObj["dimensionF"].toObject());
        _dimensionA.DeseializeData(jsonObj["dimensionA"].toObject());
        _dimensionT.DeseializeData(jsonObj["dimensionT"].toObject());
        _dimensionE.DeseializeData(jsonObj["dimensionE"].toObject());
        _dimensionB.DeseializeData(jsonObj["dimensionB"].toObject());
        _dimensionD.DeseializeData(jsonObj["dimensionD"].toObject());
        _dimensionS.DeseializeData(jsonObj["dimensionS"].toObject());
        _dimensionH.DeseializeData(jsonObj["dimensionH"].toObject());
        _dimensionLugT.DeseializeData(jsonObj["dimensionLugT"].toObject());
        _dimensionLugT1.DeseializeData(jsonObj["dimensionLugT1"].toObject());
        _dAngle.DeseializeData(jsonObj["dAngle"].toObject());
        _pushup.DeseializeData(jsonObj["pushup"].toObject());

        QJsonArray recShrtArray = jsonObj["recShrt"].toArray();
        for (const auto& childVal : recShrtArray) {
            InspectionInfoChildItem item;
            item.DeseializeData(childVal.toObject());
            _recShrt.append(item);
        }

        QJsonArray recLongArray = jsonObj["recLong"].toArray();
        for (const auto& childVal : recLongArray) {
            InspectionInfoChildItem item;
            item.DeseializeData(childVal.toObject());
            _recLong.append(item);
        }

        QJsonArray recDiagArray = jsonObj["recDiag"].toArray();
        for (const auto& childVal : recDiagArray) {
            InspectionInfoChildItem item;
            item.DeseializeData(childVal.toObject());
            _recDiag.append(item);
        }

        QJsonArray sqrSideArray = jsonObj["sqrSide"].toArray();
        for (const auto& childVal : sqrSideArray) {
            InspectionInfoChildItem item;
            item.DeseializeData(childVal.toObject());
            _sqrSide.append(item);
        }

        QJsonArray sqrDiagArray = jsonObj["sqrDiag"].toArray();
        for (const auto& childVal : sqrDiagArray) {
            InspectionInfoChildItem item;
            item.DeseializeData(childVal.toObject());
            _sqrDiag.append(item);
        }

        QJsonArray ovlShrtArray = jsonObj["ovlShrt"].toArray();
        for (const auto& childVal : ovlShrtArray) {
            InspectionInfoChildItem item;
            item.DeseializeData(childVal.toObject());
            _ovlShrt.append(item);
        }

        QJsonArray ovlLongArray = jsonObj["ovlLong"].toArray();
        for (const auto& childVal : ovlLongArray) {
            InspectionInfoChildItem item;
            item.DeseializeData(childVal.toObject());
            _ovlLong.append(item);
        }

        _flange.DeseializeData(jsonObj["flange"].toObject());
        _knockout.DeseializeData(jsonObj["knockout"].toObject());
        _codeNumber.DeseializeData(jsonObj["codeNumber"].toObject());
    }

private:
    InspectionInfoChildItem _dateTime;
    InspectionInfoChildItem _lotID;
    InspectionInfoChildItem _job;
    InspectionInfoChildItem _moldNumber;
    InspectionInfoChildItem _height;
    InspectionInfoChildItem _weight;
    QList<InspectionInfoChildItem> _bodyR;
    InspectionInfoChildItem _tilt;
    InspectionInfoChildItem _lean;
    InspectionInfoChildItem _dimensionF;
    InspectionInfoChildItem _dimensionA;
    InspectionInfoChildItem _dimensionT;
    InspectionInfoChildItem _dimensionE;
    InspectionInfoChildItem _dimensionB;
    InspectionInfoChildItem _dimensionD;
    InspectionInfoChildItem _dimensionS;
    InspectionInfoChildItem _dimensionH;
    InspectionInfoChildItem _dimensionLugT;
    InspectionInfoChildItem _dimensionLugT1;
    InspectionInfoChildItem _dAngle;
    InspectionInfoChildItem _pushup;
    QList<InspectionInfoChildItem> _recShrt;
    QList<InspectionInfoChildItem> _recLong;
    QList<InspectionInfoChildItem> _recDiag;
    QList<InspectionInfoChildItem> _sqrSide;
    QList<InspectionInfoChildItem> _sqrDiag;
    QList<InspectionInfoChildItem> _ovlShrt;
    QList<InspectionInfoChildItem> _ovlLong;

    InspectionInfoChildItem _flange;
    InspectionInfoChildItem _knockout;

    InspectionInfoChildItem _codeNumber;

};

struct InspectionSequenceData {

    INSPECT_SEQUENCE m_nCurrentInspectionSequenceStep;
    INSPECT_SEQUENCE_TYPE m_nCurrentInspectionSequenceType;
    INSPECT_SEQUENCE_CAMERA_POSITION m_nCurrentInspectionSequenceCameraPos;
    quint32  m_nCurrentSerialNumber; // current serial number
    float m_dWeight;
    float m_dDepth;
    // int m_nBottleContainerShapeImageNumber;
    // int m_nCurrentBottleContainerShapeImageNumber;
    // store image for all position when run sequence
    QHash<INSPECT_SEQUENCE_CAMERA_POSITION, QImage> m_hashSequencePosImages;
    QHash<INSPECT_SEQUENCE_CAMERA_POSITION, int> m_hashCurrentPositionImageNumber;
    QHash<INSPECT_SEQUENCE_CAMERA_POSITION, int> m_hashPositionImageNumber;

    InspectionSequenceData()
    {
        // m_nBottleContainerShapeImageNumber = 50;
        m_hashPositionImageNumber[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1] = 1;
        m_hashPositionImageNumber[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2] = 50;
        m_hashPositionImageNumber[INSPECT_SEQUENCE_CAMERA_POSITION::TOP] = 50;
        Reset();
    }

    void Reset()
    {
        m_nCurrentInspectionSequenceStep = INSPECT_SEQUENCE::UNKNOW;
        m_nCurrentInspectionSequenceType = INSPECT_SEQUENCE_TYPE::NO_OPERATION;
        m_nCurrentInspectionSequenceCameraPos = INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1;
        m_nCurrentSerialNumber = 0;
        m_dWeight = 0;
        m_dDepth = 0;
        // m_nCurrentBottleContainerShapeImageNumber = 0;
        m_hashSequencePosImages.clear();
        for (int i = 0; i < INSPECT_SEQUENCE_CAMERA_POSITION::TOTAL_POS; ++i) {
            m_hashCurrentPositionImageNumber[(INSPECT_SEQUENCE_CAMERA_POSITION)i] = 0;
        }

    }

};

struct SetoutMoldsData
{
    SetoutMoldsData() {
        Clear();
    }

    int m_nMoldNumber = 7*8;
    quint32 m_nCurrentMoldIndex = 0;
    QList<int> m_ListMoldResults; // 7*8 molds, each mold have result // 7* 8 форм, каждая форма имеет результат
    QList<QString> m_ListMoldNumbers; // 7*8 molds, each mold have result // 7* 8 форм, каждая форма имеет результат

    // update mold number // обновить номер формы
    void UpdateMoldNumber(QList<QString> data)
    {
        if(m_ListMoldResults.count() == 0)
            InitMoldResult();
        m_ListMoldNumbers = data;
    }

    // update mold result // обновить результат  формы
    void UpdateResult(MOLD_RESULT result, int moldIndex)
    {
        if(m_ListMoldResults.count() == 0)
            InitMoldResult();
        if(m_ListMoldNumbers.count() == 0)
            InitMoldNumber();
        m_ListMoldResults[moldIndex] = (int)result;
    }

    // clear all reset to 0 // сбросить все значения до 0
    void Clear()
    {
        m_ListMoldResults.clear();
        m_ListMoldNumbers.clear();
        for (int i = 0; i < m_nMoldNumber; ++i)
        {
            m_ListMoldResults.append((int)MOLD_RESULT::NO_INSPECT);
            m_ListMoldNumbers.append("");
            m_nCurrentMoldIndex = 0;
        }
    }

    void InitMoldResult()
    {
        m_ListMoldResults.clear();
        for (int i = 0; i < m_nMoldNumber; ++i)
        {
            m_ListMoldResults.append((int)MOLD_RESULT::NO_INSPECT);
        }
    }

    void InitMoldNumber()
    {
        m_ListMoldNumbers.clear();
        for (int i = 0; i < m_nMoldNumber; ++i)
        {
            m_ListMoldNumbers.append("");
        }
    }

    // get current mold number // получить текущий номер формы

    bool GetMoldNumberInspectionSequence(quint32& moldIndex)
    {
        moldIndex = 0;
        if(m_ListMoldResults.count() == 0)
            return true;
        for (int i = 0; i < m_nMoldNumber; i++)
        {
            if(m_ListMoldResults[i] == MOLD_RESULT::NO_INSPECT)
            {
                moldIndex = i;
                return true;
            }
        }
        return false;
    }




    // json
    QJsonObject toJson() const
    {
        QJsonObject jsonObj;
        QJsonArray jsonMoldNumberArray;
        for (QString value : m_ListMoldNumbers) {
            jsonMoldNumberArray.append(value);
        }
        jsonObj.insert(QString("Mold Number"), jsonMoldNumberArray);

        QJsonArray jsonMoldResultArray;
        for (int value : m_ListMoldResults) {
            jsonMoldResultArray.append(value);
        }
        jsonObj.insert(QString("Mold Result"), jsonMoldResultArray);
        return jsonObj;
    }

    void fromJson(const QJsonObject& jsonObj)
    {
        QJsonArray jsonMoldNumberArray = jsonObj[QString("Mold Number")].toArray();
        m_ListMoldNumbers.clear();
        for (const QJsonValue &value : jsonMoldNumberArray) {
            m_ListMoldNumbers.append(value.toString());
        }

        QJsonArray jsonMoldResultArray = jsonObj[QString("Mold Result")].toArray();
        m_ListMoldResults.clear();
        for (const QJsonValue &value : jsonMoldResultArray) {
            if (value.isDouble())
                m_ListMoldResults.append(value.toInt());
        }

        if(m_ListMoldResults.count() == 0)
            InitMoldResult();
    }

    bool saveToFile(const QString& fileName) const
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
            return false;

        QJsonDocument doc(toJson());
        file.write(doc.toJson());
        file.close();
        return true;
    }

    bool loadFromFile(const QString& fileName)
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            m_ListMoldNumbers.clear();
            m_ListMoldResults.clear();
            return false;
        }

        QByteArray data = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));
        if (doc.isNull())
        {
            m_ListMoldNumbers.clear();
            m_ListMoldResults.clear();
            return false;
        }
        fromJson(doc.object());
        return true;
    }
};

// calib camera position
struct CalibCameraPosData {
    // calib tool info: height = 300mm
    // width1 = 30 mm
    // width2 = 49 mm

    QHash<INSPECT_SEQUENCE_CAMERA_POSITION, double> m_hashLiftingMechanismPos; // mm: lifting position
    QHash<TRACK_INDEX, double> m_hashHidedBottleHeight; // mm: extra height for each camera to backend calculate correct the bottle height
    double toolHeight; // mm
    double toolWidth;  // mm
    double maxBottleHeightInBottom; //mm
    // resolution: m_commonInfo.appSetting.cameraConfig[(TRACK_INDEX)i].resolution

    CalibCameraPosData()
    {
        toolHeight = 300;
        toolWidth = 30;
        maxBottleHeightInBottom = 220;

        m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1] = 504;
        m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2] = 620;
        m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::TOP] = 754;

        m_hashHidedBottleHeight[TRACK_INDEX::CAMERA_1] = 614.0778 - m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1];
        m_hashHidedBottleHeight[TRACK_INDEX::CAMERA_2] = 1012.4 - m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::TOP];
    }

    // json
    QJsonObject toJson() const
    {
        QJsonObject jsonObj;

        QJsonObject toolInfo;
        toolInfo.insert("Width", toolWidth);
        toolInfo.insert("Height", toolHeight);
        toolInfo.insert("Max Bottle Height In Bottom", maxBottleHeightInBottom);
        jsonObj.insert("Tool Info", toolInfo);

        QJsonObject liftingMechanismPos;
        liftingMechanismPos.insert("Bottom 1", m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1]);
        liftingMechanismPos.insert("Bottom 2", m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2]);
        liftingMechanismPos.insert("Top", m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::TOP]);
        jsonObj.insert("Lifting Mechanism Position", liftingMechanismPos);

        QJsonObject hidedBottleHeight;
        hidedBottleHeight.insert("Bottom", m_hashHidedBottleHeight[TRACK_INDEX::CAMERA_1]);
        hidedBottleHeight.insert("Top", m_hashHidedBottleHeight[TRACK_INDEX::CAMERA_2]);
        jsonObj.insert("Hide Bottle Height", hidedBottleHeight);

        return jsonObj;
    }

    void fromJson(const QJsonObject& jsonObj)
    {
        QJsonValue toolInfo = jsonObj.value("Tool Info");
        toolWidth = toolInfo.toVariant().toHash().value(QString("Width")).toDouble();
        toolHeight = toolInfo.toVariant().toHash().value(QString("Height")).toDouble();
        maxBottleHeightInBottom = toolInfo.toVariant().toHash().value(QString("Max Bottle Height In Bottom")).toDouble();

        QJsonValue liftingMechanismPos = jsonObj.value("Lifting Mechanism Position");
        m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1] =
            liftingMechanismPos.toVariant().toHash().value(QString("Bottom 1")).toDouble();
        m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2] =
            liftingMechanismPos.toVariant().toHash().value(QString("Bottom 2")).toDouble();
        m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::TOP] =
            liftingMechanismPos.toVariant().toHash().value(QString("Top")).toDouble();


        QJsonValue hidedBottleHeight = jsonObj.value("Hide Bottle Height");
        m_hashHidedBottleHeight[TRACK_INDEX::CAMERA_1] =
            hidedBottleHeight.toVariant().toHash().value(QString("Bottom")).toDouble();
        m_hashHidedBottleHeight[TRACK_INDEX::CAMERA_2] =
            hidedBottleHeight.toVariant().toHash().value(QString("Top")).toDouble();

    }

    bool saveToFile(const QString& fileName) const
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
            return false;

        QJsonDocument doc(toJson());
        file.write(doc.toJson());
        file.close();
        return true;
    }

    bool loadFromFile(const QString& fileName)
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            saveToFile(fileName);
            return false;
        }

        QByteArray data = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));
        if (doc.isNull())
        {
            saveToFile(fileName);
            return false;
        }
        fromJson(doc.object());
        return true;
    }

};

#endif // STRUCT_DEF_H
