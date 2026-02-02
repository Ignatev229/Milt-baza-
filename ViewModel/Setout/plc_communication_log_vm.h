#ifndef PLC_COMMUNICATION_LOG_VM_H
#define PLC_COMMUNICATION_LOG_VM_H

#include <QObject>
#include "../../ViewModel/Main/debug_log_vm.h"

class PLCCommunicationLogVM : public DebugLogVM
{
    Q_OBJECT
private:
    explicit PLCCommunicationLogVM(QObject *parent = nullptr);

public:
    virtual ~PLCCommunicationLogVM();


public:
    inline static PLCCommunicationLogVM* GetInstance() {
        if(m_pInstance.isNull())
            m_pInstance.reset(new PLCCommunicationLogVM());
        return m_pInstance.data();
    }

signals:


private:
    static QScopedPointer<PLCCommunicationLogVM> m_pInstance;


};

#endif // PLC_COMMUNICATION_LOG_VM_H
