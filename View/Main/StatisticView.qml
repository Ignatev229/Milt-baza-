import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.Controls 1.4 as QtC1
import QtQuick.Controls.Styles 1.1
import QtCharts 2.15

import "../../Component"
import ConfigView 1.0
Item {
    id: main_layout
    property QtObject _model: QtObject{}
    property QtObject _tableModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property int _fontSizeText: 10
    property string _statisticName: qsTr("Statistic")
    property color _textActivateColor: "white"//"#90CAF9"
    property color headerColor: ConfigView.mainWhiteColor
    property color borderColor: ConfigView.addGrayColor
    property color textColor: "black"
    property int borderSize: 1
    property int numberColumn: 3
    property int numberRow: 8

    QtObject{
        id: tableObjectID
        property int widthCell: (content.width)/(main_layout.numberColumn) + borderSize
        property int heightCell: (content.height)/(main_layout.numberRow + 1)
    }

    Column{
        anchors.fill: parent
        anchors.centerIn: parent

        Rectangle{
            id: header_id
            width: parent.width
            height: parent.height*0.15
            color: ConfigView.addLightBlueColor
            Label {
                width: parent.width
                text: _statisticName
                wrapMode: Label.Wrap
                color: _textActivateColor
                font.family: _fontFamily
                font.pointSize: _fontSizeText + 1
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            ButtonMaterialTextHorizontal{
                height: parent.height*0.9
                // width: height*2.5
                _size: height*0.8
                _text: qsTr("Reset")
                _iconSourceOn: "restart"
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.01
                anchors.verticalCenter: parent.verticalCenter
                _colorBGDefault: ConfigView.addGrayColor
                _colorBGMouseOver: ConfigView.addThinBlueColor
                _fontFamily: main_layout._fontFamily
                _textRatio: 0.4
                onClicked: {
                    statisticsVM.resetStatistics_Qml_Slot()
                }
            }

        }

        Row {
            width:  parent.width
            height: parent.height - header_id.height

            Rectangle{
                width:  parent.width*0.3
                height: parent.height
                color: ConfigView.mainWhiteColor

                Rectangle {
                    width: parent.width*0.1
                    height: parent.height*0.5
                    anchors.verticalCenter: parent.verticalCenter
                    color: "transparent"
                    ButtonMaterialTextHorizontal{
                        height: parent.height*0.4
                        _size: height*0.8
                        _text: qsTr("Pass")
                        _iconSourceOn: "circleSlice-2"
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.leftMargin: parent.width*0.05
                        _fontFamily: main_layout._fontFamily
                        _textRatio: 0.25
                        _borderWidth: 0
                        _colorBGDefault: ConfigView.addGrayColor
                        _colorBGMouseOver: _colorBGDefault
                        _colorIconDefault: ConfigView.acceptSignalColor
                        _colorIconMouseOver: _colorIconDefault
                        _colorIconHigh: _colorIconDefault
                    }

                    ButtonMaterialTextHorizontal{
                        height: parent.height*0.4
                        _size: height*0.8
                        _text: qsTr("Fail")
                        _iconSourceOn: "circleSlice-2"
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.leftMargin: parent.width*0.05
                        _fontFamily: main_layout._fontFamily
                        _textRatio: 0.25
                        _borderWidth: 0
                        _colorBGDefault: ConfigView.addGrayColor
                        _colorBGMouseOver: _colorBGDefault
                        _colorIconDefault: ConfigView.cancelSignalColor
                        _colorIconMouseOver: _colorIconDefault
                        _colorIconHigh: _colorIconDefault
                    }
                }

                ChartView {
                    id: chart
                    width: parent.width*3
                    height: parent.height*1
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter

                    title: ""
                    titleColor: "#000000FF"
                    titleFont.family: _fontFamily
                    titleFont.pointSize: height*0.03
                    titleFont.bold: true

                    legend.font.pointSize: height*0.015
                    legend.font.family: _fontFamily
                    legend.alignment: Qt.AlignBottom
                    legend.visible: false

                    backgroundColor: "transparent"
                    antialiasing: true
                    // theme: ChartView.ChartThemeDark
                    animationOptions: ChartView.AllAnimations
                    dropShadowEnabled: true

                    PieSeries {
                        id: pieOuter
                        size: 0.9
                        holeSize:0
                        verticalPosition: 0.52
                        horizontalPosition: 0.54
                        // onHovered: {
                        //     if (state)
                        //         chart.ToolTip.show(slice.label + ":" + slice.value)
                        //     else
                        //         chart.ToolTip.hide()
                        // }
                        PieSlice {
                            label: value + "%"
                            value:  statisticsVM.yieldPass
                            color: ConfigView.acceptSignalColor
                            labelColor: "white"
                            labelVisible : true
                            labelArmLengthFactor: 0.1
                            labelFont.underline: false
                            labelPosition: PieSlice.LabelInsideHorizontal
                        }
                        PieSlice {
                            label: value + "%"
                            value:  100 - statisticsVM.yieldPass
                            color: ConfigView.cancelSignalColor
                            labelColor: "white"
                            labelVisible : true
                            labelArmLengthFactor: 0.1
                            labelFont.underline: false
                            labelPosition: PieSlice.LabelInsideHorizontal
                        }
                    }
                }

            }

            Rectangle{
                id: content
                width:  parent.width*0.7
                height: parent.height
                color: ConfigView.mainWhiteColor
                clip : true

                QtC1.TableView {
                    id: tableview
                    width: parent.width
                    height: parent.height
                    clip: true
                    alternatingRowColors: true
                    model: _model

                    style: TableViewStyle{
                        textColor: "white"
                        alternateBackgroundColor: ConfigView.mainWhiteColor
                    }

                    horizontalScrollBarPolicy: ScrollBar.AlwaysOff
                    verticalScrollBarPolicy: ScrollBar.AsNeeded

                    QtC1.TableViewColumn {
                        role: "content"
                        title: qsTr("Defect")
                        width: tableObjectID.widthCell*2
                        horizontalAlignment: Text.AlignHCenter
                    }
                    QtC1.TableViewColumn {
                        role: "value"
                        title: qsTr("Count")
                        width: tableObjectID.widthCell
                        horizontalAlignment: Text.AlignHCenter
                    }

                    headerDelegate:Rectangle{
                        color: headerColor
                        height: tableObjectID.heightCell
                        border.width: borderSize
                        border.color: borderColor
                        Text{
                            anchors.centerIn : parent
                            text: styleData.value
                            color: textColor
                            font.pointSize: _fontSizeText + 1
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    rowDelegate: Rectangle {
                        height: tableObjectID.heightCell
                    }

                    itemDelegate: Rectangle {
                        height: tableObjectID.heightCell
                        border.width: borderSize
                        border.color: borderColor
                        color: {
                            // return "#222222"
                            if(styleData.row === 1 || styleData.row === 2)
                                return ConfigView.cancelSignalColor
                            if(styleData.row === 3)
                                return ConfigView.acceptSignalColor
                            return ConfigView.mainWhiteColor

                        }
                        Text {
                            id: content_text
                            width: parent.width
                            height: parent.height
                            text: {
                                return styleData.value
                            }
                            color: 'black'
                            font.pointSize: _fontSizeText
                            anchors.centerIn : parent
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.WordWrap
                        }
                    }

                }

            }

        }



//        ButtonMaterialTextLongPress{
//            _width: parent.width
//            _height: parent.height*0.09
//            _iconSourceOn: "autorenew"
//            _colorOverlayLow: "black"
//            _colorOverlayHigh: "black"
//            _colorText: "black"
//            _text: "Reset Counter"
//            _size: _height*0.8
//            anchors.horizontalCenter: parent.horizontalCenter
//            onClicked: {
//                _tableModel.resetLotData_Qml_Slot()
//            }
//        }

    }


}
