#ifndef SETOUTVM_H
#define SETOUTVM_H

#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>


#include "../list_string_vm.h"
#include "plc_communication_log_vm.h"
#include "../../Script/Modbus/MBcommunication.h"
#include "../../Script/Modbus/MBdefine.h"
#include "../../Script/Modbus/MBDLL.h"
#include "../../ViewModel/RecipeManagement/recipe_management_vm.h"

class MasterApp;

class SetoutVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int highPressureStatus READ highPressureStatus WRITE setHighPressureStatus NOTIFY highPressureStatusChanged FINAL)
    Q_PROPERTY(int safetyRelayStatus READ safetyRelayStatus WRITE setSafetyRelayStatus NOTIFY safetyRelayStatusChanged FINAL)

public:
    explicit SetoutVM(QObject *parent = nullptr);
    ~SetoutVM();

    inline static SetoutVM* GetInstance() {

        if (m_pInstance.isNull())
            m_pInstance.reset(new SetoutVM());

        return m_pInstance.data();
    }

    // property //  Собственность
    int highPressureStatus();
    int safetyRelayStatus();
    // end // конец

    void Init(QQmlApplicationEngine &appEngine, QObject *parent = nullptr);
    void UpdateMoldUI(int column, int row, int header, int result);
    void InitSetoutMoldNumber();
    void UpdateMoldSerialNumberResult(MOLD_RESULT result, int moldIndex);

private:
    // property //  Собственность
    int _highPressureStatus;
    int _safetyRelayStatus;
    //end // конец

    MasterApp* m_pParentObject;
    static QScopedPointer<SetoutVM> m_pInstance;

signals:
    // property //  Собственность
    void highPressureStatusChanged();
    void safetyRelayStatusChanged();
    // end // конец
    void updateMoldListUI_Signal(int column, int row, int header, int result);
    void initSetoutMoldNumber_Signal(QList<QString>, QList<int>);
    void updateMoldNumberResult_Signal(int value, int moldIndex);
    void setCurrentJobName_Signal(int index);


public slots:

    // property //  Собственность
    void setHighPressureStatus(int value);
    void setSafetyRelayStatus(int value);
    // end // конец

    // qml slot // qml слот
    void runStopStatus_Qml_Slot(bool value, QString currentJobText);
    void clearAllContainers_Qml_Slot();
    void columnHeaderMoldChanged_Qml_Slot(int column, int value);
    void resetAlarm_Qml_Slot();
    void safetyRelayReset_Qml_Slot();
    void saveMoldNumbers(QList<QVariant>);
    void loadRecipe_Qml_Slot(QString currentJobText);


};

#endif // SETOUTVM_H
