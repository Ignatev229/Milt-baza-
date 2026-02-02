import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3


import ConfigView 1.0

import "../../Component/MaterialDesign"
import "../../Component"

Item {
    id: history_view_id
    width: parent.width
    height: parent.height
    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property int _fontSize: 12
    property color _textColor: ConfigView.mainBlueColor

    ListModel{
        id: menuItems
        ListElement{
            index: 0
            text: qsTr("Inspection Data")
            icon: "clipboardText"
        }
        ListElement{
            index: 1
            text: qsTr("Statistics")
            icon: "clipboardList"
        }
    }

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

    StackLayout {
        id: stack_layout
        width: parent.width - (contextMenu.visible ? contextMenu.width : 0)
        height: parent.height - open_menu_button.height
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        currentIndex: 0

        InspectionDataView {
            Layout.fillHeight: parent.height
            Layout.fillWidth: parent.width
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            _viewModel: history_view_id._viewModel
        }

        // EditRecipeView {
        //     id: edit_recipe_view
        //     Layout.fillHeight: parent.height
        //     Layout.fillWidth: parent.width

        // }


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
            font.family: history_view_id._fontFamily
            font.pointSize: history_view_id._fontSize + 2
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: parent.height*1.4
        }

        ButtonMaterialTextHorizontal{
            id: calendar_btn
            height: parent.height*0.9
            _size: height*0.8
            _text: qsTr("Calendar")
            _iconSourceOn: "calendarMonth"
            anchors.right: parent.right
            anchors.rightMargin: parent.width*0.03
            anchors.verticalCenter: parent.verticalCenter
            _fontFamily: history_view_id._fontFamily
            _textRatio: 0.4
            onClicked: {
                calendar_picker.visible = true
            }
        }

        Rectangle{
            id: history_view_border
            width: parent.width
            height: 1
            color: "#424242"
            opacity: 0.2
            anchors.topMargin: 5
            anchors.bottomMargin: 5
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
                    anchors.leftMargin: parent.height*1.1
                    color: history_view_id._textColor
                    font.family: history_view_id._fontFamily
                    font.pointSize: history_view_id._fontSize - 2
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                MaterialDesignIcon {
                    id: icon
                    name: model.icon
                    color: ConfigView.mainBlueColor
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


    CalendarPicker{
        id: calendar_picker
        width: parent.width*0.2
        height: width
        anchors.right: parent.right
        anchors.top: menu_layout.bottom
        visible: false
        onCalendarSelected_Signals: (startDate, endDate) => {
            console.log(startDate, endDate)
            calendar_picker.visible = false
            calendar_btn._text = startDate + " - " + endDate
            _viewModel.dateChanged_Qml_Slot(startDate, endDate)
        }
    }



}
