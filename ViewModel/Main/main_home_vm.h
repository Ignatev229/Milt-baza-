#ifndef MAINHOMEVM_H
#define MAINHOMEVM_H

#include <QQueue>
#include <QObject>
#include <QFuture>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QtConcurrent>

#include "../../Script/Define/struct_def.h"
//#include "../camera_vm.h"
#include "../track_vm.h"
#include "ribbon_vm.h"
#include "debug_log_vm.h"
#include "statistics_vm.h"
#include "../../Model/debug_log_model.h"
#include "../../Model/statistics_model.h"

class MasterApp;
class MainHomeVM : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<TrackVM*> listTrackVM READ listTrackVM WRITE setListTrackVM NOTIFY listTrackVMChanged)
    Q_PROPERTY(QList<int> numHorizontalCell READ numHorizontalCell WRITE setNumHorizontalCell NOTIFY numHorizontalCellChanged)
    Q_PROPERTY(QList<int> numVerticalCell READ numVerticalCell WRITE setNumVerticalCell NOTIFY numVerticalCellChanged)
    Q_PROPERTY(QList<double> resolutions READ resolutions WRITE setResolutions NOTIFY resolutionsChanged FINAL)



public:
    MainHomeVM(QQmlApplicationEngine &appEngine, QHash<TRACK_INDEX, TrackVM*> hashTrackVM, QObject *parent = nullptr);
    ~MainHomeVM();
    QScopedPointer<StatisticsVM> scopedStatisticsVM;
    QScopedPointer<RibbonVM> scopedRibbonVM;
    QHash<TRACK_INDEX, TrackVM*> hashTrackVM;
    TRACK_INDEX currentTrackIndex;
    int currentDocIndex;
    // Inspect // Проверить

    // Property //  Собственность
    QList<int> numHorizontalCell();
    QList<int> numVerticalCell();
    QList<TrackVM*> listTrackVM();
    QList<double> resolutions();
    // End property // Конечное свойство
    Q_INVOKABLE QObject* trackListAt(int index) const;

    void SetCurrentTrackDoc(TRACK_INDEX camID, int docID);
    void SetDocName(TRACK_INDEX camID, int docID, QString name);
    void UpdateDisconnectImage(TRACK_INDEX camID);
    void StreamAllCam(bool isStream);
    void SetDLModelVersion();
    void StartToChangeLanguage();
    void AddDefectInfos(QList<DefectInfoItem> defectInfos);
    void UpdateResolutionToUI();
    void Snap(TRACK_INDEX trackIndex);
    void InspectCycle(bool value);


private:
    // Property //  Собственность
    QList<TrackVM*> _listTrackVM;
    QList<int> _numHorizontalCell;
    QList<int> _numVerticalCell;
    QList<double> _resolutions;
    // End property // Конечное свойство

    void CreateConnection();
    MasterApp* m_pParentObject;
    QScopedPointer<QTimer> inspectCycleTimer;

signals:
    // Property //  Собственность
    void listTrackVMChanged();
    void numHorizontalCellChanged();
    void numVerticalCellChanged();
    void resolutionsChanged();
    // End property // Конечное свойство

    void finishSnapAllCam_Signal();
    void inspect_Signal(InputBackendInfo&);


    // qml
    void startToChangeLanguage_Signal();
    void addDataToDefectInforSignal(int trackIndex, QString strHeader, QString strDescription, QString strPixelValue, QString strmmValue);
    void clearDataToDefectInforSignal();

public slots:
    // Property //  Собственность
    void setListTrackVM(QList<TrackVM*> &value);
    void setNumHorizontalCell(QList<int> value);
    void setNumVerticalCell(QList<int> value);
    void setResolutions(QList<double> value);
    // End property // Конечное свойство
    void Inspect(BACKEND_FUNCTION function);


    void updateImage_CameraInterface_Slot(TRACK_INDEX, QImage, bool, QString);
    void cameraConnectedStatusChanged_CameraInterface_Slots(TRACK_INDEX, bool);
    void currentTrackChanged_Qml_Slot(TRACK_INDEX);

    //
    void inspectCyleTimeout();

};

#endif // MAINHOMEVM_H
