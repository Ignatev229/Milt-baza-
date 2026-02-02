import QtQuick 2.1
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4 as QC14
import QtQuick.Controls.Styles 1.4 as QCS14
import ConfigView 1.0

Item {
    id: input_text
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
    property RegExpValidator _reg;
    property var textHorizontalAlignment: TextInput.AlignHCenter
    property bool _readOnly: false
    property var _inputMethodHints: Qt.ImhNone
    signal textChanged_Signals(value: string)

    width: _width
    height: _height

    function getText(){
        return text_id.text
    }

    function setText(value){
        text_id.text = value
    }

    Rectangle{
        anchors.left: parent.left
        anchors.leftMargin: _leftMagin
        anchors.verticalCenter: parent.verticalCenter
        implicitWidth: _width
        implicitHeight: _height
        border.color: _boderColor
        border.width: 2
        radius: _radius
        color: _backgroundColor

        QC14.TextField{
            id: text_id
            text: _text
            readOnly: _readOnly
            horizontalAlignment: textHorizontalAlignment
            font.pointSize: _fontSizeText
            font.family: _fontFamily
            verticalAlignment: TextInput.AlignVCenter
            textColor: _textColor
            height: parent.height
            width: parent.width
            echoMode: TextInput.Normal
            validator: _reg
            placeholderText: _placeholderText
            inputMethodHints: _inputMethodHints
            style: QCS14.TextFieldStyle {
                background: Rectangle {
                    border.color: _boderColor
                    color: _backgroundColor
                    radius: _radius
                }
            }
            onTextChanged: {
                input_text.textChanged_Signals(text)
            }
        }
    }
}
