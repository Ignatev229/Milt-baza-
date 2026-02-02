import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3



import ConfigView 1.0

import "../../View"
import "../../Component/MaterialDesign"
import "../../Component"

Item {
    id: system_setting_view
    width: parent.width
    height: parent.height

    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.mainBlueColor
    property int _fontSize: 12


    function tabSelected (isSelected: bool){
        openMenuItem (isSelected && !open_menu_button._isClicked)
    }

    function openMenuItem (isOpen: bool){
        if(isOpen){
            contextMenu.x = 0
            contextMenu.y = open_menu_button.height
            contextMenu.open()
        }
        else{
            contextMenu.close()
        }
    }

    Rectangle{
        width: parent.width
        height: parent.height
        color: ConfigView.mainWhiteColor
    }

    ListModel{
        id: menuItems
        ListElement{
            index: 0
            text: qsTr("Restart")
            icon: ""
        }
        ListElement{
            index: 1
            text: qsTr("Config")
            icon: ""
        }
        ListElement{
            index: 2
            text: qsTr("Communication")
            icon: ""
        }
        ListElement{
            index: 3
            text: qsTr("Archive")
            icon: ""
        }
        ListElement{
            index: 4
            text: qsTr("Debug")
            icon: ""
        }
    }

    StackLayout {
        id: stack_layout
        width: parent.width - (contextMenu.visible ? contextMenu.width : 0)
        height: parent.height - open_menu_button.height
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        currentIndex: 0

        RestartView {
            _viewModel: system_setting_view._viewModel
        }

        ConfigCommunicationView {
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _viewModel: system_setting_view._viewModel
        }

        CommunicationView {
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _viewModel: system_setting_view._viewModel
        }

        ArchiveView {
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            _viewModel: system_setting_view._viewModel
        }
    }


    Rectangle {
        id: menu_layout
        height: parent.height * 0.06
        width: parent.width
        ToggleButtonMaterial{
            id: open_menu_button
            _height: parent.height
            _width: _height
            _size: _height*1.2
            _iconSourceOn: "menu"
            _iconSourceOff: "menuOpen"
            _colorBorder: " transparent"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: parent.height*0.27
            _isClicked: true
            onClicked: {
                if(!_isClicked)
                    openMenuItem(true)
                else
                    openMenuItem(false)
            }
        }

        Text {
            text: menuItems.get(stack_layout.currentIndex).text
            color: ConfigView.mainBlueColor
            font.family: _fontFamily
            font.pointSize: _fontSize + 2
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: parent.height*1.4
        }

        Rectangle{
            id: settings_view_border
            width: parent.width
            height: 1
            color: "#424242"
            opacity: 0.2
            anchors.topMargin: 5 
            anchors.top: parent.bottom
        }

    }
    

    Menu {
        id: contextMenu
        height: parent.height - open_menu_button.height
        enter: Transition {
            ParallelAnimation {
                NumberAnimation { property: "width"; from: 0.0; to: contextMenu.implicitWidth }
                // NumberAnimation { property: "height"; from: 0.0; to: contextMenu.implicitHeight }
            }
        }
        exit: Transition {
            ParallelAnimation {
                NumberAnimation { property: "width"; from: contextMenu.implicitWidth; to: 0.0 }
                // NumberAnimation { property: "height"; from: 0.0; to: contextMenu.implicitHeight }
            }

        }

        closePolicy: Popup.NoAutoClose
        Instantiator {
            model: menuItems
            MenuItem {
                // text: model.text
                Text {
                    text: qsTr(model.text)
                    anchors.left: parent.left
                    anchors.leftMargin: model.icon === "" ? parent.height*0.2 : parent.height*1.1
                    color: _textColor
                    font.family: _fontFamily
                    font.pointSize: _fontSize
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                MaterialDesignIcon {
                    id: icon
                    name: model.icon
                    color: ConfigView.textColor
                    size: parent.height*0.8
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }
                onTriggered: {
                    stack_layout.currentIndex = model.index
                    open_menu_button.changeButtonStatus(true)
                }
            }

            // The trick is on those two lines
            onObjectAdded: contextMenu.insertItem(index, object)
            onObjectRemoved: contextMenu.removeItem(object)
         }
    }




}
