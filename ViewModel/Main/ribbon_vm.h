#ifndef RIBBONVM_H
#define RIBBONVM_H

#include <QObject>
#include <QDebug>
#include <QQueue>
#include <QObject>
#include <QFuture>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "../track_vm.h"
#include "../Dialog/dialog_vm.h"
// #include "../master_app.h"

class MainHomeVM;
class RibbonVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString oldLoadImagePath READ oldLoadImagePath WRITE setOldLoadImagePath NOTIFY oldLoadImagePathChanged)

public:
    explicit RibbonVM(QQmlApplicationEngine &appEngine, QHash<TRACK_INDEX, TrackVM*> hashTrackVM, QObject *parent = nullptr);

    QHash<TRACK_INDEX, TrackVM*> hashTrackVM;
    TRACK_INDEX currentTrackIndex;
    int currentDocIndex;
    QString oldLoadImagePath();

private:
    // Property //  Собственность
    QString _oldLoadImagePath;
    // End property // Конечное свойство
    MainHomeVM* m_pParentObject;
    bool isGlassContainerShapeInspect;
    bool isTopInspect;

    void CreateConnection();
    void InspectGlassContainerShapeFolder(QString path);
    void InspectTopFolder(QString path);

signals:
    // Property //  Собственность
    void oldLoadImagePathChanged();
    // End property // Конечное свойство

    void inspectFolderStatusChanged_Signal(bool);
    void inspectGlassContainerShapeStatusChanged_Signal(bool);
    void inspectTopStatusChanged_Signal(bool);
    void inspect_Signal(BACKEND_FUNCTION);

public slots:
    // Property //  Собственность
    void setOldLoadImagePath(QString value);
    // End property // Конечное свойство



    // QML Slot
    void loadImage_Qml_Slot(QString path);
    void snap_Qml_Slot();
    void stream_Qml_Slot(bool);
    void saveImage_Qml_Slot(QString path);

    void inspect_Qml_Slot();
    void inspectCycle_Qml_Slot(bool);
    void inspectFolder_Qml_Slot(bool, QString);
    void inspectGlassContainerShape_Qml_Slot(bool, QString);
    void inspectTop_Qml_Slot(bool, QString);


    //
    void inspectFolderStatusChanged_TrackVM_Slot(bool);

};

#endif // RIBBONVM_H
