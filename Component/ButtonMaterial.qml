import QtQml 2.3
import QtQuick 2.1
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.2
import ConfigView 1.0

import "MaterialDesign"
Button {

    id: button
    // CUSTOM PROPERTIES // ПОЛЬЗОВАТЕЛЬСКИЕ СВОЙСТВА
    property string _iconSourceOn: ""
    property string _iconSourceOff: ""
    property color _colorBGDefault: ConfigView.mainWhiteColor
    property color _colorBGMouseOver: ConfigView.mainBlueColor
    property color _colorBGHigh: "transparent"
    property color _colorIconDefault : ConfigView.mainBlueColor
    property color _colorIconMouseOver: ConfigView.mainWhiteColor
    property color _colorIconHigh : ConfigView.mainBlueColor
    property color _colorBorder : ConfigView.mainBlueColor
    property color _colorText : ConfigView.mainBlueColor
    property string _text: ""
    property int _width: 70
    property int _height: 70
    property int _size: 30
    property int _radiusCorner: 10
    property string _toolTip: ""

//    Timer {
//        id: timer
//        function setTimeout(cb, delayTime) {
//            timer.interval = delayTime;
//            timer.repeat = false;
//            timer.triggered.connect(cb);
//            timer.triggered.connect(function release () {
//                timer.triggered.disconnect(cb); // This is important
//                timer.triggered.disconnect(release); // This is important as well
//            });
//            timer.start();
//        }
//    }
    QtObject{
        id: internalButton
    }

    width: _width
    height: _height


    background: Rectangle{
        id: background
        color:  button.hovered ? _colorBGMouseOver : _colorBGDefault
        radius: _radiusCorner
        border.color: _colorBorder
        border.width: 2
        anchors.fill: parent
        anchors.verticalCenter: parent.verticalCenter

        // ToolTip.visible: rect.containsMouse // Show tooltip when the mouse is over the rectangle
        // ToolTip.text: _toolTip

        MaterialDesignIcon {
            id: icon
            name: button.down ? _iconSourceOn : _iconSourceOff == "" ? _iconSourceOn : _iconSourceOff
            color:{
                button.down ? _colorIconHigh : button.hovered ? _colorIconMouseOver : _colorIconDefault
            }
            size: _size
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

}

