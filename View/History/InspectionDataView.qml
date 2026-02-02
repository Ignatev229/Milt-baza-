import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4 as QtC1
import QtQuick.Controls.Styles 1.1


import ConfigView 1.0

import "../../View"
import "../../Component"
Item {
    id: inspection_data_view
    width: parent.width
    height: parent.height

    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.textColor

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
        property int widthCell: (tableview.width)/(inspection_data_view._numberColumn) + inspection_data_view._borderSize
        property int heightCell: (tableview.height)/(inspection_data_view._numberRow)
    }

    function clearData()
    {
        sectionedModel.clear();
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
        height: parent.height*0.96
        width: parent.width*0.98
        spacing: parent.height*0.02
        anchors.centerIn: parent

        QtC1.TableView {
            id: tableview
            height: parent.height
            width: parent.width
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
                    return styleData.row %2 ? "#343434" : "#222222"
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

        function onUpdateVisionParamNumber_Signal(bodyRNumber, nonRoundShapeNumber, nonRoundShape){
            _bodyRNumber = bodyRNumber
            _nonRoundShapeNumber = nonRoundShapeNumber
            _nonRoundShape = nonRoundShape
        }
    }
}
