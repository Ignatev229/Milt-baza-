import QtQuick 2.1
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4 as QC14
import QtQuick.Controls.Styles 1.4 as QCS14
import ConfigView 1.0
import "MaterialDesign"


Item {
    property string _iconSourceOn: ""
    property string _iconSourceOff: ""
    property color _colorIconDefault : ConfigView.addLightBlueColor
    property color _colorIconMouseOver: ConfigView.addLightBlueColor
    property color _colorIconHigh : ConfigView.addLightBlueColor
    property color _backgroundColor: ConfigView.mainWhiteColor
    property color _boderColor: ConfigView.addLightBlueColor
    property color _textColor: ConfigView.mainBlueColor
    property int _fontSizeText: 12
    property string _fontFamily: "Segoe UI"
    property int _leftMagin: 5
    property int _width: 100
    property int _height: 30
    property int _radius: 5
    property string _text: ""
    property string _placeholderText: ""
    property int _size: _height
    property int _echoMode: TextInput.Normal;
    property RegExpValidator _reg;
    property var _inputMethodHints: Qt.ImhNone



    width: _width
    height: _height

    function getText(){
        return text_id.text
    }

    function setText(value){
        text_id.text = value
    }

    function setFocus(value){
        text_id.focus = value
    }

    MaterialDesignIcon {
        id: icon
        name: _iconSourceOn
        color: _colorIconDefault
        size: _size
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
    }
    Rectangle{
        anchors.left: icon.right
        anchors.leftMargin: parent.width*0.03
        anchors.verticalCenter: parent.verticalCenter
        implicitWidth: _width - _size - anchors.leftMargin
        implicitHeight: _height
        border.color: _boderColor
        border.width: 2
        radius: _radius
        color: _backgroundColor


        QC14.TextField{
            id: text_id
            text: _text
            horizontalAlignment: TextInput.AlignLeft
            verticalAlignment: TextInput.AlignVCenter
            font.pointSize: _fontSizeText
            font.family: _fontFamily
            textColor: _textColor
            height: parent.height
            width: parent.width
            echoMode: _echoMode
            validator: _reg
            placeholderText: _placeholderText
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            selectByMouse: true
            inputMethodHints: _inputMethodHints
            style: QCS14.TextFieldStyle {
                background: Rectangle {
                    border.color: _boderColor
                    color: _backgroundColor
                    radius: _radius
                }
            }
        }
    }
}
