#ifndef TABCONTROLVM_H
#define TABCONTROLVM_H

#include <QObject>
#include <QDebug>
#include "../Script/Config/config_application.h"
#include "../Script/Define/struct_def.h"
class TabControlVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentStatus READ currentStatus WRITE setCurrentStatus NOTIFY currentStatusChanged FINAL)
    Q_PROPERTY(int currentTabIndex READ currentTabIndex WRITE setCurrentTabIndex NOTIFY currentTabIndexChanged)
    Q_PROPERTY(bool isEnableMainTab READ isEnableMainTab WRITE setIsEnableMainTab NOTIFY isEnableMainTabChanged)
    Q_PROPERTY(bool isEnableSettingTab READ isEnableSettingTab WRITE setIsEnableSettingTab NOTIFY isEnableSettingTabChanged)



public:
    explicit TabControlVM(QObject *parent = nullptr);


    void SetEnableTab(bool status);

    //property //Собственность
    int currentStatus();
    int currentTabIndex();
    bool isEnableMainTab();
    bool isEnableSettingTab();

    //end //конец

private:
    //property //Собственность
    int _currentStatus;
    int _currentTabIndex;
    bool _isEnableMainTab;
    bool _isEnableSettingTab;
    //end //конец


signals:
    //property //Собственность
    void currentStatusChanged();
    void isEnableMainTabChanged();
    void isEnableSettingTabChanged();
    void currentTabIndexChanged();
    //end //конец
    void tabIndexChanged_Signal(int);
    void appStatusBtnChanged_Signal(bool);

public slots:
    //property //Собственность
    void setCurrentStatus(int value);
    void setCurrentTabIndex(int value);
    void setIsEnableMainTab(bool);
    void setIsEnableSettingTab(bool);
    //end //конец

    void tabIndexChanged_Qml_Slots(int value);

};

#endif // TABCONTROLVM_H
