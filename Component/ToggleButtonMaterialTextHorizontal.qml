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
    property color _colorBGDefault: ConfigView.addLightBlueColor
    property color _colorBGMouseOver: ConfigView.mainWhiteColor
    property color _colorBGHigh: ConfigView.mainBlueColor
    property color _colorIconDefault : "white"
    property color _colorIconMouseOver: "white"
    property color _colorIconHigh : ConfigView.mainBlueColor
    property color _colorBorder : ConfigView.mainBlueColor
    property color _colorText : "white"
    property string _text: ""
    property int _width: 90
    property int _height: 50
    property int _size: 30

    property double _textRatio: 0.17
    property bool _isClicked: false
    property int _radiusCorner: 10
    property color currentBGColor: _colorBGDefault
    property string _fontFamily: "Segoe UI"
    property int _numberStatus: 2
    property string _iconSelectedSource: "checkBold"
    property color _colorIconSelectedDefault : "orange"

    function setStatusSelected(status){
        icon_selected.visible = status
    }

    QtObject{
        id: internalButton
        property int _textFontSize: button.height*button._textRatio
    }

    width: _width
    height: _height

    function changeButtonStatus(value){
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
            color: button.hovered ? ConfigView.mainBlueColor : _colorText
            font.family: _fontFamily
            font.bold: true
            font.pixelSize: internalButton._textFontSize
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            width: contentWidth
            height: contentHeight
            anchors.left: icon.right
            anchors.leftMargin: button.width*0.01
            anchors.verticalCenter: parent.verticalCenter

        }

    }

    onClicked: {
        _isClicked = !_isClicked
        // if(_numberStatus == 3){
        //     icon_selected.visible = true
        // }
        currentBGColor = _isClicked ? _colorBGHigh : _colorBGDefault
    }

}

