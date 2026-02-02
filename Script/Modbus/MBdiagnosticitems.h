#ifndef MBDIAGNOSTICITEMS_H
#define MBDIAGNOSTICITEMS_H

#include "MBItem.h"

class MBDiagnosticItems : public MBItemList
{
    Q_OBJECT
public:
    enum class ITEM_STATUS
    {
        ITEM_OFF = 0,
        ITEM_ON,
        ITEM_ERROR
    };
    Q_ENUMS(ITEM_STATUS)
public:
    MBDiagnosticItems();
    virtual ~MBDiagnosticItems();
public slots:
    void StartToUpdateData();
};

#endif // MBDIAGNOSTICITEMS_H
