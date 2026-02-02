import QtQuick 2.15

import ConfigView 1.0

import "../../../Component"

Item {
    id: input_param
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.textColor
    property int _fontSizeText: 12

    property string _name
    property int _columnSpacing
    property int _clumn1Width
    property int _clumn2Width
    property RegExpValidator _reg
    property var _cbbModel
    property string _placeholderText: ""
    property string _imageName: ""
    property int _imageHeight: 1
    property string _type: "double" //"double", "int", "bool", "seperator", "combobox"

    signal valueChanged_Signals(name: string, value: string)


    function getValue(){
        if(_type === "double")
            return double_input.getText()
        if(_type === "int")
            return int_input.getText()
        if(_type === "bool")
            return cbb.currentIndex === 0
        if(_type === "combobox")
            return cbb.currentIndex
    }

    function setValue(value){
        if(_type === "double")
            double_input.setText(value)
        if(_type === "int")
            int_input.setText(value)
        if(_type === "bool")
            cbb.currentIndex = value ? 0 : 1
        if(_type === "combobox")
            cbb.currentIndex = value
    }

    ListModel {
        id: shape_cbb_model
        ListElement { text: qsTr("Rectangle") }
        ListElement { text: qsTr("Square") }
        ListElement { text: qsTr("Oval") }
    }

    Row {
        width: parent.width
        height: parent.height
        spacing: _columnSpacing

        Text {
            text: _name
            width: _clumn1Width
            font.pointSize: _fontSizeText
            color: _textColor
            font.family: _fontFamily
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
        }

        Rectangle {
            width: _clumn2Width
            height: parent.height*0.8
            color: "transparent"
            visible: _type != "seperator"
            InputText{
                id: double_input
                visible: _type === "double"
                _width: parent.width
                _height: parent.height
                _fontSizeText: input_param._fontSizeText
                _text: ""
                _leftMagin: 0
                anchors.verticalCenter: parent.verticalCenter
                textHorizontalAlignment: TextInput.AlignLeft
                _reg: RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                _inputMethodHints: Qt.ImhFormattedNumbersOnly
                _placeholderText: input_param._placeholderText
            }

            InputText{
                id: int_input
                visible: _type === "int"
                _width: parent.width
                _height: parent.height
                _fontSizeText: input_param._fontSizeText
                _text: ""
                _leftMagin: 0
                anchors.verticalCenter: parent.verticalCenter
                textHorizontalAlignment: TextInput.AlignLeft
                _reg: RegExpValidator{
                    regExp: /^[0-9][0-9]{1}|23/
                }
                _inputMethodHints: Qt.ImhFormattedNumbersOnly
                _placeholderText: input_param._placeholderText
                onTextChanged_Signals: (value) => {
                    input_param.valueChanged_Signals(input_param._name, value)
                }
            }

            ComboBoxCustom{
                id: cbb
                visible: _type === "bool" || _type === "combobox"
                ListModel {
                    id: cbb_model
                    ListElement { text: qsTr("True") }
                    ListElement { text: qsTr("False") }
                }
                _model: _type === "bool" ? cbb_model : shape_cbb_model
                width: parent.width
                height: parent.height*1.2
                _fontSize: input_param._fontSizeText
                _fontFamily: input_param._fontFamily
                currentIndex: 0
                anchors.horizontalCenter: parent.horizontalCenter
                onCurrentTextChanged:{
                    input_param.valueChanged_Signals(input_param._name, currentText)
                }
            }

        }

        Rectangle {
            width: parent.width*0.5
            height: parent.height*input_param._imageHeight
            color: "transparent"
            Image {
                visible: _imageName !== ""
                // width: parent.width*0.5
                height: parent.height
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source: _imageName === "" ? _imageName : ("../../../Resources/"  + _imageName)
                fillMode: Image.PreserveAspectFit
            }
        }

    }
}
