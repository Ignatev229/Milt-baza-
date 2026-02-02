import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Styles 1.4

import "Component"
import "View/Dialog"

import ConfigView 1.0


Item{
    id: title_bar_root
    property string _nameTitleBar: qsTr("Bottle Inspection")
    property url _btnMaximizeRestore: ""
    property string _fontFamily: ConfigView.fontFamily
    QtObject{
        id: internalBar
    }

    width: parent.width
    height: parent.height
    Rectangle{
        id: titleBar
        height: parent.height
        color: ConfigView.mainBlueColor
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top



        Rectangle{
            id:iconApp
            width: 100
            color: ConfigView.mainBlueColor
            height: parent.height
            anchors.left: parent.left
            anchors.top: parent.top
        }

        // Label{
        //     id: labelApp
        //     color: "white"
        //     font.family: _fontFamily
        //     font.pointSize: height*0.24
        //     text: _nameTitleBar
        //     anchors.left: parent.left
        //     anchors.right: parent.right
        //     anchors.top: parent.top
        //     anchors.bottom: parent.bottom
        //     anchors.leftMargin: parent.width*0.067
        //     verticalAlignment: Text.AlignVCenter
        // }

        Row{
            width: parent.width*0.55
            height: parent.height
            anchors.left: iconApp.right
            anchors.leftMargin: parent.width*0.1
            spacing: parent.width*0.01

            ComboBoxMaterialCustom{
                id: language
                enabled: tabControlVM.isEnableMainTab
                _model: ConfigView.language_model
                _icon: ConfigView.language_icon_model
                width: parent.width*0.22
                height: parent.height
                _fontSize: height*0.3
                _size: parent.height*0.6
                _fontFamily: title_bar_root._fontFamily
                _textColor: ConfigView.mainWhiteColor
                _textPopupColor: ConfigView.mainBlueColor
                // _iconSourceOn: "translate"
                anchors.verticalCenter: parent.verticalCenter
                _colorIconDefault: enabled ? ConfigView.textColor : "#797979"
                _boderColor: "transparent"
                _backgroundColor: "transparent"
                onCurrentIndexChanged_Signal:(index) => {
                    ConfigView.setLanguage(index);
                    mainVM.switchLanguage(index);
                }
            }

            Rectangle{
                width: 3
                height: parent.height*0.8
                anchors.verticalCenter: parent.verticalCenter
                color: "#007ACC"
            }

            Text {
                text: qsTr("Job") + ": " + recipeManagementVM.currentRecipe
                width: contentWidth
                height: parent.height
                font.family: _fontFamily
                font.pointSize: height*0.22
                font.bold: true
                color: ConfigView.textColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle{
                width: 3
                height: parent.height*0.8
                anchors.verticalCenter: parent.verticalCenter
                color: "#007ACC"
            }

            Text {
                id: username_id
                text: qsTr("Username") + ": " + loginVM.username
                width: contentWidth
                height: parent.height
                font.family: _fontFamily
                font.pointSize: height*0.22
                font.bold: true
                color: ConfigView.textColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            ButtonMaterial{
                id: login_btn1
                visible: loginVM.accessLevel === 0
                _width: parent.height
                _height: parent.height
                _size: _height*1
                _iconSourceOn: loginVM.accessLevel === 0 ? "accountOff" : (loginVM.accessLevel === 1 ? "accountCog" : "accountSearch")
                _colorBorder: " transparent"
                _colorIconHigh: "#FFCE44"
                _colorIconDefault: loginVM.accessLevel === 0 ? ConfigView.textColor : (loginVM.accessLevel === 1 ? "#E43D30" : "#289948")
                _colorBGDefault: ConfigView.mainBlueColor
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    login_dialog.open()
                }
            }

            ButtonImage{
                id: login_btn2
                visible: !login_btn1.visible
                _width: parent.height
                _height: parent.height
                _size: _height*1
                _imageSourceOn: loginVM.accessLevel === 1 ? "../../Resources/admin-icon.png" : (loginVM.accessLevel === 2 ? "../../Resources/engineer-icon.png" : "../../Resources/operator-icon.png")
                _colorBorder: "transparent"
                _colorIconHigh: "#FFCE44"
                _colorIconDefault: loginVM.accessLevel === 0 ? ConfigView.textColor : (loginVM.accessLevel === 1 ? "#E43D30" : "#289948")
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    login_dialog.open()
                }
            }

            Rectangle{
                width: 3
                height: parent.height*0.8
                anchors.verticalCenter: parent.verticalCenter
                color: "#007ACC"
            }


            ButtonMaterialTextHorizontal{
                visible: ConfigView.appMode !== 0
                enabled: loginVM.accessLevel === 1
                width: parent.height*4
                height: parent.height*0.85
                _size: height*0.8
                _text: ConfigView.appMode === 1 ? qsTr("SETUP MODE") : qsTr("RUN MODE")
                _iconSourceOn: ConfigView.appMode === 1 ? "cog" : "run"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: ConfigView.fontFamily
                _textRatio: 0.35
                _colorBGHigh: "transparent"
                onClicked: {
                    ConfigView.appMode = ConfigView.appMode === 1 ? 2 : 1

                    tab_control_bar.showMenuTab(false)
                }
            }


            ButtonMaterial{
                id: app_help_btn
                _width: parent.height
                _height: parent.height
                _size: _height*1
                _iconSourceOn: "filePdfBox"
                _colorBGDefault: ConfigView.mainBlueColor
                _colorBorder: " transparent"
                _colorIconHigh: ConfigView.mainWhiteColor
                _colorIconDefault: _colorIconHigh
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    // document_content.fileName = "document.pdf"
                    // document_dialog.open()
                    masterApp.openDocumentFile_Qml_Slots("document.pdf");
                }
            }

            ButtonMaterial{
                id: operator_manual_help_btn
                _width: parent.height
                _height: parent.height
                _size: _height*1
                _iconSourceOn: "textBox"
                _colorBGDefault: ConfigView.mainBlueColor
                _colorBorder: " transparent"
                _colorIconHigh: ConfigView.mainWhiteColor
                _colorIconDefault: _colorIconHigh
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    // document_content.fileName = "Operator's Manual.pdf"
                    // document_dialog.open()
                    masterApp.openDocumentFile_Qml_Slots("Operator's Manual.pdf");
                }
            }

        }



        Row{
            id: rowBtns
            width: parent.height*5.1
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            TopBarButton{
                _height: parent.height
                _width: _height*1.7
                _btnColorDefault: titleBar.color
                _btnColorOverlay: "#C4C4C4"
                _btnColorClicked: titleBar.color
                _btnColorMouseOver: "#474748"
                _btnIconSource: "../Resources/minimize_icon.svg"
                onClicked:{
                    internalTabControlBar.minimized()
                }
            }
            TopBarButton{
                _height: parent.height
                _width: _height*1.7
                _btnColorDefault: titleBar.color
                _btnColorOverlay: "#C4C4C4"
                _btnColorClicked: titleBar.color
                _btnColorMouseOver: "#474748"
                _btnIconSource: _btnMaximizeRestore
                onClicked:{
                    internalTabControlBar.maximizeRestore()
                }
            }
            TopBarButton{
                _height: parent.height
                _width: _height*1.7
                _btnColorDefault: titleBar.color
                _btnColorOverlay: "#C4C4C4"
                _btnColorMouseOver: "#D71526"
                _btnIconSource: "../Resources/close_icon.svg"
                onClicked:{
                    internalTabControlBar.closeApp()
                }
            }
        }

    }



    Component.onCompleted: {
        language.setIndex(1); // default rusia
    }

}
