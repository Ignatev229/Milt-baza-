#ifndef RECIPE_MANAGEMENT_VM_H
#define RECIPE_MANAGEMENT_VM_H

#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "edit_recipe_vm.h"
#include "../Main/debug_log_vm.h"
#include "../list_string_vm.h"
#include "../Limit/limit_vm.h"


class RecipeManagementVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentRecipe READ currentRecipe WRITE setCurrentRecipe NOTIFY currentRecipeChanged FINAL)
    Q_PROPERTY(bool isEnableSelectRecipeSignal READ isEnableSelectRecipeSignal WRITE setIsEnableSelectRecipeSignal NOTIFY isEnableSelectRecipeSignalChanged FINAL)

public:
    explicit RecipeManagementVM(QObject *parent = nullptr);
    virtual ~RecipeManagementVM();

    inline static RecipeManagementVM* GetInstance() {

        if (m_pInstance.isNull())
            m_pInstance.reset(new RecipeManagementVM());

        return m_pInstance.data();
    }

    void Init(QQmlApplicationEngine &appEngine);
    void InitRecipe();
    void PopulateData();

    Q_INVOKABLE void doCloneRecipe(QString newRecipeFolderName, QString currentRecipeFolderName);
    Q_INVOKABLE void doLoadRecipe(QString recipeName, bool isShowDialog);
    Q_INVOKABLE void doDeleteRecipe(QString recipeName);


    //
    QString currentRecipe();
    bool isEnableSelectRecipeSignal();
    //

    ListStringVM listRecipeModel;

private:
    QString _currentRecipe;
    bool _isEnableSelectRecipeSignal;
    static QScopedPointer<RecipeManagementVM> m_pInstance;

    void UpdateSetoutRecipe();

signals:
    // Property //  Собственность
    void currentRecipeChanged();
    void isEnableSelectRecipeSignalChanged();
    // End property // Конечное свойство

    void loadRecipe_Signal();
    void addData(int index, QString recipeName, QString dateCreated, QString dateModify);


public slots:
    // Property //  Собственность
    void setCurrentRecipe(QString value);
    void setIsEnableSelectRecipeSignal(bool value);
    // End property // Конечное свойство
};

#endif // RECIPE_MANAGEMENT_VM_H
