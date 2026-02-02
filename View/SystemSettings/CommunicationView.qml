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

    Column {
        height: parent.height*0.9
        width: parent.width*0.9
        spacing: parent.height*0.1
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            width: parent.width*0.8
            height: parent.height*0.01
            color: "transparent"
        }

        GroupBox{
            width: parent.width
            height: parent.height*0.3
            anchors.verticalCenter: parent.verticalCenter
            background:Rectangle{
                color: "transparent"
                width: parent.width
                height: parent.height
                radius: 10
                border.width: 2
                border.color: "#7F7F7F"
            }

            label:Rectangle{
                color: ConfigView.addLightBlueColor
                radius: 10
                width: title1.contentWidth*1.1
                height: parent.height*0.2
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.bottom: parent.top
                anchors.bottomMargin: -height/2
                Text {
                    id: title1
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    verticalAlignment: Text.AlignVCenter
                    text: qsTr("IP Settings")
                    color: _textColor
                    font.bold: true
                    font.pointSize: _fontSize + 2
                    font.family: _fontFamily
                }
            }

            Column {
                width: parent.width*0.86
                height: parent.height*0.9
                spacing: parent.height*0.04
                property int textWidth: width*0.28
                property int inputTextWidth: width*0.7
                property int itemHeight: height*0.3
                anchors.centerIn: parent
                Row {
                    id: ip_address_layout
                    width: parent.width
                    height: parent.itemHeight
                    spacing: parent.width*0.02
                    enabled: false
                    opacity: enabled ? 1 : 0.5

                    Text {
                        text: qsTr("IP Address") + ": "
                        width: parent.parent.textWidth
                        font.pointSize: _fontSize
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }


                    InputText{
                        id: ip_address_text
                        _width: parent.parent.inputTextWidth
                        _height: parent.height
                        _fontSizeText: _fontSize
                        _text: _viewModel.ipAddress
                        _leftMagin: 0
                        anchors.verticalCenter: parent.verticalCenter
                        textHorizontalAlignment: TextInput.AlignLeft
                    }
                }

                Row {
                    visible: false
                    width: parent.width
                    height: parent.itemHeight
                    spacing: parent.width*0.02
                    Text {
                        text: qsTr("Subnet") + ": "
                        width: parent.parent.textWidth
                        font.pointSize: _fontSize
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    InputText{
                        id: subnet_text
                        _width: parent.parent.inputTextWidth
                        _height: parent.height
                        _fontSizeText: _fontSize
                        _text: _viewModel.subnet
                        _leftMagin: 0
                        anchors.verticalCenter: parent.verticalCenter
                        textHorizontalAlignment: TextInput.AlignLeft
                    }
                }

                Row {
                    visible: false
                    width: parent.width
                    height: parent.itemHeight
                    spacing: parent.width*0.02
                    Text {
                        text: qsTr("Gateway") + ": "
                        width: parent.parent.textWidth
                        font.pointSize: _fontSize
                        color: _textColor
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    InputText{
                        id: gateway_text
                        _width: parent.parent.inputTextWidth
                        _height: parent.height
                        _fontSizeText: _fontSize
                        _text: _viewModel.gateway
                        _leftMagin: 0
                        anchors.verticalCenter: parent.verticalCenter
                        textHorizontalAlignment: TextInput.AlignLeft
                    }
                }

                Row {
                    visible: false
                    width: parent.width
                    height: parent.itemHeight
                    spacing: parent.width*0.02

                    CheckBox {
                        id: use_dhcp
                        checked: _viewModel.useDHCP
                        text: qsTr("Use DHCP")
                        anchors.verticalCenter: parent.verticalCenter
                        scale: 1.25
                    }
                }

                Rectangle {
                    color: "transparent"
                    width: parent.width
                    height: parent.itemHeight/2
                }

                Row {
                    width: parent.width
                    height: parent.itemHeight*1.5
                    spacing: parent.width*0.2

                    ButtonMaterialTextHorizontal{
                        height: parent.height*0.9
                        width: parent.width*0.23
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
                            _viewModel.saveIPSetting_Qml_Slot(ip_address_text.getText(),
                                                              subnet_text.getText(),
                                                              gateway_text.getText(),
                                                              use_dhcp.checked)
                            ip_address_layout.enabled = false;
                        }
                    }

                    Rectangle {
                        height: parent.height*0.9
                        width: parent.width*0.14
                        color: "transparent"
                    }

                    ButtonMaterialTextHorizontal{
                        height: parent.height*0.9
                        width: parent.width*0.23
                        _size: height*0.8
                        _text: qsTr("Edit")
                        _iconSourceOn: "databaseEdit"
                        anchors.verticalCenter: parent.verticalCenter
                        _fontFamily: _fontFamily
                        _textRatio: 0.3
                        _colorIconDefault: ConfigView.mainBlueColor
                        _colorIconMouseOver: _colorIconDefault
                        onClicked: {
                            ip_address_layout.enabled = true;
                            ip_address_text.setText(_viewModel.ipAddress)
                            subnet_text.setText(_viewModel.subnet)
                            gateway_text.setText(_viewModel.gateway)
                            use_dhcp.checked = _viewModel.useDHCP
                        }
                    }
                }
            }
        }



    //     GroupBox{
    //         width: parent.width*0.8
    //         height: parent.height*0.2
    //         anchors.horizontalCenter: parent.horizontalCenter
    //         background:Rectangle{
    //             color: "transparent"
    //             width: parent.width
    //             height: parent.height
    //             radius: 10
    //             border.width: 2
    //             border.color: "#7F7F7F"
    //         }

    //         label:Rectangle{
    //             color: "#222222"
    //             width: title.contentWidth*1.1
    //             height: parent.height*0.06
    //             anchors.left: parent.left
    //             anchors.leftMargin: 10
    //             anchors.bottom: parent.top
    //             anchors.bottomMargin: -height/2
    //             Text {
    //                 id: title
    //                 height: parent.height
    //                 anchors.verticalCenter: parent.verticalCenter
    //                 anchors.left: parent.left
    //                 anchors.leftMargin: 10
    //                 verticalAlignment: Text.AlignVCenter
    //                 text: qsTr("Master Host")
    //                 color: layout._textColor
    //                 font.bold: true
    //                 font.pointSize: _fontSize + 2
    //                 font.family: _fontFamily
    //             }
    //         }

    //         Row {
    //             id: master_host_ratio_group
    //             width: parent.width*0.6
    //             height: parent.height*0.9
    //             spacing: parent.width*0.2
    //             anchors.centerIn: parent
    //             property int currentIndex: _viewModel.masterHost
    //             RadioButton {
    //                 checked: master_host_ratio_group.currentIndex == 0
    //                 text: qsTr("None")
    //                 anchors.verticalCenter: parent.verticalCenter
    //                 scale: 1.75
    //                 onClicked: {
    //                     master_host_ratio_group.currentIndex = 0
    //                 }
    //             }
    //             RadioButton {
    //                 checked: master_host_ratio_group.currentIndex == 1
    //                 text: qsTr("Serial")
    //                 anchors.verticalCenter: parent.verticalCenter
    //                 scale: 1.75
    //                 onClicked: {
    //                     master_host_ratio_group.currentIndex = 1
    //                 }
    //             }
    //             RadioButton {
    //                 checked: master_host_ratio_group.currentIndex == 2
    //                 text: qsTr("Network")
    //                 anchors.verticalCenter: parent.verticalCenter
    //                 scale: 1.75
    //                 onClicked: {
    //                     master_host_ratio_group.currentIndex = 2
    //                 }
    //             }
    //         }

    //     }

    //     Rectangle {
    //         width: parent.width*0.8
    //         height: parent.height*0.2
    //         anchors.horizontalCenter: parent.horizontalCenter
    //         color: "transparent"

    //         GroupBox{
    //             width: parent.width*0.3
    //             height: parent.height
    //             anchors.verticalCenter: parent.verticalCenter
    //             anchors.left: parent.left
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
    //                     text: qsTr("Serial")
    //                     color: layout._textColor
    //                     font.bold: true
    //                     font.pointSize: _fontSize + 2
    //                     font.family: _fontFamily
    //                 }
    //             }

    //             Rectangle {
    //                 width: parent.width
    //                 height: parent.height*0.9
    //                 anchors.centerIn: parent
    //                 color: "transparent"

    //                 CheckBox {
    //                     id: enable_serial
    //                     checked: _viewModel.enableSerial
    //                     text: qsTr("Enabled")
    //                     anchors.verticalCenter: parent.verticalCenter
    //                     anchors.horizontalCenter: parent.horizontalCenter
    //                     scale: 1.75
    //                 }

    //             }

    //         }

    //         GroupBox{
    //             width: parent.width*0.3
    //             height: parent.height
    //             anchors.verticalCenter: parent.verticalCenter
    //             anchors.right: parent.right
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
    //                 width: title2.contentWidth*1.1
    //                 height: parent.height*0.06
    //                 anchors.left: parent.left
    //                 anchors.leftMargin: 10
    //                 anchors.bottom: parent.top
    //                 anchors.bottomMargin: -height/2
    //                 Text {
    //                     id: title2
    //                     height: parent.height
    //                     anchors.verticalCenter: parent.verticalCenter
    //                     anchors.left: parent.left
    //                     anchors.leftMargin: 10
    //                     verticalAlignment: Text.AlignVCenter
    //                     text: qsTr("Network")
    //                     color: layout._textColor
    //                     font.bold: true
    //                     font.pointSize: _fontSize + 2
    //                     font.family: _fontFamily
    //                 }
    //             }

    //             Rectangle {
    //                 width: parent.width
    //                 height: parent.height*0.9
    //                 anchors.centerIn: parent
    //                 color: "transparent"

    //                 CheckBox {
    //                     id: enable_network
    //                     checked: _viewModel.enableNetwork
    //                     text: qsTr("Enabled")
    //                     anchors.verticalCenter: parent.verticalCenter
    //                     anchors.horizontalCenter: parent.horizontalCenter
    //                     scale: 1.75
    //                 }

    //             }

    //         }

    //     }

    //     Row {
    //         width: parent.width*0.8
    //         height: parent.height*0.2
    //         anchors.horizontalCenter: parent.horizontalCenter
    //         ButtonMaterialTextHorizontal{
    //             height: parent.height*0.6
    //             _size: height*0.8
    //             _text: qsTr("Save")
    //             _iconSourceOn: "contentSave"
    //             anchors.verticalCenter: parent.verticalCenter
    //             anchors.horizontalCenter: parent.horizontalCenter
    //             _fontFamily: _fontFamily
    //             _textRatio: 0.4
    //             _colorIconDefault: ConfigView.mainBlueColor
    //             _colorIconMouseOver: _colorIconDefault
    //             _colorIconHigh: ConfigView.mainBlueColor
    //             onClicked: {
    //                 _viewModel.saveCommunication_Qml_Slot(master_host_ratio_group.currentIndex,
    //                                                       enable_serial.checked,
    //                                                       enable_network.checked)
    //             }
    //         }
    //     }



    }


}
