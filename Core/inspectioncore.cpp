#include "inspectioncore.h"

InspectionCore::InspectionCore(QObject *parent)
    : QThread{parent}
{
    isRun = true;
    // create tcp backend // создать Бэкенд tcp
    scopedTCPBackendClient.reset(new TCPBackendClient);
    defaultResultFlags = "None";

    inputBackendQueues = QQueue<InputBackendInfo>();
    isReadyCamInspectProcess = true;
    ResetOutputBackendInfo();

    connect(this, SIGNAL(sendInputInspect_Signal(InputBackendInfo&)), this, SLOT(sendInputInspect_Slot(InputBackendInfo&)));
    connect(scopedTCPBackendClient.data(), SIGNAL(receiveMessage_Signal(OutputBackendInfo&)), this, SLOT(receiveInspResult_TCPBackendClient_Slot(OutputBackendInfo&)));
}

InspectionCore::~InspectionCore()
{
    scopedTCPBackendClient.data()->Disconnect();
    scopedTCPBackendClient.data()->deleteLater();
    isRun = false;
    Resume();
    this->quit();
    this->wait();
}

void InspectionCore::run()
{
    while(isRun)
    {
        if(isTotalEmptyQueue())
        {
            Pause();
            sync.lock();
            if(pause)
                pauseCond.wait(&sync);
            sync.unlock();
        }
        QThread::msleep(10);
        if(inputBackendQueues.isEmpty() || !isReadyCamInspectProcess)
            continue;
        currentInputBackend = inputBackendQueues.dequeue();
        isReadyCamInspectProcess = false;
        processedTimes.start();
        emit sendInputInspect_Signal(currentInputBackend);
    }
}

void InspectionCore::Resume()
{
    sync.lock();
    pause = false;
    sync.unlock();
    pauseCond.wakeAll();
}

void InspectionCore::Pause()
{
    sync.lock();
    pause = true;
    sync.unlock();
}

bool InspectionCore::isTotalEmptyQueue()
{
    if(!inputBackendQueues.isEmpty())
        return false;
    return true;
}

void InspectionCore::ResetOutputBackendInfo()
{
    outputBackendInfo.function = BACKEND_FUNCTION::INSPECT_DONE;
    outputBackendInfo.defectInfos.clear();
    outputBackendInfo.defectCodes.clear();
    for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
    {
        outputBackendInfo.images[(TRACK_INDEX)i] = QImage();
        outputBackendInfo.operatorImages[(TRACK_INDEX)i] = QImage();
        outputBackendInfo.operatorImagePaths[(TRACK_INDEX)i] = "";
    }
    outputBackendInfo.moldResult = MOLD_RESULT::MOLD_PASS;
    outputBackendInfo.resultString = ConfigApplication::instance()->ConvertDefectCodeToString(BACKEND_RESULT::PASS);
    outputBackendInfo.processTime = 0;
}

void InspectionCore::RecipeChanged()
{
    scopedTCPBackendClient.data()->RecipeChanged();
}

void InspectionCore::receiveInspResult_TCPBackendClient_Slot(OutputBackendInfo &output)
{
    if(output.function == BACKEND_FUNCTION::INSPECT_DONE ||
        output.function == BACKEND_FUNCTION::VALIDATION_INSPECT_DONE)
    {
        ConfigApplication::instance()->WriteDebugLog("[Inspection Core]", "Receive inspect result");

        outputBackendInfo.function = output.function;
        for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i) {
            outputBackendInfo.images[(TRACK_INDEX)i] = currentInputBackend.images[(INSPECT_SEQUENCE_CAMERA_POSITION)(i+1)];
        }
        outputBackendInfo.operatorImages = output.operatorImages;
        outputBackendInfo.dateTime = QDateTime::currentDateTime();

        // process result string defect_infos$defect_code$mold_result // Обработать Результат Строки defect_infos$defect_code$mold_result
        QStringList data = output.resultString.split("&");
        if(data.count() == 3)
        {
            bool ok;
            // defect code // код дефекта
            QStringList subSplitData = data[0].split("$");
            for (int i = 0; i < subSplitData.count(); ++i)
            {
                QStringList subSplitData1 = subSplitData[i].split(";");
                if(subSplitData1.count() != 2)
                    continue;

                int value = subSplitData1[1].toInt(&ok);
                if(!ok)
                    continue;
                outputBackendInfo.defectCodes.append((BACKEND_RESULT)value);
            }


            // defect info // информация о дефекте
            subSplitData = data[1].split("$");
            for (int i = 0; i < subSplitData.count(); ++i)
            {
                QStringList subSplitData1 = subSplitData[i].split(";");
                if(subSplitData1.count() != 5)
                    continue;

                int value = subSplitData1[0].toInt(&ok);
                if(!ok)
                    continue;
                double dvalue = subSplitData1[3].toDouble(&ok);
                if(!ok)
                    continue;

                DefectInfoItem defectInfoItem;
                defectInfoItem.trackIndex = (TRACK_INDEX)value;
                defectInfoItem.defect = ConfigApplication::instance()->ConvertBEStringToDefectCode(subSplitData1[1]);
                defectInfoItem.parameter = subSplitData1[2];
                defectInfoItem.pixelValue = dvalue;
                defectInfoItem.mmValue = dvalue;
                defectInfoItem.isPass = subSplitData1[4] == "True";
                outputBackendInfo.defectInfos.append(defectInfoItem);
            }

            // mold result //  результат  формы
            int value = data[2].toInt(&ok);
            if(ok && value)
            {
                outputBackendInfo.moldResult = (MOLD_RESULT)value;
            }
        }

        // prepare folder for save image // Подготовительная папка для сохранения изображения
        QString ImageFolder = ConfigApplication::instance()->m_commonInfo.saving_image_info.save_dir + "/" +
                ConfigApplication::instance()->m_strInspectImageName + "/" +\
                outputBackendInfo.dateTime.toString("yyyy_MM_dd");
        if(!QDir(ImageFolder).exists())
        {
            QDir().mkdir(ImageFolder);
        }
        // prepare folder for save image // Подготовительная папка для сохранения изображения
        ImageFolder = ImageFolder.replace(ConfigApplication::instance()->m_strInspectImageName,
                                          ConfigApplication::instance()->m_strOperatorImageName);
        if(!QDir(ImageFolder).exists())
        {
            QDir().mkdir(ImageFolder);
        }
        outputBackendInfo.resultString = ConfigApplication::instance()->ConvertDefectCodeToString(BACKEND_RESULT::PASS);
        if(outputBackendInfo.defectCodes.count() > 0)
        {
            outputBackendInfo.resultString = ConfigApplication::instance()->ConvertDefectCodeToString(outputBackendInfo.defectCodes[0]);
        }
        else
        {
            outputBackendInfo.defectCodes.append(BACKEND_RESULT::PASS);
        }
        ImageFolder += ("/" + outputBackendInfo.resultString);
        if(!QDir(ImageFolder).exists())
        {
            QDir().mkdir(ImageFolder);
        }
        for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
        {
            outputBackendInfo.operatorImagePaths[(TRACK_INDEX)i] =
                QString("%1/%2%3.jpg")
                        .arg(ImageFolder)
                        .arg(outputBackendInfo.dateTime.toString("yyyyMMddhhmmsszzz"))
                        .arg(ConfigApplication::instance()->m_hashExtendImageName[(TRACK_INDEX)i]);
        }
        outputBackendInfo.processTime = processedTimes.elapsed();
        emit sendFinishInspect_Signal(outputBackendInfo);
    }

    else if(output.function == BACKEND_FUNCTION::CALIBRATION_INSPECT_DONE)
    {
        ConfigApplication::instance()->WriteDebugLog("[Inspection Core]", "Receive calibration camera position result");

        outputBackendInfo.function = output.function;
        for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i) {
            outputBackendInfo.images[(TRACK_INDEX)i] = currentInputBackend.images[(INSPECT_SEQUENCE_CAMERA_POSITION)(i+1)];
        }
        outputBackendInfo.operatorImages = output.operatorImages;
        outputBackendInfo.dateTime = QDateTime::currentDateTime();

        // process result string defect_infos$defect_code$mold_result // Обработать Результат Строки defect_infos$defect_code$mold_result
        QStringList data = output.resultString.split("&");
        if(data.count() == 3)
        {
            bool ok;
            // defect code // код дефекта
            QStringList subSplitData = data[0].split("$");
            for (int i = 0; i < subSplitData.count(); ++i)
            {
                QStringList subSplitData1 = subSplitData[i].split(";");
                if(subSplitData1.count() != 2)
                    continue;

                int value = subSplitData1[1].toInt(&ok);
                if(!ok)
                    continue;
                outputBackendInfo.defectCodes.append((BACKEND_RESULT)value);
            }


            // defect info // информация о дефекте
            subSplitData = data[1].split("$");

            if(subSplitData.count() == 5)
            {
                double dvalue = subSplitData[0].toDouble(&ok);
                if(ok)
                    ConfigApplication::instance()->m_commonInfo.appSetting.cameraConfig[TRACK_INDEX::CAMERA_1].resolution = dvalue;

                dvalue = subSplitData[1].toDouble(&ok);
                if(ok)
                    ConfigApplication::instance()->m_strCalibCameraPosData.m_hashHidedBottleHeight[TRACK_INDEX::CAMERA_1] = dvalue;

                //
                dvalue = subSplitData[2].toDouble(&ok);
                if(ok)
                    ConfigApplication::instance()->m_strCalibCameraPosData.maxBottleHeightInBottom = dvalue;

                //
                dvalue = subSplitData[3].toDouble(&ok);
                if(ok)
                    ConfigApplication::instance()->m_commonInfo.appSetting.cameraConfig[TRACK_INDEX::CAMERA_2].resolution = dvalue;

                dvalue = subSplitData[4].toDouble(&ok);
                if(ok)
                    ConfigApplication::instance()->m_strCalibCameraPosData.m_hashHidedBottleHeight[TRACK_INDEX::CAMERA_2] = dvalue;

            }
            else
            {
                outputBackendInfo.defectCodes.clear();
                outputBackendInfo.defectCodes.append(BACKEND_RESULT::PROCESS_ERROR);
            }

        }

        // prepare folder for save image // Подготовительная папка для сохранения изображения
        QString ImageFolder = ConfigApplication::instance()->m_commonInfo.saving_image_info.save_dir + "/" +
                              ConfigApplication::instance()->m_strInspectImageName + "/" +\
                                                                                          outputBackendInfo.dateTime.toString("yyyy_MM_dd");
        if(!QDir(ImageFolder).exists())
        {
            QDir().mkdir(ImageFolder);
        }
        // prepare folder for save image // Подготовительная папка для сохранения изображения
        ImageFolder = ImageFolder.replace(ConfigApplication::instance()->m_strInspectImageName,
                                          ConfigApplication::instance()->m_strOperatorImageName);
        if(!QDir(ImageFolder).exists())
        {
            QDir().mkdir(ImageFolder);
        }
        outputBackendInfo.resultString = ConfigApplication::instance()->ConvertDefectCodeToString(BACKEND_RESULT::PASS);
        if(outputBackendInfo.defectCodes.count() > 0)
        {
            outputBackendInfo.resultString = ConfigApplication::instance()->ConvertDefectCodeToString(outputBackendInfo.defectCodes[0]);
        }
        else
        {
            outputBackendInfo.defectCodes.append(BACKEND_RESULT::PASS);
        }
        ImageFolder += ("/" + outputBackendInfo.resultString);
        if(!QDir(ImageFolder).exists())
        {
            QDir().mkdir(ImageFolder);
        }
        for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
        {
            outputBackendInfo.operatorImagePaths[(TRACK_INDEX)i] =
                QString("%1/%2%3.jpg")
                    .arg(ImageFolder)
                    .arg(outputBackendInfo.dateTime.toString("yyyyMMddhhmmsszzz"))
                    .arg(ConfigApplication::instance()->m_hashExtendImageName[(TRACK_INDEX)i]);
        }
        outputBackendInfo.processTime = processedTimes.elapsed();
        emit sendFinishInspect_Signal(outputBackendInfo);
    }

    else if(output.function == BACKEND_FUNCTION::NON_ROUND_SHAPE_INSPECT_DONE)
    {
        ConfigApplication::instance()->WriteDebugLog("[Inspection Core]", "Receive inspect Bottom camera result");

        outputBackendInfo.function = output.function;
        // outputBackendInfo.images =  currentInputBackend.images; // выходной Бэкенд информации.изображения =  текущего ввода Бэкенд.изображения;
        outputBackendInfo.images[TRACK_INDEX::CAMERA_1] = currentInputBackend.images[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2];
        outputBackendInfo.operatorImages = output.operatorImages;

        // process result string defect_infos$defect_code // Обработка результирующей строки defect_infos$defect_code
        QStringList data = output.resultString.split("&");
        if(data.count() == 2)
        {
            bool ok;
            // defect code // код дефекта
            QStringList subSplitData = data[0].split("$");
            for (int i = 0; i < subSplitData.count(); ++i)
            {
                QStringList subSplitData1 = subSplitData[i].split(";");
                if(subSplitData1.count() != 2)
                    continue;

                int value = subSplitData1[1].toInt(&ok);
                if(!ok)
                    continue;
                outputBackendInfo.defectCodes.append((BACKEND_RESULT)value);
            }


            // defect info // информация о дефекте
            subSplitData = data[1].split("$");
            for (int i = 0; i < subSplitData.count(); ++i)
            {
                QStringList subSplitData1 = subSplitData[i].split(";");
                if(subSplitData1.count() != 5)
                    continue;

                int value = subSplitData1[0].toInt(&ok);
                if(!ok)
                    continue;
                double dvalue = subSplitData1[3].toDouble(&ok);
                if(!ok)
                    continue;

                DefectInfoItem defectInfoItem;
                defectInfoItem.trackIndex = (TRACK_INDEX)value;
                defectInfoItem.defect = ConfigApplication::instance()->ConvertBEStringToDefectCode(subSplitData1[1]);
                defectInfoItem.parameter = subSplitData1[2];
                defectInfoItem.pixelValue = dvalue;
                defectInfoItem.mmValue = dvalue;
                defectInfoItem.isPass = subSplitData1[4] == "True";
                outputBackendInfo.defectInfos.append(defectInfoItem);
            }
        }

        // // prepare folder for save image // // подготовьте папку для сохранения изображения
        // QString ImageFolder = ConfigApplication::instance()->m_commonInfo.saving_image_info.save_dir + "/" +
        //                       ConfigApplication::instance()->m_strInspectImageName + "/" +\
        //                                                                                   QDateTime::currentDateTime().toString("yyyy_MM_dd");
        // if(!QDir(ImageFolder).exists())
        // {
        //     QDir().mkdir(ImageFolder);
        // }
        // // prepare folder for save image // // подготовьте папку для сохранения изображения
        // ImageFolder = ImageFolder.replace(ConfigApplication::instance()->m_strInspectImageName,
        //                                   ConfigApplication::instance()->m_strOperatorImageName);
        // if(!QDir(ImageFolder).exists())
        // {
        //     QDir().mkdir(ImageFolder);
        // }
        outputBackendInfo.resultString = ConfigApplication::instance()->ConvertDefectCodeToString(BACKEND_RESULT::PASS);
        if(outputBackendInfo.defectCodes.count() > 0)
        {
            outputBackendInfo.resultString = ConfigApplication::instance()->ConvertDefectCodeToString(outputBackendInfo.defectCodes[0]);
        }
        else
        {
            outputBackendInfo.defectCodes.append(BACKEND_RESULT::PASS);
        }
        // ImageFolder += ("/" + outputBackendInfo.resultString); Папка изображений += ("/" + вывод Бэкенд-информации.строка результата);
        // if(!QDir(ImageFolder).exists())
        // {
        //     QDir().mkdir(ImageFolder);
        // }
        // for (int i = 0; i < ConfigApplication::instance()->m_nCamNum; ++i)
        // {
        //     outputBackendInfo.operatorImagePaths[(TRACK_INDEX)i] =
        //         QString("%1/%2%3.jpg")
        //             .arg(ImageFolder)
        //             .arg(QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz"))
        //             .arg(ConfigApplication::instance()->m_hashExtendImageName[(TRACK_INDEX)i]);
        // }
        outputBackendInfo.processTime = processedTimes.elapsed();
        emit sendFinishInspect_Signal(outputBackendInfo);
    }
    else if(output.function == BACKEND_FUNCTION::TOP_INSPECT_DONE ||
               output.function == BACKEND_FUNCTION::CORRECTION_INSPECT_DONE)
    {
        ConfigApplication::instance()->WriteDebugLog("[Inspection Core]", "Receive inspect Top camera result");

        outputBackendInfo.function = output.function;
        outputBackendInfo.images[TRACK_INDEX::CAMERA_2] = currentInputBackend.images[INSPECT_SEQUENCE_CAMERA_POSITION::TOP];
        outputBackendInfo.operatorImages = output.operatorImages;


        // process result string defect_infos$defect_code // обработать строку результата defect_infos$defect_code
        QStringList data = output.resultString.split("&");
        if(data.count() == 2)
        {
            bool ok;
            // defect code // код дефекта
            QStringList subSplitData = data[0].split("$");
            for (int i = 0; i < subSplitData.count(); ++i)
            {
                QStringList subSplitData1 = subSplitData[i].split(";");
                if(subSplitData1.count() != 2)
                    continue;

                int value = subSplitData1[1].toInt(&ok);
                if(!ok)
                    continue;
                outputBackendInfo.defectCodes.append((BACKEND_RESULT)value);
            }


            // defect info // информация о дефекте
            subSplitData = data[1].split("$");
            for (int i = 0; i < subSplitData.count(); ++i)
            {
                QStringList subSplitData1 = subSplitData[i].split(";");
                if(subSplitData1.count() != 5)
                    continue;

                int value = subSplitData1[0].toInt(&ok);
                if(!ok)
                    continue;
                double dvalue = subSplitData1[3].toDouble(&ok);
                if(!ok)
                    continue;

                DefectInfoItem defectInfoItem;
                defectInfoItem.trackIndex = (TRACK_INDEX)value;
                defectInfoItem.defect = ConfigApplication::instance()->ConvertBEStringToDefectCode(subSplitData1[1]);
                defectInfoItem.parameter = subSplitData1[2];
                defectInfoItem.pixelValue = dvalue;
                defectInfoItem.mmValue = dvalue;
                defectInfoItem.isPass = subSplitData1[4] == "True";
                outputBackendInfo.defectInfos.append(defectInfoItem);
            }
        }

        outputBackendInfo.resultString = ConfigApplication::instance()->ConvertDefectCodeToString(BACKEND_RESULT::PASS);
        if(outputBackendInfo.defectCodes.count() > 0)
        {
            outputBackendInfo.resultString = ConfigApplication::instance()->ConvertDefectCodeToString(outputBackendInfo.defectCodes[0]);
        }
        else
        {
            outputBackendInfo.defectCodes.append(BACKEND_RESULT::PASS);
        }
        outputBackendInfo.processTime = processedTimes.elapsed();
        emit sendFinishInspect_Signal(outputBackendInfo);
    }
    else if(output.function == BACKEND_FUNCTION::CHANGE_RECIPE_DONE)
    {
        // // process result string class1;class2;... // // обработать строку результата class1;class2;...
        // QStringList data = output.resultString.split(";"); // QStringList данные = output.resultString.split(";");
        emit sendRecipeLoaded_Signal(output.resultString == "True");
    }


    isReadyCamInspectProcess = true;
}

void InspectionCore::sendInputInspect_Slot(InputBackendInfo &inputBackendInfo)
{
    scopedTCPBackendClient.data()->Send(inputBackendInfo);
}

void InspectionCore::inspect_MainHomeVM_Slot(InputBackendInfo &input)
{
    if(!scopedTCPBackendClient.data()->isConnected)
        return;
    inputBackendQueues.enqueue(input);
    Resume();
}



















