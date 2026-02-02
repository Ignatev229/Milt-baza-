import QtQml 2.3
import QtQuick 2.1
import QtQuick.Controls 2.1
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.2

import "MaterialDesign"

import ConfigView 1.0

Button {

    id: button
    // CUSTOM PROPERTIES // ПОЛЬЗОВАТЕЛЬСКИЕ СВОЙСТВА
    property string _iconSourceOn: ""
    property string _iconSourceOff: ""
    property color _colorBGDefault: ConfigView.addLightBlueColor
    property color _colorBGMouseOver: ConfigView.mainWhiteColor
    property color _colorBGHigh: ConfigView.mainBlueColor
    
    property color _colorIconDefault : ConfigView.mainBlueColor
    property color _colorIconHigh : ConfigView.mainWhiteColor
    property color _colorIconMouseOver: "white"
    

    property color _colorTextDefault : ConfigView.mainWhiteColor
    property color _colorTextMouseOver: ConfigView.mainBlueColor
    property color _colorTextHigh : ConfigView.mainWhiteColor
    
    property color _colorBorder : ConfigView.mainBlueColor
    property string _text: ""
    property int _width: 90
    property int _height: 50
    property int _size: 30
    property double _textRatio: 0.35
    property int _radiusCorner: 10
    property string _fontFamily: "Segoe UI"
    property int _borderWidth: 2
    property int _numberStatus: 2
    property string _iconSelectedSource: "checkBold"
    property color _colorIconSelectedDefault : "orange"


    function setStatusSelected(status){
        icon_selected.visible = status
    }

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


    width: text.contentWidth + _size*3
    height: _height


    background: Rectangle{
        id: background
        color:  button.hovered ? _colorBGMouseOver : _colorBGDefault
        radius: _radiusCorner
        border.color: _colorBorder
        border.width: _borderWidth
        anchors.fill: parent
        anchors.verticalCenter: parent.verticalCenter
        MaterialDesignIcon {
            id: icon
            name: button.down ? _iconSourceOn : _iconSourceOff == "" ? _iconSourceOn : _iconSourceOff
            color:{
                button.down ? _colorIconHigh : _colorIconDefault
            }
            size: _size
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.01
            anchors.verticalCenter: parent.verticalCenter
        }

        MaterialDesignIcon {
            id: icon_selected
            visible: false
            name: _iconSelectedSource
            color: _colorIconSelectedDefault
            size: _size
            anchors.right: parent.right
            anchors.rightMargin: parent.width*0.01
            anchors.verticalCenter: parent.verticalCenter
        }

        Text{
            id:text
            text: _text
            color: button.hovered ?  _colorTextMouseOver : _colorTextDefault
            font.family: _fontFamily
            font.bold: true
            font.pixelSize: internalButton._textFontSize
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            width: contentWidth
            height: contentHeight
            anchors.left: icon.right
            anchors.leftMargin: button.width*0.08
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
                    parent.color =  _colorBGMouseOver;
                    // if(_numberStatus == 3){
                    //     icon_selected.visible = true
                    // }
                }, 100);

            }
        }
    }

}

