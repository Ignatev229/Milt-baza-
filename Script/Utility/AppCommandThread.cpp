#include "AppCommandThread.h"
#include "../Define/struct_def.h"
#include "ViewModel/master_app.h"
#include "ViewModel/track_vm.h"

AppCommandThread::AppCommandThread(QObject *parent)
    : QThread{parent}
	, m_bExit(false)
	, m_bIsCommandReady(false)
	, m_nImageIndex(0)
{
	m_pParentObject = reinterpret_cast<MasterApp*>(parent);
}

void AppCommandThread::ReceiveCommand(int command, int imageIndex)
{
	
	if (m_bIsCommandReady) return;

	QMutexLocker locker(&m_mutexCommand);

	m_nImageIndex = imageIndex;
	m_nCommand = command;
	m_bIsCommandReady = true;
	m_waitCommandCondition.wakeAll();
}

void AppCommandThread::Exit()
{

	QMutexLocker locker(&m_mutexCommand);

	m_bExit = true;
	m_waitCommandCondition.wakeAll();
}

void AppCommandThread::run()
{
	while (true)
	{
		QMutexLocker locker(&m_mutexCommand);

        // Wait until a command is ready or thread exit // Подождите, пока команда не будет готова или поток не завершит работу
		while (!m_bIsCommandReady && !m_bExit) {
			m_waitCommandCondition.wait(&m_mutexCommand);
		}

		if (m_bExit) break;

		if (m_bIsCommandReady)
		{
            // start execute command // начать выполнение команды
			switch (m_nCommand)
			{
			case COMMAND_CALIBRATION:
                //capture at m_nImageIndex //захват в m_nImageIndex
                // inspect //проверить
                // can emit signal to master app for easy handle // может передавать сигнал в главное приложение для удобства управления
				m_pParentObject->hashTrackVM[(TRACK_INDEX)m_nImageIndex]->Snap();
				QThread::msleep(100);

				break;

            case COMMAND_INSPECTION_SEQUENCE:
                m_pParentObject->InspectionSequence();
                break;


			default:
				break;
			}
            // set false after execute // установить значение false после выполнения
			m_bIsCommandReady = false;
		}

		locker.unlock();
	}
}
