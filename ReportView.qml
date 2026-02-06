import QtQuick 2.15
import QtQuick.Controls 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.Controls 1.4 as QtC1
import QtQuick.Controls.Styles 1.1
import QtQuick.Dialogs 1.3 as QDialog
import ConfigView 1.0

import "../../View"
import "../../Component"

Item {
    id: report_view
    width: parent.width
    height: parent.height

    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.mainWhiteColor
    property bool _lockReportCbbSignal: false

    property color _headerColor: ConfigView.addLightBlueColor 
    property color _borderColor: ConfigView.mainBlueColor
    property int _borderSize: 1
    property int _fontSize: 12
    property int _numberColumn: 11
    property int _numberRow: 9
    property int _selectedRow: 1
    property int _bodyRNumber: 1
    property int _nonRoundShapeNumber: 1
    property int _nonRoundShape: 0

    QtObject{
        id: tableObjectID
        property int widthCell: (tableview.width)/(report_view._numberColumn) + report_view._borderSize
        property int heightCell: (tableview.height)/(report_view._numberRow)
    }

    function clearData()
    {
        sectionedModel.clear();
    }
    function formatBodyRValue(data, dimensionIndex)
        {
            var baseIndex = dimensionIndex * 4;
            var labels = ["Dim", "Min", "Max", "Oval"];
            var parts = [];
            for (var i = 0; i < 4; i++) {
                var itemIndex = baseIndex + i;
                if (data.bodyR.length > itemIndex) {
                    var entry = data.bodyR[itemIndex];
                    var value = entry.value + (entry.isPass ? "" : "$");
                    if (value !== "") {
                        parts.push(labels[i] + ":" + value);
                    }
                }
            }
            return parts.join(" ");
        }

    function addData(data)
    {
        sectionedModel.append({
            "job": data.job.value,
            "moldNumber": data.moldNumber.value,
            "codeNumber": data.codeNumber.value + ((data.codeNumber.value === "" || data.codeNumber.isPass) ? "" : "$"),
            "height": data.height.value + (data.height.isPass ? "" : "$"),
            "weight": data.weight.value + (data.weight.isPass ? "" : "$"),
            "tilt": data.tilt.value + (data.tilt.isPass ? "" : "$"),
            "lean": data.lean.value + (data.lean.isPass ? "" : "$"),
            "f": data.dimensionF.value + (data.dimensionF.isPass ? "" : "$"),
            "a": data.dimensionA.value + (data.dimensionA.isPass ? "" : "$"),
            "t": data.dimensionT.value + (data.dimensionT.isPass ? "" : "$"),
            "e": data.dimensionE.value + (data.dimensionE.isPass ? "" : "$"),
            "b": data.dimensionB.value + (data.dimensionB.isPass ? "" : "$"),
            "d": data.dimensionD.value + (data.dimensionD.isPass ? "" : "$"),
            "s": data.dimensionS.value + (data.dimensionS.isPass ? "" : "$"),
            "h": data.dimensionH.value + (data.dimensionH.isPass ? "" : "$"),
            "lugT": data.dimensionLugT.value + ((data.dimensionLugT.value === "" || data.dimensionLugT.isPass) ? "" : "$"),
            "lugT1": data.dimensionLugT1.value + ((data.dimensionLugT1.value === "" || data.dimensionLugT1.isPass) ? "" : "$"),
            "dAngle": data.dAngle.value + ((data.dAngle.value === "" || data.dAngle.isPass) ? "" : "$"),
            "pushup": data.pushup.value + (data.pushup.isPass ? "" : "$"),

                                  "flange": data.flange.value + ((data.flange.value === "" || data.flange.isPass) ? "" : "$"),
                                  "knockout": data.knockout.value + ((data.knockout.value === "" || data.knockout.isPass) ? "" : "$"),
                                  "bodyR": formatBodyRValue(data, 0),
                                  "body2R": formatBodyRValue(data, 1),
                                  "body3R": formatBodyRValue(data, 2),
                                  "body4R": formatBodyRValue(data, 3),
                                  "body5R": formatBodyRValue(data, 4),
                                  "body6R": formatBodyRValue(data, 5),
                                  "body7R": formatBodyRValue(data, 6),
                                  "body8R": formatBodyRValue(data, 7),
                                  "body9R": formatBodyRValue(data, 8),
                                  "body10R": formatBodyRValue(data, 9),
                                  "body11R": formatBodyRValue(data, 10),
                                  "body12R": formatBodyRValue(data, 11),
                                  "body13R": formatBodyRValue(data, 12),
                                  "body14R": formatBodyRValue(data, 13),
                                  "body15R": formatBodyRValue(data, 14),
                                  "body16R": formatBodyRValue(data, 15),
                                  "body17R": formatBodyRValue(data, 16),
                                  "body18R": formatBodyRValue(data, 17),
                                  "body19R": formatBodyRValue(data, 18),
                                  "body20R": formatBodyRValue(data, 19),
                                  "body21R": formatBodyRValue(data, 20),
                                  "body22R": formatBodyRValue(data, 21),
                                  "body23R": formatBodyRValue(data, 22),

            "recShrt1": data.recShrt.length > 0 ? (data.recShrt[0].value + ((data.recShrt[0].value === "" || data.recShrt[0].isPass) ? "" : "$")) : "",
            "recLong1": data.recLong.length > 0 ? (data.recLong[0].value + ((data.recLong[0].value === "" || data.recLong[0].isPass) ? "" : "$")) : "",
            "recDiag1": data.recDiag.length > 0 ? (data.recDiag[0].value + ((data.recDiag[0].value === "" || data.recDiag[0].isPass) ? "" : "$")) : "",
            "sqrSide1": data.sqrSide.length > 0 ? (data.sqrSide[0].value + ((data.sqrSide[0].value === "" || data.sqrSide[0].isPass) ? "" : "$")) : "",
            "sqrDiag1": data.sqrDiag.length > 0 ? (data.sqrDiag[0].value + ((data.sqrDiag[0].value === "" || data.sqrDiag[0].isPass) ? "" : "$")) : "",
            "ovlShrt1": data.ovlShrt.length > 0 ? (data.ovlShrt[0].value + ((data.ovlShrt[0].value === "" || data.ovlShrt[0].isPass) ? "" : "$")) : "",
            "ovlLong1": data.ovlLong.length > 0 ? (data.ovlLong[0].value + ((data.ovlLong[0].value === "" || data.ovlLong[0].isPass) ? "" : "$")) : "",

            "recShrt2": data.recShrt.length > 1 ? (data.recShrt[1].value + ((data.recShrt[1].value === "" || data.recShrt[1].isPass) ? "" : "$")) : "",
            "recLong2": data.recLong.length > 1 ? (data.recLong[1].value + ((data.recLong[1].value === "" || data.recLong[1].isPass) ? "" : "$")) : "",
            "recDiag2": data.recDiag.length > 1 ? (data.recDiag[1].value + ((data.recDiag[1].value === "" || data.recDiag[1].isPass) ? "" : "$")) : "",
            "sqrSide2": data.sqrSide.length > 1 ? (data.sqrSide[1].value + ((data.sqrSide[1].value === "" || data.sqrSide[1].isPass) ? "" : "$")) : "",
            "sqrDiag2": data.sqrDiag.length > 1 ? (data.sqrDiag[1].value + ((data.sqrDiag[1].value === "" || data.sqrDiag[1].isPass) ? "" : "$")) : "",
            "ovlShrt2": data.ovlShrt.length > 1 ? (data.ovlShrt[1].value + ((data.ovlShrt[1].value === "" || data.ovlShrt[1].isPass) ? "" : "$")) : "",
            "ovlLong2": data.ovlLong.length > 1 ? (data.ovlLong[1].value + ((data.ovlLong[1].value === "" || data.ovlLong[1].isPass) ? "" : "$")) : "",

            "recShrt3": data.recShrt.length > 2 ? (data.recShrt[2].value + ((data.recShrt[2].value === "" || data.recShrt[2].isPass) ? "" : "$")) : "",
            "recLong3": data.recLong.length > 2 ? (data.recLong[2].value + ((data.recLong[2].value === "" || data.recLong[2].isPass) ? "" : "$")) : "",
            "recDiag3": data.recDiag.length > 2 ? (data.recDiag[2].value + ((data.recDiag[2].value === "" || data.recDiag[2].isPass) ? "" : "$")) : "",
            "sqrSide3": data.sqrSide.length > 2 ? (data.sqrSide[2].value + ((data.sqrSide[2].value === "" || data.sqrSide[2].isPass) ? "" : "$")) : "",
            "sqrDiag3": data.sqrDiag.length > 2 ? (data.sqrDiag[2].value + ((data.sqrDiag[2].value === "" || data.sqrDiag[2].isPass) ? "" : "$")) : "",
            "ovlShrt3": data.ovlShrt.length > 2 ? (data.ovlShrt[2].value + ((data.ovlShrt[2].value === "" || data.ovlShrt[2].isPass) ? "" : "$")) : "",
            "ovlLong3": data.ovlLong.length > 2 ? (data.ovlLong[2].value + ((data.ovlLong[2].value === "" || data.ovlLong[2].isPass) ? "" : "$")) : "",

            "recShrt4": data.recShrt.length > 3 ? (data.recShrt[3].value + ((data.recShrt[3].value === "" || data.recShrt[3].isPass) ? "" : "$")) : "",
            "recLong4": data.recLong.length > 3 ? (data.recLong[3].value + ((data.recLong[3].value === "" || data.recLong[3].isPass) ? "" : "$")) : "",
            "recDiag4": data.recDiag.length > 3 ? (data.recDiag[3].value + ((data.recDiag[3].value === "" || data.recDiag[3].isPass) ? "" : "$")) : "",
            "sqrSide4": data.sqrSide.length > 3 ? (data.sqrSide[3].value + ((data.sqrSide[3].value === "" || data.sqrSide[3].isPass) ? "" : "$")) : "",
            "sqrDiag4": data.sqrDiag.length > 3 ? (data.sqrDiag[3].value + ((data.sqrDiag[3].value === "" || data.sqrDiag[3].isPass) ? "" : "$")) : "",
            "ovlShrt4": data.ovlShrt.length > 3 ? (data.ovlShrt[3].value + ((data.ovlShrt[3].value === "" || data.ovlShrt[3].isPass) ? "" : "$")) : "",
            "ovlLong4": data.ovlLong.length > 3 ? (data.ovlLong[3].value + ((data.ovlLong[3].value === "" || data.ovlLong[3].isPass) ? "" : "$")) : "",

            "recShrt5": data.recShrt.length > 4 ? (data.recShrt[4].value + ((data.recShrt[4].value === "" || data.recShrt[4].isPass) ? "" : "$")) : "",
            "recLong5": data.recLong.length > 4 ? (data.recLong[4].value + ((data.recLong[4].value === "" || data.recLong[4].isPass) ? "" : "$")) : "",
            "recDiag5": data.recDiag.length > 4 ? (data.recDiag[4].value + ((data.recDiag[4].value === "" || data.recDiag[4].isPass) ? "" : "$")) : "",
            "sqrSide5": data.sqrSide.length > 4 ? (data.sqrSide[4].value + ((data.sqrSide[4].value === "" || data.sqrSide[4].isPass) ? "" : "$")) : "",
            "sqrDiag5": data.sqrDiag.length > 4 ? (data.sqrDiag[4].value + ((data.sqrDiag[4].value === "" || data.sqrDiag[4].isPass) ? "" : "$")) : "",
            "ovlShrt5": data.ovlShrt.length > 4 ? (data.ovlShrt[4].value + ((data.ovlShrt[4].value === "" || data.ovlShrt[4].isPass) ? "" : "$")) : "",
            "ovlLong5": data.ovlLong.length > 4 ? (data.ovlLong[4].value + ((data.ovlLong[4].value === "" || data.ovlLong[4].isPass) ? "" : "$")) : "",

            "recShrt6": data.recShrt.length > 5 ? (data.recShrt[5].value + ((data.recShrt[5].value === "" || data.recShrt[5].isPass) ? "" : "$")) : "",
            "recLong6": data.recLong.length > 5 ? (data.recLong[5].value + ((data.recLong[5].value === "" || data.recLong[5].isPass) ? "" : "$")) : "",
            "recDiag6": data.recDiag.length > 5 ? (data.recDiag[5].value + ((data.recDiag[5].value === "" || data.recDiag[5].isPass) ? "" : "$")) : "",
            "sqrSide6": data.sqrSide.length > 5 ? (data.sqrSide[5].value + ((data.sqrSide[5].value === "" || data.sqrSide[5].isPass) ? "" : "$")) : "",
            "sqrDiag6": data.sqrDiag.length > 5 ? (data.sqrDiag[5].value + ((data.sqrDiag[5].value === "" || data.sqrDiag[5].isPass) ? "" : "$")) : "",
            "ovlShrt6": data.ovlShrt.length > 5 ? (data.ovlShrt[5].value + ((data.ovlShrt[5].value === "" || data.ovlShrt[5].isPass) ? "" : "$")) : "",
            "ovlLong6": data.ovlLong.length > 5 ? (data.ovlLong[5].value + ((data.ovlLong[5].value === "" || data.ovlLong[5].isPass) ? "" : "$")) : "",

            "recShrt7": data.recShrt.length > 6 ? (data.recShrt[6].value + ((data.recShrt[6].value === "" || data.recShrt[6].isPass) ? "" : "$")) : "",
            "recLong7": data.recLong.length > 6 ? (data.recLong[6].value + ((data.recLong[6].value === "" || data.recLong[6].isPass) ? "" : "$")) : "",
            "recDiag7": data.recDiag.length > 6 ? (data.recDiag[6].value + ((data.recDiag[6].value === "" || data.recDiag[6].isPass) ? "" : "$")) : "",
            "sqrSide7": data.sqrSide.length > 6 ? (data.sqrSide[6].value + ((data.sqrSide[6].value === "" || data.sqrSide[6].isPass) ? "" : "$")) : "",
            "sqrDiag7": data.sqrDiag.length > 6 ? (data.sqrDiag[6].value + ((data.sqrDiag[6].value === "" || data.sqrDiag[6].isPass) ? "" : "$")) : "",
            "ovlShrt7": data.ovlShrt.length > 6 ? (data.ovlShrt[6].value + ((data.ovlShrt[6].value === "" || data.ovlShrt[6].isPass) ? "" : "$")) : "",
            "ovlLong7": data.ovlLong.length > 6 ? (data.ovlLong[6].value + ((data.ovlLong[6].value === "" || data.ovlLong[6].isPass) ? "" : "$")) : "",

            "recShrt8": data.recShrt.length > 7 ? (data.recShrt[7].value + ((data.recShrt[7].value === "" || data.recShrt[7].isPass) ? "" : "$")) : "",
            "recLong8": data.recLong.length > 7 ? (data.recLong[7].value + ((data.recLong[7].value === "" || data.recLong[7].isPass) ? "" : "$")) : "",
            "recDiag8": data.recDiag.length > 7 ? (data.recDiag[7].value + ((data.recDiag[7].value === "" || data.recDiag[7].isPass) ? "" : "$")) : "",
            "sqrSide8": data.sqrSide.length > 7 ? (data.sqrSide[7].value + ((data.sqrSide[7].value === "" || data.sqrSide[7].isPass) ? "" : "$")) : "",
            "sqrDiag8": data.sqrDiag.length > 7 ? (data.sqrDiag[7].value + ((data.sqrDiag[7].value === "" || data.sqrDiag[7].isPass) ? "" : "$")) : "",
            "ovlShrt8": data.ovlShrt.length > 7 ? (data.ovlShrt[7].value + ((data.ovlShrt[7].value === "" || data.ovlShrt[7].isPass) ? "" : "$")) : "",
            "ovlLong8": data.ovlLong.length > 7 ? (data.ovlLong[7].value + ((data.ovlLong[7].value === "" || data.ovlLong[7].isPass) ? "" : "$")) : "",

        });
    }

    ListModel {
        id: sectionedModel
    }

    Column {
        height: parent.height*0.98
        width: parent.width
        spacing: parent.height*0.02
        anchors.verticalCenter: parent.verticalCenter
        Row {
            height: parent.height*0.1
            width: parent.width*0.96
            spacing: parent.width*0.03
            anchors.horizontalCenter: parent.horizontalCenter

            ComboBoxCustom{
                id: report_cbb
                ListModel {
                    id: report_cbb_model
                }
                _model: report_cbb_model
                width: parent.width*0.2
                height: parent.height
                _fontSize: report_view._fontSize
                _fontFamily: report_view._fontFamily
                currentIndex: 0
                anchors.verticalCenter: parent.verticalCenter
                onCurrentTextChanged:{
                    if(report_view._lockReportCbbSignal)
                        return
                    _viewModel.currentReportIndexChanged_Qml_Slot(currentIndex)
                }
            }


            GroupBox{
                id: page_group
                width: parent.width*0.15
                height: parent.height
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
                    width: title.contentWidth*1.4
                    height: parent.height*0.25
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    anchors.bottom: parent.top
                    anchors.bottomMargin: - height/2
                    Text {
                        id: title
                        height: parent.height
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        verticalAlignment: Text.AlignVCenter
                        text: qsTr("Page")
                        color: _textColor
                        font.bold: true
                        font.pointSize: _fontSize
                        font.family: _fontFamily
                    }
                }

                Row {
                    width: parent.width*0.88
                    height: parent.height*0.9
                    spacing: parent.width*0.02
                    anchors.centerIn: parent
                    ButtonMaterial{
                        _width: parent.height
                        _height: parent.height
                        _size: _height*1
                        _iconSourceOn: "chevronLeftBox"
                        _colorBorder: " transparent"
                        _colorIconHigh: "#FFCE44"
                        _colorIconDefault: ConfigView.addLightBlueColor
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: {
                            var index = parseInt(page_index_text.getText()) - 1
                            if(index < 0)
                                return
                            page_index_text.setText(index)
                        }
                    }

                    InputText{
                        id: page_index_text
                        _width: _height*2
                        _height: parent.height
                        _fontSizeText: _fontSize
                        _text: "1"
                        _leftMagin: 0
                        _reg: RegExpValidator{regExp: /\d+/}
                        _inputMethodHints: Qt.ImhFormattedNumbersOnly
                    }

                    ButtonMaterial{
                        _width: parent.height
                        _height: parent.height
                        _size: _height*1
                        _iconSourceOn: "chevronRightBox"
                        _colorBorder: " transparent"
                        _colorIconHigh: "#FFCE44"
                        _colorIconDefault: ConfigView.addLightBlueColor
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: {
                            var index = parseInt(page_index_text.getText()) + 1
                            if(index > _viewModel.maxPageNumber)
                                return
                            page_index_text.setText(parseInt(page_index_text.getText()) + 1)
                        }
                    }

                }


            }


            ButtonMaterialTextHorizontal{
                id: export_btn
                height: parent.height*0.9
                _size: height*0.8
                _text: qsTr("Export")
                _iconSourceOn: "databaseExport"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: report_view._fontFamily
                _textRatio: 0.4
                _colorIconMouseOver: _colorIconDefault
                onClicked: {
                    _viewModel.export_Qml_Slot(report_cbb.currentIndex,
                                page_index_text.getText());

                                //export_table_dlg.open();
                    //var fileHeader = report_cbb.currentText + " " + "Page " + page_index_text.getText()
                    //console.log(fileHeader)

                    export_table_dlg.open();
            
                }
            }

            ButtonMaterialTextHorizontal{
                id: print_btn
                height: parent.height*0.9
                _size: height*0.8
                _text: qsTr("Print")
                _iconSourceOn: "printer"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: report_view._fontFamily
                _textRatio: 0.4
                _colorIconMouseOver: _colorIconDefault
                onClicked: {
                    _viewModel.print_Qml_Slot(report_cbb.currentIndex,
                                page_index_text.getText());


                    print_table_dlg.open();

                }
            }

        }

        Column {
            height: parent.height*0.87
            width: parent.width
            Rectangle {
                height: parent.height*0.1
                width: parent.width*0.96
                anchors.horizontalCenter: parent.horizontalCenter
                color: ConfigView.mainBlueColor
                Text {
                    text: report_cbb.currentText +
                          "        " + qsTr("Machine") + ": " + qsTr("MiniLab") + "        " + qsTr("Job name") + ": " +
                          recipeManagementVM.currentRecipe /*+
                          "        "+ qsTr("Date") + ": " +
                          _viewModel.lastReportTime*/
                    width: parent.width
                    font.pointSize: _fontSize + 2
                    color: ConfigView.textColor
                    font.family: _fontFamily
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            QtC1.TableView {
                id: tableview
                height: parent.height*0.9
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
                    role: "job"
                    title: qsTr("Job")
                    width: tableObjectID.widthCell*1.5
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    role: "moldNumber"
                    title: qsTr("Mold Number")
                    width: tableObjectID.widthCell*1.5
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "codeNumber"
                    title: qsTr("Code Number")
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
                QtC1.TableViewColumn {
                    role: "tilt"
                    title: qsTr("Tilt")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "lean"
                    title: qsTr("Lean")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "f"
                    title: qsTr("F")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "a"
                    title: qsTr("A")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "t"
                    title: qsTr("T")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "e"
                    title: qsTr("E")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "b"
                    title: qsTr("B")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "d"
                    title: qsTr("D")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "s"
                    title: qsTr("S")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "h"
                    title: qsTr("H")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "lugT"
                    title: qsTr("LugT")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "lugT1"
                    title: qsTr("LugT1")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "dAngle"
                    title: qsTr("D-Angle")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "pushup"
                    title: qsTr("Pushup")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }

                // 1
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 1 && _nonRoundShape == 0
                    role: "recShrt1"
                    title: qsTr("RecShrt") + "1"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 1 && _nonRoundShape == 0
                    role: "recLong1"
                    title: qsTr("RecLong") + "1"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 1 && _nonRoundShape == 0
                    role: "recDiag1"
                    title: qsTr("RecDiag") + "1"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 1 && _nonRoundShape == 1
                    role: "sqrSide1"
                    title: qsTr("SqrSide") + "1"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 1 && _nonRoundShape == 1
                    role: "sqrDiag1"
                    title: qsTr("SqrDiag") + "1"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 1 && _nonRoundShape == 2
                    role: "ovlShrt1"
                    title: qsTr("OvlShrt") + "1"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 1 && _nonRoundShape == 2
                    role: "ovlLong1"
                    title: qsTr("OvlLong") + "1"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                // 2
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 2 && _nonRoundShape == 0
                    role: "recShrt2"
                    title: qsTr("RecShrt") + "2"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 2 && _nonRoundShape == 0
                    role: "recLong2"
                    title: qsTr("RecLong") + "2"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 2 && _nonRoundShape == 0
                    role: "recDiag2"
                    title: qsTr("RecDiag") + "2"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 2 && _nonRoundShape == 1
                    role: "sqrSide2"
                    title: qsTr("SqrSide") + "2"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 2 && _nonRoundShape == 1
                    role: "sqrDiag2"
                    title: qsTr("SqrDiag") + "2"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 2 && _nonRoundShape == 2
                    role: "ovlShrt2"
                    title: qsTr("OvlShrt") + "2"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 2 && _nonRoundShape == 2
                    role: "ovlLong2"
                    title: qsTr("OvlLong") + "2"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                // 3
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 3 && _nonRoundShape == 0
                    role: "recShrt3"
                    title: qsTr("RecShrt") + "3"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 3 && _nonRoundShape == 0
                    role: "recLong3"
                    title: qsTr("RecLong") + "3"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 3 && _nonRoundShape == 0
                    role: "recDiag3"
                    title: qsTr("RecDiag") + "3"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 3 && _nonRoundShape == 1
                    role: "sqrSide3"
                    title: qsTr("SqrSide") + "3"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 3 && _nonRoundShape == 1
                    role: "sqrDiag3"
                    title: qsTr("SqrDiag") + "3"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 3 && _nonRoundShape == 2
                    role: "ovlShrt3"
                    title: qsTr("OvlShrt") + "3"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 3 && _nonRoundShape == 2
                    role: "ovlLong3"
                    title: qsTr("OvlLong") + "3"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                // 4
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 4 && _nonRoundShape == 0
                    role: "recShrt4"
                    title: qsTr("RecShrt") + "4"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 4 && _nonRoundShape == 0
                    role: "recLong4"
                    title: qsTr("RecLong") + "4"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 4 && _nonRoundShape == 0
                    role: "recDiag4"
                    title: qsTr("RecDiag") + "4"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 4 && _nonRoundShape == 1
                    role: "sqrSide4"
                    title: qsTr("SqrSide") + "4"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 4 && _nonRoundShape == 1
                    role: "sqrDiag4"
                    title: qsTr("SqrDiag") + "4"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 4 && _nonRoundShape == 2
                    role: "ovlShrt4"
                    title: qsTr("OvlShrt") + "4"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 4 && _nonRoundShape == 2
                    role: "ovlLong4"
                    title: qsTr("OvlLong") + "4"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                // 5
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 5 && _nonRoundShape == 0
                    role: "recShrt5"
                    title: qsTr("RecShrt") + "5"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 5 && _nonRoundShape == 0
                    role: "recLong5"
                    title: qsTr("RecLong") + "5"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 5 && _nonRoundShape == 0
                    role: "recDiag5"
                    title: qsTr("RecDiag") + "5"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 5 && _nonRoundShape == 1
                    role: "sqrSide5"
                    title: qsTr("SqrSide") + "5"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 5 && _nonRoundShape == 1
                    role: "sqrDiag5"
                    title: qsTr("SqrDiag") + "5"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 5 && _nonRoundShape == 2
                    role: "ovlShrt5"
                    title: qsTr("OvlShrt") + "5"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 5 && _nonRoundShape == 2
                    role: "ovlLong5"
                    title: qsTr("OvlLong") + "5"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                // 6
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 6 && _nonRoundShape == 0
                    role: "recShrt6"
                    title: qsTr("RecShrt") + "6"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 6 && _nonRoundShape == 0
                    role: "recLong6"
                    title: qsTr("RecLong") + "6"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 6 && _nonRoundShape == 0
                    role: "recDiag6"
                    title: qsTr("RecDiag") + "6"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 6 && _nonRoundShape == 1
                    role: "sqrSide6"
                    title: qsTr("SqrSide") + "6"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 6 && _nonRoundShape == 1
                    role: "sqrDiag6"
                    title: qsTr("SqrDiag") + "6"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 6 && _nonRoundShape == 2
                    role: "ovlShrt6"
                    title: qsTr("OvlShrt") + "6"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 6 && _nonRoundShape == 2
                    role: "ovlLong6"
                    title: qsTr("OvlLong") + "6"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                // 7
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 7 && _nonRoundShape == 0
                    role: "recShrt7"
                    title: qsTr("RecShrt") + "7"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 7 && _nonRoundShape == 0
                    role: "recLong7"
                    title: qsTr("RecLong") + "7"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 7 && _nonRoundShape == 0
                    role: "recDiag7"
                    title: qsTr("RecDiag") + "7"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 7 && _nonRoundShape == 1
                    role: "sqrSide7"
                    title: qsTr("SqrSide") + "7"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 7 && _nonRoundShape == 1
                    role: "sqrDiag7"
                    title: qsTr("SqrDiag") + "7"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 7 && _nonRoundShape == 2
                    role: "ovlShrt7"
                    title: qsTr("OvlShrt") + "7"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 7 && _nonRoundShape == 2
                    role: "ovlLong7"
                    title: qsTr("OvlLong") + "7"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                // 8
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 8 && _nonRoundShape == 0
                    role: "recShrt8"
                    title: qsTr("RecShrt") + "8"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 8 && _nonRoundShape == 0
                    role: "recLong8"
                    title: qsTr("RecLong") + "8"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 8 && _nonRoundShape == 0
                    role: "recDiag8"
                    title: qsTr("RecDiag") + "8"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 8 && _nonRoundShape == 1
                    role: "sqrSide8"
                    title: qsTr("SqrSide") + "8"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 8 && _nonRoundShape == 1
                    role: "sqrDiag8"
                    title: qsTr("SqrDiag") + "8"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }

                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 8 && _nonRoundShape == 2
                    role: "ovlShrt8"
                    title: qsTr("OvlShrt") + "8"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    visible: _nonRoundShapeNumber >= 8 && _nonRoundShape == 2
                    role: "ovlLong8"
                    title: qsTr("OvlLong") + "8"
                    width: tableObjectID.widthCell*2
                    horizontalAlignment: Text.AlignHCenter
                }


                QtC1.TableViewColumn {
                    role: "flange"
                    title: qsTr("Flange")
                    width: tableObjectID.widthCell
                    horizontalAlignment: Text.AlignHCenter
                }
                QtC1.TableViewColumn {
                    role: "knockout"
                    title: qsTr("Knockout")
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
                        return styleData.row %2 ? ConfigView.mainWhiteColor : ConfigView.mainWhiteColor
                    }

                    Text {
                        id: content_text
                        width: parent.width
                        height: parent.height
                        text: {
                            if(styleData.role === "moldNumber")
                                return styleData.value
                            return styleData.value.replace("$", "")
                        }
                        font.bold: true
                        font.pointSize: _fontSize
                        anchors.centerIn : parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WrapAnywhere
                        color: ConfigView.mainBlueColor
                    }

                }

            }

        }

    }

    QDialog.FileDialog {
        id: print_table_dlg
        title: "Select Save Report PDF"
        selectExisting: false
        selectMultiple: false
        nameFilters: ["PDF Files (*.pdf)"]
        onAccepted: {
            var raw_text = String(print_table_dlg.fileUrl);
            var path = Qt.platform.os === "windows" ?
                        raw_text.substring(8, raw_text.length) :
                        raw_text.substring(7, raw_text.length)


            var extension = ".pdf"
            if (!path.endsWith(extension)) {
                path += extension; // Add '.csv' if not present
            }

            doPrintFilePDF(path);

            print_table_dlg.close()
        }
    }

    QDialog.FileDialog {
        id: export_table_dlg
        title: qsTr("Select Save Report CSV")
        selectMultiple: false
        selectExisting: false
        nameFilters: ["CSV Files (*.csv)", "All Files (*.*)"]
        onAccepted: {
            var raw_text = String(export_table_dlg.fileUrl);
            var path = Qt.platform.os === "windows" ?
                        raw_text.substring(8, raw_text.length) :
                        raw_text.substring(7, raw_text.length)


            var extension = ".csv"
            if (!path.endsWith(extension)) {
                path += extension; // Add '.csv' if not present
            }

            doExportFileCSV(path);

            export_table_dlg.close()
        }
    }
    property string reportData: ""
    property string reportHeader: ""

    function reportDataCSVBuilder()
    {
        // reset
        reportData = ""

        //build header
        for (var i = 0; i < tableview.columnCount; i++) {
            var column = tableview.getColumn(i);
            if(column.visible)
                reportData +=  column.title + ","
        }
        reportData += "\n"

        for (var i = 0; i < sectionedModel.count; i++) {
            var item = sectionedModel.get(i);

            reportData += Number(item.job.replace("$", "")) + ","
            reportData += Number(item.moldNumber.replace("$", "")) + ","
            reportData += Number(item.codeNumber.replace("$", "")) + ","
            reportData += Number(item.height.replace("$", "")).toFixed(2) + ","
            reportData += Number(item.weight.replace("$", "")).toFixed(2)  + ","

            // -1 mean not visible␊
            if(_bodyRNumber >= 1)
                reportData += item.bodyR.replace("$", "") + ","
            if(_bodyRNumber >= 2)
                reportData += item.body2R.replace("$", "") + ","
            if(_bodyRNumber >= 3)
                reportData += item.body3R.replace("$", "") + ","
            if(_bodyRNumber >= 4)
                reportData += item.body4R.replace("$", "") + ","
            if(_bodyRNumber >= 5)
                reportData += item.body5R.replace("$", "") + ","
            if(_bodyRNumber >= 6)
                reportData += item.body6R.replace("$", "") + ","
            if(_bodyRNumber >= 7)
                reportData += item.body7R.replace("$", "") + ","
            if(_bodyRNumber >= 8)
                reportData += item.body8R.replace("$", "") + ","
            if(_bodyRNumber >= 9)
                reportData += item.body9R.replace("$", "") + ","
            if(_bodyRNumber >= 10)
                reportData += item.body10R.replace("$", "") + ","
            if(_bodyRNumber >= 11)
                reportData += item.body11R.replace("$", "") + ",";
            if(_bodyRNumber >= 12)
                reportData += item.body12R.replace("$", "") + ","
            if(_bodyRNumber >= 13)
                reportData += item.body13R.replace("$", "") + ","
            if(_bodyRNumber >= 14)
                reportData += item.body14R.replace("$", "") + ","
            if(_bodyRNumber >= 15)
                reportData += item.body15R.replace("$", "") + ","
            if(_bodyRNumber >= 16)
                reportData += item.body16R.replace("$", "") + ","
            if(_bodyRNumber >= 17)
                reportData += item.body17R.replace("$", "") + ","
            if(_bodyRNumber >= 18)
                reportData += item.body18R.replace("$", "") + ","
            if(_bodyRNumber >= 19)
                reportData += item.body19R.replace("$", "") + ","
            if(_bodyRNumber >= 20)
                reportData += item.body20R.replace("$", "") + ","
            if(_bodyRNumber >= 21)
                reportData += item.body21R.replace("$", "") + ","
            if(_bodyRNumber >= 22)
                reportData += item.body22R.replace("$", "") + ","
            if(_bodyRNumber >= 23)
                reportData += item.body23R.replace("$", "") + ","


            reportData += Number(item.tilt.replace("$", "")).toFixed(2)    + ","
            reportData += Number(item.lean.replace("$", "")).toFixed(2)    + ","
            reportData += Number(item.f.replace("$", "")).toFixed(2)       + ","
            reportData += Number(item.a.replace("$", "")).toFixed(2)       + ","
            reportData += Number(item.t.replace("$", "")).toFixed(2)       + ","
            reportData += Number(item.e.replace("$", "")).toFixed(2)       + ","
            reportData += Number(item.b.replace("$", "")).toFixed(2)       + ","
            reportData += Number(item.d.replace("$", "")).toFixed(2)       + ","
            reportData += Number(item.s.replace("$", "")).toFixed(2)       + ","
            reportData += Number(item.h.replace("$", "")).toFixed(2)       + ","
            reportData += Number(item.lugT.replace("$", "")).toFixed(2)    + ","
            reportData += Number(item.lugT1.replace("$", "")).toFixed(2)   + ","
            reportData += Number(item.dAngle.replace("$", "")).toFixed(2)  + ","
            reportData += Number(item.pushup.replace("$", "")).toFixed(2)  + ","

            if(_nonRoundShapeNumber >= 1)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt1.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recLong1.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recDiag1.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide1.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.sqrDiag1.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt1.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.ovlLong1.replace("$", "")).toFixed(2)   + ","
                }
            }

            if(_nonRoundShapeNumber >= 2)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt2.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recLong2.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recDiag2.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide2.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.sqrDiag2.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt2.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.ovlLong2.replace("$", "")).toFixed(2)   + ","
                }
            }

            if(_nonRoundShapeNumber >= 3)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt3.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recLong3.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recDiag3.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide3.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.sqrDiag3.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt3.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.ovlLong3.replace("$", "")).toFixed(2)   + ","
                }
            }

            if(_nonRoundShapeNumber >= 4)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt4.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recLong4.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recDiag4.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide4.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.sqrDiag4.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt4.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.ovlLong4.replace("$", "")).toFixed(2)   + ","
                }
            }

            if(_nonRoundShapeNumber >= 5)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt5.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recLong5.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recDiag5.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide5.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.sqrDiag5.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt5.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.ovlLong5.replace("$", "")).toFixed(2)   + ","
                }
            }

            if(_nonRoundShapeNumber >= 6)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt6.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recLong6.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recDiag6.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide6.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.sqrDiag6.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt6.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.ovlLong6.replace("$", "")).toFixed(2)   + ","
                }
            }

            if(_nonRoundShapeNumber >= 7)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt7.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recLong7.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recDiag7.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide7.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.sqrDiag7.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt7.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.ovlLong7.replace("$", "")).toFixed(2)   + ","
                }
            }

            if(_nonRoundShapeNumber >= 8)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt8.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recLong8.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.recDiag8.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide8.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.sqrDiag8.replace("$", "")).toFixed(2)   + ","
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt8.replace("$", "")).toFixed(2)   + ","
                    reportData += Number(item.ovlLong8.replace("$", "")).toFixed(2)   + ","
                }
            }

            reportData += "\n"
                
        }
    }

    function reportDataPDFBuilder()
    {
        // reset
        reportData = ""
        reportHeader = ""


        //build header
        for (var i = 0; i < tableview.columnCount; i++) {
            var column = tableview.getColumn(i);
            if(column.visible)
                reportHeader += column.title + "\n"
        }

        
        for (var i = 0; i < sectionedModel.count; i++) {
            var item = sectionedModel.get(i);

            reportData += Number(item.job.replace("$", "")) + "\n"
            reportData += Number(item.moldNumber.replace("$", "")) + "\n"
            reportData += Number(item.codeNumber.replace("$", "")) + "\n"
            reportData += Number(item.height.replace("$", "")).toFixed(2) + "\n"
            reportData += Number(item.weight.replace("$", "")).toFixed(2)  + "\n"

            // -1 mean not visible␊
            if(_bodyRNumber >= 1)
                reportData += item.bodyR.replace("$", "") + "\n"
            if(_bodyRNumber >= 2)
                reportData += item.body2R.replace("$", "") + "\n"
            if(_bodyRNumber >= 3)
                reportData += item.body3R.replace("$", "") + "\n"
            if(_bodyRNumber >= 4)
                reportData += item.body4R.replace("$", "") + "\n"
            if(_bodyRNumber >= 5)
                reportData += item.body5R.replace("$", "") + "\n"
            if(_bodyRNumber >= 6)
                reportData += item.body6R.replace("$", "") + "\n"
            if(_bodyRNumber >= 7)
                reportData += item.body7R.replace("$", "") + "\n"
            if(_bodyRNumber >= 8)
                reportData += item.body8R.replace("$", "") + "\n"
            if(_bodyRNumber >= 9)
                reportData += item.body9R.replace("$", "") + "\n"
            if(_bodyRNumber >= 10)
                reportData += item.body10R.replace("$", "") + "\n"
            if(_bodyRNumber >= 11)
                reportData += item.body11R.replace("$", "") + "\n";
            if(_bodyRNumber >= 12)
                reportData += item.body12R.replace("$", "") + "\n"
            if(_bodyRNumber >= 13)
                reportData += item.body13R.replace("$", "") + "\n"
            if(_bodyRNumber >= 14)
                reportData += item.body14R.replace("$", "") + "\n"
            if(_bodyRNumber >= 15)
                reportData += item.body15R.replace("$", "") + "\n"
            if(_bodyRNumber >= 16)
                reportData += item.body16R.replace("$", "") + "\n"
            if(_bodyRNumber >= 17)
                reportData += item.body17R.replace("$", "") + "\n"
            if(_bodyRNumber >= 18)
                reportData += item.body18R.replace("$", "") + "\n"
            if(_bodyRNumber >= 19)
                reportData += item.body19R.replace("$", "") + "\n"
            if(_bodyRNumber >= 20)
                reportData += item.body20R.replace("$", "") + "\n"
            if(_bodyRNumber >= 21)
                reportData += item.body21R.replace("$", "") + "\n"
            if(_bodyRNumber >= 22)
                reportData += item.body22R.replace("$", "") + "\n"
            if(_bodyRNumber >= 23)
                reportData += item.body23R.replace("$", "") + "\n"


            reportData += Number(item.tilt.replace("$", "")).toFixed(2)    + "\n"
            reportData += Number(item.lean.replace("$", "")).toFixed(2)    + "\n"
            reportData += Number(item.f.replace("$", "")).toFixed(2)       + "\n"
            reportData += Number(item.a.replace("$", "")).toFixed(2)       + "\n"
            reportData += Number(item.t.replace("$", "")).toFixed(2)       + "\n"
            reportData += Number(item.e.replace("$", "")).toFixed(2)       + "\n"
            reportData += Number(item.b.replace("$", "")).toFixed(2)       + "\n"
            reportData += Number(item.d.replace("$", "")).toFixed(2)       + "\n"
            reportData += Number(item.s.replace("$", "")).toFixed(2)       + "\n"
            reportData += Number(item.h.replace("$", "")).toFixed(2)       + "\n"
            reportData += Number(item.lugT.replace("$", "")).toFixed(2)       + "\n"
            reportData += Number(item.lugT1.replace("$", "")).toFixed(2)       + "\n"
            reportData += Number(item.dAngle.replace("$", "")).toFixed(2)       + "\n"
            reportData += Number(item.pushup.replace("$", "")).toFixed(2)  + "\n"


            if(_nonRoundShapeNumber >= 1)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt1.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recLong1.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recDiag1.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide1.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.sqrDiag1.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt1.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.ovlLong1.replace("$", "")).toFixed(2)   + "\n"
                }
            }

            if(_nonRoundShapeNumber >= 2)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt2.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recLong2.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recDiag2.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide2.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.sqrDiag2.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt2.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.ovlLong2.replace("$", "")).toFixed(2)   + "\n"
                }
            }

            if(_nonRoundShapeNumber >= 3)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt3.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recLong3.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recDiag3.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide3.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.sqrDiag3.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt3.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.ovlLong3.replace("$", "")).toFixed(2)   + "\n"
                }
            }

            if(_nonRoundShapeNumber >= 4)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt4.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recLong4.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recDiag4.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide4.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.sqrDiag4.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt4.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.ovlLong4.replace("$", "")).toFixed(2)   + "\n"
                }
            }

            if(_nonRoundShapeNumber >= 5)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt5.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recLong5.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recDiag5.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide5.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.sqrDiag5.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt5.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.ovlLong5.replace("$", "")).toFixed(2)   + "\n"
                }
            }

            if(_nonRoundShapeNumber >= 6)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt6.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recLong6.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recDiag6.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide6.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.sqrDiag6.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt6.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.ovlLong6.replace("$", "")).toFixed(2)   + "\n"
                }
            }

            if(_nonRoundShapeNumber >= 7)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt7.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recLong7.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recDiag7.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide7.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.sqrDiag7.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt7.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.ovlLong7.replace("$", "")).toFixed(2)   + "\n"
                }
            }

            if(_nonRoundShapeNumber >= 8)
            {
                if(_nonRoundShape == 0)
                {
                    reportData += Number(item.recShrt8.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recLong8.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.recDiag8.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 1)
                {
                    reportData += Number(item.sqrSide8.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.sqrDiag8.replace("$", "")).toFixed(2)   + "\n"
                }
                else if(_nonRoundShape == 2)
                {
                    reportData += Number(item.ovlShrt8.replace("$", "")).toFixed(2)   + "\n"
                    reportData += Number(item.ovlLong8.replace("$", "")).toFixed(2)   + "\n"
                }
            }

            reportData += "------\n"
        }
    }

    function doExportFileCSV(fullSavePath)
    {
        reportDataCSVBuilder()
        _viewModel.saveReportTableCSV(fullSavePath, reportData)
           
    }

    function doPrintFilePDF(fullSavePath)
    {
         reportDataPDFBuilder()
        _viewModel.saveReportTablePDF(fullSavePath, reportData, reportHeader)
    }

    Connections{
        target: _viewModel
        function onReportNumberChanged_Signal(number) {
            report_view._lockReportCbbSignal = true
            var temp = report_cbb.currentIndex
            report_cbb_model.clear();
            for(var i = 1; i <= number; i++)
            {
                report_cbb_model.append( { text: qsTr("Report") + " " + i } );
            }
            report_cbb.currentIndex = temp;
            report_view._lockReportCbbSignal = false
        }

        function onAddInspectionData_Signal(data) {
            addData(data)
        }

        function onClearInspectionData_Signal(){
            clearData()
        }

        function onUpdateVisionParamNumber_Signal(bodyRNumber, nonRoundShapeNumber, nonRoundShape){
            _bodyRNumber = bodyRNumber
            _nonRoundShapeNumber = nonRoundShapeNumber
            _nonRoundShape = nonRoundShape
        }

        function onUpdateCurrentReport(number) {
            report_view._lockReportCbbSignal = true
            report_cbb.currentIndex = number
            report_view._lockReportCbbSignal = false
        }
    }


}
