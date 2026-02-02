#ifndef MASTERAPP_H
#define MASTERAPP_H

#include <QObject>
#include "track_vm.h"
#include "../Script/Config/config_application.h"
#include "../Script/Define/struct_def.h"
#include "Dialog/dialog_vm.h"
#include "tab_control_vm.h"
#include "login_vm.h"
#include "Main/main_home_vm.h"
#include "Core/inspectioncore.h"
#include "Review/review_vm.h"
#include "SystemSettings/system_setting_vm.h"
#include "FeederAndPushers/feeder_and_pushers_vm.h"
#include "Table/table_vm.h"
#include "RecipeManagement/recipe_management_vm.h"
#include "Calibration/calib_table_vm.h"
#include "Setout/setout_vm.h"
#include "System/system_vm.h"
#include "Validation/validation_vm.h"
#include "Report/report_vm.h"
#include "ViewModel/ContainerTab/ContainerVM.h"
#include "ViewModel/Setout/plc_communication_log_vm.h"
#include "ViewModel/History/history_vm.h"
#include "Correction/correction_vm.h"
#include "Script/SaveImage/save_image_thread.h"
#include <array>
#include "ViewModel/Limit/limit_vm.h"
#include "../Script/Sql/sql_management.h"

class AppCommandThread;

class MasterApp : public QObject
{
    Q_OBJECT
public:
    explicit MasterApp(QQmlApplicationEngine &appEngine, QObject *parent = nullptr);
    ~MasterApp();

public:
    void ExecuteCommandThread(int command);
    AppCommandThread* m_pCommandThread;
public:
    QHash<TRACK_INDEX, TrackVM*> hashTrackVM;
    QScopedPointer<TabControlVM> scopedTabControlVM;
    QScopedPointer<LoginVM> scopedLoginVM;
    QScopedPointer<MainHomeVM> scopedMainHomeVM;
    QScopedPointer<ReviewVM> scopedReviewVM;
    QScopedPointer<SystemSettingVM> scopedSystemSettingVM;
    QScopedPointer<FeederAndPushersVM> scopedFeederAndPushersVM;
    QScopedPointer<TableVM> scopedTableVM;
    // QScopedPointer<SetoutVM> scopedSetoutVM;
    QScopedPointer<SystemVM> scopedSystemVM;
    // QScopedPointer<ValidationVM> scopedValidationVM;
    // QScopedPointer<ReportVM> scopedReportVM;
    QScopedPointer<InspectionCore> scopedInspectionCore;
    // QScopedPointer<RecipeManagementVM> scopedRecipeManagementVM;
    // QScopedPointer<CalibTableVM> scopedCalibTableVM;
    QScopedPointer<ContainerVM> scopedContainerVM;
    QScopedPointer<SaveImageThread> scopedSaveImageThread;

    // QScopedPointer<LimitTabVM> scopedLimitTabVM;

    // INSPECTION SEQUENCE // ПОСЛЕДОВАТЕЛЬНОСТЬ ПРОВЕРКИ
    void InspectionSequence();
    InspectionSequenceData m_strcInspectionSequenceData;
    SetoutMoldsData m_strcSetoutMoldsData;
    double GetTablePositionNeedToMove(INSPECT_SEQUENCE_CAMERA_POSITION pos);
    TRACK_INDEX GetTablePositionCamera(INSPECT_SEQUENCE_CAMERA_POSITION pos);


    // VALIDATION SEQUENCE
    void DoValidation();

private:
    void InitApp();
    void CreateConnection();

    QScopedPointer<QProcess> scopedBackendProcess;

    // get first //  Получить  Сначала
    const int lookup[16] = {
        -1, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
    };
    int GetFirstSetBitPosition(uint16_t num);

    void CalibrationHandler();
    void CalibrationInitData();
    std::array<CalibratioStepInfor, TOTAL_CALIBRATION_STEP> m_arrayCalibrationStepInfor;
    int m_nCurrentStepCalibration;
    int m_nCurrentInspectState;

    // Once the bottle is transferred to the infeed sensor, the data exchange procedure begins. // Как только бутылка будет  Перемещена к датчику подачи, начнется процедура обмена данными.
    void BottleTransferredInfeedSensorHandler();
    int m_nCurrentBottleTransferredInfeedSensorState;

    // INSPECTION SEQUENCE // ПОСЛЕДОВАТЕЛЬНОСТЬ ПРОВЕРКИ
    void ResetInspectionSequenceEN();



signals:

    // qml
    void machineStatusChanged(int index);

    void sendAppCommandSignal(int command, int imageIndex);

private slots:
    // tab control // управление вкладками
    void tabIndexChanged_TabControlVM_Slots(int);

    // login // войти в систему
    void login_LoginVM_Slots(bool);



    // setting // настройка
    void registerNewCamera_SettingVM_Slots(TRACK_INDEX);
    void dlModelPathChanged_SettingVM_Slots(TRACK_INDEX);

    // inspection core //  Проверочный сердечник
    void inspectFinish_InspectionCore_Slots(OutputBackendInfo&);
    void modelLoaded_InspectionCore_Slots(QStringList&);
    void recipeLoaded_InspectionCore_Slots(bool);


    void StartToChangeLanguage();

public slots:
    // slot to receive signal from data aggregation to ItemList // слот для приема сигнала от агрегации данных в список элементов
    void StartToUpdateMTData();

    // manage recipe // управление рецептом
    void loadRecipe_RecipeManagementVM_Slots();
    void editRecipe_EditRecipeVM_Slots();

    void openDocumentFile_Qml_Slots(QString name);

};

#endif // MASTERAPP_H
