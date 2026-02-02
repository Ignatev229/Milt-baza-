import QtQuick 2.15
import QtQuick.Controls 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.Controls 1.4 as QtC1
import QtQuick.Controls.Styles 1.1
import QtQuick.Dialogs 1.3

import ConfigView 1.0

import "../../View"
import "../../Component"
import "../Dialog"

Item {

    id: validation_view
    width: parent.width
    height: parent.height

    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.textColor
    property color _backgroundColor: ConfigView.mainBlueColor
    property color _headerColor: ConfigView.addLightBlueColor
    property color _borderColor: ConfigView.mainBlueColor
    property int _borderSize: 1
    property int _fontSize: 12
    property int _numberColumn: 6
    property int _numberRow: 10
    property int _selectedRow: 1
    property int _bodyRNumber: 1

    QtObject{
        id: tableObjectID
        property int widthCell: (tableview.width)/(validation_view._numberColumn) + validation_view._borderSize
        property int heightCell: (tableview.height)/(validation_view._numberRow)
    }

    function clearData()
    {
        sectionedModel.clear();
    }

    function addData(data)
    {
        sectionedModel.append({
            "date": data.dateTime.value.split(" ")[0],
            "time": data.dateTime.value.split(" ")[1],
            "height": data.height.value + (data.height.isPass ? "" : "$"),

            "bodyR": data.bodyR.length > 0 ? data.bodyR[0].value + (data.bodyR[0].isPass ? "" : "$") : "",
            "body2R": data.bodyR.length > 1 ? data.bodyR[1].value + (data.bodyR[1].isPass ? "" : "$") : "",
            "body3R": data.bodyR.length > 2 ? data.bodyR[2].value + (data.bodyR[2].isPass ? "" : "$") : "",
            "body4R": data.bodyR.length > 3 ? data.bodyR[3].value + (data.bodyR[3].isPass ? "" : "$") : "",
            "body5R": data.bodyR.length > 4 ? data.bodyR[4].value + (data.bodyR[4].isPass ? "" : "$") : "",
            "body6R": data.bodyR.length > 5 ? data.bodyR[5].value + (data.bodyR[5].isPass ? "" : "$") : "",
            "body7R": data.bodyR.length > 6 ? data.bodyR[6].value + (data.bodyR[6].isPass ? "" : "$") : "",
            "body8R": data.bodyR.length > 7 ? data.bodyR[7].value + (data.bodyR[7].isPass ? "" : "$") : "",
            "body9R": data.bodyR.length > 8 ? data.bodyR[8].value + (data.bodyR[8].isPass ? "" : "$") : "",
            "body10R": data.bodyR.length > 9 ? data.bodyR[9].value + (data.bodyR[9].isPass ? "" : "$") : "",
            "body11R": data.bodyR.length > 10 ? data.bodyR[10].value + (data.bodyR[10].isPass ? "" : "$") : "",
            "body12R": data.bodyR.length > 11 ? data.bodyR[11].value + (data.bodyR[11].isPass ? "" : "$") : "",
            "body13R": data.bodyR.length > 12 ? data.bodyR[12].value + (data.bodyR[12].isPass ? "" : "$") : "",
            "body14R": data.bodyR.length > 13 ? data.bodyR[13].value + (data.bodyR[13].isPass ? "" : "$") : "",
            "body15R": data.bodyR.length > 14 ? data.bodyR[14].value + (data.bodyR[14].isPass ? "" : "$") : "",
            "body16R": data.bodyR.length > 15 ? data.bodyR[15].value + (data.bodyR[15].isPass ? "" : "$") : "",
            "body17R": data.bodyR.length > 16 ? data.bodyR[16].value + (data.bodyR[16].isPass ? "" : "$") : "",
            "body18R": data.bodyR.length > 17 ? data.bodyR[17].value + (data.bodyR[17].isPass ? "" : "$") : "",
            "body19R": data.bodyR.length > 18 ? data.bodyR[18].value + (data.bodyR[18].isPass ? "" : "$") : "",
            "body20R": data.bodyR.length > 19 ? data.bodyR[19].value + (data.bodyR[19].isPass ? "" : "$") : "",
            "body21R": data.bodyR.length > 20 ? data.bodyR[20].value + (data.bodyR[20].isPass ? "" : "$") : "",
            "body22R": data.bodyR.length > 21 ? data.bodyR[21].value + (data.bodyR[21].isPass ? "" : "$") : "",
            "body23R": data.bodyR.length > 22 ? data.bodyR[22].value + (data.bodyR[22].isPass ? "" : "$") : "",

        });
    }

    ListModel {
        id: sectionedModel
    }

    Column {
        height: parent.height
        width: parent.width
        spacing: parent.height*0.02
        Row {
            height: parent.height*0.08
            width: parent.width*0.96
            spacing: parent.width*0.03
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                text: qsTr("Job") + ": "
                width: parent.width*0.15
                font.pointSize: _fontSize + 2
                color: ConfigView.mainBlueColor
                font.family: _fontFamily
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter

            }

            Text {
                text: recipeManagementVM.currentRecipe
                width: parent.width*0.25
                font.pointSize: _fontSize + 2
                color: ConfigView.mainBlueColor
                font.family: _fontFamily
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            // Text {
            //     text: qsTr("Type") + ": "
            //     width: parent.width*0.1
            //     font.pointSize: _fontSize + 2
            //     color: "#90CAF9"
            //     font.family: _fontFamily
            //     font.bold: true
            //     verticalAlignment: Text.AlignVCenter
            //     anchors.verticalCenter: parent.verticalCenter

            // }

            // ComboBoxCustom{
            //     id: type_cbb
            //     ListModel {
            //         id: type_cbb_model
            //         ListElement { text: qsTr("Single") }
            //         ListElement { text: qsTr("Double") }
            //     }
            //     _model: type_cbb_model
            //     width: parent.width*0.1
            //     height: parent.height
            //     _fontSize: validation_view._fontSize
            //     _fontFamily: validation_view._fontFamily
            //     currentIndex: 0
            //     anchors.verticalCenter: parent.verticalCenter
            //     onCurrentTextChanged:{

            //     }
            // }

            ButtonMaterialTextHorizontal{
                height: parent.height*0.9
                _size: height*0.8
                _text: qsTr("Run")
                _iconSourceOn: "run"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: validation_view._fontFamily
                _textRatio: 0.4
                onClicked: {
                    if(recipeManagementVM.currentRecipe === "CalToolTest")
                    {
                        _viewModel.run_Qml_Slot()
                    }
                    else
                    {
                        message_dialog.openDialog(qsTr("Job not correct"),
                                                qsTr("Load the CalToolTest Job before starting validation"),
                                                StandardIcon.Warning, StandardButton.Yes)
                    }
                }
            }


        }

        Row {
            height: parent.height*0.08
            width: parent.width*0.96
            spacing: parent.width*0.03
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                text: qsTr("Last Validation") + ": "
                width: parent.width*0.15
                font.pointSize: _fontSize + 2
                color: ConfigView.mainBlueColor
                font.family: _fontFamily
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter

            }

            Text {
                text: _viewModel.lastValidationTime
                width: parent.width*0.25
                font.pointSize: _fontSize + 2
                color: ConfigView.mainBlueColor
                font.family: _fontFamily
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            // Text {
            //     text: qsTr("Number of times") + ": "
            //     width: parent.width*0.1
            //     font.pointSize: _fontSize + 2
            //     color: "#90CAF9"
            //     font.family: _fontFamily
            //     font.bold: true
            //     verticalAlignment: Text.AlignVCenter
            //     anchors.verticalCenter: parent.verticalCenter

            // }

            // InputText{
            //     id: number_of_times_text
            //     _width: parent.width*0.1
            //     _height: parent.height*0.8
            //     _fontSizeText: _fontSize
            //     _text: "1"
            //     _leftMagin: 0
            //     _reg: RegExpValidator{regExp: /\d+/}
            // }

        }


        QtC1.TableView {
            id: tableview
            height: parent.height*0.75
            width: parent.width*0.96
            anchors.horizontalCenter: parent.horizontalCenter
            clip: true
            alternatingRowColors: true
            model: sectionedModel
            backgroundVisible: false

            verticalScrollBarPolicy: Qt.ScrollBarAsNeeded
            horizontalScrollBarPolicy: Qt.AsNeeded
            flickableItem.flickableDirection : Flickable.HorizontalAndVerticalFlick
            flickableItem.boundsBehavior: Flickable.StopAtBounds


            style: TableViewStyle{
                textColor: "white"
                alternateBackgroundColor: "#222222"
            }

            QtC1.TableViewColumn {
                role: "date"
                title: qsTr("Date")
                width: tableObjectID.widthCell*2
                horizontalAlignment: Text.AlignHCenter
            }

            QtC1.TableViewColumn {
                role: "time"
                title: qsTr("Time")
                width: tableObjectID.widthCell*2
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "height"
                title: qsTr("Height")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 0
                role: "bodyR"
                title: qsTr("BodyR")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 1
                role: "body2R"
                title: qsTr("Body2R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 2
                role: "body3R"
                title: qsTr("Body3R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 3
                role: "body4R"
                title: qsTr("Body4R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 4
                role: "body5R"
                title: qsTr("Body5R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 5
                role: "body6R"
                title: qsTr("Body6R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 6
                role: "body7R"
                title: qsTr("Body7R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 7
                role: "body8R"
                title: qsTr("Body8R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 8
                role: "body9R"
                title: qsTr("Body9R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 9
                role: "body10R"
                title: qsTr("Body10R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 10
                role: "body11R"
                title: qsTr("Body11R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 11
                role: "body12R"
                title: qsTr("Body12R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 12
                role: "body13R"
                title: qsTr("Body13R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 13
                role: "body14R"
                title: qsTr("Body14R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 14
                role: "body15R"
                title: qsTr("Body15R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 15
                role: "body16R"
                title: qsTr("Body16R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 16
                role: "body17R"
                title: qsTr("Body17R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 17
                role: "body18R"
                title: qsTr("Body18R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 18
                role: "body19R"
                title: qsTr("Body19R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 19
                role: "body20R"
                title: qsTr("Body20R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 20
                role: "body21R"
                title: qsTr("Body21R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 21
                role: "body22R"
                title: qsTr("Body22R")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                visible: _bodyRNumber > 22
                role: "body23R"
                title: qsTr("Body23R")
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
                    if(styleData.value.indexOf("$") !== -1)
                        return "red"
                    return styleData.row %2 ? "#343434" : "#222222"
                }

                Text {
                    id: content_text
                    width: parent.width
                    height: parent.height
                    text: {
                        return styleData.value.replace("$", "")
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

    Connections{
        target: _viewModel


        function onAddInspectionData_Signal(data) {
            addData(data)
        }

        function onClearInspectionData_Signal(){
            clearData()
        }

        function onUpdateVisionParamNumber_Signal(bodyRNumber){
            _bodyRNumber = bodyRNumber
        }
    }

    DialogView {
        id: message_dialog
        onButtonClicked_Signal: (buttonType)=>{

            if(buttonType === StandardButton.Yes){
                _viewModel.run_Qml_Slot()
            }
            else if(buttonType === StandardButton.No){

            }
        }
    }

}
