import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "../Component"

import ConfigView 1.0

Item {
    id: login_window
    property int _width: 600
    property int _height: 500
    property int _fontSizeText: 10
    property color _textColor: ConfigView.textColor
    property string _fontFamily: ConfigView.fontFamily

    signal closeLoginWindow()

    function resetTextBox(){
        login_user_name.setText("")
        login_password.setText("")
        create_user_name.setText("")
        create_password.setText("")
        create_confirm_password.setText("")
    }
    width: _width
    height: _height

    anchors.fill: parent
    
    Rectangle{

        anchors.fill: parent
        anchors.centerIn: parent
        color: ConfigView.mainWhiteColor

        Column{

            width: parent.width
            height: parent.height
            spacing: 10

            
            Rectangle{
                id: header_layout
                width: parent.width*0.96
                height: parent.height*0.25
                color: "transparent"

                ButtonMaterial{
                    id: icon_id
                    visible: loginVM.accessLevel === 0
                    _width: parent.height
                    _height: parent.height
                    _size: _height*1.2
                    _iconSourceOn: loginVM.accessLevel === 0 ? "accountOff" : (loginVM.accessLevel === 1 ? "accountCog" : "accountSearch")
                    _colorBorder: " transparent"
                    _colorIconHigh: "transparent"
                    _colorIconDefault: loginVM.accessLevel === 0 ? ConfigView.addLightBlueColor : (loginVM.accessLevel === 1 ? ConfigView.cancelSignalColor : ConfigView.acceptSignalColor)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                }

                Image {
                    visible: !icon_id.visible
                    width: parent.height
                    height: parent.height
                    anchors.verticalCenter: parent.verticalCenter
                    source: loginVM.accessLevel === 1 ? "../../Resources/admin-icon.png" : (loginVM.accessLevel === 2 ? "../../Resources/engineer-icon.png" : "../../Resources/operator-icon.png")
                    fillMode: Image.PreserveAspectFit
                }

                Rectangle{
                    width: parent.width*0.65
                    height: parent.height
                    anchors.left: icon_id.right
                    anchors.leftMargin: parent.width*0.1
                    color: "transparent"

                    Rectangle{
                        color: "transparent"
                        width: parent.width
                        height: parent.height*0.35
                        anchors.top: parent.top
                        anchors.topMargin: parent.height*0.1
                        border.color: ConfigView.addLightBlueColor
                        border.width: 2
                        radius: 5
                        Text {
                            text: qsTr("Username") + ": "
                            width: parent.width*0.4
                            anchors.left: parent.left
                            anchors.leftMargin: parent.width*0.08
                            font.pointSize: _fontSizeText + 1
                            color: ConfigView.addLightBlueColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Text {
                            text: loginVM.username
                            width: parent.width*0.5
                            anchors.left: parent.left
                            anchors.leftMargin: parent.width*0.6
                            font.pointSize: _fontSizeText + 1
                            color: ConfigView.addLightBlueColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }


                    Rectangle{
                        color: "transparent"
                        width: parent.width
                        height: parent.height*0.35
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: parent.height*0.08
                        border.color: ConfigView.addLightBlueColor
                        border.width: 2
                        radius: 5
                        Text {
                            text: qsTr("Account Level") + ": "
                            width: parent.width*0.4
                            anchors.left: parent.left
                            anchors.leftMargin: parent.width*0.08
                            font.pointSize: _fontSizeText + 1
                            color: ConfigView.addLightBlueColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Text {
                            text: loginVM.accessLevel === 0 ? qsTr("None") : (loginVM.accessLevel === 1 ? qsTr("Administrator") : (loginVM.accessLevel === 2 ? qsTr("Engineer") : qsTr("Operator")))
                            width: parent.width*0.5
                            anchors.left: parent.left
                            anchors.leftMargin: parent.width*0.6
                            font.pointSize: _fontSizeText + 1
                            color: ConfigView.addLightBlueColor
                            font.family: _fontFamily
                            verticalAlignment: Text.AlignVCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                }

            }
            // Rectangle{
            //     id: info_layout
            //     width: parent.width*0.96
            //     height: parent.height*0.1
            //     color: "transparent"
            //     Text {
            //         text: loginVM.loginInfo
            //         width: parent.width
            //         height: parent.height
            //         anchors.horizontalCenter: parent.horizontalCenter
            //         font.pointSize: _fontSizeText + 1
            //         color: loginVM.loginInfoColor
            //         font.family: _fontFamily
            //         verticalAlignment: Text.AlignVCenter
            //         horizontalAlignment: Text.AlignHCenter
            //         anchors.verticalCenter: parent.verticalCenter
            //     }
            // }

            TabBar {
                id:tabBar
                width: parent.width*0.8
                anchors.horizontalCenter: parent.horizontalCenter

                contentHeight: 30
                TabButton {
                    height: parent.height

                    text: qsTr("Login")
                    onClicked: {
                        login_user_name.setText("")
                        login_user_name.setFocus(true)
                    }
                }

                TabButton {
                    height: parent.height
                    text: qsTr("Create")
                    visible: loginVM.isLogin
                    onClicked: {
                        create_user_name.setText("")
                        create_user_name.setFocus(true)

                    }
                }
            }


        }


        // tab layout
        StackLayout {
            width: parent.width
            height: parent.height*0.9 - tabBar.height - header_layout.height
            anchors.top: tabBar.bottom
            anchors.bottom: parent.bottom
            currentIndex: tabBar.currentIndex

            Item {
                Layout.fillHeight: parent.height
                Layout.fillWidth: parent.width

                Column{
                    width: parent.width*0.9
                    height: parent.height
                    anchors.centerIn: parent
                    spacing: parent.height*0.1

                    InputMaterialText{
                        id: login_user_name
                        _width: parent.width*0.8
                        _height: parent.height*0.15
                        _fontSizeText: _fontSizeText
                        anchors.horizontalCenter: parent.horizontalCenter
                        _text: ""
                        _placeholderText: qsTr("Username")
                        _iconSourceOn: "account"
                        focus: true
                    }


                    InputMaterialText{
                        id: login_password
                        _width: parent.width*0.8
                        _height: parent.height*0.15
                        _fontSizeText: _fontSizeText
                        anchors.horizontalCenter: parent.horizontalCenter
                        _text: ""
                        _placeholderText: qsTr("Password")
                        _iconSourceOn: "lock"
                        _echoMode: TextInput.Password
                    }

                    Rectangle{
                        width: parent.width*0.8
                        height: parent.height*0.3
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "transparent"
                        ButtonMaterialTextHorizontal{
                            width: parent.width*0.4
                            height: width*0.3
                            _size: height*0.8
                            _text: qsTr("Login")
                            _iconSourceOn: "login"
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: login_window._fontFamily
                            onClicked: {

                                loginVM.login_Slots(login_user_name.getText(), login_password.getText())
                            }
                        }

                        ButtonMaterialTextHorizontal{
                            width: parent.width*0.4
                            height: width*0.3
                            _size: height*0.8
                            _text: qsTr("Log Out")
                            _iconSourceOn: "logout"
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: login_window._fontFamily
                            onClicked: {
                                loginVM.logout_Slots()
                                loginVM.loginInfo = ""
                                resetTextBox()
                                closeLoginWindow()
                                ConfigView.appMode = 0
                            }
                        }
                    }


                }


            }


            // Create a RegExpValidator with a specific pattern
            RegExpValidator {
                id: regexValidatorLogin
                regExp: RegExp("[^\\s]*") // Disallow spaces
            }

            Item {
                Layout.fillHeight: parent.height
                Layout.fillWidth: parent.width
                Column{
                    width: parent.width*0.9
                    height: parent.height
                    anchors.centerIn: parent
                    spacing: parent.height*0.05

                    InputMaterialText{
                        id: create_user_name
                        _width: parent.width*0.8
                        _height: parent.height*0.12
                        _fontSizeText: _fontSizeText
                        anchors.horizontalCenter: parent.horizontalCenter
                        _text: ""
                        _placeholderText: qsTr("Username")
                        _iconSourceOn: "account"
                        _reg: regexValidatorLogin
                        focus: true
                    }

                    InputMaterialText{
                        id: create_password
                        _width: parent.width*0.8
                        _height: parent.height*0.12
                        _fontSizeText: _fontSizeText
                        anchors.horizontalCenter: parent.horizontalCenter
                        _text: ""
                        _placeholderText: qsTr("Password")
                        _iconSourceOn: "lock"
                        _echoMode: TextInput.Password
                        _reg: regexValidatorLogin
                    }

                    InputMaterialText{
                        id: create_confirm_password
                        _width: parent.width*0.8
                        _height: parent.height*0.12
                        _fontSizeText: _fontSizeText
                        anchors.horizontalCenter: parent.horizontalCenter
                        _text: ""
                        _placeholderText: qsTr("Confirm Password")
                        _iconSourceOn: "lock"
                        _echoMode: TextInput.Password
                        _reg: regexValidatorLogin
                    }

                    ComboBoxMaterialCustom{
                        id: access_level
                        ListModel {
                            id: access_level_model
                            ListElement { text: qsTr("Administrator") }
                            ListElement { text: qsTr("Engineer") }
                            ListElement { text: qsTr("Operator") }
                        }

                
                        _model: access_level_model
                        _icon: ConfigView.accessLevel_icon_model
                        width: parent.width*0.8
                        height: parent.height*0.15
                        _fontSize: _fontSizeText
                        _fontFamily: login_window._fontFamily
                        _size: parent.height*0.16
                        
                        anchors.horizontalCenter: parent.horizontalCenter
                    }


                    Rectangle{
                        width: parent.width*0.8
                        height: parent.height*0.15
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "transparent"
                        ButtonMaterialTextHorizontal{
                            width: parent.width*0.4
                            height: width*0.2
                            _size: height*0.8
                            _text: qsTr("Create")
                            _iconSourceOn: "accountPlus"
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            _fontFamily: login_window._fontFamily
                            onClicked: {

                                loginVM.createNewUser_Slots(create_user_name.getText(), create_password.getText(), create_confirm_password.getText(),
                                                            access_level.getIndex() + 1)
                                resetTextBox();
                            }
                        }

                    }


                }

            }
        }

    }


    Keys.onPressed: (event)=> {
            if (event.key === 16777220){
                console.log("Enter")
                loginVM.login_Slots(login_user_name.getText(), login_password.getText())
            }
            else if (event.key === 16777216){
                console.log("ESC")
                loginVM.loginInfo = ""
                resetTextBox()
                closeLoginWindow()
            }

        }
    onVisibleChanged: {
        if(visible === true){
            login_user_name.setText("")
            login_user_name.setFocus(true)
        }

    }

    Connections{
        target: loginVM
        function onCloseLoginDialog_Qml_Signals(){
            loginVM.loginInfo = ""
            resetTextBox()
            closeLoginWindow()
        }
    }

}
