#include "MBdiagnosticitems.h"
#include "MBdefine.h"
#include "MBDLL.h"
#include "MBcommunication.h"

MBDiagnosticItems::MBDiagnosticItems()
{
  
    int defaultInitStatus = (int)ITEM_STATUS::ITEM_ERROR;
    // Define data // Определение данных

    m_Items.append(MBItem(tr("Conveyor"),
        "Conveyor",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_1,
        MT_HOLDING_REGISTER, 
        QVector<int>{ (int)REGISTER_DIAGNOSTIC_1_PROFILE::CONVEYOR_ERROR,
        (int)REGISTER_DIAGNOSTIC_1_PROFILE::CONVEYOR_STATUS },
        defaultInitStatus));

    m_Items.append(MBItem(tr("Infeed cylinder 1"),
        "Infeed cylinder 1",
       (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_1,
        MT_HOLDING_REGISTER,
        QVector<int>{ (int)REGISTER_DIAGNOSTIC_1_PROFILE::INFEED_CYLINDER_1_ERROR,(int)REGISTER_DIAGNOSTIC_1_PROFILE::INFEED_CYLINDER_1_STATUS },
        defaultInitStatus));

    m_Items.append(MBItem(tr("Infeed cylinder 2"),
        "Infeed cylinder 2",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_1,
        MT_HOLDING_REGISTER, 
        QVector<int>{(int)REGISTER_DIAGNOSTIC_1_PROFILE::INFEED_CYLINDER_2_ERROR, (int)REGISTER_DIAGNOSTIC_1_PROFILE::INFEED_CYLINDER_2_STATUS},
        defaultInitStatus));


    m_Items.append(MBItem(tr("Outfeed cylinder"),
        "Outfeed cylinder",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_1,
        MT_HOLDING_REGISTER,
        QVector<int>{ (int)REGISTER_DIAGNOSTIC_1_PROFILE::OUTFEED_CYLINDER_ERROR, (int)REGISTER_DIAGNOSTIC_1_PROFILE::OUTFEED_CYLINDER_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Rotate cylinder"),
        "Rotate cylinder",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_1,
        MT_HOLDING_REGISTER,
        QVector<int>{ (int)REGISTER_DIAGNOSTIC_1_PROFILE::ROTATE_CYLINDER_ERROR, (int)REGISTER_DIAGNOSTIC_1_PROFILE::ROTATE_CYLINDER_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Scale pusher"),
        "Scale pusher",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_2,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_2_PROFILE::SCALE_PUSHER_ERROR, (int)REGISTER_DIAGNOSTIC_2_PROFILE::SCALE_PUSHER_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Table pusher"),
        "Table pusher",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_2,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_2_PROFILE::TABLE_PUSHER_ERROR, (int)REGISTER_DIAGNOSTIC_2_PROFILE::TABLE_PUSHER_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Table elevation"),
        "Table pusher",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_2,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_2_PROFILE::TABLE_LIFTING_ERROR, (int)REGISTER_DIAGNOSTIC_2_PROFILE::TABLE_LIFTING_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Table turning"),
        "Table turning",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_2,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_2_PROFILE::TABLE_TURNING_ERROR, (int)REGISTER_DIAGNOSTIC_2_PROFILE::TABLE_TURNING_STATUS},
        defaultInitStatus));

    // m_Items.append(MBItem(tr("Camera adjustment"),
    //     "Camera adjustment",
    //     (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_2,
    //     MT_HOLDING_REGISTER,
    //     QVector<int>{(int)REGISTER_DIAGNOSTIC_2_PROFILE::CAMERA_ADJUSTMENT_ERROR, (int)REGISTER_DIAGNOSTIC_2_PROFILE::CAMERA_ADJUSTMENT_STATUS},
    //     defaultInitStatus));

    m_Items.append(MBItem(tr("Safety relay"),
        "Safety relay",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_3_PROFILE::SAFETY_REPLY},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Scales"),
        "Scales",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_3_PROFILE::SCALE_ERROR},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Infeed cylinder 1 \n sensor 1"),
      "Infeed cylinder 1 \n sensor 1",
      (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_1,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_1_PROFILE::INFEED_CYLINDER_1_OPEN_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Infeed cylinder 1 \n sensor 2"),
        "Infeed cylinder 1 \n sensor 2",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_1,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_1_PROFILE::INFEED_CYLINDER_1_CLOSE_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Infeed cylinder 2 \n sensor 1"),
        "Infeed cylinder 2 \n sensor 1",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_1,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_1_PROFILE::INFEED_CYLINDER_2_OPEN_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Infeed cylinder 2 \n sensor 2"),
        "Infeed cylinder 2 \n sensor 2",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_1,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_1_PROFILE::INFEED_CYLINDER_2_CLOSE_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Outfeed cylinder \n sensor 1"),
        "Outfeed cylinder \n sensor 1",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_1,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_1_PROFILE::OUTFEED_CYLINDER_OPEN_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Outfeed cylinder \n sensor 2"),
        "Outfeed cylinder \n sensor 2",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_1,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_1_PROFILE::OUTFEED_CYLINDER_CLOSE_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Rotate cylinder \n sensor 1"),
        "Rotate cylinder \n sensor 1",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_2,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_2_PROFILE::ROTATE_CYLINDER_OPEN_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Rotate cylinder \n sensor 2"),
        "Rotate cylinder \n sensor 2",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_2,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_2_PROFILE::ROTATE_CYLINDER_CLOSE_SENSOR_STATUS},
        defaultInitStatus));


    m_Items.append(MBItem(tr("Scale pusher sensor"),
        "Scale pusher sensor",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_2,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_2_PROFILE::SCALE_PUSHER_SENSOR_STATUS},
        defaultInitStatus));


    m_Items.append(MBItem(tr("Table pusher sensor"),
        "Table pusher sensor",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_2,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_2_PROFILE::TABLE_PUSHER_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Table elevation sensor"),
        "Table elevation sensor",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_2,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_2_PROFILE::TABLE_LIFTING_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Table turning sensor"),
        "Table turning sensor",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_2,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_2_PROFILE::TABLE_TURNING_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Infeed sensor"),
        "Infeed sensor",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_3_PROFILE::INFEED_SENSOR_STATUS},
        defaultInitStatus));


    m_Items.append(MBItem(tr("Bottle down sensor"),
        "Bottle down sensor",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_3_PROFILE::BOTTLE_DOWN_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Bottle extra sensor"),
        "Bottle extra sensor",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_3_PROFILE::BOTTLE_EXTRA_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Outfeed sensor"),
        "Outfeed sensor",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_3_PROFILE::OUTFEED_SENSOR_STATIS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Vacuum sensor"),
        "Vacuum sensor",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_3_PROFILE::VACUUM_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Air compressor sensor"),
        "Air compressor sensor",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_3_PROFILE::HIGH_PRESURRE_AIR_SENSOR_STATUS},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Temperature sensor"),
        "Temperature sensor",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_3_PROFILE::CONTROL_BOX_TEMPERATURE_SENSOR_STATUS},
        defaultInitStatus));


    m_Items.append(MBItem(tr("Voltage relay"),
        "Voltage relay",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_3_PROFILE::VOLTAGE_RELAY_SENSOR},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Left door"),
        "Left door",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_3_PROFILE::LEFT_DOOR_SENSOR},
        defaultInitStatus));

    m_Items.append(MBItem(tr("Middle door"),
        "Middle door",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_3_PROFILE::MIDDLE_DOOR_SENSOR},
        defaultInitStatus));


    m_Items.append(MBItem(tr("Right door"),
        "Right door",
        (int)MB_HOLDING_REGISTER_ITEMS::REGISTER_DIAGNOSTIC_3,
        MT_HOLDING_REGISTER,
        QVector<int>{(int)REGISTER_DIAGNOSTIC_3_PROFILE::RIGHT_DOOR_SENSOR},
        defaultInitStatus));


  /*  m_Items.append(MBItem(tr("Index gate cylinder \n sensor 1"),
        "Index gate cylinder \n sensor 1",
        (int)MB_DISCRETE_INPUT_ITEMS::INDEX_GATE_CYCLINDER_SENSOR_1,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Index gate cylinder \n sensor 2"),
        "Index gate cylinder \n sensor 2",
        (int)MB_DISCRETE_INPUT_ITEMS::INDEX_GATE_CYCLINDER_SENSOR_2,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Index gate cylinder \n sensor 3"),
        "Index gate cylinder \n sensor 3",
        (int)MB_DISCRETE_INPUT_ITEMS::INDEX_GATE_CYCLINDER_SENSOR_3,
        MT_DISCRETE_INPUT));*/

  /*  m_Items.append(MBItem(tr("Index gate cylinder \n sensor 4"),
        "Index gate cylinder \n sensor 4",
                          (int)MB_DISCRETE_INPUT_ITEMS::INDEX_GATE_CYCLINDER_SENSOR_4,
                          MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Infeed sensor"),
        "Infeed sensor",
                          (int)MB_DISCRETE_INPUT_ITEMS::INFREED_SENSOR,
                          MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Bottle down sensor"),
        "Bottle down sensor",
                          (int)MB_DISCRETE_INPUT_ITEMS::BOTTLE_DOWN_SENSOR,
                          MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Extra bottle sensor"),
        "Extra bottle sensor",
                          (int)MB_DISCRETE_INPUT_ITEMS::EXTRA_BOTTLE_SENSOR,
                          MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Push sensor 1"),
        "Push sensor 1",
                          (int)MB_DISCRETE_INPUT_ITEMS::PUSH_SENSOR_1,
                          MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Push sensor 2"),
        "Push sensor 2",
        (int)MB_DISCRETE_INPUT_ITEMS::PUSH_SENSOR_2,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Push up sensor"),
        "Push up sensor",
        (int)MB_DISCRETE_INPUT_ITEMS::PUSH_UP_SENSOR,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Home position sensor"),
        "Home position sensor",
        (int)MB_DISCRETE_INPUT_ITEMS::HOME_POSITION_SENSOR,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Rotation table"),
        "Rotation table",
        (int)MB_DISCRETE_INPUT_ITEMS::ROTATION_TABLE,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Elevator"),
        "Elevator",
        (int)MB_DISCRETE_INPUT_ITEMS::ELAVATOR,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Finish camera motor"),
        "Finish camera motor",
        (int)MB_DISCRETE_INPUT_ITEMS::FINISH_CAMERA_MOTOR,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Rotate cylinder \n sensor 1"),
        "Rotate cylinder \n sensor 1",
        (int)MB_DISCRETE_INPUT_ITEMS::ROTATE_CYLINDER_SENSOR_1,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Rotate cylinder \n sensor 2"),
        "Rotate cylinder \n sensor 2",
        (int)MB_DISCRETE_INPUT_ITEMS::ROTATE_CYLINDER_SENSOR_2,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Push back \n Sensor 1"),
        "Push back \n Sensor 1",
        (int)MB_DISCRETE_INPUT_ITEMS::PUSH_BACK_SENSOR_1,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Push back \n Sensor 2"),
        "Push back \n Sensor 2",
        (int)MB_DISCRETE_INPUT_ITEMS::PUSH_BACK_SENSOR_2,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Vacuum Sensor"),
        "Vacuum Sensor",
        (int)MB_DISCRETE_INPUT_ITEMS::VACUUM_SENSOR,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Outfeed Sensor"),
        "Outfeed Sensor",
        (int)MB_DISCRETE_INPUT_ITEMS::OUTFEED_SENSOR,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("E-stop 1"),
        "E-stop 1",
        (int)MB_DISCRETE_INPUT_ITEMS::E_STOP_1,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("E-stop 2"),
        "E-stop 2",
        (int)MB_DISCRETE_INPUT_ITEMS::E_STOP_2,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("E-stop 3"),
        "E-stop 3",
        (int)MB_DISCRETE_INPUT_ITEMS::E_STOP_3,
        MT_DISCRETE_INPUT));

    m_Items.append(MBItem(tr("Machine Guard"),
        "Machine Guard",
        (int)MB_DISCRETE_INPUT_ITEMS::MACHINE_GUARD,
        MT_DISCRETE_INPUT));*/

}

MBDiagnosticItems::~MBDiagnosticItems()
{

}


void MBDiagnosticItems::StartToUpdateData()
{
    auto mbData = MBCommunication::GetInstance()->GetMBData();

    for (int i = 0; i < m_Items.size(); i++)
    {
        auto& item = m_Items[i];

        MBKeyData k(item.m_address, item.m_table);

        if (!mbData.contains(k)) continue;

        quint16 registerResult = mbData[k];
        // start to get result // начните получать результат
        quint16 result = (int)ITEM_STATUS::ITEM_ERROR;
        // when bit position is empty will take into account value of whole register // при пустой позиции бита будет учитываться значение всего регистра
        if (item.m_vectorBitPositonValue.isEmpty())
        {
            result = mbData.value(k);
        }
        else
        {
            // for button status, there are some button that combine 2 bit value to determine button state // что касается состояния кнопки, то существуют некоторые кнопки, которые объединяют 2-битное значение для определения состояния кнопки
            // specially for diagnostic, if more than 2 bit, the first bit will determine button error or not // специально для диагностики, если больше 2 бит, то первый бит определит, ошибка кнопки или нет
            if (item.m_vectorBitPositonValue.size() >= 2)
            {
                // check the bit position at index 0 to make sure not error // проверьте положение бита с индексом 0, чтобы убедиться в отсутствии ошибки
                if ((registerResult & item.m_vectorBitPositonValue.at(0)) == 0)
                {
          
                    result = (registerResult & item.m_vectorBitPositonValue.at(1)) ? (int)ITEM_STATUS::ITEM_ON : (int)ITEM_STATUS::ITEM_OFF;
                }
                else {
                    // item error // ошибка в элементе
                }
            }
            else // case just use one bit for determine button state //  Случае просто используйте один бит для определения состояния кнопки
            {
                result = (registerResult & item.m_vectorBitPositonValue.at(0)) ? (int)ITEM_STATUS::ITEM_ON : (int)ITEM_STATUS::ITEM_OFF;

                // for Safety relay and Scales, it difference color, True: red(ITEM_ERROR), False: Yellow(ITEM_OFF) // для реле безопасности и весов он имеет разный цвет, True: красный(ITEM_ERROR), False: желтый(ITEM_OFF)
                if(item.m_originalDescription == "Scales" || item.m_originalDescription == "Safety relay")
                {
                    result = (registerResult & item.m_vectorBitPositonValue.at(0)) ? (int)ITEM_STATUS::ITEM_ERROR : (int)ITEM_STATUS::ITEM_OFF;
                }
            }
        }

        // not update when the value is not changed // не обновляется, если значение не изменено
        if (item.m_result == result) continue;

        item.m_result = result;

        emit dataContexDataChangedSignal(i);
        
    }

}
