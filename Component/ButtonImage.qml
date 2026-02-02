import QtQml 2.3
import QtQuick 2.1
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.2

import "MaterialDesign"
Button {

    id: button
    // CUSTOM PROPERTIES // ПОЛЬЗОВАТЕЛЬСКИЕ СВОЙСТВА
    property string _imageSourceOn: ""
    property string _imageSourceOff: ""
    property string _iconSourceOn: ""
    property string _iconSourceOff: ""
    property color _colorBGDefault: "transparent"
    property color _colorBGMouseOver: "transparent"
    property color _colorBGHigh: "transparent"
    property color _colorIconDefault : "white"
    property color _colorIconMouseOver: "#ED7D31"
    property color _colorIconHigh : "#90CAF9"
    property color _colorBorder : "#7F7F7F"
    property color _colorText : "white"
    property string _text: ""
    property int _width: 70
    property int _height: 70
    property int _size: 30

    property int _radiusCorner: 10

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

        Image {
            width: _size
            height: _size
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            source: button.down ? _imageSourceOn : _imageSourceOff == "" ? _imageSourceOn : _imageSourceOff
            fillMode: Image.PreserveAspectFit
        }

    }

}

