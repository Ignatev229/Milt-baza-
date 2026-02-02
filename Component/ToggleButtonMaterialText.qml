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
    property color _colorBGMouseOver: ConfigView.mainWhiteColor
    property color _colorBGHigh: ConfigView.mainBlueColor
    property color _colorIconDefault : ConfigView.mainBlueColor
    property color _colorIconMouseOver: "white"
    property color _colorIconHigh : ConfigView.mainWhiteColor
    property color _colorBorder : ConfigView.mainBlueColor
    property color _colorText : ConfigView.mainBlueColor
    property color _colorTextHigh: ConfigView.mainWhiteColor
    property string _text: ""
    property int _width: 90
    property int _height: 50
    property int _size: 30

    property double _textRatio: 0.17
    property bool _isClicked: false
    property int _radiusCorner: 10
    property color currentTextColor: _colorText
    property color currentBGColor: _colorBGDefault
    property color currentIconColor: _colorIconDefault
    property string _fontFamily: "Segoe UI"


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
        property int _textFontSize: button.height*button._textRatio
    }

    width: _width
    height: _height

    function changeButtonStatus(){

        if (_isClicked){
            
            currentBGColor = _colorBGHigh
            currentIconColor = _colorIconHigh
            currentTextColor = _colorTextHigh
        }

        if (!_isClicked) {
            
            currentBGColor = _colorBGDefault
            currentIconColor = _colorIconDefault
            currentTextColor = _colorText
        }

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
            anchors.top: parent.top
            anchors.topMargin: button.height*0.05
            anchors.right: parent.right
            anchors.rightMargin: button.height*0.05
        }

        Text{
            id:text
            text: _text
            color: currentTextColor
            font.family: _fontFamily
            font.bold: true
            font.pixelSize: internalButton._textFontSize
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            width: contentWidth
            height: contentHeight
            anchors.bottom: parent.bottom
            anchors.bottomMargin: button.height*0.05
            anchors.left: parent.left
            anchors.leftMargin: button.height*0.05
        }

    }

    onClicked: {
        _isClicked = !_isClicked

        changeButtonStatus()
    }

}

