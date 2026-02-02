#include "edit_recipe_vm.h"

QScopedPointer<EditRecipeVM> EditRecipeVM::m_pInstance;
EditRecipeVM::EditRecipeVM(QObject *parent)
    : QObject{parent}
{
    ResetDefaultParameter();
}

EditRecipeVM::~EditRecipeVM()
{

}

void EditRecipeVM::ResetDefaultParameter()
{
    bottleDiameter.ResetDefaulValues();
    heightInspect.ResetDefaulValues();
    weightInspect.ResetDefaulValues();
    noneRoundShapeInspect.ResetDefaulValues();
    bodyRInspect.ResetDefaulValues();
    leanInspect.ResetDefaulValues();
    // bentNeckInspect.ResetDefaulValues();
    tiltInspect.ResetDefaulValues();
    groupFinishDimensionInspect.ResetDefaulValues();
    flangeInspect.ResetDefaulValues();
    knockoutInspect.ResetDefaulValues();
    pushupBodyInspect.ResetDefaulValues();
    insideNeckInspect.ResetDefaulValues();
    wallThicknessInspect.ResetDefaulValues();
    numberCodeDecode.ResetDefaulValues();
}

void EditRecipeVM::LoadRecipe()
{
    // read vision param // считывание параметров зрения
    ReadVisionParam();
    //
}

void EditRecipeVM::UpdateVisionParamToUI()
{
    // update current vision paramter to UI // обновить текущий Зрения параметр в пользовательском интерфейсе
    QList<QList<QVariant>> data;
    data.append(bottleDiameter.getValues());
    data.append(heightInspect.getValues());
    data.append(weightInspect.getValues());
    data.append(noneRoundShapeInspect.getValues());
    data.append(bodyRInspect.getValues());
    data.append(leanInspect.getValues());
    // data.append(bentNeckInspect.getValues());
    data.append(tiltInspect.getValues());
    data.append(groupFinishDimensionInspect.getValues());
    data.append(flangeInspect.getValues());
    data.append(knockoutInspect.getValues());
    data.append(pushupBodyInspect.getValues());
    data.append(insideNeckInspect.getValues());
    data.append(wallThicknessInspect.getValues());
    data.append(numberCodeDecode.getValues());
    emit updateVisionParamToUI_Signal(data);
}

void EditRecipeVM::ReadVisionParam()
{
    // read vision parameter // считывание параметров  Зрения
    QString recipeFile = ConfigApplication::instance()->m_strConfigRecipePath + "/" +
                         ConfigApplication::instance()->m_strConfigRecipeName + "/" +
                         ConfigApplication::instance()->m_strVisionParamName;

    QFile file(recipeFile);
    if(!file.exists())
    {
        WriteVisionParam();
    }

    QString line;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        line = in.readAll();
        file.close();
    }
    if(line == "")
    {
        WriteVisionParam();
        return;
    }

    QStringList dataStr = line.split("\n");
    QHash<QString, QVariant> hashValues;
    QString groupName = "";
    QString variableName = "";
    for (int i = 0; i < dataStr.length(); ++i)
    {
        if(dataStr[i] == "")
            continue;
        if(dataStr[i].contains('[')) // group name
        {
            groupName = dataStr[i].replace('[', "").replace(']', "");
        }
        if(dataStr[i].contains('=')) // variable value
        {
            hashValues[groupName + " :: " + dataStr[i].split('=')[0]] = dataStr[i].split('=')[1];
        }
    }
    QString key;
    ResetDefaultParameter();

    bottleDiameter.ReadParam(hashValues);
    heightInspect.ReadParam(hashValues);
    weightInspect.ReadParam(hashValues);
    noneRoundShapeInspect.ReadParam(hashValues);
    bodyRInspect.ReadParam(hashValues);
    leanInspect.ReadParam(hashValues);
    // bentNeckInspect.ReadParam(hashValues);
    tiltInspect.ReadParam(hashValues);
    groupFinishDimensionInspect.ReadParam(hashValues);
    flangeInspect.ReadParam(hashValues);
    knockoutInspect.ReadParam(hashValues);
    pushupBodyInspect.ReadParam(hashValues);
    insideNeckInspect.ReadParam(hashValues);
    wallThicknessInspect.ReadParam(hashValues);
    numberCodeDecode.ReadParam(hashValues);
    // seamInspect.ReadParam(hashValues);

    // calculate liftingMechanismPos again // снова рассчитайте параметры подъемного механизма
    CalculateLiftingMechanismPos();

    // update to UI // обновление пользовательского интерфейса
    UpdateVisionParamToUI();

    //
}

void EditRecipeVM::WriteVisionParam()
{
    // calculate liftingMechanismPos again // снова рассчитайте параметры подъемного механизма
    CalculateLiftingMechanismPos();

    // save vision paramter // сохранить параметры зрения
    QString recipeFile = ConfigApplication::instance()->m_strConfigRecipePath + "/" +
                        ConfigApplication::instance()->m_strConfigRecipeName + "/" +
                         ConfigApplication::instance()->m_strVisionParamName;

    QFile file(recipeFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QTextStream stream( &file );

        bottleDiameter.WriteParam(stream);
        heightInspect.WriteParam(stream);
        weightInspect.WriteParam(stream);
        noneRoundShapeInspect.WriteParam(stream);
        bodyRInspect.WriteParam(stream);
        leanInspect.WriteParam(stream);
        // bentNeckInspect.WriteParam(stream);
        tiltInspect.WriteParam(stream);
        groupFinishDimensionInspect.WriteParam(stream);
        flangeInspect.WriteParam(stream);
        knockoutInspect.WriteParam(stream);
        pushupBodyInspect.WriteParam(stream);
        insideNeckInspect.WriteParam(stream);
        wallThicknessInspect.WriteParam(stream);
        numberCodeDecode.WriteParam(stream);
    }
    file.close();

}

void EditRecipeVM::CreateDefaultValidationRecipe()
{
    QString recipeFolder = ConfigApplication::instance()->m_strConfigRecipePath + "/" +
                         ConfigApplication::instance()->m_strValidationRecipeName;
    QDir dir(recipeFolder);
    if(dir.exists())
    {
        return;
    }

    dir.mkpath(recipeFolder);

    // calculate liftingMechanismPos again // снова рассчитайте параметры подъемного механизма
    CalculateLiftingMechanismPos();

    // save vision paramter // сохранить параметры зрения
    QString recipeFile = recipeFolder + "/" +
                        ConfigApplication::instance()->m_strVisionParamName;

    QFile file(recipeFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QTextStream stream( &file );

        bottleDiameter.WriteParam(stream);
        heightInspect.WriteParam(stream);

        weightInspect.enable = false;
        weightInspect.WriteParam(stream);
        noneRoundShapeInspect.enable = false;
        noneRoundShapeInspect.WriteParam(stream);

        bodyRInspect.WriteParam(stream);

        leanInspect.enable = false;
        leanInspect.WriteParam(stream);
        // bentNeckInspect.enable = false;
        // bentNeckInspect.WriteParam(stream);
        tiltInspect.enable = false;
        tiltInspect.WriteParam(stream);
        groupFinishDimensionInspect.enable = false;
        groupFinishDimensionInspect.WriteParam(stream);
        flangeInspect.enable = false;
        flangeInspect.WriteParam(stream);
        knockoutInspect.enable = false;
        knockoutInspect.WriteParam(stream);
        pushupBodyInspect.enable = false;
        pushupBodyInspect.WriteParam(stream);
        insideNeckInspect.enable = false;
        insideNeckInspect.WriteParam(stream);
        wallThicknessInspect.enable = false;
        wallThicknessInspect.WriteParam(stream);
        numberCodeDecode.enable = false;
        numberCodeDecode.WriteParam(stream);
    }
    file.close();

    ResetDefaultParameter();

}

void EditRecipeVM::CalculateLiftingMechanismPos()
{
    // qDebug() << ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1] <<
    //     ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2] <<
    //     ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::TOP];

    for (int i = 0; i < INSPECT_SEQUENCE_CAMERA_POSITION::TOTAL_POS; ++i) {
        if(i == 1)
        {
            heightInspect.liftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION(i)] =
                ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION(i)];
            continue;
        }
        heightInspect.liftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION(i)] =
            ConfigApplication::instance()->m_strCalibCameraPosData.m_hashLiftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION(i)] +
            ConfigApplication::instance()->m_strCalibCameraPosData.toolHeight - heightInspect.height;
    }

    // 300 mm
    // heightInspect.liftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM1] = 804 - heightInspect.height; // bottom
    // heightInspect.liftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::BOTTOM2] = 620; // bottom
    // // heightInspect.liftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::MIDDLE] = 987 - heightInspect.height; // mid
    // // heightInspect.liftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::MIDDLE] = 1047.5 - heightInspect.height; // mid
    // heightInspect.liftingMechanismPos[INSPECT_SEQUENCE_CAMERA_POSITION::TOP] = 1054 - heightInspect.height; // top
}

void EditRecipeVM::saveVisionParam_Slot(QList<QList<QVariant>> data)
{
    // save all vision param to current UI // сохранить все параметры  Зрения в текущем пользовательском интерфейсе
    int index = 0;
    bottleDiameter.SetValues(data[index++]);
    heightInspect.SetValues(data[index++]);
    weightInspect.SetValues(data[index++]);
    noneRoundShapeInspect.SetValues(data[index++]);
    bodyRInspect.SetValues(data[index++]);
    leanInspect.SetValues(data[index++]);
    // bentNeckInspect.SetValues(data[index++]);
    tiltInspect.SetValues(data[index++]);
    groupFinishDimensionInspect.SetValues(data[index++]);
    flangeInspect.SetValues(data[index++]);
    knockoutInspect.SetValues(data[index++]);
    pushupBodyInspect.SetValues(data[index++]);
    insideNeckInspect.SetValues(data[index++]);
    wallThicknessInspect.SetValues(data[index++]);
    numberCodeDecode.SetValues(data[index++]);

    WriteVisionParam();

    emit editRecipe_Signal();
}














