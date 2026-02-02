import QtQuick 2.14
import QtQuick.Controls 2.14
import QtGraphicalEffects 1.14

Button{
    id: btnTopBar
    property url _btnIconSource: "../../Resources/minimize_icon.svg"
    property color _btnColorDefault: "#1C1D20"
    property color _btnColorMouseOver: "#23272E"
    property color _btnColorClicked: "#007ACC"
    property color _btnColorOverlay: "#FFFFFF"
    property int _width: 35
    property int _height: 35
    QtObject{
        id: internal
        // Mouse over and click change color // Наведите курсор мыши и нажмите изменить цвет
        property var dynamicColor: if(btnTopBar.down){
            btnTopBar.down ? _btnColorClicked : _btnColorDefault
        } else{
            btnTopBar.hovered ? _btnColorMouseOver : _btnColorDefault
        }
    }
    width: _width
    height: _height

    background: Rectangle{
        id: bgBtn
        color: internal.dynamicColor
        anchors.fill: parent
        // radius: 5
        Image{
            id: iconBtn
            source: _btnIconSource
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            height: btnTopBar.height*0.7
            width: height
            visible: false
            fillMode: Image.PreserveAspectFit
            antialiasing: false
        }
        ColorOverlay{
            anchors.fill: iconBtn
            source: iconBtn
            color: _btnColorOverlay
            antialiasing: false
        }
    }
}
