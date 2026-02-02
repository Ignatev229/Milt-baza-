#include "MBDLL.h"
#include <QLibrary>
#include <QDebug>

bool MBDLLControl::m_isInit = false;


MTCreateFactoryFunc					MBDLLControl::m_pMTCreateFactoryFunc				= nullptr;
MTDestroyFactoryFunc				MBDLLControl::m_pMTDestroyFactoryFunc				= nullptr;
MTSetUpConnectionParameterFunc		MBDLLControl::m_pMTSetUpConnectionParameterFunc		= nullptr;
MTSetUpUnitDataFunc					MBDLLControl::m_pMTSetUpUnitDataFunc				= nullptr;
MTSetUpCallbackFunc					MBDLLControl::m_pMTSetUpCallbackFunc				= nullptr;
									
MTInitFunc							MBDLLControl::m_pMTInitFunc							= nullptr;
MTStartFunc							MBDLLControl::m_pMTStartFunc						= nullptr;
MTStopFunc							MBDLLControl::m_pMTStopFunc							= nullptr;

MTGetDataUnitInforFunc				MBDLLControl::m_pMTGetDataUnitInforFunc				= nullptr;
MTWriteDataUnitFunc					MBDLLControl::m_pMTWriteDataUnitFunc				= nullptr;
MTReadDataUnitFunc					MBDLLControl::m_pMTReadDataUnitFunc					= nullptr;
MTIsConnectedFunc					MBDLLControl::m_pMTIsConnectedFunc					= nullptr;

bool MBDLLControl::RegisterDLL(const char* dllName)
{
    // init dll one time only // инициализировать dll только один раз
	if (m_isInit) return false;

	QLibrary library(dllName);
	if (!library.load()) {

		qDebug() << "Can not load library";
		return false;
	}

	
	m_pMTCreateFactoryFunc = reinterpret_cast<MTCreateFactoryFunc>(library.resolve("MTCreateFactory"));
	if (m_pMTCreateFactoryFunc == nullptr)
	{
		qDebug() << "Can not library function MTCreateFactory";
		return false;
	}

	m_pMTDestroyFactoryFunc = reinterpret_cast<MTDestroyFactoryFunc>(library.resolve("MTDestroyFactory"));
	if (m_pMTDestroyFactoryFunc == nullptr)
	{
		qDebug() << "Can not library function MTDestroyFactory";
		return false;
	}


	m_pMTSetUpConnectionParameterFunc = reinterpret_cast<MTSetUpConnectionParameterFunc>(library.resolve("MTSetUpConnectionParameter"));
	if (m_pMTSetUpConnectionParameterFunc == nullptr)
	{
		qDebug() << "Can not library function MTSetUpConnectionParameter";
		return false;
	}


	m_pMTSetUpUnitDataFunc = reinterpret_cast<MTSetUpUnitDataFunc>(library.resolve("MTSetUpUnitData"));
	if (m_pMTSetUpUnitDataFunc == nullptr)
	{
		qDebug() << "Can not library function MTSetUpUnitData";
		return false;
	}

	m_pMTSetUpCallbackFunc = reinterpret_cast<MTSetUpCallbackFunc>(library.resolve("MTSetUpCallback"));
	if (m_pMTSetUpCallbackFunc == nullptr)
	{
		qDebug() << "Can not library function MTSetUpUnitData";
		return false;
	}

	m_pMTInitFunc = reinterpret_cast<MTInitFunc>(library.resolve("MTInit"));
	if (m_pMTInitFunc == nullptr)
	{
		qDebug() << "Can not library function MTInit";
		return false;
	}

	m_pMTStartFunc = reinterpret_cast<MTStartFunc>(library.resolve("MTStart"));
	if (m_pMTStartFunc == nullptr)
	{
		qDebug() << "Can not library function MTStart";
		return false;
	}

	m_pMTStopFunc = reinterpret_cast<MTStopFunc>(library.resolve("MTStop"));
	if (m_pMTStopFunc == nullptr)
	{
		qDebug() << "Can not library function MTStop";
		return false;
	}

	m_pMTGetDataUnitInforFunc = reinterpret_cast<MTGetDataUnitInforFunc>(library.resolve("MTGetDataUnitInfor"));
	if (m_pMTGetDataUnitInforFunc == nullptr)
	{
		qDebug() << "Can not library function MTGetDataUnitInfor";
		return false;
	}

	m_pMTWriteDataUnitFunc = reinterpret_cast<MTWriteDataUnitFunc>(library.resolve("MTWriteDataUnit"));
	if (m_pMTWriteDataUnitFunc == nullptr)
	{
		qDebug() << "Can not library function MTWriteDataUnit";
		return false;
	}



	m_pMTReadDataUnitFunc = reinterpret_cast<MTReadDataUnitFunc>(library.resolve("MTReadDataUnit"));
	if (m_pMTReadDataUnitFunc == nullptr)
	{
		qDebug() << "Can not library function MTReadDataUnit";
		return false;
	}

	m_pMTIsConnectedFunc = reinterpret_cast<MTIsConnectedFunc>(library.resolve("MTIsConnected"));
	if (m_pMTIsConnectedFunc == nullptr)
	{
		qDebug() << "Can not library function MTIsConnected";
		return false;
	}


	qDebug() << "Load modbus dll success";

	m_isInit = true;

	return true;
}
