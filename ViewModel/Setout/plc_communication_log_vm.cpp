#include "plc_communication_log_vm.h"

QScopedPointer<PLCCommunicationLogVM> PLCCommunicationLogVM::m_pInstance;

PLCCommunicationLogVM::PLCCommunicationLogVM(QObject *parent)
    : DebugLogVM{parent}
{

}

PLCCommunicationLogVM::~PLCCommunicationLogVM()
{
    // this->deleteLater();
}


