#include "recipe_management_vm.h"
#include <QDir>
#include <QStringList>
#include <ViewModel/Dialog/dialog_vm.h>
#include "Script/Utility/AppUtility.h"
#include "../Setout/setout_vm.h"

QScopedPointer<RecipeManagementVM> RecipeManagementVM::m_pInstance;
RecipeManagementVM::RecipeManagementVM(QObject *parent)
    : QObject{parent}
{

}

RecipeManagementVM::~RecipeManagementVM()
{

}

void RecipeManagementVM::Init(QQmlApplicationEngine &appEngine)
{
    appEngine.rootContext()->setContextProperty(QStringLiteral("editRecipeVM"), EditRecipeVM::GetInstance());
    appEngine.rootContext()->setContextProperty(QStringLiteral("listRecipeModel"), &listRecipeModel);
    setCurrentRecipe(ConfigApplication::instance()->m_strConfigRecipeName);
}

void RecipeManagementVM::InitRecipe()
{
    setIsEnableSelectRecipeSignal(true);
    EditRecipeVM::GetInstance()->CreateDefaultValidationRecipe();
    EditRecipeVM::GetInstance()->LoadRecipe();
    LimitTabVM::GetInstance()->LoadDataFromFile();
    PopulateData();
    emit loadRecipe_Signal();
    // UpdateSetoutRecipe();
}

void RecipeManagementVM::PopulateData()
{
    // disable signal from cbb recipe in setout tab
    setIsEnableSelectRecipeSignal(false);
    // loop folder to get information // циклическая папка для получения информации
    auto folderPath = ConfigApplication::instance()->m_strConfigRecipePath;

    QDir dir(folderPath);

    // Set the filter to list directories only and not include '.' and '..' // Установите фильтр так, чтобы он отображал только  Директории и не включал "." и ".."
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    // Get the list of directories // Получить список  Директорий
    QStringList list = dir.entryList();

    // clear list recipe //  Очистить список рецептов
    listRecipeModel.removeCompletedItems();

    int count = 0;
    foreach(QString directory, list) {

        QFileInfo dirInfo(dir.filePath(directory));

        auto dateCreated = dirInfo.created().toString("yyyy-MM-dd HH:mm:ss");
        auto dateLastModified = dirInfo.lastModified().toString("yyyy-MM-dd HH:mm:ss");

        emit addData(count, directory, dateCreated, dateLastModified);

        listRecipeModel.AppendValue(directory);

        count++;
    }

    setIsEnableSelectRecipeSignal(true);

    // set current job for cbb in setout tab
    UpdateSetoutRecipe();
}

void RecipeManagementVM::doCloneRecipe(QString newRecipeFolderName, QString currentRecipeFolderName)
{
    auto folderPath = ConfigApplication::instance()->m_strConfigRecipePath;
    auto newFolderPath = QDir::cleanPath(folderPath + QDir::separator() + newRecipeFolderName);
    auto currentFolderPath = QDir::cleanPath(folderPath + QDir::separator() + currentRecipeFolderName);
    //check folder exist or not //проверьте, существует папка или нет
    if (QDir(newFolderPath).exists())
    {
        // 2 means icon warning in dialog icon // 2 означает значок предупреждения в диалоговом окне
        DialogVM::instance()->ShowDialog("", tr("Clone failed. Folder already existed"), 2);

        return;
    }

    // create folder // создать папку
    if (QDir().mkdir(newFolderPath) == false)
    {
        // 2 means icon warning in dialog icon // 2 означает значок предупреждения в диалоговом окне
        DialogVM::instance()->ShowDialog("", tr("Clone failed. Create folder failed"), 2);

        return;
    }
    
    // Start to copy data // Начать копировать данные
    if (copyFolderRecursively(currentFolderPath, newFolderPath) == false)
    {
        DialogVM::instance()->ShowDialog("", tr("Clone failed. Copy folder failed"), 2);
        return;
    }
    QFileInfo dirInfo(newFolderPath);
    DialogVM::instance()->ShowDialog("", tr("Clone Recipe Succeed"), 1);
    DebugLogVM::instance()->WriteDebugLog("RecipeManagementVM", "Recipe Management: Clone new recipe " + dirInfo.baseName());

    // reupdate data to ui // повторно обновить данные в пользовательском интерфейсе
    PopulateData();

    // // set current job for cbb in setout tab
    // UpdateSetoutRecipe();

}

void RecipeManagementVM::doLoadRecipe(QString recipeName, bool isShowDialog)
{
    if(recipeName == ConfigApplication::instance()->m_strConfigRecipeName)
    {
        // already load // уже загружен
        // 1 means icon info in dialog icon // 1 означает информацию о значке в диалоговом окне
        if(isShowDialog)
            DialogVM::instance()->ShowDialog(tr("Load Recipe"), tr("Recipe already loaded"), 1);
        return;
    }

    auto folderPath = ConfigApplication::instance()->m_strConfigRecipePath;
    auto recipeFolderPath = QDir::cleanPath(folderPath + QDir::separator() + recipeName);
    //check folder exist or not // проверьте, существует папка или нет
    if (!QDir(recipeFolderPath).exists())
    {
        // 2 means icon warning in dialog icon // 2 означает значок предупреждения в диалоговом окне
        DialogVM::instance()->ShowDialog(tr("Load Recipe"), tr("Recipe folder not existed"), 2);
        return;
    }

    ConfigApplication::instance()->m_strConfigRecipeName = recipeName;
    ConfigApplication::instance()->WriteAppSetting();
    EditRecipeVM::GetInstance()->LoadRecipe();
    setCurrentRecipe(ConfigApplication::instance()->m_strConfigRecipeName);
    LimitTabVM::GetInstance()->LoadDataFromFile();

    // set current job for cbb in setout tab
    UpdateSetoutRecipe();

    emit loadRecipe_Signal();
    if(isShowDialog)
    {
        DialogVM::instance()->ShowDialog(tr("Load Recipe"), tr("Load Recipe Succeed"), 1);
    }
    DebugLogVM::instance()->WriteDebugLog("RecipeManagementVM", "Recipe Management: Load recipe " + ConfigApplication::instance()->m_strConfigRecipeName);
}

void RecipeManagementVM::doDeleteRecipe(QString recipeName)
{
    auto folderPath = ConfigApplication::instance()->m_strConfigRecipePath;
    auto recipeFolderPath = QDir::cleanPath(folderPath + QDir::separator() + recipeName);
    QDir dir(recipeFolderPath);
    //check folder exist or not //проверьте, существует папка или нет
    if (!dir.exists())
    {
        // 2 means icon warning in dialog icon // 2 означает значок предупреждения в диалоговом окне
        DialogVM::instance()->ShowDialog(tr("Delete Recipe"), tr("Recipe folder not existed"), 2);
        return;
    }

    if(recipeName == ConfigApplication::instance()->m_strConfigRecipeName)
    {
        // 2 means icon warning in dialog icon // 2 означает значок предупреждения в диалоговом окне
        DialogVM::instance()->ShowDialog(tr("Delete Recipe"), tr("Can not delete current loaded recipe"), 2);
        return;
    }


    dir.removeRecursively();
    DialogVM::instance()->ShowDialog(tr("Delete Recipe"), tr("Delete Recipe Succeed"), 1);
    DebugLogVM::instance()->WriteDebugLog("RecipeManagementVM", "Recipe Management: Delete recipe " + recipeName);


    // reupdate data to ui // повторно обновить данные в пользовательском интерфейсе
    PopulateData();

    // // set current job for cbb in setout tab
    // UpdateSetoutRecipe();


}

QString RecipeManagementVM::currentRecipe()
{
    return _currentRecipe;
}

bool RecipeManagementVM::isEnableSelectRecipeSignal()
{
    return _isEnableSelectRecipeSignal;
}

void RecipeManagementVM::UpdateSetoutRecipe()
{
    // set current job for cbb in setout tab
    int currentJobIndex = listRecipeModel.getItemIndex(ConfigApplication::instance()->m_strConfigRecipeName);
    emit SetoutVM::GetInstance()->setCurrentJobName_Signal(currentJobIndex);
}

void RecipeManagementVM::setCurrentRecipe(QString value)
{
    if(_currentRecipe != value){_currentRecipe = value; emit currentRecipeChanged();}
}

void RecipeManagementVM::setIsEnableSelectRecipeSignal(bool value)
{
    if(_isEnableSelectRecipeSignal != value){_isEnableSelectRecipeSignal = value; emit isEnableSelectRecipeSignalChanged();}
}
