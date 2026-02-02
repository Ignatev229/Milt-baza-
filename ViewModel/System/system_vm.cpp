#include "system_vm.h"

SystemVM::SystemVM(QObject *parent)
    : QObject{parent}
{
    setNumberOfBottles(0);
    setLastBottleTime(QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss"));
}

int SystemVM::numberOfBottles()
{
    return _numberOfBottles;
}

QString SystemVM::lastBottleTime()
{
    return _lastBottleTime;
}

void SystemVM::UpdateInspectInfo()
{
    setNumberOfBottles(_numberOfBottles+1);
    setLastBottleTime(QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss"));
}

void SystemVM::setNumberOfBottles(int value)
{
    if(_numberOfBottles != value){_numberOfBottles = value; emit numberOfBottlesChanged();}
}

void SystemVM::setLastBottleTime(QString value)
{
    if(_lastBottleTime != value){_lastBottleTime = value; emit lastBottleTimeChanged();}
}
