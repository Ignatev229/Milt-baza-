import QtQuick 2.15
import QtQuick.Controls 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.Controls 1.4 as QtC1
import QtQuick.Controls.Styles 1.1

import ConfigView 1.0

import "../../View"
import "../../Component"

Item {
    id: dimension_view
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
    property int _numberColumn: 4
    property int _numberRow: 11
    property int _selectedRow: 1

    ListModel{
        id: job_info_model
        ListElement{
            idx: 1
            local: "Visota"
            custom: "Height"
            english: "Height"
        }
        ListElement{
            idx: 4
            local: "Ves"
            custom: "Width"
            english: "Width"
        }

        ListElement{
            idx: 12
            local: "Ukup.koltso"
            custom: "E"
            english: "E"
        }
        ListElement{
            idx: 11
            local: "Rezba"
            custom: "T"
            english: "T"
        }
        ListElement{
            idx: 21
            local: "Venchik"
            custom: "B"
            english: "B"
        }
        ListElement{
            idx: 13
            local: "Visota venchika"
            custom: "D"
            english: "D"
        }
        ListElement{
            idx: 20
            local: "Verh.shir"
            custom: "Ovlong1"
            english: "Ovlong1"
        }
        ListElement{
            idx: 19
            local: "Verh.uzkay"
            custom: "OvlShort1"
            english: "OvlShort1"
        }
        ListElement{
            idx: 3
            local: "Paralenost"
            custom: "Tilt"
            english: "Tilt"
        }
        ListElement{
            idx: 2
            local: "Perpendikulyamost"
            custom: "Lean"
            english: "Lean"
        }

    }

    QtObject{
        id: tableObjectID
        property int widthCell: (tableview.width)/(dimension_view._numberColumn) + dimension_view._borderSize
        property int heightCell: (tableview.height)/(dimension_view._numberRow)
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

        }

        QtC1.TableView {
            id: tableview
            height: parent.height*0.85
            width: parent.width*0.96
            anchors.horizontalCenter: parent.horizontalCenter
            clip: true
            alternatingRowColors: true
            model: job_info_model
            horizontalScrollBarPolicy: ScrollBar.AlwaysOff
            verticalScrollBarPolicy: ScrollBar.AlwaysOff
            backgroundVisible: false

            style: TableViewStyle{
                textColor: "white"
                alternateBackgroundColor: "#222222"
            }

            QtC1.TableViewColumn {
                role: "idx"
                title: qsTr("Id")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "local"
                title: qsTr("Local")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "custom"
                title: qsTr("Custom")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "english"
                title: qsTr("English")
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

                Text {
                    id: content_text
                    width: parent.width
                    height: parent.height
                    text: {
                        return styleData.value
                    }
                    font.bold: true
                    font.pointSize: _fontSize
                    anchors.centerIn : parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WrapAnywhere
                    color: _textColor
                }

            }

        }

    }



}
