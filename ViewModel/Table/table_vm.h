#ifndef TABLEVM_H
#define TABLEVM_H

#include <QObject>
#include <QDebug>
#include <QThread>

#include "../../Script/Modbus/MBcommunication.h"
#include "../../Script/Modbus/MBdefine.h"
#include "../../Script/Modbus/MBDLL.h"

class TableVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double tableElevationValue READ tableElevationValue WRITE setTableElevationValue NOTIFY tableElevationValueChanged FINAL)
    Q_PROPERTY(double tableAngleValue READ tableAngleValue WRITE setTableAngleValue NOTIFY tableAngleValueChanged FINAL)
    Q_PROPERTY(double loadPosition READ loadPosition WRITE setLoadPosition NOTIFY loadPositionChanged FINAL)
    Q_PROPERTY(double unloadPosition READ unloadPosition WRITE setUnloadPosition NOTIFY unloadPositionChanged FINAL)

public:
    explicit TableVM(QObject *parent = nullptr);
    ~TableVM();

    // property //  Собственность
    double tableElevationValue();
    double tableAngleValue();
    double loadPosition();
    double unloadPosition();

    // end // конец

private:
    // property //  Собственность
    double _tableElevationValue;
    double _tableAngleValue;
    double _loadPosition;
    double _unloadPosition;
    // end // конец

signals:
    // property //  Собственность
    void tableElevationValueChanged();
    void tableAngleValueChanged();
    void loadPositionChanged();
    void unloadPositionChanged();
    // end // конец


public slots:
    // property //  Собственность
    void setTableElevationValue(double);
    void setTableAngleValue(double);
    void setLoadPosition(double);
    void setUnloadPosition(double);
    // end // конец

    // qml slot // qml слот
    void tableElevationGo_Qml_Slot(QString value);
    void tableElevationHome_Qml_Slot();
    void tableAngleRotateLeft_Qml_Slot(QString value);
    void tableAngleRotateRight_Qml_Slot(QString value);
    void tableAngleHome_Qml_Slot();
    void testGotoLoad_Qml_Slot();
    void testGotoUnload_Qml_Slot();
    void saveAsLoad_Qml_Slot();
    void saveAsUnload_Qml_Slot();
};

#endif // TABLEVM_H
