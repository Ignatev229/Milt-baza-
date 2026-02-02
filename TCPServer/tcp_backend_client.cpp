#include "tcp_backend_client.h"

TCPBackendClient::TCPBackendClient(QObject *parent)
    : QObject{parent}
{
    sizeRequired = -1;
    scopedSocket.reset(new QTcpSocket);
    connect(scopedSocket.data(), SIGNAL(connected()), this, SLOT(Connected_Slots()), Qt::DirectConnection);
    connect(scopedSocket.data(), SIGNAL(readyRead()), this, SLOT(ReadyRead_Slots()),Qt::DirectConnection);
    connect(scopedSocket.data(), SIGNAL(disconnected()), this, SLOT(Disconnected_Slots()),Qt::DirectConnection);
    scopedSocket.data()->connectToHost("127.0.0.2", ConfigApplication::instance()->m_nBackendPort);
    isConnected = scopedSocket.data()->waitForConnected(2000);
    qDebug() << "[TCPBackend]" << "Connect to backend server: " << isConnected;
    //    DebugLogVM::instance()->WriteDebugLog("Connect to backend server: " + QVariant(isConnected).toString()); // DebugLogVM::instance()->WriteDebugLog("Подключиться к  Бэкенд-серверу: " + QVariant(подключен).toString());
}

TCPBackendClient::~TCPBackendClient()
{
    scopedSocket.data()->deleteLater();
}


bool TCPBackendClient::Send(InputBackendInfo &inputBackendInfo)
{
    if(!isConnected)
    {
        qDebug() << "[TCPBackend]" << "Can not connect to backend server";
        return false;
    }
    // buffer length = 4, function index = 4, stepDebug = 2, numberImage = 4, width = 4, height = 4, channel = 2, roi = 16, issaveimage = 2, длина буфера = 4, индекс функции = 4, шаг отладки = 2, номер изображения = 4, ширина = 4, высота = 4, канал = 2, roi = 16, значение сохранения изображения = 2,
    // Score = 4, image byte, path name //  Балл = 4, байт изображения, имя пути
    QByteArray bytesToSend;

    // function // функция
    QByteArray functionBytes(reinterpret_cast<const char*>(&inputBackendInfo.function), sizeof(int));

    // stepDebug // этап отладки
    int isStepDebug = 0;
    QByteArray isStepDebugBytes(reinterpret_cast<const char*>(&isStepDebug), 2);

    // process image // изображение процесса
    // convert qImage to Byte // преобразовать qImage в байт
    QByteArray imageBytes;
    int numberImage = 0;
    for (int i = 0; i < INSPECT_SEQUENCE_CAMERA_POSITION::TOTAL_POS; ++i)
    {
        if(!inputBackendInfo.images.contains((INSPECT_SEQUENCE_CAMERA_POSITION)i))
            continue;
        // image width // ширина изображения
        int width = inputBackendInfo.images[(INSPECT_SEQUENCE_CAMERA_POSITION)i].width();

        QByteArray widthBytes(reinterpret_cast<const char*>(&width), sizeof(int));
        // image height // высота изображения
        int height = inputBackendInfo.images[(INSPECT_SEQUENCE_CAMERA_POSITION)i].height();
        QByteArray heightBytes(reinterpret_cast<const char*>(&height), sizeof(int));
        // channel // канал
        int channel = 1;
        QByteArray channelBytes(reinterpret_cast<const char*>(&channel), 2);

        inputBackendInfo.images[(INSPECT_SEQUENCE_CAMERA_POSITION)i] = inputBackendInfo.images[(INSPECT_SEQUENCE_CAMERA_POSITION)i].convertToFormat(QImage::Format_Grayscale8);
        imageBytes.append(widthBytes);
        imageBytes.append(heightBytes);
        imageBytes.append(channelBytes);
        imageBytes.append(QByteArray::fromRawData((const char*)inputBackendInfo.images[(INSPECT_SEQUENCE_CAMERA_POSITION)i].bits(), inputBackendInfo.images[(INSPECT_SEQUENCE_CAMERA_POSITION)i].byteCount()));
        numberImage++;
    }



    QByteArray inputStrBytes = QByteArray::fromStdString(inputBackendInfo.inputStr.toStdString());

    QByteArray infoToSend;
    infoToSend.append(functionBytes);
    infoToSend.append(isStepDebugBytes);
    infoToSend.append(reinterpret_cast<const char*>(&numberImage), sizeof(int));
    if(inputBackendInfo.function == BACKEND_FUNCTION::INSPECT ||
        inputBackendInfo.function == BACKEND_FUNCTION::NON_ROUND_SHAPE_INSPECT_START ||
        inputBackendInfo.function == BACKEND_FUNCTION::NON_ROUND_SHAPE_INSPECT ||
        inputBackendInfo.function == BACKEND_FUNCTION::TOP_INSPECT_START ||
        inputBackendInfo.function == BACKEND_FUNCTION::TOP_INSPECT ||
        inputBackendInfo.function == BACKEND_FUNCTION::VALIDATION_INSPECT ||
        inputBackendInfo.function == BACKEND_FUNCTION::CALIBRATION_INSPECT ||
        inputBackendInfo.function == BACKEND_FUNCTION::CORRECTION_FIRST_INSPECT ||
        inputBackendInfo.function == BACKEND_FUNCTION::CORRECTION_INSPECT)
    {
        infoToSend.append(imageBytes);
        // add plc data // добавить данные плк
        QString plcData = QString("%1$%2$%3")
                    .arg(inputBackendInfo.weight)
                    .arg(inputBackendInfo.depth)
                    .arg(inputBackendInfo.correctionData);
        inputStrBytes = QByteArray::fromStdString(plcData.toStdString());
    }
    else
    {
        numberImage = 0;
    }
    infoToSend.append(inputStrBytes);
    // message length // длина сообщения
    int sendMessageLenght = 4 + infoToSend.length();
    QByteArray contentLength(reinterpret_cast<const char*>(&sendMessageLenght), sizeof(int));


    qDebug() << "[TCPBackend]" << "Send Message: " << inputBackendInfo.function;

    bytesToSend.append(contentLength);
    bytesToSend.append(infoToSend);

    scopedSocket.data()->write(bytesToSend);
    scopedSocket.data()->flush();

    return true;
}

void TCPBackendClient::Disconnect()
{
    InputBackendInfo inputBackendInfo;
    QImage image = QImage(4, 4, QImage::Format_Grayscale8);
    inputBackendInfo.function = BACKEND_FUNCTION::DISCONNECT;
    // for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
    // {
    //     inputBackendInfo.images[(TRACK_INDEX)i] = image;
    // }
    inputBackendInfo.images.clear();
    inputBackendInfo.inputStr = "";
    Send(inputBackendInfo);
}

void TCPBackendClient::DLModelPathChanged(TRACK_INDEX trackID)
{
    // InputBackendInfo inputBackendInfo;
    // QImage image = QImage(0, 0, QImage::Format_Grayscale8);
    // inputBackendInfo.function = BACKEND_FUNCTION::CHANGE_RECIPE;
    // inputBackendInfo.camID = trackID;
    // inputBackendInfo.image = image;
    // inputBackendInfo.inputStr = ConfigApplication::instance()->m_hashConfigCameras[trackID].dl_path;
    // Send(inputBackendInfo);
}

void TCPBackendClient::RecipeChanged()
{
    InputBackendInfo inputBackendInfo;
    QImage image = QImage(0, 0, QImage::Format_Grayscale8);
    inputBackendInfo.function = BACKEND_FUNCTION::CHANGE_RECIPE;
    // for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
    // {
    //     inputBackendInfo.images[(TRACK_INDEX)i] = image;
    // }
    inputBackendInfo.images.clear();
    auto folderPath = ConfigApplication::instance()->m_strConfigRecipePath;
    auto recipeFolderPath = QDir::cleanPath(folderPath + QDir::separator() + ConfigApplication::instance()->m_strConfigRecipeName);
    inputBackendInfo.inputStr = recipeFolderPath;
    Send(inputBackendInfo);
}

void TCPBackendClient::ReceiveMessage()
{
    try
    {
        if(sizeRequired == -1)
        {
            //buffer length = 4, function index = 4, width = 4, height = 4, channel = 2, image byte, result str //длина буфера = 4, индекс функции = 4, ширина = 4, высота = 4, канал = 2, байт изображения, строка результата
            //1. Read Header: contains 4 bytes represent as content lenght message //1. Заголовок чтения: содержит 4 байта, представляющие собой сообщение длиной содержимого
            QByteArray contentLength = scopedSocket.data()->read(4);
            int messageLenght = qFromLittleEndian<qint32>(contentLength);
            sizeRequired = messageLenght - 4;

        }
        int size = scopedSocket.data()->bytesAvailable();
        if(size < sizeRequired)
            return;

        int currentLength = 0;
        QByteArray functionBytes = scopedSocket.data()->read(4);
        int functionIndex = qFromLittleEndian<qint32>(functionBytes);
        currentLength += 4;

        OutputBackendInfo output;
        output.function = (BACKEND_FUNCTION)functionIndex;

        // process image // изображение процесса



        if(output.function == BACKEND_FUNCTION::INSPECT_DONE ||
            output.function == BACKEND_FUNCTION::VALIDATION_INSPECT_DONE ||
            output.function == BACKEND_FUNCTION::CALIBRATION_INSPECT_DONE)
        {
            for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
            {
                QByteArray widthBytes = scopedSocket.data()->read(4);
                int width = qFromLittleEndian<qint32>(widthBytes);
                QByteArray heightBytes = scopedSocket.data()->read(4);
                int height = qFromLittleEndian<qint32>(heightBytes);
                QByteArray channelBytes = scopedSocket.data()->read(2);
                int channel = qFromLittleEndian<qint16>(channelBytes);
                int imageSize = width*height*channel;
                QImage image = QImage(0, 0, QImage::Format_Grayscale8);
                if(imageSize != 0)
                {
                    QByteArray imageBytes = scopedSocket.data()->read(imageSize);
                    if(channel == 3)
                    {
                        image = QImage((const uchar*)imageBytes.data(), width, height, QImage::Format_BGR888);
                    }
                    else
                    {
                        image = QImage((const uchar*)imageBytes.data(), width, height, QImage::Format_Grayscale8);
                    }

                    QPixmap pixmap = QPixmap::fromImage(image);
                    image = pixmap.toImage();
                }
                output.operatorImages[(TRACK_INDEX)i] = image;
                currentLength += (10+imageSize);
            }
        }
        else if(output.function == BACKEND_FUNCTION::NON_ROUND_SHAPE_INSPECT_DONE)
        {
            QByteArray widthBytes = scopedSocket.data()->read(4);
            int width = qFromLittleEndian<qint32>(widthBytes);
            QByteArray heightBytes = scopedSocket.data()->read(4);
            int height = qFromLittleEndian<qint32>(heightBytes);
            QByteArray channelBytes = scopedSocket.data()->read(2);
            int channel = qFromLittleEndian<qint16>(channelBytes);
            int imageSize = width*height*channel;
            QImage image = QImage(0, 0, QImage::Format_Grayscale8);
            if(imageSize != 0)
            {
                QByteArray imageBytes = scopedSocket.data()->read(imageSize);
                if(channel == 3)
                {
                    image = QImage((const uchar*)imageBytes.data(), width, height, QImage::Format_BGR888);
                }
                else
                {
                    image = QImage((const uchar*)imageBytes.data(), width, height, QImage::Format_Grayscale8);
                }

                QPixmap pixmap = QPixmap::fromImage(image);
                image = pixmap.toImage();
            }
            output.operatorImages[TRACK_INDEX::CAMERA_1] = image;
            currentLength += (10+imageSize);
        }
        else if(output.function == BACKEND_FUNCTION::TOP_INSPECT_DONE ||
                   output.function == BACKEND_FUNCTION::CORRECTION_INSPECT_DONE)
        {
            QByteArray widthBytes = scopedSocket.data()->read(4);
            int width = qFromLittleEndian<qint32>(widthBytes);
            QByteArray heightBytes = scopedSocket.data()->read(4);
            int height = qFromLittleEndian<qint32>(heightBytes);
            QByteArray channelBytes = scopedSocket.data()->read(2);
            int channel = qFromLittleEndian<qint16>(channelBytes);
            int imageSize = width*height*channel;
            QImage image = QImage(0, 0, QImage::Format_Grayscale8);
            if(imageSize != 0)
            {
                QByteArray imageBytes = scopedSocket.data()->read(imageSize);
                if(channel == 3)
                {
                    image = QImage((const uchar*)imageBytes.data(), width, height, QImage::Format_BGR888);
                }
                else
                {
                    image = QImage((const uchar*)imageBytes.data(), width, height, QImage::Format_Grayscale8);
                }

                QPixmap pixmap = QPixmap::fromImage(image);
                image = pixmap.toImage();
            }
            output.operatorImages[TRACK_INDEX::CAMERA_2] = image;
            currentLength += (10+imageSize);
        }

        // read result string // прочитать строку результата
        int resultStrLength = sizeRequired - currentLength;
        std::string resultStr = "";
        if(resultStrLength > 0)
        {
            QByteArray resultStrBytes = scopedSocket.data()->read(resultStrLength);
            resultStr = resultStrBytes.toStdString();
            // qDebug() << "[Bacckend Client] Result String: " << QString::fromStdString(resultStr);
        }
        output.resultString = resultStr.c_str();
        emit receiveMessage_Signal(output);
        sizeRequired = -1;

    }
    catch(const std::exception& e)
    {
        qDebug() << "[Bacckend Client] Unknown_Command" ;
    }
}

void TCPBackendClient::ReadyRead_Slots()
{
    ReceiveMessage();
}

void TCPBackendClient::Disconnected_Slots()
{
    qDebug() << "[Bacckend Client] Disconnect";
}

void TCPBackendClient::Connected_Slots()
{
    qDebug() << "[Bacckend Client] Connect";
}

