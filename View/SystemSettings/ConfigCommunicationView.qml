import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import ConfigView 1.0

import "../../View"
import "../../Component"

Item {
    id: layout
    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.textColor
    property int _fontSize: 12
    property int _radus: 10

    Column {
        height: parent.height*0.9
        width: parent.width*0.9
        spacing: parent.height*0.1
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        GroupBox{
            width: parent.width
            height: parent.height*0.2
            anchors.horizontalCenter: parent.horizontalCenter
            background:Rectangle{
                color: "transparent"
                width: parent.width
                height: parent.height
                radius: _radus
                border.width: 2
                border.color: "#7F7F7F"
            }

            label:Rectangle{
                color: ConfigView.addLightBlueColor
                width: title.contentWidth*1.1
                height: parent.height*0.2
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.bottom: parent.top
                anchors.bottomMargin: -height/2
                radius: _radus
                Text {
                    id: title
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("Machine Name")
                    color: _textColor
                    font.bold: true
                    font.pointSize: _fontSize + 2
                    font.family: _fontFamily
                }
            }

            Row {
                width: parent.width*0.96
                height: parent.height*0.9
                spacing: parent.width*0.04
                anchors.centerIn: parent

                InputText{
                    id: machine_name_text
                    enabled: false
                    opacity: enabled ? 1 : 0.5
                    _width: parent.width*0.56
                    _height: parent.height*0.6
                    _fontSizeText: _fontSize
                    _text: _viewModel.machineName
                    anchors.verticalCenter: parent.verticalCenter
                    _leftMagin: 0
                    textHorizontalAlignment: TextInput.AlignLeft
                }

                ButtonMaterialTextHorizontal{
                    id: machine_name_save_btn
                    enabled: false
                    opacity: enabled ? 1 : 0.5
                    height: parent.height*0.6
                    width: parent.width*0.18
                    _size: height*0.8
                    _text: qsTr("Save")
                    _iconSourceOn: "databaseExport"
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: _fontFamily
                    _textRatio: 0.3
                    _colorIconDefault: ConfigView.mainBlueColor
                    _colorIconMouseOver: _colorIconDefault
                    onClicked: {
                        _viewModel.saveMachineName_Qml_Slot(machine_name_text.getText())
                        machine_name_text.enabled = false;
                        machine_name_save_btn.enabled = false;

                    }
                }

                ButtonMaterialTextHorizontal{
                    height: machine_name_save_btn.height
                    width: machine_name_save_btn.width
                    _size: height*0.8
                    _text: qsTr("Edit")
                    _iconSourceOn: "databaseEdit"
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: _fontFamily
                    _textRatio: 0.3
                    _colorIconDefault: ConfigView.mainBlueColor
                    _colorIconMouseOver: _colorIconDefault
                    onClicked: {
                        // machine_name_text.setText(_viewModel.machineName)
                        machine_name_text.setText(_viewModel.machineName)
                        machine_name_text.enabled = true;
                        machine_name_save_btn.enabled = true
                    }
                }
            }

        }

        GroupBox{
            width: parent.width
            height: parent.height*0.2
            background:Rectangle{
                color: "transparent"
                width: parent.width
                height: parent.height
                radius: _radus
                border.width: 2
                border.color: "#7F7F7F"
            }

            label:Rectangle{
                color: ConfigView.addLightBlueColor
                width: title.contentWidth*1.1
                height: parent.height*0.2
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.bottom: parent.top
                anchors.bottomMargin: -height/2
                radius: _radus
                Text {
                    id: title2
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("Distance Units")
                    color: _textColor
                    font.bold: true
                    font.pointSize: _fontSize + 2
                    font.family: _fontFamily
                }
            }

            Row {
                width: parent.width*0.96
                height: parent.height*0.9
                spacing: parent.width*0.04
                anchors.centerIn: parent

                ComboBoxCustom{
                    id: distance_unit_cbb
                    ListModel {
                        id: distance_unit_cbb_model
                        ListElement { text: qsTr("Inches") }
                        ListElement { text: qsTr("mm") }
                        ListElement { text: qsTr("um") }
                    }
                    enabled: false
                    opacity: enabled ? 1 : 0.5
                    _model: distance_unit_cbb_model
                    width: machine_name_text.width
                    height: parent.height*0.65
                    _fontSize: layout._fontSize
                    _fontFamily: layout._fontFamily
                    currentIndex: _viewModel.distanceUnit
                    anchors.verticalCenter: parent.verticalCenter
                    onCurrentTextChanged:{

                    }
                }

                ButtonMaterialTextHorizontal{
                    id: distance_unit_save_btn
                    enabled: false
                    opacity: enabled ? 1 : 0.5
                    height: machine_name_save_btn.height
                    width: machine_name_save_btn.width
                    _size: height*0.8
                    _text: qsTr("Save")
                    _iconSourceOn: "databaseExport"
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: _fontFamily
                    _textRatio: 0.3
                    _colorIconDefault: ConfigView.mainBlueColor
                    _colorIconMouseOver: _colorIconDefault
                    _colorIconHigh: ConfigView.mainBlueColor
                    onClicked: {
                        _viewModel.saveDistanceUnit_Qml_Slot(distance_unit_cbb.currentIndex)
                        distance_unit_cbb.enabled = false;
                        distance_unit_save_btn.enabled = false;
                    }
                }

                ButtonMaterialTextHorizontal{
                    height: machine_name_save_btn.height
                    width: machine_name_save_btn.width
                    _size: height*0.8
                    _text: qsTr("Edit")
                    _iconSourceOn: "databaseEdit"
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: _fontFamily
                    _textRatio: 0.3
                    _colorIconDefault: ConfigView.mainBlueColor
                    _colorIconMouseOver: _colorIconDefault
                    onClicked: {
                        distance_unit_cbb.currentIndex = _viewModel.distanceUnit
                        distance_unit_cbb.enabled = true;
                        distance_unit_save_btn.enabled = true;
                    }
                }

            }
        }

        GroupBox{
            width: parent.width
            height: parent.height*0.2
            background:Rectangle{
                color: "transparent"
                width: parent.width
                height: parent.height
                radius: _radus
                border.width: 2
                border.color: "#7F7F7F"
            }

            label:Rectangle{
                color: ConfigView.addLightBlueColor
                width: title2.contentWidth*1.1
                height: parent.height*0.2
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.bottom: parent.top
                anchors.bottomMargin: -height/2
                radius: _radus
                Text {
                    id: title3
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("Weight Units")
                    color: _textColor
                    font.bold: true
                    font.pointSize: _fontSize + 2
                    font.family: _fontFamily
                }
            }

            Row {
                width: parent.width*0.96
                height: parent.height*0.9
                spacing: parent.width*0.04
                anchors.centerIn: parent

                ComboBoxCustom{
                    id: weight_unit_cbb
                    ListModel {
                        id: weight_unit_cbb_model
                        ListElement { text: qsTr("gams") }
                        ListElement { text: qsTr("kgams") }
                    }
                    enabled: false
                    opacity: enabled ? 1 : 0.5
                    _model: weight_unit_cbb_model
                    width: machine_name_text.width
                    height: parent.height*0.65
                    _fontSize: layout._fontSize
                    _fontFamily: layout._fontFamily
                    currentIndex: _viewModel.weightUnit
                    anchors.verticalCenter: parent.verticalCenter
                    onCurrentTextChanged:{

                    }
                }

                ButtonMaterialTextHorizontal{
                    id: weight_unit_save_btn
                    enabled: false
                    opacity: enabled ? 1 : 0.5
                    height: machine_name_save_btn.height
                    width: machine_name_save_btn.width
                    _size: height*0.8
                    _text: qsTr("Save")
                    _colorIconDefault: ConfigView.mainBlueColor
                    _colorIconMouseOver: _colorIconDefault
                    _colorIconHigh: ConfigView.mainBlueColor
                    _iconSourceOn: "databaseExport"
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: _fontFamily
                    _textRatio: 0.3
                    onClicked: {
                        _viewModel.saveWeightUnit_Qml_Slot(weight_unit_cbb.currentIndex)
                        weight_unit_cbb.enabled = false;
                        weight_unit_save_btn.enabled = false;
                    }
                }

                ButtonMaterialTextHorizontal{
                    height: machine_name_save_btn.height
                    width: machine_name_save_btn.width
                    _size: height*0.8
                    _text: qsTr("Edit")
                    _iconSourceOn: "databaseEdit"
                    anchors.verticalCenter: parent.verticalCenter
                    _fontFamily: _fontFamily
                    _textRatio: 0.3
                    _colorIconDefault: ConfigView.mainBlueColor
                    _colorIconMouseOver: _colorIconDefault
                    onClicked: {
                        weight_unit_cbb.currentIndex = _viewModel.weightUnit
                        weight_unit_cbb.enabled = true;
                        weight_unit_save_btn.enabled = true;
                    }
                }

            }
        }



    //     Row {
    //         width: parent.width
    //         height: parent.height*0.7
    //         anchors.horizontalCenter: parent.horizontalCenter
    //         spacing: parent.width*0.02
    //         GroupBox{
    //             width: parent.width*0.4
    //             height: parent.height
    //             anchors.verticalCenter: parent.verticalCenter
    //             background:Rectangle{
    //                 color: "transparent"
    //                 width: parent.width
    //                 height: parent.height
    //                 radius: 10
    //                 border.width: 2
    //                 border.color: "#7F7F7F"
    //             }

    //             label:Rectangle{
    //                 color: "#222222"
    //                 width: title1.contentWidth*1.1
    //                 height: parent.height*0.06
    //                 anchors.left: parent.left
    //                 anchors.leftMargin: 10
    //                 anchors.bottom: parent.top
    //                 anchors.bottomMargin: -height/2
    //                 Text {
    //                     id: title1
    //                     height: parent.height
    //                     anchors.verticalCenter: parent.verticalCenter
    //                     anchors.left: parent.left
    //                     anchors.leftMargin: 10
    //                     verticalAlignment: Text.AlignVCenter
    //                     text: qsTr("IP Settings")
    //                     color: _textColor
    //                     font.bold: true
    //                     font.pointSize: _fontSize + 2
    //                     font.family: _fontFamily
    //                 }
    //             }

    //             Column {
    //                 width: parent.width*0.86
    //                 height: parent.height*0.9
    //                 spacing: parent.height*0.04
    //                 property int textWidth: width*0.28
    //                 property int inputTextWidth: width*0.7
    //                 property int itemHeight: height*0.1
    //                 anchors.centerIn: parent
    //                 Row {
    //                     width: parent.width
    //                     height: parent.itemHeight
    //                     spacing: parent.width*0.02

    //                     Text {
    //                         text: qsTr("IP Address") + ": "
    //                         width: parent.parent.textWidth
    //                         font.pointSize: _fontSize
    //                         color: _textColor
    //                         font.family: _fontFamily
    //                         verticalAlignment: Text.AlignVCenter
    //                         anchors.verticalCenter: parent.verticalCenter
    //                     }


    //                     InputText{
    //                         id: ip_address_text
    //                         _width: parent.parent.inputTextWidth
    //                         _height: parent.height
    //                         _fontSizeText: _fontSize
    //                         _text: _viewModel.ipAddress
    //                         _leftMagin: 0
    //                         anchors.verticalCenter: parent.verticalCenter
    //                         textHorizontalAlignment: TextInput.AlignLeft
    //                     }
    //                 }

    //                 Row {
    //                     width: parent.width
    //                     height: parent.itemHeight
    //                     spacing: parent.width*0.02
    //                     Text {
    //                         text: qsTr("Subnet") + ": "
    //                         width: parent.parent.textWidth
    //                         font.pointSize: _fontSize
    //                         color: _textColor
    //                         font.family: _fontFamily
    //                         verticalAlignment: Text.AlignVCenter
    //                         anchors.verticalCenter: parent.verticalCenter
    //                     }
    //                     InputText{
    //                         id: subnet_text
    //                         _width: parent.parent.inputTextWidth
    //                         _height: parent.height
    //                         _fontSizeText: _fontSize
    //                         _text: _viewModel.subnet
    //                         _leftMagin: 0
    //                         anchors.verticalCenter: parent.verticalCenter
    //                         textHorizontalAlignment: TextInput.AlignLeft
    //                     }
    //                 }

    //                 Row {
    //                     width: parent.width
    //                     height: parent.itemHeight
    //                     spacing: parent.width*0.02
    //                     Text {
    //                         text: qsTr("Gateway") + ": "
    //                         width: parent.parent.textWidth
    //                         font.pointSize: _fontSize
    //                         color: _textColor
    //                         font.family: _fontFamily
    //                         verticalAlignment: Text.AlignVCenter
    //                         anchors.verticalCenter: parent.verticalCenter
    //                     }
    //                     InputText{
    //                         id: gateway_text
    //                         _width: parent.parent.inputTextWidth
    //                         _height: parent.height
    //                         _fontSizeText: _fontSize
    //                         _text: _viewModel.gateway
    //                         _leftMagin: 0
    //                         anchors.verticalCenter: parent.verticalCenter
    //                         textHorizontalAlignment: TextInput.AlignLeft
    //                     }
    //                 }

    //                 Row {
    //                     width: parent.width
    //                     height: parent.itemHeight
    //                     spacing: parent.width*0.02

    //                     CheckBox {
    //                         id: use_dhcp
    //                         checked: _viewModel.useDHCP
    //                         text: qsTr("Use DHCP")
    //                         anchors.verticalCenter: parent.verticalCenter
    //                         scale: 1.25
    //                     }
    //                 }

    //                 Rectangle {
    //                     color: "transparent"
    //                     width: parent.width
    //                     height: parent.itemHeight
    //                 }

    //                 Row {
    //                     width: parent.width
    //                     height: parent.itemHeight*2
    //                     spacing: parent.width*0.2

    //                     ButtonMaterialTextHorizontal{
    //                         height: parent.height*0.9
    //                         width: parent.width*0.4
    //                         _size: height*0.8
    //                         _text: qsTr("Save")
    //                         _iconSourceOn: "databaseExport"
    //                         anchors.verticalCenter: parent.verticalCenter
    //                         _fontFamily: _fontFamily
    //                         _textRatio: 0.3
    //                         _colorIconDefault: ConfigView.mainBlueColor
    //                         _colorIconMouseOver: _colorIconDefault
    //                         _colorIconHigh: ConfigView.mainBlueColor
    //                         onClicked: {
    //                             _viewModel.saveIPSetting_Qml_Slot(ip_address_text.getText(),
    //                                                               subnet_text.getText(),
    //                                                               gateway_text.getText(),
    //                                                               use_dhcp.checked)
    //                         }
    //                     }


    //                     ButtonMaterialTextHorizontal{
    //                         height: parent.height*0.9
    //                         width: parent.width*0.4
    //                         _size: height*0.8
    //                         _text: qsTr("Cancel")
    //                         _iconSourceOn: "databaseExport"
    //                         anchors.verticalCenter: parent.verticalCenter
    //                         _fontFamily: _fontFamily
    //                         _textRatio: 0.3
    //                         _colorIconDefault: ConfigView.mainBlueColor
    //                         _colorIconMouseOver: _colorIconDefault
    //                         _colorIconHigh: ConfigView.mainBlueColor
    //                         onClicked: {
    //                             ip_address_text.setText(_viewModel.ipAddress)
    //                             subnet_text.setText(_viewModel.subnet)
    //                             gateway_text.setText(_viewModel.gateway)
    //                             use_dhcp.checked = _viewModel.useDHCP

    //                         }
    //                     }

    //                 }
    //             }
    //         }


    //         Column{
    //             width: parent.width*0.58
    //             height: parent.height
    //             anchors.verticalCenter: parent.verticalCenter
    //             spacing: parent.height*0.04

    //             GroupBox{
    //                 width: parent.width
    //                 height: parent.height*0.3
    //                 background:Rectangle{
    //                     color: "transparent"
    //                     width: parent.width
    //                     height: parent.height
    //                     radius: 10
    //                     border.width: 2
    //                     border.color: "#7F7F7F"
    //                 }

    //                 label:Rectangle{
    //                     color: "#222222"
    //                     width: title2.contentWidth*1.1
    //                     height: parent.height*0.06
    //                     anchors.left: parent.left
    //                     anchors.leftMargin: 10
    //                     anchors.bottom: parent.top
    //                     anchors.bottomMargin: -height/2
    //                     Text {
    //                         id: title2
    //                         height: parent.height
    //                         anchors.verticalCenter: parent.verticalCenter
    //                         anchors.left: parent.left
    //                         anchors.leftMargin: 10
    //                         verticalAlignment: Text.AlignVCenter
    //                         text: qsTr("Distance Units")
    //                         color: _textColor
    //                         font.bold: true
    //                         font.pointSize: _fontSize + 2
    //                         font.family: _fontFamily
    //                     }
    //                 }

    //                 Row {
    //                     width: parent.width*0.86
    //                     height: parent.height*0.6
    //                     spacing: parent.width*0.04
    //                     anchors.centerIn: parent

    //                     ComboBoxCustom{
    //                         id: distance_unit_cbb
    //                         ListModel {
    //                             id: distance_unit_cbb_model
    //                             ListElement { text: qsTr("Inches") }
    //                             ListElement { text: qsTr("mm") }
    //                             ListElement { text: qsTr("um") }
    //                         }
    //                         _model: distance_unit_cbb_model
    //                         width: parent.width*0.73
    //                         height: parent.height
    //                         _fontSize: layout._fontSize
    //                         _fontFamily: layout._fontFamily
    //                         currentIndex: _viewModel.distanceUnit
    //                         anchors.verticalCenter: parent.verticalCenter
    //                         onCurrentTextChanged:{

    //                         }
    //                     }

    //                     ButtonMaterialTextHorizontal{
    //                         height: parent.height*0.9
    //                         width: parent.width*0.23
    //                         _size: height*0.8
    //                         _text: qsTr("Save")
    //                         _iconSourceOn: "databaseExport"
    //                         anchors.verticalCenter: parent.verticalCenter
    //                         _fontFamily: _fontFamily
    //                         _textRatio: 0.3
    //                         _colorIconDefault: ConfigView.mainBlueColor
    //                         _colorIconMouseOver: _colorIconDefault
    //                         _colorIconHigh: ConfigView.mainBlueColor
    //                         onClicked: {
    //                             _viewModel.saveDistanceUnit_Qml_Slot(distance_unit_cbb.currentIndex)
    //                         }
    //                     }

    //                 }
    //             }

    //             GroupBox{
    //                 width: parent.width
    //                 height: parent.height*0.3
    //                 background:Rectangle{
    //                     color: "transparent"
    //                     width: parent.width
    //                     height: parent.height
    //                     radius: 10
    //                     border.width: 2
    //                     border.color: "#7F7F7F"
    //                 }

    //                 label:Rectangle{
    //                     color: "#222222"
    //                     width: title3.contentWidth*1.1
    //                     height: parent.height*0.06
    //                     anchors.left: parent.left
    //                     anchors.leftMargin: 10
    //                     anchors.bottom: parent.top
    //                     anchors.bottomMargin: -height/2
    //                     Text {
    //                         id: title3
    //                         height: parent.height
    //                         anchors.verticalCenter: parent.verticalCenter
    //                         anchors.left: parent.left
    //                         anchors.leftMargin: 10
    //                         verticalAlignment: Text.AlignVCenter
    //                         text: qsTr("Weight Units")
    //                         color: _textColor
    //                         font.bold: true
    //                         font.pointSize: _fontSize + 2
    //                         font.family: _fontFamily
    //                     }
    //                 }

    //                 Row {
    //                     width: parent.width*0.86
    //                     height: parent.height*0.6
    //                     spacing: parent.width*0.04
    //                     anchors.centerIn: parent

    //                     ComboBoxCustom{
    //                         id: weight_unit_cbb
    //                         ListModel {
    //                             id: weight_unit_cbb_model
    //                             ListElement { text: qsTr("gams") }
    //                             ListElement { text: qsTr("kgams") }
    //                         }
    //                         _model: weight_unit_cbb_model
    //                         width: parent.width*0.73
    //                         height: parent.height
    //                         _fontSize: layout._fontSize
    //                         _fontFamily: layout._fontFamily
    //                         currentIndex: _viewModel.weightUnit
    //                         anchors.verticalCenter: parent.verticalCenter
    //                         onCurrentTextChanged:{

    //                         }
    //                     }

    //                     ButtonMaterialTextHorizontal{
    //                         height: parent.height*0.9
    //                         width: parent.width*0.23
    //                         _size: height*0.8
    //                         _text: qsTr("Save")
    //                         _colorIconDefault: ConfigView.mainBlueColor
    //                         _colorIconMouseOver: _colorIconDefault
    //                         _colorIconHigh: ConfigView.mainBlueColor
    //                         _iconSourceOn: "databaseExport"
    //                         anchors.verticalCenter: parent.verticalCenter
    //                         _fontFamily: _fontFamily
    //                         _textRatio: 0.3
    //                         onClicked: {
    //                             _viewModel.saveWeightUnit_Qml_Slot(weight_unit_cbb.currentIndex)
    //                         }
    //                     }

    //                 }
    //             }


    //         }



    //     }


    }



}
