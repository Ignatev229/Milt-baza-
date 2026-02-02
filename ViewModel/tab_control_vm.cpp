#include "tab_control_vm.h"

TabControlVM::TabControlVM(QObject *parent)
    : QObject{parent}
{
    SetEnableTab(false);

}

void TabControlVM::SetEnableTab(bool status)
{
    setIsEnableMainTab(status);
    setIsEnableSettingTab(ConfigApplication::instance()->m_strcCurrentAccountLevel == ACCOUNT_LEVEL::ADMINISTRATOR);
}

int TabControlVM::currentStatus()
{
    return _currentStatus;
}

int TabControlVM::currentTabIndex()
{
    return _currentTabIndex;
}

bool TabControlVM::isEnableMainTab()
{
    return _isEnableMainTab;
}

bool TabControlVM::isEnableSettingTab()
{
    return _isEnableSettingTab;
}

void TabControlVM::setCurrentStatus(int value)
{
    if(_currentStatus != value){_currentStatus = value; emit currentStatusChanged();}
}

void TabControlVM::setCurrentTabIndex(int value)
{
    if(_currentTabIndex != value){_currentTabIndex = value; emit currentTabIndexChanged();}
}

void TabControlVM::setIsEnableMainTab(bool value)
{
    if(_isEnableMainTab != value){_isEnableMainTab = value; emit isEnableMainTabChanged();}
}

void TabControlVM::setIsEnableSettingTab(bool value)
{
    if(_isEnableSettingTab != value){_isEnableSettingTab = value; emit isEnableSettingTabChanged();}
}

void TabControlVM::tabIndexChanged_Qml_Slots(int value)
{
    qDebug() << "[TabControlVM]" << "Tab index changed: " << value;
  
    // setting tab, need to update UI // вкладка настроек, необходимо обновить пользовательский интерфейс
    emit tabIndexChanged_Signal(value);
    
}
