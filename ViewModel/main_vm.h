#ifndef MAINVM_H
#define MAINVM_H

#include <QDebug>
#include <QMetaType>
#include <QObject>
#include <QString>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QTimer>

#include <QWindow>
#include <QWidget>
#include <QMdiSubWindow>
#ifdef Q_OS_WIN
    #include "Windows.h"
#endif

#include "master_app.h"
#include "image_writer.h"
#include "list_string_vm.h"
#include "../Model/list_string_model.h"
#include "Script/Modbus/MBItem.h"
#include <array>
#include "Script/Define/struct_def.h"

class MBDiagnosticItems;

class MainVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString homePath READ homePath WRITE setHomePath NOTIFY homePathChanged FINAL)

public:
    MainVM();
    ~MainVM();
    void Init(QQmlApplicationEngine &appEngine, QApplication* appMain);
    MasterApp *masterApp;

    //property //собственность
    QString homePath();
    //end //конец

    // Data of modbus
    QScopedPointer<MBDiagnosticItems> m_modbusDiagnosticDataContext;


    QTranslator m_translator;
    QApplication* m_pMainApp;
    QQmlApplicationEngine* m_pMainQMLEngine;

    bool m_bIsAppClosing;
private:
    //property //собственность
    QString _homePath;
    //end //конец

public slots:

signals:
    void propagateChangeLanguageSignal();
    //property //собственность
    void homePathChanged();
    //end //конец
public slots:
    //property //собственность
    void setHomePath(QString value);
    //end //конец
    void appClose();

    void allComponentLoaded();
    void switchLanguage(int languageSelected);
};

extern MainVM theMainVM;

#endif // MAINVM_H
