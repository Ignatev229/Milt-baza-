QT += quick sql webengine
QT += concurrent
QT += network
QT += widgets
QT += qml quick virtualkeyboard


QT_QML_GENERATE_QMLLS_INI=ON

# Set file version at here #Здесь можно установить версию файла
win32 {
    VERSION = 1.1.0
} else : unix {
    VER_MAJ = 1
    VER_MIN = 1
    VER_PAT = 0
}



TRANSLATIONS += translations/BottleInsp_en.ts translations/BottleInsp_ru.ts


# You can make your code fail to compile if it uses deprecated APIs. #Вы можете привести к сбою компиляции вашего кода, если он использует устаревшие API.
# In order to do so, uncomment the following line. #Для этого раскомментируйте следующую строку.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000 #DEFINES += QT_отключать_осуждаемый_до=0x060000    # disables all the APIs deprecated before Qt 6.0.0 #отключает все API, которые были устаревшими до Qt 6.0.0

SOURCES += \
        Core/inspectioncore.cpp \
        Model/debug_log_model.cpp \
        Model/image_model.cpp \
        Model/limit_table_model.cpp \
        Model/list_string_model.cpp \
        Model/modbus_list_model.cpp \
        Model/statistics_model.cpp \
        Script/Config/config_application.cpp \
        Script/Hardware/Camera/CameraDLL.cpp \
        Script/Hardware/Camera/camera_interface.cpp \
        Script/Modbus/MBDLL.cpp \
        Script/Modbus/MBdiagnosticitems.cpp \
        Script/Modbus/MBItem.cpp \
        Script/Modbus/MBcommunication.cpp \
        Script/SaveImage/save_image_thread.cpp \
        Script/Sql/sql_management.cpp \
        Script/Utility/AppCommandThread.cpp \
        Script/Utility/AppUtility.cpp \
        TCPServer/tcp_backend_client.cpp \
        ViewModel/Calibration/calib_table_vm.cpp \
        ViewModel/ContainerTab/ContainerVM.cpp \
        ViewModel/Correction/correction_vm.cpp \
        ViewModel/Dialog/dialog_vm.cpp \
        ViewModel/FeederAndPushers/feeder_and_pushers_vm.cpp \
        ViewModel/History/history_vm.cpp \
        ViewModel/Limit/limit_vm.cpp \
        ViewModel/Main/debug_log_vm.cpp \
        ViewModel/Main/main_home_vm.cpp \
        ViewModel/Main/ribbon_vm.cpp \
        ViewModel/Main/statistics_vm.cpp \
        ViewModel/RecipeManagement/edit_recipe_vm.cpp \
        ViewModel/RecipeManagement/recipe_management_vm.cpp \
        ViewModel/Report/report_vm.cpp \
        ViewModel/Review/image_review_vm.cpp \
        ViewModel/Review/review_vm.cpp \
        ViewModel/Review/single_review_vm.cpp \
        ViewModel/Setout/plc_communication_log_vm.cpp \
        ViewModel/Setout/setout_vm.cpp \
        ViewModel/System/system_vm.cpp \
        ViewModel/SystemSettings/system_setting_vm.cpp \
        ViewModel/Table/table_vm.cpp \
        ViewModel/Validation/validation_vm.cpp \
        ViewModel/image_view_vm.cpp \
        ViewModel/image_writer.cpp \
        ViewModel/list_string_vm.cpp \
        ViewModel/login_vm.cpp \
        ViewModel/main_vm.cpp \
        ViewModel/master_app.cpp \
        ViewModel/tab_control_vm.cpp \
        ViewModel/track_vm.cpp \
        main.cpp


RC_ICONS = Resources/AppIcon.ico

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model # Дополнительный путь импорта, используемый для разрешения QML-модулей в модели кода Qt Creator
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer # Дополнительный путь импорта, используемый для разрешения модулей QML только для Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment. # Правила развертывания по умолчанию.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Core/inspectioncore.h \
    Core/colors.h \
    Model/debug_log_model.h \
    Model/image_model.h \
    Model/limit_table_model.h \
    Model/list_string_model.h \
    Model/modbus_list_model.h \
    Model/statistics_model.h \
    Script/Config/config_application.h \
    Script/Hardware/Camera/CameraDLL.h \
    Script/Hardware/Camera/camera_interface.h \
    Script/Define/struct_def.h \
    Script/Modbus/MBDLL.h \
    Script/Modbus/MBdiagnosticitems.h \
    Script/Modbus/MBItem.h \
    Script/Modbus/MBcommunication.h \
    Script/Modbus/MBdefine.h \
    Script/SaveImage/save_image_thread.h \
    Script/Sql/sql_management.h \
    Script/Utility/AppCommandThread.h \
    Script/Utility/AppUtility.h \
    TCPServer/tcp_backend_client.h \
    ViewModel/Calibration/calib_table_vm.h \
    ViewModel/ContainerTab/ContainerVM.h \
    ViewModel/Correction/correction_vm.h \
    ViewModel/Dialog/dialog_vm.h \
    ViewModel/FeederAndPushers/feeder_and_pushers_vm.h \
    ViewModel/History/history_vm.h \
    ViewModel/Limit/limit_vm.h \
    ViewModel/Main/debug_log_vm.h \
    ViewModel/Main/main_home_vm.h \
    ViewModel/Main/ribbon_vm.h \
    ViewModel/Main/statistics_vm.h \
    ViewModel/RecipeManagement/edit_recipe_vm.h \
    ViewModel/RecipeManagement/recipe_management_vm.h \
    ViewModel/RecipeManagement/vision_parameters.h \
    ViewModel/Report/report_vm.h \
    ViewModel/Review/image_review_vm.h \
    ViewModel/Review/review_vm.h \
    ViewModel/Review/single_review_vm.h \
    ViewModel/Setout/plc_communication_log_vm.h \
    ViewModel/Setout/setout_vm.h \
    ViewModel/System/system_vm.h \
    ViewModel/SystemSettings/system_setting_vm.h \
    ViewModel/Table/table_vm.h \
    ViewModel/Validation/validation_vm.h \
    ViewModel/image_view_vm.h \
    ViewModel/image_writer.h \
    ViewModel/list_string_vm.h \
    ViewModel/login_vm.h \
    ViewModel/main_vm.h \
    ViewModel/master_app.h \
    ViewModel/tab_control_vm.h \
    ViewModel/track_vm.h

INCLUDEPATH += $$PWD

# OpenCV Setup # Настройка OpenCV
message("OpenCV setup version 4.6.0")
win32 {

    OPENCV_INCLUDE_DIRECTORY = $$PWD/external/Opencv/include
    OPENCV_LIB_DIRECTORY = $$PWD/external/Opencv/lib

    CONFIG(debug, debug|release) {
        OPENCV_LIB_FILE_NAME = 'opencv_world460d'
    } else {
        OPENCV_LIB_FILE_NAME = 'opencv_world460'
    }
    INCLUDEPATH += $$OPENCV_INCLUDE_DIRECTORY
    DEPENDPATH += $$OPENCV_INCLUDE_DIRECTORY
    LIBS += -L$$OPENCV_LIB_DIRECTORY -l$$OPENCV_LIB_FILE_NAME


} else : unix {
}

# MVS camera # MVS камера
win32{
    message("MVSCamera setup version 3.4.2.0")
    MVS_INCLUDE_DIRECTORY = 'C:/Program Files (x86)/MVS/Development/Includes'
    MVS_LIB_DIRECTORY = 'C:/Program Files (x86)/MVS/Development/Libraries/win64'
    MVS_LIB_FILE_NAME = 'MvCameraControl'

    INCLUDEPATH += $$MVS_INCLUDE_DIRECTORY
    DEPENDPATH += $$MVS_INCLUDE_DIRECTORY
    LIBS += -L$$MVS_LIB_DIRECTORY -l$$MVS_LIB_FILE_NAME

} else : unix {
    message("MVSCamera set up version 4.3.0.4")
    MVS_INCLUDE_DIRECTORY = '/opt/MVS/include'
    MVS_LIB_DIRECTORY = '/opt/MVS/lib/64/'
    MVS_LIB_FILE_NAME = 'MvCameraControl'

    INCLUDEPATH += $$MVS_INCLUDE_DIRECTORY
    DEPENDPATH += $$MVS_INCLUDE_DIRECTORY
    LIBS += -L$$MVS_LIB_DIRECTORY -l$$MVS_LIB_FILE_NAME
}

# add zip file
win32{
    INCLUDEPATH += $$PWD/external/zip/include
    LIBS += -L$$PWD/external/zip/lib -lzlib -lquazip1-qt5
} else : unix {
    INCLUDEPATH += $$PWD/external/zip/include
    LIBS += -L$$PWD/external/zip/lib -lquazip5
}
# INCLUDEPATH += D:/PO/Project/QT/C++/Zip/quazip-master/quazip
# LIBS += -LD:/PO/Project/QT/C++/Zip/quazip-master/quazip/quazip/Release -lquazip1-qt5







