#ifndef CAMERADLL_H
#define CAMERADLL_H



#define CC_TRIGGER_MODE_OFF                   0
#define CC_TRIGGER_MODE_ON                    1

#define CC_TRIGGER_SOURCE_LINE0               0
#define CC_TRIGGER_SOURCE_LINE1               1
#define CC_TRIGGER_SOURCE_LINE2               2
#define CC_TRIGGER_SOURCE_LINE3               3
#define CC_TRIGGER_SOURCE_COUNTER0            4
#define CC_TRIGGER_SOURCE_SOFTWARE            7
#define CC_TRIGGER_SOURCE_FrequencyConverter  8


//--- DLL ---//
typedef int (*CCOpenDeviceFunc)(void* device, const char* serialNumber);
typedef int (*CCCloseDeviceFunc)(void* device);

typedef void* (*CCCreateDeviceFunc)();
typedef bool (*CCDestroyDeviceFunc)(void* device);

typedef bool (*CCExecuteSoftwareTriggerFunc)(void* device);

typedef int (*CCSetTriggerModeFunc)(void* device, int mode);
typedef int (*CCGetTriggerModeFunc)(void* device, int& mode);

typedef int (*CCSetTriggerSouceFunc)(void* device, int source);
typedef int (*CCGetTriggerSouceFunc)(void* device, int& source);

typedef int (*CCSetExposeFunc)(void* device, int expose);
typedef int (*CCGetExposeFunc)(void* device, int& expose);
typedef int (*CCSetGainFunc)(void* device, int gain);
typedef int (*CCGetGainFunc)(void* device, int& gain);

typedef bool (*CCIsDeviceOpenedFunc)(void* device);
typedef bool (*CCSetDeviceWidthHeightFunc)(void* device, int width, int height, int maxWidth, int maxHeight);
typedef bool (*CCGetDeviceWidthHeightFunc)(void* device, int& width, int& height, int& maxWidth, int& maxHeight);

typedef int (*CCGetDeviceBufferFunc)(void* device, unsigned char*& buffer,
                                     int& width, int& height, int& stride);

typedef int (*CCStartGrabbingFunc)(void *device);
typedef int (*CCStopGrabbingFunc)(void* device);

//Save image file with hardcode file name for testing //Сохраните файл изображения с именем файла с жестким  кодированием для тестирования
typedef int (*CCSaveImageFunc)(void *device);
////////


class CameraDLLControl
{
public:
    // need to call this one first // сначала нужно позвонить этому
    static bool RegisterDLL(const char* dlllName);

    static inline bool CheckFuncDeviceValid(void* fn) { return fn == nullptr ? false : true; }

    static inline int OpenDevice(void* device, const char* serialNumber)
    {
        // if (CheckFuncDeviceValid(m_pCCOpenDeviceFunc) == false) return -1;
      
        return m_pCCOpenDeviceFunc(device, serialNumber);
    }

    static inline int CloseDevice(void* device)
    {
        // if (CheckFuncDeviceValid(m_pCCCloseDeviceFunc) == false) return -1;
     
        return m_pCCCloseDeviceFunc(device);
    }

    static inline void* CreateDevice()
    {
        // if (CheckFuncDeviceValid(m_pCCCreateDeviceFunc) == false) return nullptr;

        return m_pCCCreateDeviceFunc();
    }

    static inline bool DestroyDevice(void* device)
    {
        // if (CheckFuncDeviceValid(m_pCCDestroyDeviceFunc) == false) return false;

        return m_pCCDestroyDeviceFunc(device);
    }

    static inline bool ExecuteSoftwareTrigger(void* device)
    {
        // if (CheckFuncDeviceValid(m_pCCExecuteSoftwareTriggerFunc) == false) return false;

        return m_pCCExecuteSoftwareTriggerFunc(device);
    }

    static inline int SetTriggerMode(void* device, int mode)
    {
        // if (CheckFuncDeviceValid(m_pCCSetTriggerModeFunc) == false) return -1;

        return m_pCCSetTriggerModeFunc(device, mode);
    }

    static inline int GetTriggerMode(void* device, int& mode)
    {
        // if (CheckFuncDeviceValid(m_pCCGetTriggerModeFunc) == false) return -1;

        return m_pCCGetTriggerModeFunc(device, mode);
    }

    static inline int SetTriggerSouce(void* device, int source)
    {
        // if (CheckFuncDeviceValid(m_pCCSetTriggerSouceFunc) == false) return -1;

        return m_pCCSetTriggerSouceFunc(device, source);
    }

    static inline int GetTriggerSource(void* device, int& source)
    {
        // if (CheckFuncDeviceValid(m_pCCGetTriggerSouceFunc) == false) return -1;

        return m_pCCGetTriggerSouceFunc(device, source);
    }

    static inline int SetExposure(void* device, int exposure)
    {
        // if (CheckFuncDeviceValid(m_pCCSetExposeFunc) == false) return -1;

        return m_pCCSetExposeFunc(device, exposure);
    }

    static inline int GetExposure(void* device, int& exposure)
    {
        // if (CheckFuncDeviceValid(m_pCCGetExposeFunc) == false) return -1;

        return m_pCCGetExposeFunc(device, exposure);
    }

    static inline int SetGain(void* device, int gain)
    {
        // if (CheckFuncDeviceValid(m_pCCSetGainFunc) == false) return -1;

        return m_pCCSetGainFunc(device, gain);
    }

    static inline int GetGain(void* device, int& gain)
    {
        // if (CheckFuncDeviceValid(m_pCCGetGainFunc) == false) return -1;

        return m_pCCGetGainFunc(device, gain);
    }

    static inline bool IsDeviceOpened(void* device)
    {
        // if (CheckFuncDeviceValid(m_pCCIsDeviceOpenedFunc) == false) return false;

        return m_pCCIsDeviceOpenedFunc(device);
    }

    static inline bool SetDeviceWidthHeight(void* device, int width, int height, int maxWidth, int maxHeight)
    {
        // if (CheckFuncDeviceValid(m_pCCSetDeviceWidthHeightFunc) == false) return false;

        return m_pCCSetDeviceWidthHeightFunc(device, width, height, maxWidth, maxHeight);
    }

    static inline bool GetDeviceWidthHeight(void* device, int& width, int& height, int& maxWidth, int& maxHeight)
    {
        // if (CheckFuncDeviceValid(m_pCCGetDeviceWidthHeightFunc) == false) return false;

        return m_pCCGetDeviceWidthHeightFunc(device, width, height, maxWidth, maxHeight);
    }

    static inline int GetDeviceBuffer(void* device, unsigned char*& buffer, int& width, int& height, int& stride)
    {
        // if (CheckFuncDeviceValid(m_pCCGetDeviceBufferFunc) == false) return -1;

        return m_pCCGetDeviceBufferFunc(device, buffer, width, height, stride);
    }


    static inline int StartGrabbing(void* device)
    {
        // if (CheckFuncDeviceValid(m_pCCStartGrabbingFunc) == false) return -1;

        return m_pCCStartGrabbingFunc(device);
    }


    static inline int StopGrabbing(void* device)
    {
        // if (CheckFuncDeviceValid(m_pCCStopGrabbingFunc) == false) return -1;

        return m_pCCStopGrabbingFunc(device);
    }


    static inline int SaveImage(void* device)
    {
        // if (CheckFuncDeviceValid(m_pCCSaveImageFunc) == false) return -1;

        return m_pCCSaveImageFunc(device);
    }

private:
    static bool m_isInit;


    // DLL function pointer // Указатель  Dll-функции
    static CCOpenDeviceFunc                m_pCCOpenDeviceFunc;
    static CCCloseDeviceFunc               m_pCCCloseDeviceFunc;
    static CCCreateDeviceFunc              m_pCCCreateDeviceFunc;
    static CCDestroyDeviceFunc             m_pCCDestroyDeviceFunc;
    static CCExecuteSoftwareTriggerFunc    m_pCCExecuteSoftwareTriggerFunc;
    static CCSetTriggerModeFunc            m_pCCSetTriggerModeFunc;
    static CCGetTriggerModeFunc            m_pCCGetTriggerModeFunc;
    static CCSetTriggerSouceFunc           m_pCCSetTriggerSouceFunc;
    static CCGetTriggerSouceFunc           m_pCCGetTriggerSouceFunc;
    static CCSetExposeFunc                 m_pCCSetExposeFunc;
    static CCGetExposeFunc                 m_pCCGetExposeFunc;
    static CCSetGainFunc                   m_pCCSetGainFunc;
    static CCGetGainFunc                   m_pCCGetGainFunc;
    static CCIsDeviceOpenedFunc            m_pCCIsDeviceOpenedFunc;
    static CCSetDeviceWidthHeightFunc      m_pCCSetDeviceWidthHeightFunc;
    static CCGetDeviceWidthHeightFunc      m_pCCGetDeviceWidthHeightFunc;
    static CCGetDeviceBufferFunc           m_pCCGetDeviceBufferFunc;
    static CCStartGrabbingFunc             m_pCCStartGrabbingFunc;
    static CCStopGrabbingFunc              m_pCCStopGrabbingFunc;
    static CCSaveImageFunc                 m_pCCSaveImageFunc;
};

#endif // CAMERADLL_H
