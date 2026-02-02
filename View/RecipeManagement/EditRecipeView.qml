import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Controls 1.5 as C1_5
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4


import ConfigView 1.0

import "../../Component"
import "../../Component/MaterialDesign"
import "VisionParam"


Item {
    id: main_item
    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property int _spacing: height*0.02
    property color _backgroundColor: "#333333"
    property int _cellHeight: parent.height*0.05
    property int _headerWidth: width*0.25*scale
    property int _contentMargin: width*0.3*scale
    property int _contentWidth: width*0.6*scale
    property int _buttonMargin: width*0.9*scale
    property int _buttonWidth: width*0.1
    property int _fontSizeText: 12
    property color _textColor: ConfigView.textColor
    property double scale: 0.15




    ListModel {
        id: _group_input_item_model

        ListElement {
            name: qsTr("Pusher Dimension")
            image_path: ""
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Dimension")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                }
            ]
        }

        ListElement {
            name: qsTr("Height Inspect")
            image_path: "height_insp.png"
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                }
            ]
        }

        ListElement {
            name: qsTr("Weight Inspect")
            image_path: ""
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Weight")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                }
            ]
        }

        ListElement {
            name: qsTr("Non-round Shape Inspect")
            image_path: ""
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Shape")
                    type: "combobox"
                    cbbModel: 1
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Number Dimension")
                    type: "int"
                    range: "[1:8]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 1 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    image_path: "rec_insp.png"
                    image_height: 7
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecShrt")
                    type: "double"
                    range: "[1:99999]"
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecLong")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecDiag")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Square
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    image_path: "sqr_insp.png"
                    image_height: 7
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrSide")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrDiag")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Oval
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    image_path: "ovl_insp.png"
                    image_height: 7
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlShrt")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlLong")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },


                ListElement {
                    name: qsTr("-------------------- Dimension 2 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Square
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrSide")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Oval
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 3 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Square
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrSide")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Oval
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 4 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Square
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrSide")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Oval
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 5 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Square
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrSide")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Oval
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 6 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Square
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrSide")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Oval
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 7 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Square
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrSide")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Oval
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 8 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("RecDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max RecDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Square
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrSide")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrSide Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("SqrDiag")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max SqrDiag Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                // Oval
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlShrt")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlShrt Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("OvlLong")
                    type: "double"
                    range: "[1:99999]"
                    image_path: ""
                    image_height: 3
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max OvlLong Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                }

            ]
        }

        ListElement {
            name: qsTr("BodyR Inspect")
            image_path: "bodyr_insp"
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("Number Dimension")
                    type: "int"
                    range: "[1:23]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 5 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 6 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true

                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 7 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true

                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 8 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true

                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 57 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true

                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },


                ListElement {
                    name: qsTr("-------------------- Dimension 58 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true

                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },


                ListElement {
                    name: qsTr("-------------------- Dimension 59 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true

                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 60 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true

                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 61 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true

                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 62 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true

                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 63 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 64 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true

                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 71 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 72 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 73 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 74 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 75 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 76 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 77 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 78 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 79 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 80 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                ListElement {
                    name: qsTr("-------------------- Dimension 81 --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Height")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                }
            ]
        }

        ListElement {
            name: qsTr("Lean Inspect")
            image_path: "lean_insp.png"
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: false
                },
                ListElement {
                    name: qsTr("Parameter 2")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Deviation")
                    type: "double"
                    range: "[0:1000]"
                    desription: ""
                    isVisible: true
                }
            ]
        }

        // ListElement {
        //     name: qsTr("Lean2 Inspect (Bent Neck)")
        //     image_path: ""
        //     isVisible: true
        //     items: [
        //         ListElement {
        //             name: qsTr("Enable")
        //             type: "bool"
        //             desription: ""
        //             isVisible: true
        //         },
        //         ListElement {
        //             name: qsTr("Angle")
        //             type: "double"
        //             range: "[0:360]"
        //             desription: ""
        //             isVisible: true
        //         },
        //         ListElement {
        //             name: qsTr("Min Tolerance")
        //             type: "double"
        //             range: "[0:360]"
        //             desription: ""
        //             isVisible: true
        //         },
        //         ListElement {
        //             name: qsTr("Max Tolerance")
        //             type: "double"
        //             range: "[0:360]"
        //             desription: ""
        //             isVisible: true
        //         }
        //     ]
        // }

        ListElement {
            name: qsTr("Tilt Inspect")
            image_path: "tilt_insp.png"
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[0:100]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 2")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Height")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: true
                }
            ]
        }

        ListElement {
            name: qsTr("Group Finish Dimension Inspect")
            image_path: ""
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    isVisible: true
                },
                //
                ListElement {
                    name: qsTr("-------------------- F Dimension --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    image_path: "f_dimension_insp.png"
                    image_height: 6
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Dimension")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                //
                ListElement {
                    name: qsTr("-------------------- A Dimension --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    image_path: "a_dimension_insp.png"
                    image_height: 6
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Dimension")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                //
                ListElement {
                    name: qsTr("-------------------- T Dimension --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    image_path: "t_dimension_insp.png"
                    image_height: 6
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 2")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Dimension")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                //
                ListElement {
                    name: qsTr("-------------------- E Dimension --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    image_path: "e_dimension_insp.png"
                    image_height: 6
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 2")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Dimension")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                //
                ListElement {
                    name: qsTr("-------------------- D Dimension --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    image_path: "d_dimension_insp.png"
                    image_height: 6
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 2")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 3")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Dimension")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                //
                ListElement {
                    name: qsTr("-------------------- B Dimension --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    image_path: "b_dimension_insp.png"
                    image_height: 6
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 2")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Dimension")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                //
                ListElement {
                    name: qsTr("-------------------- S Dimension --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    image_path: "s_dimension_insp.png"
                    image_height: 6
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 2")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Dimension")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },

                //
                ListElement {
                    name: qsTr("-------------------- H Dimension --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    image_path: "h_dimension_insp.png"
                    image_height: 6
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 2")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Dimension")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                //
                ListElement {
                    name: qsTr("-------------------- LugT Dimension --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    image_path: "lugt_dimension_insp.png"
                    image_height: 6
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 2")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Dimension")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                //
                ListElement {
                    name: qsTr("-------------------- LugT1 Dimension --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    image_path: "lugt1_dimension_insp.png"
                    image_height: 6
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 2")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Dimension")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                //
                ListElement {
                    name: qsTr("-------------------- D Angle --------------------")
                    type: "seperator"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    image_path: "d_angle_insp.png"
                    image_height: 6
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 2")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 3")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Angle")
                    type: "double"
                    range: "[0:360]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[0:360]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[0:360]"
                    desription: ""
                    isVisible: true
                }

            ]
        }

        ListElement {
            name: qsTr("Flange Inspect")
            image_path: "flange_dimension_insp.png"
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 2")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 3")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 4")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: true
                }
            ]
        }

        ListElement {
            name: qsTr("Knockout Inspect")
            image_path: "knockout_dimension_insp.png"
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 2")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 3")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 4")
                    type: "double"
                    range: "[0:99999]"
                    desription: ""
                    isVisible: true
                }
            ]
        }

        ListElement {
            name: qsTr("Pushup Inspect")
            image_path: "pushup_dimension_insp.png"
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Pushup")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                }
            ]
        }

        ListElement {
            name: qsTr("Inside Neck Inspect")
            image_path: "inside_neck_insp.png"
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Parameter 1")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Diameter")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                }
            ]
        }

        ListElement {
            name: qsTr("Wall Thickness Inspect")
            image_path: ""
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Thickness")
                    type: "double"
                    range: "[1:99999]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Min Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Max Tolerance")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                }
            ]
        }

        ListElement {
            name: qsTr("Code Number Decode")
            image_path: ""
            isVisible: true
            items: [
                ListElement {
                    name: qsTr("Enable")
                    type: "bool"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("Code Number")
                    type: "int"
                    range: "[1:99]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("ROI Bottom")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                },
                ListElement {
                    name: qsTr("ROI Height")
                    type: "double"
                    range: "[1:1000]"
                    desription: ""
                    isVisible: true
                }
            ]
        }

        // ListElement {
        //     name: qsTr("Seam Inspect")
        //     image_path: ""
        //     isVisible: true
        //     items: [
        //         ListElement {
        //             name: qsTr("Enable")
        //             type: "bool"
        //             desription: ""
        //             isVisible: true
        //         },
        //         ListElement {
        //             name: qsTr("Body Height")
        //             type: "double"
        //             range: "[1:99999]"
        //             desription: ""
        //             isVisible: true
        //         },
        //         ListElement {
        //             name: qsTr("Min Body Height Tolerance")
        //             type: "double"
        //             range: "[1:1000]"
        //             desription: ""
        //             isVisible: true
        //         },
        //         ListElement {
        //             name: qsTr("Max Body Height Tolerance")
        //             type: "double"
        //             range: "[1:1000]"
        //             desription: ""
        //             isVisible: true
        //         },
        //         ListElement {
        //             name: qsTr("Bottom Height")
        //             type: "double"
        //             range: "[1:99999]"
        //             desription: ""
        //             isVisible: true
        //         },
        //         ListElement {
        //             name: qsTr("Min Bottom Height Tolerance")
        //             type: "double"
        //             range: "[1:1000]"
        //             desription: ""
        //             isVisible: true
        //         },
        //         ListElement {
        //             name: qsTr("Max Bottom Height Tolerance")
        //             type: "double"
        //             range: "[1:1000]"
        //             desription: ""
        //             isVisible: true
        //         }
        //     ]
        // }


    }


    property int itemHeight: height*0.08
    property int itemWidth: width*0.92
    property int itemSpacing: height*0.015
    property int itemColumnSpacing: width*0.03
    property int itemColumn1Width: width*0.27
    property int itemColumn2Width: width*0.28
    property int groupSpacing: height*0.04
    property int headerHeight: height*0.03

    Column {
        height: parent.height
        width: parent.width*0.96
        spacing: groupSpacing
        anchors.centerIn: parent
        Row {
            height: parent.height*0.1
            width: parent.width*0.96
            spacing: parent.width*0.03
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                text: qsTr("Recipe") + ": "
                width: parent.width*0.1
                font.pointSize: _fontSizeText + 2
                color: ConfigView.mainBlueColor
                font.family: _fontFamily
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter

            }

            Text {
                text: recipeManagementVM.currentRecipe
                width: contentWidth
                font.pointSize: _fontSizeText + 2
                color: ConfigView.mainBlueColor
                font.family: _fontFamily
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            ButtonMaterialTextHorizontal{
                id: save_btn
                height: parent.height*0.9
                _size: height*0.8
                _text: qsTr("Save")
                _iconSourceOn: "contentSave"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: main_item._fontFamily
                _textRatio: 0.4
                onClicked: {
                    var data = []
                    for(var i = 0; i < _group_input_item_model.count; i++){
                        var values = group_input_items.itemAt(i).getValues()
                        data.push(values)
                    }
                    _viewModel.saveVisionParam_Slot(data)
                }
            }

            ToggleButtonMaterialTextHorizontal{
                height: parent.height*0.9
                width: save_btn.width
                _size: height*0.8
                _text: _isClicked ? qsTr("Collapse") : qsTr("Expand")
                _iconSourceOn: "arrowCollapseVertical"
                _iconSourceOff: "arrowExpandVertical"
                _colorIconDefault: ConfigView.mainBlueColor
                _colorIconMouseOver: _colorIconDefault
                _colorIconHigh: ConfigView.mainBlueColor
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: _fontFamily
                _textRatio: 0.35
                onClicked: {
                    for(var i = 0; i < group_input_items.model.count; i++){
                        group_input_items.itemAt(i).doSwitchExpand(_isClicked);
                    }
                }
            }

        }

        C1_5.ScrollView {
            width: parent.width
            height: parent.height*0.88
            anchors.horizontalCenter: parent.horizontalCenter
            style: ScrollViewStyle {
                property int iScrollWidth: 10
                handle: Rectangle {
                    implicitWidth: iScrollWidth
                    color: "lightgray"
                    radius: 20
                }
                scrollBarBackground: Rectangle {
                    implicitWidth: iScrollWidth
                    color: "gray"
                    radius: 20
                }
                decrementControl: Rectangle {
                    implicitWidth: 0
                }
                incrementControl: Rectangle {
                    implicitWidth: 0
                }
            }

            verticalScrollBarPolicy: Qt.ScrollBarAsNeeded
            horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            flickableItem.flickableDirection : Flickable.VerticalFlick
            flickableItem.boundsBehavior: Flickable.StopAtBounds

            ColumnLayout  {
                // width: parent.width
                // height: parent.height*0.98

                spacing: groupSpacing
                clip: true

                Rectangle {
                    width: parent.width
                    height: 10
                    color: "transparent"

                }

                Repeater {
                    id: group_input_items
                    model: _group_input_item_model
                    delegate:
                        GroupInputItems {
                            id: group_input
                            width: parent.width
                            height: itemHeight*(model.items.length + 0.5)
                            _groupName: model.name
                            _inputItemModel: model.items
                            _headerHeight: headerHeight
                            _itemWidth: itemWidth
                            _itemHeight: itemHeight
                            _itemSpacing: itemSpacing
                            _itemColumnSpacing: itemColumnSpacing
                            _itemColumn1Width: itemColumn1Width
                            _itemColumn2Width: itemColumn2Width
                            _imageName: model.image_path
                        }


                }
            }
        }
    }

    Rectangle {
        visible: false
        width: parent.width*0.25
        height: parent.height*0.2
        color: "orange"
        opacity: 0.6
        anchors.right: parent.right
        anchors.top: parent.top

        transitions: Transition
        {
            reversible: true
            from: ""
            to: "iconOff"
            PropertyAnimation
            {
                properties: "x,y,visible"
                easing.type: Easing.InOutQuad
                from: selectIconRow
                property: "visible"
            }
        }

        Text {
            text: qsTr("The distance from the bottom of the Container to the highest point on the finish of the Container")
            width: parent.width*0.8
            font.pointSize: _fontSizeText + 2
            color: _textColor
            font.family: _fontFamily
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            wrapMode: Text.WrapAnywhere

        }
    }

    Connections {
        target: _viewModel
        function onUpdateVisionParamToUI_Signal(data) {
            // update vision param
            for(var i = 0; i < data.length; i++){
                group_input_items.itemAt(i).setValues(data[i]);
                group_input_items.itemAt(i).doSwitchExpand(false);
            }
        }
        function onChangeLanguage_Signal() {
            for(var i = 0; i < group_input_items.model.count; i++){
                // group_input_items.itemAt(i).processValueChangedAgain();
            }
        }
    }

}
