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
    property color _colorBGDefault: "transparent"
    property color _colorBGMouseOver: "transparent"
    property color _colorBGHigh: "transparent"
    property color _colorIconDefault : ConfigView.mainBlueColor
    property color _colorIconMouseOver: "#ED7D31"
    property color _colorIconHigh : ConfigView.mainBlueColor
    property color _colorBorder : ConfigView.mainBlueColor
    property color _colorText : "white"
    property int _width: 70
    property int _height: 70
    property int _size: 30

    property bool _isClicked: false
    property int _radiusCorner: 10
    property color currentBGColor: _colorBGDefault

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

    function changeButtonStatus(value){
        if(_isClicked === value)
            return
        _isClicked = value
        currentBGColor = _isClicked ? _colorBGHigh : _colorBGDefault
    }


    background: Rectangle{
        id: background
        color:  button.hovered ? _colorBGMouseOver : currentBGColor
        radius: _radiusCorner
        border.color: _colorBorder
        border.width: 2
        anchors.fill: parent
        anchors.verticalCenter: parent.verticalCenter
        MaterialDesignIcon {
            id: icon
            name: _isClicked ? _iconSourceOn : _iconSourceOff == "" ? _iconSourceOn : _iconSourceOff
            color:{
                button.down ? _colorIconMouseOver : (_isClicked ? _colorIconHigh : _colorIconDefault)
            }
            size: _size
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    onClicked: {
        _isClicked = !_isClicked
        currentBGColor = _isClicked ? _colorBGHigh : _colorBGDefault
    }

}

