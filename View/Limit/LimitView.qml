import QtQuick 2.15
import QtQuick.Controls 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.Controls 1.4 as QtC1
import QtQuick.Controls.Styles 1.1

import ConfigView 1.0

import "../../View"
import "../../Component"

Item {
    id: limit_view
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
    property int _numberColumn: 7
    property int _numberRow: 14
    property int _selectedRow: 1


    QtObject{
        id: tableObjectID
        property int widthCell: (tableview.width)/(limit_view._numberColumn) + limit_view._borderSize
        property int heightCell: (tableview.height)/(limit_view._numberRow)
    }

    Column {
        height: parent.height
        width: parent.width
        spacing: parent.height*0.02


        Row {
            id: rowInformation
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



            // Save button
            ButtonMaterialTextHorizontal{
                height: parent.height*0.8
                _size: height*0.8
                _text: qsTr("Save")
                _iconSourceOn: "contentSave"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: limit_view._fontFamily
                _textRatio: 0.4
                _colorIconDefault: ConfigView.acceptSignalColor
                _colorIconMouseOver: _colorIconDefault
                _colorIconHigh: ConfigView.acceptSignalColor
                onClicked: {
                    _viewModel.saveDataTableSlot()
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
            model: _viewModel.tableDataModel
            horizontalScrollBarPolicy: ScrollBar.AlwaysOff
            verticalScrollBarPolicy: ScrollBar.AlwaysOff
            backgroundVisible: true

            style: TableViewStyle{
                textColor: "white"
                alternateBackgroundColor: "#222222"
            }

            QtC1.TableViewColumn {
                role: "name"
                title: qsTr("Name")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter

                delegate: ItemDelegate {
                    contentItem:  Rectangle {
                        color: styleData.row %2 ? "#343434" : "#222222"
                        anchors.fill: parent

                        border.color: "black"
                        border.width: 1


                        Text {

                            width: parent.width
                            height: parent.height
                            text: model.name
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
            QtC1.TableViewColumn {
                role: "diffWarning"
                title: qsTr("Difference \nWarning")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter

                delegate: ItemDelegate {
                    contentItem:  Rectangle {
                        color: styleData.row %2 ? "#343434" : "#222222"
                        anchors.fill: parent
                        border.color: "black"
                        border.width: 1

                        TextField  {
                            id: diffWarningEditor

                            width: parent.width
                            height: parent.height
                            text: model.diffWarning
                            font.bold: true
                            font.pointSize: _fontSize
                            anchors.centerIn : parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.WrapAnywhere
                            color: _textColor

                            validator: RegExpValidator {
                                regExp: /^-?\d*\.?\d*$/
                            }


                            onTextChanged: {
                                if(text != "")
                                {
                                    if(model.diffWarning !== Number(text))
                                        model.diffWarning = Number(text)
                                }
                                else
                                {
                                    text = model.diffWarning
                                }

                            }

                            //onEditingFinished: {
                            //    if(text != "")
                            //    {
                            //         model.diffWarning = Number(text)
                            //    }
                            //    else {
                            //        text = model.diffWarning;
                            //    }
                            //}

                        }
                    }

                }
            }
            QtC1.TableViewColumn {
                role: "diffAlarm"
                title: qsTr("Difference \nAlarm")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter

                delegate: ItemDelegate {
                    contentItem:  Rectangle {
                        color: styleData.row %2 ? "#343434" : "#222222"
                        anchors.fill: parent
                        border.color: "black"
                        border.width: 1

                        TextField  {
                            id: diffAlarmEditor

                            width: parent.width
                            height: parent.height
                            text: model.diffAlarm
                            font.bold: true
                            font.pointSize: _fontSize
                            anchors.centerIn : parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.WrapAnywhere
                            color: _textColor
                            validator: RegExpValidator {
                                regExp: /^-?\d*\.?\d*$/
                            }

                            onTextChanged: {

                                if(text != "")
                                {
                                    if(model.diffAlarm !== Number(text))
                                        model.diffAlarm = Number(text)
                                }
                                else
                                {
                                    text = model.diffAlarm
                                }

                            }

                            //onEditingFinished: {
                            //    if(text != "")
                            //    {
                            //         model.diffAlarm = Number(text)
                            //    }
                            //    else {
                            //        text = model.diffAlarm;
                            //    }
                        }

                    }
                }

            }

            QtC1.TableViewColumn {
                role: "minAlarm"
                title: qsTr("Minumum \nAlarm")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter

                delegate: ItemDelegate {
                    contentItem:  Rectangle {
                        color: "#FF6068"
                        anchors.fill: parent
                        border.color: "black"
                        border.width: 1

                        TextField  {
                            id: minAlarmEditor

                            width: parent.width
                            height: parent.height
                            text: model.minAlarm
                            font.bold: true
                            font.pointSize: _fontSize
                            anchors.centerIn : parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.WrapAnywhere
                            color: _textColor

                            validator: RegExpValidator {
                                regExp: /^-?\d*\.?\d*$/
                            }

                            onTextChanged: {

                                if(text != "")
                                {
                                    if(model.minAlarm !== Number(text))
                                        model.minAlarm = Number(text)
                                }
                                else
                                {
                                    text = model.minAlarm
                                }

                            }
                            //onEditingFinished: {
                            //    if(text != "")
                            //    {
                            //         model.minAlarm = Number(text)
                            //    }
                            //    else {
                            //        text = model.minAlarm;
                            //    }
                            //}

                        }
                    }

                }
            }
            QtC1.TableViewColumn {
                role: "minWarning"
                title: qsTr("Minumum \nWarning")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter

                delegate: ItemDelegate {
                    contentItem:  Rectangle {
                        color: "#F7BD14"
                        anchors.fill: parent
                        border.color: "black"
                        border.width: 1

                        TextField  {
                            id: minWarningEditor
                            width: parent.width
                            height: parent.height
                            text: model.minWarning
                            font.bold: true
                            font.pointSize: _fontSize
                            anchors.centerIn : parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.WrapAnywhere
                            color: _textColor

                            validator: RegExpValidator {
                                regExp: /^-?\d*\.?\d*$/
                            }

                            onTextChanged: {

                                if(text != "")
                                {
                                    if(model.minWarning !== Number(text))
                                        model.minWarning = Number(text)
                                }
                                else
                                {
                                    text = model.minWarning
                                }

                            }

                            //onEditingFinished: {
                            //    if(text != "")
                            //    {
                            //         model.minWarning = Number(text)
                            //    }
                            //    else {
                            //        text = model.minWarning;
                            //    }
                            //}

                        }
                    }

                }
            }
            QtC1.TableViewColumn {
                role: "maxWarning"
                title: qsTr("Maximum \nWarning")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter

                delegate: ItemDelegate {
                    contentItem:  Rectangle {
                        color: "#F7BD14"
                        anchors.fill: parent
                        border.color: "black"
                        border.width: 1

                        TextField  {
                            id: maxWarningEditor

                            width: parent.width
                            height: parent.height
                            text: model.maxWarning
                            font.bold: true
                            font.pointSize: _fontSize
                            anchors.centerIn : parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.WrapAnywhere
                            color: _textColor

                            validator: RegExpValidator {
                                regExp: /^-?\d*\.?\d*$/
                            }

                            onTextChanged: {

                                if(text != "")
                                {
                                    if(model.maxWarning !== Number(text))
                                        model.maxWarning = Number(text)
                                }
                                else
                                {
                                    text = model.maxWarning
                                }

                            }
                            //onEditingFinished: {
                            //    if(text != "")
                            //    {
                            //         model.maxWarning = Number(text)
                            //    }
                            //    else {
                            //        text = model.maxWarning;
                            //    }
                            //}

                        }
                    }

                }
            }
            QtC1.TableViewColumn {
                role: "maxAlarm"
                title: qsTr("Maximum \nAlarm")
                width: tableObjectID.widthCell
                horizontalAlignment: Text.AlignHCenter

                delegate: ItemDelegate {
                    contentItem:  Rectangle {
                        color: "#FF6068"
                        anchors.fill: parent
                        border.color: "black"
                        border.width: 1

                        TextField  {
                            id: maxAlarmEditor
                            width: parent.width
                            height: parent.height
                            text: model.maxAlarm
                            font.bold: true
                            font.pointSize: _fontSize
                            anchors.centerIn : parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.WrapAnywhere
                            color: _textColor

                            validator: RegExpValidator {
                                regExp: /^-?\d*\.?\d*$/
                            }

                            onTextChanged: {

                                if(text != "")
                                {
                                    if(model.maxAlarm !== Number(text))
                                        model.maxAlarm = Number(text)
                                }
                                else
                                {
                                    text = model.maxAlarm
                                }

                            }
                            //onEditingFinished: {
                            //    if(text != "")
                            //    {
                            //         model.maxAlarm = Number(text)
                            //    }
                            //    else {
                            //        text = model.maxAlarm;
                            //    }
                            //}

                        }
                    }

                }

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
            }
        }
    }
}


