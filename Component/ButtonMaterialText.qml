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
    property color _colorBGMouseOver: ConfigView.mainBlueColor
    property color _colorBGHigh: "transparent"
    property color _colorIconDefault : ConfigView.mainBlueColor
    property color _colorIconMouseOver: ConfigView.mainWhiteColor
    property color _colorIconHigh : ConfigView.mainBlueColor
    property color _colorBorder : ConfigView.mainBlueColor
    property color _colorText : ConfigView.mainBlueColor
    property string _text: ""
    property int _width: 90
    property int _height: 50
    property int _size: 30
    property double _textRatio: 0.17
    property int _radiusCorner: 10
    property string _fontFamily: "Segoe UI"


    Timer {
        id: timer
        function setTimeout(cb, delayTime) {
            timer.interval = delayTime;
            timer.repeat = false;
            timer.triggered.connect(cb);
            timer.triggered.connect(function release () {
                timer.triggered.disconnect(cb); // This is important
                timer.triggered.disconnect(release); // This is important as well
            });
            timer.start();
        }
    }
    QtObject{
        id: internalButton
        property int _textFontSize: button.height*button._textRatio
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
        MaterialDesignIcon {
            id: icon
            name: button.down ? _iconSourceOn : _iconSourceOff == "" ? _iconSourceOn : _iconSourceOff
            color:{
                button.down ? _colorIconHigh : button.hovered ? ConfigView.mainWhiteColor : _colorIconDefault
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
            color: button.hovered ? ConfigView.mainWhiteColor : _colorText
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

        MouseArea{
            id: mouse_area
            anchors.fill: parent
            hoverEnabled: true
           onEntered: {
               if(timer.running)
                   return
               parent.color=_colorBGMouseOver
           }
           onExited: {
               if(timer.running)
                   return
               parent.color = _colorBGDefault
           }
            onClicked: {
                if(timer.running)
                    return
                button.clicked()
                parent.color = _colorBGHigh
                timer.setTimeout(function(){
                    parent.color =  _colorBGDefault;
                }, 400);

            }
        }
    }

}

