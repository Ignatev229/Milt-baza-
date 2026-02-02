#include "limit_vm.h"
#include "QFile"
#include "QDir"
#include "Script/Define/struct_def.h"
#include "Script/Config/config_application.h"

QScopedPointer<LimitTabVM> LimitTabVM::m_pInstance;

LimitTabVM::LimitTabVM(QObject *parent)
    : QObject{parent}
{
    m_tableDataModel = new limit_table_model(this);

    LoadDataFromFile();
}


limit_table_model *LimitTabVM::tableDataModel() const
{
    return m_tableDataModel;
}

void LimitTabVM::setTableDataModel(limit_table_model *newTableDataModel)
{
    if (m_tableDataModel == newTableDataModel)
        return;
    m_tableDataModel = newTableDataModel;
    emit tableDataModelChanged();
}

void LimitTabVM::SaveDataToFile()
{
    // QString filePath = QDir::cleanPath(QString("%1/%2/%3").arg(ConfigApplication::instance()->m_strConfigRecipePath)
    //     .arg(ConfigApplication::instance()->m_strConfigRecipeName)
    //     .arg(LIMIT_FILE_NAME));

    // m_tableDataModel->saveDataToFile(filePath);

}

void LimitTabVM::LoadDataFromFile()
{

    //  QString filePath = QDir::cleanPath(QString("%1/%2/%3").arg(ConfigApplication::instance()->m_strConfigRecipePath)
    //      .arg(ConfigApplication::instance()->m_strConfigRecipeName)
    //      .arg(LIMIT_FILE_NAME));

    // if (QFile(filePath).exists())
    // {
    //     m_tableDataModel->loadDataFromFile(filePath);
    // }
    // else
    // {
    //     // if not exist will generate with default value // если не существует, то будет сгенерировано значение по умолчанию
    //     SaveDataToFile();
    // }
    
}

void LimitTabVM::saveDataTableSlot()
{
    SaveDataToFile();
    emit loadRecipe_Signal();
}
