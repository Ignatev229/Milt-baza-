import QtQuick 2.15

import ConfigView 1.0
import "../../Component"

Item {

    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.textColor
    property int _fontSizeText: 12
    property int _numberRow: 10
    property int _numberCol: 10

    ListModel {
        id: _inputItemModel
    }

    Column {
        width: parent.width
        height: parent.height
        spacing: parent.height*0.03
        anchors.horizontalCenter: parent.horizontalCenter


        GridView{
            id: number_grid
            property int padding: parent.width*0.005
            width: parent.width
            height: parent.height*0.9
            focus: true
            model: _inputItemModel
            anchors.verticalCenter: parent.verticalCenter
            cellHeight: height/_numberRow
            cellWidth: width/_numberCol
            clip: true
            interactive: false
            delegate: contacts_delegate
            currentIndex: 0
            cacheBuffer: number_grid.cellHeight * number_grid.numRow
            flow: GridView.FlowLeftToRight
            highlightRangeMode: GridView.ApplyRange
            snapMode: GridView.SnapOneRow

            Component{
                id: contacts_delegate
                Item {
                    width: number_grid.cellWidth
                    height: number_grid.cellHeight

                    Rectangle{
                        width: number_grid.cellWidth - number_grid.padding
                        height: number_grid.cellHeight - number_grid.padding
                        color: "red"
                        radius: 5
                        anchors.centerIn: parent

                        Text {
                            text: number
                            font.pointSize: _fontSize
                            color: _textColor
                            font.family: _fontFamily
                            anchors.centerIn: parent
                            verticalAlignment: Text.AlignVCenter

                        }
                    }
                }
            }
        }

    }

}
