pragma Singleton
import QtQuick 2.15

Item {
    id: config_view
    // Enum
    enum MOUSE_ACTION { LEFT_CLICK, RIGHT_CLICK, LEFT_DOUBLE_CLICK, RIGHT_DOUBLE_CLICK }

    // Hard Model
    property ListModel language_model: ListModel {
        ListElement { text: qsTr("English")}
        ListElement { text: qsTr("Russia")}
    }

    property var language_icon_model: [
        "../Resources/united-kingdom.png",
        "../Resources/russia.png"
    ]

    property var accessLevel_icon_model: [
        "../Resources/admin-icon",
        "../Resources/engineer-icon.png",
        "../Resources/operator-icon.png"
    ]

    // general config:
    property color mainBlueColor: "#192864"
    property color mainWhiteColor: "#FFFFFF"

    property color addThinBlueColor: "#e3ecff"
    property color addLightBlueColor: "#4673d7"
    property color addDarkBlueColor: "#374ba5"
    property color addGrayColor: "#AAAAAA"

    property color acceptSignalColor: "#54e26d"
    property color cancelSignalColor: "#fa6464"
    property color warningSignalColor: "#ece88b"

    property double fontSizeScale: 0.6
    property string fontFamily: "Geologica Roman"
    property int tabBarFontSize: 24

    property color tabBarSelectedColor: mainBlueColor
    property color tabBarSelectedTextColor:mainWhiteColor 

    property color tabBarUnselectedColor: mainWhiteColor
    property color tabBarUnselectedTextColor: mainBlueColor
    
    property color textColor: mainWhiteColor

    property string currentDate: qsTr("")
    property string currentTime: qsTr("")
    property int currentDay: 0
    property var listDay: [qsTr("Sunday"), qsTr("Monday"), qsTr("Tuesday"), qsTr("Wednesday"), qsTr("Thursday"), qsTr("Friday"), qsTr("Saturday")]
    property string systemStartDateTime: Qt.formatDateTime(new Date(), "yyyy.MM.dd hh:mm:ss")

    // pixel ruler
    property bool isShowPixelRuler: false

    // app mode
    property int appMode: 0 // 0: no select (log out), 1: running mode. 2: setup mode

    // app running status
    property bool isAppRunning: false
    property bool isAutoMode: false


    // Language

    enum Language { ENGLISH, RUSSIA}
    property int language: 1

    function setLanguage(index: int){
        language = index
        mainVM.switchLanguage(language)
    }

}
