import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import QtQuick.Controls 1.4 as QtC1
import QtQuick.Controls.Styles 1.4 as QCS14
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Styles 1.1


import ConfigView 1.0

import "../../View"
import "../../Component"
import "../../View/Dialog"

Item {
    id: containers_view
    width: parent.width
    height: parent.height

    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.textColor
    property color _backgroundColor: "#333333"
    property color _headerColor: "#515151"
    property color _borderColor: "#424242"
    property int _borderSize: 1
    property int _fontSize: 12
    property int _numberColumn: 6
    property int _numberRow: 8
    property int _selectedRow: 1


    Component.onCompleted: {
        _viewModel.loadCompleted()
    }

    ListModel{
        id: job_info_model
  
    }

    QtObject{
        id: tableObjectID
        property int widthCell: (tableview.width)/(containers_view._numberColumn) + containers_view._borderSize
        property int heightCell: (tableview.height)/(containers_view._numberRow)
    }

    Connections {
        target: _viewModel
        function onAddData(index, item, height, weight, eMin, eMax, tMin, tMax)
        {
            if(index === 0) job_info_model.clear()

            job_info_model.append({
                "item": item,
                "height": height,
                "weight": weight,
                "eMin": eMin,
                "eMax": eMax,
                "tMin": tMin,
                "tMax": tMax
            })
        }
    }

    Column {
        height: parent.height
        width: parent.width
        spacing: parent.height*0.02
        Row {
            height: parent.height*0.1
            width: parent.width*0.96
            spacing: parent.width*0.03
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                text: qsTr("Job") + ": "
                width: parent.width*0.1
                font.pointSize: _fontSize + 2
                color: "#90CAF9"
                font.family: _fontFamily
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter

            }

            Text {
                text: recipeManagementVM.currentRecipe
                width: contentWidth
                font.pointSize: _fontSize + 2
                color: "#90CAF9"
                font.family: _fontFamily
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle {
                width: parent.width*0.1
                height: 1
                color: "transparent"
            }

            ButtonMaterialTextHorizontal{
                height: parent.height*0.8
                _size: height*0.8
                _text: qsTr("Save")
                _iconSourceOn: "contentSave"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: containers_view._fontFamily
                _textRatio: 0.4
                _colorIconDefault: ConfigView.acceptSignalColor
                _colorIconMouseOver: _colorIconDefault
                _colorIconHigh: ConfigView.acceptSignalColor
                onClicked: {
                    message_dialog.openDialog(qsTr("Save All Of Containers"),
                                              qsTr("Are you sure you want to save all of the containers?"),
                                              StandardIcon.Question, StandardButton.Yes | StandardButton.No)

                }
            }

        }

        QtC1.TableView {
            id: tableview
            height: parent.height*0.85
            width: parent.width*0.96
            anchors.horizontalCenter: parent.horizontalCenter
            clip: true
            alternatingRowColors: true
            model: job_info_model

            backgroundVisible: false

            verticalScrollBarPolicy: Qt.ScrollBarAsNeeded
            horizontalScrollBarPolicy: Qt.ScrollBarAsNeeded
            flickableItem.flickableDirection : Flickable.HorizontalAndVerticalFlick
            flickableItem.boundsBehavior: Flickable.StopAtBounds

            style: TableViewStyle{
                textColor: "white"
                alternateBackgroundColor: "#222222"
            }

            QtC1.TableViewColumn {
                role: "item"
                title: qsTr("")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "height"
                title: qsTr("Height")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "weight"
                title: qsTr("Weight")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "eMin"
                title: qsTr("E (min.)")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "eMax"
                title: qsTr("E (max.)")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "tMin"
                title: qsTr("T (min.)")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "tMax"
                title: qsTr("T (max.)")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }

            headerDelegate:Rectangle{
                color: _headerColor
                height: tableObjectID.heightCell
                border.width: _borderSize
                border.color: _borderColor
                Text{
                    anchors.centerIn : parent
                    text: styleData.value
                    color: _textColor
                    font.pointSize: _fontSize + 1
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

            }
            rowDelegate: Rectangle {
                height: tableObjectID.heightCell
            }

            itemDelegate: Rectangle {
                id: item_id
                height: tableObjectID.heightCell
                border.width: _borderSize
                border.color: _borderColor
                color:{
                    return styleData.row %2 ? "#343434" : "#222222"
                }

                // Text {
                //     id: content_text
                //     width: parent.width
                //     height: parent.height
                //     text: {
                //         return styleData.value
                //     }
                //     font.bold: true
                //     font.pointSize: _fontSize
                //     anchors.centerIn : parent
                //     horizontalAlignment: Text.AlignHCenter
                //     verticalAlignment: Text.AlignVCenter
                //     wrapMode: Text.WrapAnywhere
                //     color: _textColor
                // }

                QtC1.TextField{
                    id: content_text
                    width: parent.width
                    height: parent.height
                    text: {
                        return (styleData.role === "item" && styleData.row === 0) ? qsTr("Average") : styleData.value
                    }
                    font.bold: true
                    font.pointSize: _fontSize
                    font.family: _fontFamily

                    anchors.centerIn : parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    textColor: _textColor
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    echoMode: TextInput.Normal
                    validator: RegExpValidator { regExp : /[0-9]+\.[0-9]+/ }
                    style: QCS14.TextFieldStyle {
                        background: Rectangle {
                            color: "transparent"
                        }
                    }
                }
            }

        }

    }

    DialogView {
        id: message_dialog
        onButtonClicked_Signal: (buttonType)=>{
            if(buttonType === StandardButton.Yes){

                console.log(containers_view._viewModel.saveDataContainer());
                //main_home_view_id._viewModel.clearAllContainers_Qml_Slot()
                //initContainersModel()
            }
            else if(buttonType === StandardButton.No){

            }
        }
    }

}
