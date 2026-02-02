#include "dialog_vm.h"
static DialogVM * p_instance = 0;

DialogVM::DialogVM(QObject *parent)
    : QObject{parent}
{

}

DialogVM * DialogVM::instance()
{
    if(!p_instance) p_instance = new DialogVM();
    return p_instance;
}

void DialogVM::ShowDialog(QString title, QString content, int iconIndex)
{
    
    setContent(content);
    setTitle(title);
    emit openMessageInfo_Signal(iconIndex);
}

QString DialogVM::title()
{
    return _title;
}

QString DialogVM::content()
{
    return _content;
}

void DialogVM::setTitle(QString value)
{
    if(_title != value){_title = value; emit titleChanged();}
}

void DialogVM::setContent(QString value)
{
    if(_content != value){_content = value; emit contentChanged();}
}
