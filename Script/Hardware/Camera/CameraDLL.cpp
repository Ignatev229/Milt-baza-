#include "CameraDLL.h"
#include <QLibrary>
#include <QDebug>

bool CameraDLLControl::m_isInit = false;

CCOpenDeviceFunc                CameraDLLControl::m_pCCOpenDeviceFunc               = nullptr;
CCCloseDeviceFunc               CameraDLLControl::m_pCCCloseDeviceFunc              = nullptr;
CCCreateDeviceFunc              CameraDLLControl::m_pCCCreateDeviceFunc             = nullptr;
CCDestroyDeviceFunc             CameraDLLControl::m_pCCDestroyDeviceFunc            = nullptr;
CCExecuteSoftwareTriggerFunc    CameraDLLControl::m_pCCExecuteSoftwareTriggerFunc   = nullptr;
CCSetTriggerModeFunc            CameraDLLControl::m_pCCSetTriggerModeFunc           = nullptr;
CCGetTriggerModeFunc            CameraDLLControl::m_pCCGetTriggerModeFunc           = nullptr;
CCSetTriggerSouceFunc           CameraDLLControl::m_pCCSetTriggerSouceFunc          = nullptr;
CCGetTriggerSouceFunc           CameraDLLControl::m_pCCGetTriggerSouceFunc          = nullptr;
CCSetExposeFunc                 CameraDLLControl::m_pCCSetExposeFunc                = nullptr;
CCGetExposeFunc                 CameraDLLControl::m_pCCGetExposeFunc                = nullptr;
CCSetGainFunc                   CameraDLLControl::m_pCCSetGainFunc                  = nullptr;
CCGetGainFunc                   CameraDLLControl::m_pCCGetGainFunc                  = nullptr;
CCIsDeviceOpenedFunc            CameraDLLControl::m_pCCIsDeviceOpenedFunc           = nullptr;
CCSetDeviceWidthHeightFunc      CameraDLLControl::m_pCCSetDeviceWidthHeightFunc     = nullptr;
CCGetDeviceWidthHeightFunc      CameraDLLControl::m_pCCGetDeviceWidthHeightFunc     = nullptr;
CCGetDeviceBufferFunc           CameraDLLControl::m_pCCGetDeviceBufferFunc          = nullptr;
CCStartGrabbingFunc             CameraDLLControl::m_pCCStartGrabbingFunc            = nullptr;
CCStopGrabbingFunc              CameraDLLControl::m_pCCStopGrabbingFunc             = nullptr;
CCSaveImageFunc                 CameraDLLControl::m_pCCSaveImageFunc                = nullptr;

bool CameraDLLControl::RegisterDLL(const char* dllName)
{
    // init dll one time only // инициализировать dll только один раз
    if(m_isInit) return false;

    QLibrary library(dllName);
    if (!library.load()) {

        qDebug() << "Can not load library";
        return false;
    }

    m_pCCOpenDeviceFunc = reinterpret_cast<CCOpenDeviceFunc>(library.resolve("CCOpenDevice"));

    if(m_pCCOpenDeviceFunc == nullptr){
        qDebug() << "Can not load library function CCOpenDevice";
        return false;
    }

    m_pCCCloseDeviceFunc = reinterpret_cast<CCCloseDeviceFunc>(library.resolve("CCCloseDevice"));

    if(m_pCCCloseDeviceFunc == nullptr){
        qDebug() << "Can not load library function CCloseDevice";
        return false;
    }

    m_pCCCreateDeviceFunc = reinterpret_cast<CCCreateDeviceFunc>(library.resolve("CCCreateDevice"));

    if(m_pCCCreateDeviceFunc == nullptr){
        qDebug() << "Can not load library function CCreateDevice";
        return false;
    }


    m_pCCDestroyDeviceFunc = reinterpret_cast<CCDestroyDeviceFunc>(library.resolve("CCDestroyDevice"));

    if(m_pCCDestroyDeviceFunc == nullptr){
        qDebug() << "Can not load library function CCDestroyDevice";
        return false;
    }

    m_pCCExecuteSoftwareTriggerFunc = reinterpret_cast<CCExecuteSoftwareTriggerFunc>(library.resolve("CCExecuteSoftwareTrigger"));

    if(m_pCCExecuteSoftwareTriggerFunc == nullptr){
        qDebug() << "Can not load library function CCExecuteSoftwareTrigger";
        return false;
    }

    m_pCCSetTriggerModeFunc = reinterpret_cast<CCSetTriggerModeFunc>(library.resolve("CCSetTriggerMode"));

    if(m_pCCSetTriggerModeFunc == nullptr){
        qDebug() << "Can not load library function CCSetTriggerMode";
        return false;
    }

    m_pCCGetTriggerModeFunc = reinterpret_cast<CCGetTriggerModeFunc>(library.resolve("CCGetTriggerMode"));

    if(m_pCCGetTriggerModeFunc == nullptr){
        qDebug() << "Can not load library function CCGetTriggerMode";
        return false;
    }

    m_pCCSetTriggerSouceFunc = reinterpret_cast<CCSetTriggerSouceFunc>(library.resolve("CCSetTriggerSouce"));

    if(m_pCCSetTriggerSouceFunc == nullptr){
        qDebug() << "Can not load library function CCSetTriggerSouce";
        return false;
    }

    m_pCCGetTriggerSouceFunc = reinterpret_cast<CCGetTriggerSouceFunc>(library.resolve("CCGetTriggerSouce"));

    if(m_pCCGetTriggerSouceFunc == nullptr){
        qDebug() << "Can not load library function CCGetTriggerSouce";
        return false;
    }

    m_pCCSetExposeFunc = reinterpret_cast<CCSetExposeFunc>(library.resolve("CCSetExpose"));

    if(m_pCCSetExposeFunc == nullptr){
        qDebug() << "Can not load library function CCSetExpose";
        return false;
    }

    m_pCCGetExposeFunc = reinterpret_cast<CCGetExposeFunc>(library.resolve("CCGetExpose"));

    if(m_pCCGetExposeFunc == nullptr){
        qDebug() << "Can not load library function CCGetExpose";
        return false;
    }

    m_pCCSetGainFunc = reinterpret_cast<CCSetGainFunc>(library.resolve("CCSetGain"));

    if(m_pCCSetGainFunc == nullptr){
        qDebug() << "Can not load library function CCSetGain";
        return false;
    }

    m_pCCGetGainFunc = reinterpret_cast<CCGetGainFunc>(library.resolve("CCGetGain"));

    if(m_pCCGetGainFunc == nullptr){
        qDebug() << "Can not load library function CCGetGain";
        return false;
    }

    m_pCCIsDeviceOpenedFunc = reinterpret_cast<CCIsDeviceOpenedFunc>(library.resolve("CCIsDeviceOpened"));

    if(m_pCCIsDeviceOpenedFunc == nullptr){
        qDebug() << "Can not load library function CCIsDeviceOpened";
        return false;
    }

    m_pCCSetDeviceWidthHeightFunc = reinterpret_cast<CCSetDeviceWidthHeightFunc>(library.resolve("CCSetDeviceWidthHeight"));

    if(m_pCCSetDeviceWidthHeightFunc == nullptr){
        qDebug() << "Can not load library function CCSetDeviceWidthHeight";
        return false;
    }

    m_pCCGetDeviceWidthHeightFunc = reinterpret_cast<CCGetDeviceWidthHeightFunc>(library.resolve("CCGetDeviceWidthHeight"));

    if(m_pCCGetDeviceWidthHeightFunc == nullptr){
        qDebug() << "Can not load library function CCGetDeviceWidthHeight";
        return false;
    }


    m_pCCGetDeviceBufferFunc = reinterpret_cast<CCGetDeviceBufferFunc>(library.resolve("CCGetDeviceBuffer"));

    if(m_pCCGetDeviceBufferFunc == nullptr){
        qDebug() << "Can not load library function CCGetDeviceBuffer";
        return false;
    }

    m_pCCStartGrabbingFunc = reinterpret_cast<CCStartGrabbingFunc>(library.resolve("CCStartGrabbing"));

    if(m_pCCStartGrabbingFunc == nullptr){
        qDebug() << "Can not load library function CCStartGrabbing";
        return false;
    }

    m_pCCStopGrabbingFunc = reinterpret_cast<CCStopGrabbingFunc>(library.resolve("CCStopGrabbing"));

    if(m_pCCStopGrabbingFunc == nullptr){
        qDebug() << "Can not load library function CCStopGrabbing";
        return false;
    }

    m_pCCSaveImageFunc = reinterpret_cast<CCSaveImageFunc>(library.resolve("CCSaveImage"));

    if(m_pCCSaveImageFunc == nullptr){
        qDebug() << "Can not load library function CCSaveImage";
        return false;
    }

    qDebug() << "Load camera dll success";

    m_isInit = true;
    return true;
}
