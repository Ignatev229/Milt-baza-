#ifndef MBDEFINE_H
#define MBDEFINE_H


enum class MB_DISCRETE_INPUT_ITEMS : int {

    START = 4000,

    ////--//
    INDEX_GATE_CYCLINDER_SENSOR_1 = START,
    INDEX_GATE_CYCLINDER_SENSOR_2,
    INDEX_GATE_CYCLINDER_SENSOR_3,
    INDEX_GATE_CYCLINDER_SENSOR_4,
    INFREED_SENSOR,
    BOTTLE_DOWN_SENSOR,
    EXTRA_BOTTLE_SENSOR,
    PUSH_SENSOR_1,
    PUSH_SENSOR_2,
    PUSH_UP_SENSOR,
    HOME_POSITION_SENSOR,
    ROTATION_TABLE,
    ELAVATOR,
    FINISH_CAMERA_MOTOR,
    ROTATE_CYLINDER_SENSOR_1,
    ROTATE_CYLINDER_SENSOR_2,
    PUSH_BACK_SENSOR_1,
    PUSH_BACK_SENSOR_2,
    VACUUM_SENSOR,
    OUTFEED_SENSOR,
    E_STOP_1,
    E_STOP_2,
    E_STOP_3,
    MACHINE_GUARD,

    //--//
    END = 4000
};

enum class MB_COIL_ITEMS : int {
    START = 4000,

    ////--//
    //CONVEYOR = START,
    //INFEED_CYLINDER_1,
    //INFEED_CYLINDER_2,
    //OUTFEED_CYLINDER_2,
    //ROTATE_CYLINDER,
    //SCALE_PUSHER_DISTANCE,
    //TABLE_PUSHER_DISTANCE,
    //PUSHUP_DISTANCE_TEST,
    //TEST_BOTTLE_DIAMETER,
    //GO_TO_LOAD,
    //GO_TO_UNLOAD,
    //SAVE_AS_LOAD,
    //SAVE_AS_UNLOAD,
    //SAVE_TABLE_ELEVATION_ANGLE,

    //--//
    END = 4000
};

enum class MB_INPUT_REGISTER_ITEMS : int {
    START = 4000,


    //--//
    END  = 4000
};

enum class MB_HOLDING_REGISTER_ITEMS : int {
    START = 0,

    //--//
    REGISTER_0 = START,
    REGISTER_1 = 1,
    REGISTER_2 = 2,
    REGISTER_SCALE_PUSHER_VALUE = 4, //2 register //2  Регистр
    REGISTER_TABLE_PUSHER_VALUE = 6, //2 register //2  Регистр
    REGISTER_TABLE_ANGLE_VALUE = 8, // 2 register //2  Регистр
    REGISTER_TABLE_ELEVATION_VALUE = 10, // 2 register //2  Регистр
    REGISTER_CAMERA_ADJUSTMENT_VALUE = 12, // 2 register //2  Регистр
    REGISTER_14 = 14,


    REGISTER_500 = 500,
    OPERATION_TYPE_VALUE = 501, // 1 register //1  Регистр
    OPERATION_TYPE_ACK_VALUE = 502, // 1 register //1  Регистр
    BOTTLE_SERIALNUMBER_VALUE = 503, // 503, 504
    BOTTLE_SERIALNUMBER_ACK_VALUE = 505, // 505, 506
    BOTTLE_DIAMETER_VALUE = 507, // 507, 508
    BOTTLE_DIAMETER_ACK_VALUE = 509, // 509, 510
    BOTTLE_HEIGHT_VALUE = 511, // 511, 512
    BOTTLE_HEIGHT_ACK_VALUE = 513, // 513, 514
    // SCALE_PUSHER_POSITION_VALUE = 515, // 515, 516
    // SCALE_PUSHER_POSITION_ACK_VALUE = 517, // 517, 518
    // TABLE_PUSHER_POSITION_VALUE = 519, // 519, 520
    // TABLE_PUSHER_POSITION_ACK_VALUE = 521, // 521, 522
    LIFTING_MECHANISM_POSION_VALUE = 515, //
    LIFTING_MECHANISM_POSION_ACK_VALUE = 517, //
    BOTTLE_WEIGHT_VALUE = 519, //
    BOTTLE_WEIGHT_ACK_VALUE = 521, //
    BOTTLE_BOTTOM_DEPTH_VALUE = 523, //
    BOTTLE_BOTTOM_DEPTH_ACK_VALUE = 525, //



    REGISTER_STATUS_START = 1000, // for status in bottom bar
    REGISTER_1000 = REGISTER_STATUS_START,
    REGISTER_STATUS_END = 1003,

    REGISTER_SCALE_PUSHER_CURRENT_VALUE = 1005, // 2 REGISTER //2  Регистр
    REGISTER_TABLE_PUSHER_CURRENT_VALUE = 1007, // 2 REGISTER //2  Регистр
    REGISTER_TABLE_TURNING_CURRENT_VALUE = 1009, // 2 REGISTER //2  Регистр
    REGISTER_TABLE_LIFTING_CURRENT_VALUE = 1011, // 2 REGISTER //2  Регистр
    REGISTER_CAMERA_POSITION_CURRENT_VALUE = 1013, // 2 REGISTER //2  Регистр
    REGISTER_PUSHUP_DISTANCE_CURRENT_VALUE = 1015, // 2 REGISTER //2  Регистр
    REGISTER_SCALE_CURRENT_VALUE = 1017, // 2 REGISTER //2  Регистр
    REGISTER_DIAGNOSTIC_1 = 1021,
    REGISTER_DIAGNOSTIC_2 = 1022,
    REGISTER_DIAGNOSTIC_3 = 1023,
    REGISTER_DIAGNOSTIC_4 = 1024,


    REGISTER_STATUS2_START = 1025, // for status in bottom bar
    REGISTER_STATUS2_END = 1025,

    //--//
    // replace last register as end // заменить последний регистр в качестве конечного
    END = REGISTER_STATUS2_END
};

enum class REGISTER_0_PROFILE : int
{
    MACHINE_COMMAND_CHANGE_AUTO_MODE = 1 << 0,
    MACHINE_COMMAND_CHANGE_MANUAL_MODE = 1 << 1,
    START_AUTOMATIC_CYCLE = 1 << 2,
    MACHINE_COMMAND_CHANGE_TO_ORIGINAL_STATE = 1 << 3,
    STOP_AUTOMATIC_CYCLE = 1 << 4,


    RESET_ERROR_STATE = 1 << 5,
    SAFETY_RELAY_RESET_STATE = 1 << 6,

    STEP_DRIVE_POWER_RESET = 1 << 9,

};

enum class REGISTER_1_PROFILE : int
{
    CONVEYOR_COMMAND_RUN = 1 << 0,
    CONVEYOR_COMMAND_STOP = 1 << 1,

    INFEED_CYCLINDER_1_COMMAND_OPEN = 1 << 2,
    INFEED_CYCLINDER_1_COMMAND_CLOSE = 1 << 3,

    INFEED_CYCLINDER_2_COMMAND_OPEN = 1 << 4,
    INFEED_CYCLINDER_2_COMMAND_CLOSE = 1 << 5,

    OUTFEED_CYCLINDER_COMMAND_OPEN = 1 << 6,
    OUTFEED_CYCLINDER_COMMAND_CLOSE = 1 << 7,

    ROTATE_CYCLINDER_COMMAND_OPEN = 1 << 8,
    ROTATE_CYCLINDER_COMMAND_CLOSE = 1 << 9,

    SCALE_PUSHER_COMMAND_GO = 1 << 10,
    SCALE_PUSHER_COMMAND_HOME = 1 << 11,

    TABLE_PUSHER_COMMAND_GO = 1 << 12,
    TABLE_PUSHER_COMMAND_HOME = 1 << 13,

    TABLE_ANGLE_COMMAND_GO = 1 << 14,
    TABLE_ANGLE_COMMAND_HOME = 1 << 15,
};

enum class REGISTER_2_PROFILE : int
{
    TABLE_ELEVATION_COMMAND_GO = 1 << 0,
    TABLE_ELEVATION_COMMAND_HOME = 1 << 1,

    CAMERA_ADJUSTMENT_COMMAND_GO = 1 << 2,
    CAMERA_ADJUSTMENT_COMMAND_HOME = 1 << 3,

    SCALE_COMMAND_RESET = 1 << 4,
    PUSHUP_COMMAND_RESET = 1 << 5,

    TABLE_ANGLE_COMMAND_TURN_RIGHT = 1 << 6,
    TABLE_ANGLE_COMMAND_TURN_LEFT = 1 << 7,

    SCALE_PUSHER_COMMAND_STOP = 1 << 8,
    TABLE_PUSHER_COMMAND_STOP = 1 << 9,
    TABLE_ANGLE_COMMAND_STOP = 1 << 10,
    TABLE_ELEVATION_COMMAND_STOP = 1 << 11,
    CAMERA_ADJUSTMENT_COMMAND_STOP = 1 << 12,

    HIGH_PRESSURE_AIR_COMMAND_OPEN = 1 << 13,
    HIGH_PRESSURE_AIR_COMMAND_CLOSE = 1 << 14,

};

enum class REGISTER_14_PROFILE : int
{
    VACCUM_COMMAND_OPEN = 1 << 0,
    VACCUM_COMMAND_CLOSE = 1 << 1,
};

enum class REGISTER_500_PROFILE : int
{
    REQUEST = 1 << 0,
    REQUEST_ACK = 1 << 1,
    RESPONSE = 1 << 2,
    RESPONSE_ACK = 1 << 3,
    OPERATION_COMPLETE = 1 << 4,
    OPERATION_COMPLETE_ACK = 1 << 5,
    OPERATION_ALL_COMPLETE = 1 << 6,
    OPERATION_ALL_COMPLETE_ACK = 1 << 7,
};

enum class REGISTER_DIAGNOSTIC_1_PROFILE : int
{
    // False - No error, True - Error // False - Ошибки нет, True - Ошибка
    CONVEYOR_ERROR = 1 << 0,
    // False - Hold, True - Run //  False-удерживать, True - Запускать
    CONVEYOR_STATUS = 1 << 1,

    // False - No error, True - Error // False - Ошибки нет, True - Ошибка
    INFEED_CYLINDER_1_ERROR = 1 << 2,
    // False - Hold, True - Opening or Closing //  False-удерживать, True - Открывание или закрывание
    INFEED_CYLINDER_1_STATUS = 1 << 3,
    INFEED_CYLINDER_1_OPEN_SENSOR_STATUS = 1 << 4,
    INFEED_CYLINDER_1_CLOSE_SENSOR_STATUS = 1 << 5,

    // False - No error, True - Error // False - Ошибки нет, True - Ошибка
    INFEED_CYLINDER_2_ERROR = 1 << 6,
    // False - Hold, True - Opening or Closing //  False-удерживать, True - Открывание или закрывание
    INFEED_CYLINDER_2_STATUS = 1 << 7,
    INFEED_CYLINDER_2_OPEN_SENSOR_STATUS = 1 << 8,
    INFEED_CYLINDER_2_CLOSE_SENSOR_STATUS = 1 << 9,

    // False - No error, True - Error // False - Ошибки нет, True - Ошибка
    OUTFEED_CYLINDER_ERROR = 1 << 10,
    // False - Hold, True - Opening or Closing //  False-удерживать, True - Открывание или закрывание
    OUTFEED_CYLINDER_STATUS = 1 << 11,
    OUTFEED_CYLINDER_OPEN_SENSOR_STATUS = 1 << 12,
    OUTFEED_CYLINDER_CLOSE_SENSOR_STATUS = 1 << 13,

    // False - No error, True - Error // False - Ошибки нет, True - Ошибка
    ROTATE_CYLINDER_ERROR = 1 << 14,
    // False - Hold, True - Opening or Closing //  False-удерживать, True - Открывание или закрывание
    ROTATE_CYLINDER_STATUS = 1 << 15,

};

enum class REGISTER_DIAGNOSTIC_2_PROFILE : int
{
    ROTATE_CYLINDER_OPEN_SENSOR_STATUS = 1 << 0,
    ROTATE_CYLINDER_CLOSE_SENSOR_STATUS = 1 << 1,

    // False - No error, True - Error // False - Ошибки нет, True - Ошибка
    SCALE_PUSHER_ERROR = 1 << 2,
    // False - Hold, True - Moving //  False-удерживать, True - перемещение
    SCALE_PUSHER_STATUS = 1 << 3,
    SCALE_PUSHER_SENSOR_STATUS = 1 << 4,

    // False - No error, True - Error // False - Ошибки нет, True - Ошибка
    TABLE_PUSHER_ERROR = 1 << 5,
    // False - Hold, True - Moving //  False-удерживать, True - перемещение
    TABLE_PUSHER_STATUS = 1 << 6,
    TABLE_PUSHER_SENSOR_STATUS = 1 << 7, 

    // False - No error, True - Error // False - Ошибки нет, True - Ошибка
    TABLE_TURNING_ERROR = 1 << 8,
    // False - Hold, True - Moving //  False-удерживать, True - перемещение
    TABLE_TURNING_STATUS = 1 << 9,
    TABLE_TURNING_SENSOR_STATUS = 1 << 10,

    // False - No error, True - Error // False - Ошибки нет, True - Ошибка
    TABLE_LIFTING_ERROR = 1 << 11,
    // False - Hold, True - Moving //  False-удерживать, True - перемещение
    TABLE_LIFTING_STATUS = 1 << 12,
    TABLE_LIFTING_SENSOR_STATUS = 1 << 13,

    // False - No error, True - Error // False - Ошибки нет, True - Ошибка
    CAMERA_ADJUSTMENT_ERROR = 1 << 14,
    // False - Hold, True - Moving //  False-удерживать, True - перемещение
    CAMERA_ADJUSTMENT_STATUS = 1 << 15
};

enum class REGISTER_DIAGNOSTIC_3_PROFILE : int
{
    CAMERA_ADJUSTMENT_SENSOR_STATUS = 1 << 0,

    // False - No error, True - Error // False - Ошибки нет, True - Ошибка
    SCALE_ERROR = 1 << 1,

    INFEED_SENSOR_STATUS = 1 << 2,

    BOTTLE_DOWN_SENSOR_STATUS = 1 << 3,
    BOTTLE_EXTRA_SENSOR_STATUS = 1 << 4,

    OUTFEED_SENSOR_STATIS = 1 << 5,
    // False - No vacuum, True - Vacuum reached // False - Вакуума нет, True - Вакуум достигнут
    VACUUM_SENSOR_STATUS = 1 << 6,

    // False - Air pressure low, True - Air pressure reached // False - Давление воздуха низкое, True - давление воздуха достигнуто
    HIGH_PRESURRE_AIR_SENSOR_STATUS = 1 << 7,

    // False - temperature is normal, True - temperature is high // False - температура нормальная, True - температура высокая
    CONTROL_BOX_TEMPERATURE_SENSOR_STATUS = 1 << 8,

    // False - door closed, True - door opened // False - дверь закрыта, True - дверь открыта
    LEFT_DOOR_SENSOR = 1 << 9,
    // False - door closed, True - door opened // False - дверь закрыта, True - дверь открыта
    MIDDLE_DOOR_SENSOR = 1 << 10,
    // False - door closed, True - door opened // False - дверь закрыта, True - дверь открыта
    RIGHT_DOOR_SENSOR = 1 << 11,

    // False - Voltage is low, True - Voltage is normal // False - Напряжение низкое, True - Напряжение норме
    VOLTAGE_RELAY_SENSOR = 1 << 12,
    // False - Normal state, True - Safety or ESTOP // False - Нормальное состояние, True - Безопасная или аварийная ОСТАНОВКА
    SAFETY_REPLY = 1 << 13,

    RESERVED_1 = 1 << 14,
    RESERVED_2 = 1 << 15
};

enum class REGISTER_DIAGNOSTIC_4_PROFILE : int
{

};

enum class REGISTER_CALIBRATION_SEQUENCE_1 : int
{
    // FALSE: INSPECT_DONE, TRUE: PLC Trigger start inspect // FALSE: ПРОВЕРКА ЗАВЕРШЕНА, TRUE: Триггер ПЛК для Запуска проверки
    TRIGER_INSPECT_STATUS_INSPECT = 1 << 0,

    // TRUE: Inspecting, FALSE, not inspect // TRUE:  Проверяем, FALSE, не проверяем
    TRIGER_INSPECT_STATUS_INSPECTING = 1 << 1,

    TRIGER_REQUEST_PLC_MOVEMENT = 1 << 2,
    TRIGER_INSPECT_RESULT = 1 << 3,

    // PLC_MOVING_STATUS = 1 << 4
};

enum class REGISTER_1000_PROFILE : int
{
    AUTOMATIC_CYCLE = 1 << 4,
};

#endif // MBDEFINE_H
