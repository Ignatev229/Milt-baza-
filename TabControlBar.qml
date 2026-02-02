import QtQml 2.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.15

import "Component"
import "View"
import "View/Main"
import "View/SystemSettings"
import "View/Review"
import "View/RecipeManagement"
import "View/History"
import "View/Dialog"

import "View/Setout"
import "View/Containers"
import "View/Limit"
import "View/Dimension"
import "View/Validation"
import "View/System"
import "View/Report"
import "View/Diagnostic"
import "View/FeederAndPushers"
import "View/Table"
import "View/Calibration"
import "View/Correction"

import ConfigView 1.0

Item {
    id: tab_control_bar
    property int windowStatus: 1 // 1 Normal, 2 maximize
    property int windowMargin: 10
    property int previousX
    property int previousY
    property bool keyboardOpenFirsttime: true

    function showMenuTab(isShow) {

        //recipe_management_view.tabSelected(isShow)   
        history_view.tabSelected(isShow)
        job_management_view.tabSelected(isShow)
        // calibration_view.tabSelected(isShow)
        system_setting_view.tabSelected(isShow)
        main_tab_content.tabSelected(isShow)

    }

    QtObject{
        id: internalTabControlBar

        property url _btnMaximizeRestore: "../Resources/maximize_icon.svg"
        function maximizeRestore() {
            if(windowStatus == 1){
                mainWindow.showMaximized()
                windowStatus = 2
                windowMargin = 0
                _btnMaximizeRestore = "../Resources/restore_icon.svg"
            }
            else{
                mainWindow.showNormal()
                windowStatus = 1
                windowMargin = 10
                _btnMaximizeRestore="../Resources/maximize_icon.svg"
            }
        }

        function minimized() {
            mainWindow.showMinimized()
            windowMargin = 10
            _btnMaximizeRestore = "../Resources/maximize_icon.svg"
        }

        function closeApp() {
            mainWindow.close()
        }

        function updateLocalTime(){
            var currentDate = new Date();
            ConfigView.currentDate = Qt.formatDateTime(currentDate, "yyyy.MM.dd");
            ConfigView.currentTime = Qt.formatDateTime(currentDate, "hh:mm:ss");
            ConfigView.currentDay = currentDate.getDay();

        }

    }

    // timer // таймер
    Timer{
        interval: 1000
        repeat: true
        running: true
        triggeredOnStart: true
        onTriggered: {
            internalTabControlBar.updateLocalTime()
        }
    }

    Column{
        id: headerBar
        height: parent.height*0.1
        width: parent.width

        // TitleBar // Строка заголовка
        Rectangle{
            height: parent.height*0.4
            width: parent.width
            z: 2
            Rectangle{
                height: headerBar.height
                width: parent.width*0.067
                color: ConfigView.mainWhiteColor
                Image{
                    id: iconApp
                    height: parent.height * 0.45
                    width: parent.width * 0.95
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    source: "../Resources/AppIcon.png"
                    fillMode: Image.PreserveAspectFit
                }
            }
            MouseArea{
                anchors.fill: parent
                onPressed: {
                    previousX = mouseX
                    previousY = mouseY
                }
                onMouseXChanged: {
                    if(windowStatus == 2)return
                    var dx = mouseX - previousX
                    mainWindow.setX(mainWindow.x + dx)
                }
                onMouseYChanged: {
                    if(windowStatus == 2)return
                    var dy = mouseY - previousY
                    mainWindow.setY(mainWindow.y + dy)
                }
            }
            TitleBar{
                _btnMaximizeRestore: internalTabControlBar._btnMaximizeRestore
                _fontFamily: ConfigView.fontFamily
            }
        }

        // Tab bar // Панель вкладок
        // Setup mode // Режим настройки
        Row{
            visible: ConfigView.appMode === 2 // setup mode // Режим настройки
            width: parent.width*0.933
            height: parent.height*0.6
            anchors.right: parent.right
            z: 1
            TabBar {
                id:tab_bar_setup_mode
                width: parent.width*0.87
                contentHeight: parent.height

                TabButton {
                    id: button
                    height: parent.height
                    font.pointSize: ConfigView.tabBarFontSize
                    onClicked: {
                    }
                   
                    background: Rectangle {
                        color: tab_bar_setup_mode.currentIndex == 0 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_main
                            text: qsTr("Main")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_setup_mode.currentIndex == 0 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }

                }

                TabButton {
                    height: parent.height
                    font.pointSize: ConfigView.tabBarFontSize
                    onClicked: {
                    }
                    background: Rectangle {
                        color: tab_bar_setup_mode.currentIndex == 1 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_settings
                            text: qsTr("Setting")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_setup_mode.currentIndex == 1 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }
                }

                TabButton {
                    height: 0
                    width: 0
                    font.pointSize: ConfigView.tabBarFontSize
                    visible: false
                    onClicked: {
                    }
                    background: Rectangle {
                        color: tab_bar_setup_mode.currentIndex == 2 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_recipe_mangement
                            text: qsTr("Recipe Management")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_setup_mode.currentIndex == 2 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }
                }

                TabButton {
                    height: parent.height
                    font.pointSize: ConfigView.tabBarFontSize
                    onClicked: {
                    }
                    background: Rectangle {
                        color: tab_bar_setup_mode.currentIndex == 3 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_review
                            text: qsTr("Review")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_setup_mode.currentIndex == 3 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }
                }

                TabButton {
                    height: parent.height
                    font.pointSize: ConfigView.tabBarFontSize
                    onClicked: {
                    }
                    background: Rectangle {
                        color: tab_bar_setup_mode.currentIndex == 4 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_history
                            text: qsTr("History")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_setup_mode.currentIndex == 4 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }
                }

                TabButton {
                    height: parent.height
                    onClicked: {
                    }
                    background: Rectangle {
                        color: tab_bar_setup_mode.currentIndex == 5 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_actuators
                            text: qsTr("Actuators")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_setup_mode.currentIndex == 5 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }
                }

                TabButton {
                    height: parent.height
                    font.pointSize: ConfigView.tabBarFontSize
                    onClicked: {
                    }

                    background: Rectangle {
                        color: tab_bar_setup_mode.currentIndex == 6 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_table
                            text: qsTr("Table")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_setup_mode.currentIndex == 6 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }
                }

                TabButton {
                    height: parent.height
                    font.pointSize: ConfigView.tabBarFontSize
                    onClicked: {
                    }
                    background: Rectangle {
                        color: tab_bar_setup_mode.currentIndex == 7 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_calibration
                            text: qsTr("Calibration")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_setup_mode.currentIndex == 7 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }
                }

                TabButton {
                    height: parent.height
                    onClicked: {
                    }
                    background: Rectangle {
                        color: tab_bar_setup_mode.currentIndex == 8 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor

                        Text{
                            id:text_correction
                            text: qsTr("Correction")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_setup_mode.currentIndex == 8 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }
                }

                onCurrentIndexChanged: {

                    if(tab_bar_setup_mode.currentIndex === 1){
                        // update setting tab //  Обновить вкладку настроек
                        tabControlVM.tabIndexChanged_Qml_Slots(1)
                    }
                    if(tab_bar_setup_mode.currentIndex === 2){
                        // notify when tab manage recipe selected // уведомлять о выборе вкладки "управление рецептом"
                        tabControlVM.tabIndexChanged_Qml_Slots(2)
                    }
                    else{

                    }
                    system_setting_view.tabSelected(tab_bar_setup_mode.currentIndex === 1)
                    // recipe_management_view.tabSelected(tab_bar_setup_mode.currentIndex === 2)
                    history_view.tabSelected(tab_bar_setup_mode.currentIndex === 4)
                    main_tab_content.tabSelected(tab_bar_setup_mode.currentIndex === 0)
                    // calibration_view.tabSelected(tab_bar_setup_mode.currentIndex === 7)
                }
            }

            Rectangle{
                id: appStatusBtn1
                width: parent.width*0.13
                height: parent.height
                anchors.right: parent.right
                color: ConfigView.isAppRunning ? ConfigView.acceptSignalColor : ConfigView.cancelSignalColor
                Text {
                    text: ConfigView.isAppRunning ? qsTr("Running") : qsTr("Stopped")
                    color: ConfigView.textColor
                    font.bold: true
                    font.pointSize: 14
                    font.family: ConfigView.fontFamily
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: (mouse)=> {
                        if (mouse.button === Qt.LeftButton)
                           // ConfigView.isAppRunning = !ConfigView.isAppRunning
                           setoutVM.runStopStatus_Qml_Slot(!ConfigView.isAppRunning, set_out.getcurrentJobText())
                    }
                }
            }
        }


        // Tab bar // Панель вкладок
        // Run mode // Режим запуска
        Row{
            visible: ConfigView.appMode === 1
            width: parent.width*0.933
            height: parent.height*0.6
            anchors.right: parent.right
            z: 1
            TabBar {
                id: tab_bar_run_mode
                width: parent.width*0.85
                contentHeight: parent.height

                TabButton {
                    height: parent.height
                    font.pointSize: ConfigView.tabBarFontSize
                    onClicked: {
                    }
                    background: Rectangle {
                        color: tab_bar_run_mode.currentIndex === 0 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_setout
                            text: qsTr("Setout")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_run_mode.currentIndex === 0 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }

                }

                TabButton {
                    height: parent.height
                    font.pointSize: ConfigView.tabBarFontSize
                    onClicked: {
                    }
                    background: Rectangle {
                        color: tab_bar_run_mode.currentIndex === 1 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_job
                            text: qsTr("Job")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_run_mode.currentIndex === 1 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }
                }

                // TabButton {
                //     height: parent.height
                //     text: qsTr("Containers")
                //     font.pointSize: ConfigView.tabBarFontSize
                //     onClicked: {
                //     }
                //     background: Rectangle {
                //         color: tab_bar_run_mode.currentIndex === 2 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        // Text{
                        //     id:text
                        //     text: qsTr("Correction")
                        //     font.family: ConfigView.fontFamily
                        //     color: tab_bar_run_mode.currentIndex == 8 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                        //     font.pixelSize: ConfigView.tabBarFontSize
                        //     verticalAlignment: Text.AlignVCenter
                        //     horizontalAlignment: Text.AlignHCenter
                        //     anchors.verticalCenter: parent.verticalCenter
                        //     anchors.horizontalCenter: parent.horizontalCenter
                        //     width: contentWidth
                        //     height: contentHeight
                        //     anchors.left: icon.right
                        //     anchors.leftMargin: button.width*0.08
                        // }
                //     }
                // }

                TabButton {
                    height: parent.height
                    font.pointSize: ConfigView.tabBarFontSize
                    onClicked: {
                    }
                    background: Rectangle {
                        color: tab_bar_run_mode.currentIndex === 2 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_system
                            text: qsTr("System")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_run_mode.currentIndex === 2 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }
                }

                TabButton {
                    height: parent.height
                    font.pointSize: ConfigView.tabBarFontSize
                    onClicked: {
                    }
                    background: Rectangle {
                        color: tab_bar_run_mode.currentIndex === 3 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_validation
                            text: qsTr("Validation")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_run_mode.currentIndex === 3 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }
                }

                // TabButton {
                //     height: parent.height
                //     text: qsTr("Limits")
                //     font.pointSize: ConfigView.tabBarFontSize
                //     onClicked: {
                //     }
                //     background: Rectangle {
                //         color: tab_bar_run_mode.currentIndex === 5 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        // Text{
                        //     id:text
                        //     text: qsTr("Correction")
                        //     font.family: ConfigView.fontFamily
                        //     color: tab_bar_run_mode.currentIndex == 8 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                        //     font.pixelSize: ConfigView.tabBarFontSize
                        //     verticalAlignment: Text.AlignVCenter
                        //     horizontalAlignment: Text.AlignHCenter
                        //     anchors.verticalCenter: parent.verticalCenter
                        //     anchors.horizontalCenter: parent.horizontalCenter
                        //     width: contentWidth
                        //     height: contentHeight
                        //     anchors.left: icon.right
                        //     anchors.leftMargin: button.width*0.08
                        // }
                //     }
                // }

                // TabButton {
                //     height: parent.height
                //     text: qsTr("Dimension")
                //     font.pointSize: ConfigView.tabBarFontSize
                //     onClicked: {
                //     }
                //     background: Rectangle {
                //         color: tab_bar_run_mode.currentIndex === 6 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        // Text{
                        //     id:text
                        //     text: qsTr("Correction")
                        //     font.family: ConfigView.fontFamily
                        //     color: tab_bar_run_mode.currentIndex == 8 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                        //     font.pixelSize: ConfigView.tabBarFontSize
                        //     verticalAlignment: Text.AlignVCenter
                        //     horizontalAlignment: Text.AlignHCenter
                        //     anchors.verticalCenter: parent.verticalCenter
                        //     anchors.horizontalCenter: parent.horizontalCenter
                        //     width: contentWidth
                        //     height: contentHeight
                        //     anchors.left: icon.right
                        //     anchors.leftMargin: button.width*0.08
                        // }
                //     }
                // }

                TabButton {
                    height: parent.height
                    font.pointSize: ConfigView.tabBarFontSize
                    onClicked: {
                    }
                    background: Rectangle {
                        color: tab_bar_run_mode.currentIndex === 4 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_report
                            text: qsTr("Report")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_run_mode.currentIndex === 4 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }
                }

                TabButton {
                    height: parent.height
                    font.pointSize: ConfigView.tabBarFontSize
                    onClicked: {
                    }
                    background: Rectangle {
                        color: tab_bar_run_mode.currentIndex === 5 ? ConfigView.tabBarSelectedColor : ConfigView.tabBarUnselectedColor
                        
                        Text{
                            id:text_diagnostic
                            text: qsTr("Diagnostic")
                            font.family: ConfigView.fontFamily
                            color: tab_bar_run_mode.currentIndex === 5 ? ConfigView.tabBarSelectedTextColor : ConfigView.tabBarUnselectedTextColor
                            font.pixelSize: ConfigView.tabBarFontSize
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: contentWidth
                            height: contentHeight
                        }
                    }
                }

                onCurrentIndexChanged: {
                    job_management_view.tabSelected(tab_bar_run_mode.currentIndex === 1)

                    if(tab_bar_run_mode.currentIndex === 1){
                        // notify when tab manage recipe selected // уведомлять о выборе вкладки "управление рецептом"
                        tabControlVM.tabIndexChanged_Qml_Slots(2)
                    }

                }
            }

            Rectangle{
                id: appStatusBtn2
                width: parent.width*0.15
                height: parent.height
                color: ConfigView.isAppRunning ? ConfigView.acceptSignalColor : ConfigView.cancelSignalColor
                Text {
                    text: ConfigView.isAppRunning ? qsTr("Running") : qsTr("Stopped")
                    color: ConfigView.textColor
                    font.bold: true
                    font.pointSize: 14
                    font.family: ConfigView.fontFamily
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked: (mouse)=> {
                        if (mouse.button === Qt.LeftButton)
                           // ConfigView.isAppRunning = !ConfigView.isAppRunning
                           setoutVM.runStopStatus_Qml_Slot(!ConfigView.isAppRunning, set_out.getcurrentJobText())
                    }
                }
            }
        }

    }

    Rectangle{
        width: parent.width
        height: 3
        color: "#007ACC"
        anchors.top: headerBar.bottom
    }

    // tab setup mode layout // макет вкладки режима настройки
    StackLayout {
        width: parent.width
        height: parent.height - headerBar.height - bottom_bar.height - 10
        anchors.top: headerBar.bottom
        anchors.topMargin: 5
        anchors.bottom: bottom_bar.top
        currentIndex: tab_bar_setup_mode.currentIndex
        visible: ConfigView.appMode === 2

        // load main tab // загрузить главную вкладку
        MainHomeView {
            id: main_tab_content
            enabled: tabControlVM.isEnableMainTab
            opacity: enabled ? 1 : 0.5
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _homeModel: mainHomeVM
            _fontFamily: ConfigView.fontFamily

        }

        SystemSettingView {
            id: system_setting_view
            enabled: tabControlVM.isEnableSettingTab
            opacity: enabled ? 1 : 0.5
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _fontFamily: ConfigView.fontFamily
            _viewModel: systemSettingVM
        }

        // RecipeManagementView{
        //     id: recipe_management_view
        //     enabled: tabControlVM.isEnableMainTab
        //     opacity: enabled ? 1 : 0.5
        //     Layout.fillHeight: parent.height
        //     Layout.fillWidth: parent.width
        //     _fontFamily: ConfigView.fontFamily
        // }
        Item {
        }

        ReviewView{
            enabled: tabControlVM.isEnableMainTab
            opacity: enabled ? 1 : 0.5
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _fontFamily: ConfigView.fontFamily
            _viewModel: reviewVM
        }

        HistoryView {
            id: history_view
            enabled: tabControlVM.isEnableMainTab
            opacity: enabled ? 1 : 0.5
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _fontFamily: ConfigView.fontFamily
            _viewModel: historyVM
        }

        FeederAndPushersView {
            enabled: tabControlVM.isEnableMainTab
            opacity: enabled ? 1 : 0.5
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _fontFamily: ConfigView.fontFamily
            _viewModel: feederAndPushersVM
        }

        TableView {
            enabled: tabControlVM.isEnableMainTab
            opacity: enabled ? 1 : 0.5
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _fontFamily: ConfigView.fontFamily
            _viewModel: tableVM
        }

        CalibTableView {
            id: calibration_view
            enabled: tabControlVM.isEnableMainTab
            opacity: enabled ? 1 : 0.5
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _viewModel: calibTableVM
        }

        CorrectionView {
            enabled: tabControlVM.isEnableMainTab
            opacity: enabled ? 1 : 0.5
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _viewModel: correctionVM
        }


    }

    // tab run mode layout // макет вкладки режима запуска
    StackLayout {
        width: parent.width
        height: parent.height - headerBar.height - bottom_bar.height - 10
        anchors.top: headerBar.bottom
        anchors.topMargin: 5
        anchors.bottom: bottom_bar.top
        currentIndex: ConfigView.appMode === 1 ? tab_bar_run_mode.currentIndex : 0
        visible: ConfigView.appMode === 1

        SetoutView {
            id: set_out
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _homeModel: mainHomeVM
            _fontFamily: ConfigView.fontFamily
            _viewModel: setoutVM
        }

        RecipeManagementView{
            id: job_management_view
            enabled: tabControlVM.isEnableMainTab
            opacity: enabled ? 1 : 0.5
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _fontFamily: ConfigView.fontFamily
        }

        // ContainerView {
        //     Layout.fillHeight: parent.height
        //     Layout.fillWidth: parent.width
        //     _fontFamily: ConfigView.fontFamily
        //     _viewModel: containerVM
        // }

        SystemView {
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _fontFamily: ConfigView.fontFamily
            _viewModel: systemVM
        }

        ValidationView {
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _fontFamily: ConfigView.fontFamily
            _viewModel: validationVM
        }

        // LimitView {
        //     Layout.fillHeight: parent.height
        //     Layout.fillWidth: parent.width
        //     _fontFamily: ConfigView.fontFamily
        //     _viewModel: limitTabVM
        // }
        // DimensionView {
        // }
        ReportView {
            _viewModel: reportVM
        }

        DiagnosticView {
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _fontFamily: ConfigView.fontFamily
        }

    }

    Rectangle{
        width: parent.width
        height: 5
        anchors.bottom: parent.bottom
        color: "#222222"
    }

    // Bottom bar // нижняя панель
    BottomBar {
        id: bottom_bar
        width: parent.width
        height: parent.height*0.08
        anchors.bottom: parent.bottom
    }

    Popup {
        id: message_info
        DialogView{
            _viewModel: dialogVM
        }
    }

    Popup {
        id: login_dialog
        width: 700
        height: 500
        anchors.centerIn: parent
        modal: true
        focus: true
        closePolicy: Popup.CloseOnPressOutside
        contentItem: LoginView{
             id: login_window
             _width:parent.width
             _height:parent.height
             _fontFamily: ConfigView.fontFamily
        }
        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            border.color: "transparent"
            color: "red"
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#202020" }
                GradientStop { position: 0.5; color: "#2E2F30" }
                GradientStop { position: 1.0; color: "#494A4B" }
            }
        }
        Connections{
            target: login_window
            function onCloseLoginWindow(){
                login_dialog.close()
            }
        }
    }

    // document pdf dialog
    Popup {
        id: document_dialog
        width: 800
        height: 900
        modal: false
        closePolicy: Popup.CloseOnEscape
        focus: true

        contentItem: DocumentDlg {
            id: document_content
            titleDescription: ""
            anchors.fill: parent

            onMoveByTitleBar: {
                document_dialog.x += xPos
                document_dialog.y += yPos
            }
            onCloseDlg: {
                document_dialog.close()
            }
        }
    }


    InputPanel {
        id: inputPanel
        z: 99
        width: parent.width*0.5
        visible: Qt.inputMethod.visible
    }

    Connections{
        target: Qt.inputMethod
        function onVisibleChanged(){
            if(Qt.inputMethod.visible){
                console.log("show")
            }
            else{
                console.log("hide")
            }

            if (activeFocusItem) {
                if(keyboardOpenFirsttime)
                {
                    inputPanel.x = 0
                    inputPanel.y = 0
                    keyboardOpenFirsttime = false
                    return
                }

                var globalPos = activeFocusItem.mapToGlobal(0, 0);
                globalPos.x -= mainWindow.x
                globalPos.y -= mainWindow.y
                if(globalPos.x > mainWindow.width/2)
                {
                    inputPanel.x = 0
                }
                else
                {
                    inputPanel.x = mainWindow.width - inputPanel.width
                }

                if(globalPos.y > mainWindow.height/2)
                {
                    inputPanel.y = 0
                }
                else
                {
                    inputPanel.y = mainWindow.height - inputPanel.height
                }


                if(inputPanel.x > mainWindow.width - inputPanel.width){
                    inputPanel.x = mainWindow.width - inputPanel.width
                }
                else if(inputPanel.x < 0){
                    inputPanel.x = 0
                }
                if(inputPanel.y > mainWindow.height - inputPanel.height){
                    inputPanel.y = mainWindow.height - inputPanel.height
                }
                else if(inputPanel.y < 0){
                    inputPanel.y = 0
                }

            } else {
                console.log("No item is focused.");
            }

        }
    }


    Rectangle {
        width: parent.width
        height: parent.height - headerBar.height
        anchors.top: headerBar.bottom
        anchors.bottom: parent.bottom
        visible: ConfigView.appMode === 0

        Image {
            opacity: 0.4
            width: parent.width
            height: parent.height
            source: "Resources/LoginBG.png"
        }

        Rectangle {
            enabled: loginVM.accessLevel >= 1 // already login // уже вошел в систему
            opacity: enabled ? 1 : 0.5
            width: parent.width/2
            height: parent.height
            color: "transparent"
            ButtonMaterialTextHorizontal{
                width: parent.width*0.45
                height: width*0.35
                _size: height*0.8
                _text: qsTr("RUN MODE")
                _iconSourceOn: "run"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: ConfigView.fontFamily
                _textRatio: 0.15
                onClicked: {
                    ConfigView.appMode = 1
                    showMenuTab(false)
                }
            }
        }

        Rectangle {
            enabled: loginVM.accessLevel === 1 // admin // администратор
            opacity: enabled ? 1 : 0.5
            width: parent.width/2
            height: parent.height
            color: "transparent"
            anchors.right: parent.right
            ButtonMaterialTextHorizontal{
                width: parent.width*0.45
                height: width*0.35
                _size: height*0.8
                _text: qsTr("SETUP MODE")
                _iconSourceOn: "cog"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: ConfigView.fontFamily
                _textRatio: 0.15
                onClicked: {
                    ConfigView.appMode = 2
                    showMenuTab(false)
                }
            }
        }

    }

    Component.onCompleted:{
        login_dialog.open()
    }

    Connections{
        target: tabControlVM
        function onAppStatusBtnChanged_Signal(status){
            ConfigView.isAppRunning = status
            // setoutVM.runStopStatus_Qml_Slot(ConfigView.isAppRunning, set_out.getcurrentJobText())
        }
    }
}
