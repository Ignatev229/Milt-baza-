import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.5 as C1_5
import ConfigView 1.0
import QtQuick.Controls.Styles 1.4

import "../../View"
import "../../Component"

import BI.modbus.MBDiagnosticDataContext 1.0
import BI.modbus.Modbus_list_model 1.0
Item {
    id: diagnostic_view
    width: parent.width
    height: parent.height

    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: "black"
    property int _fontSize: 13


    // allow max display 4 item per row
    readonly property int _numberCol: 4

    function getColorStatus(state){

       switch(state) {
            case DiagnosticItemStatus.ITEM_OFF:
                return ConfigView.warningSignalColor;
            case DiagnosticItemStatus.ITEM_ON:
                return ConfigView.acceptSignalColor;
            case DiagnosticItemStatus.ITEM_ERROR:
                return ConfigView.cancelSignalColor;
            default:
                return "gray";
        }
    }


    //ScrollView {
        //width: parent.width
        //height: parent.height
        //anchors.centerIn: parent
        //contentWidth: grid_layout.width
        //contentHeight: grid_layout.height
        //clip: true
        //style: ScrollViewStyle {
        //    property int iScrollWidth: 10
        //    handle: Rectangle {
        //        implicitWidth: iScrollWidth
        //        color: "lightgray"
        //        radius: 20
        //    }
        //    scrollBarBackground: Rectangle {
        //        implicitWidth: iScrollWidth
        //        color: "gray"
        //        radius: 20
        //    }
        //    decrementControl: Rectangle {
        //        implicitWidth: 0
        //    }
        //    incrementControl: Rectangle {
        //        implicitWidth: 0
        //    }
        //}

        //verticalScrollBarPolicy: Qt.ScrollBarAsNeeded
        //horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        //flickableItem.flickableDirection : Flickable.VerticalFlick
        //flickableItem.boundsBehavior: Flickable.StopAtBounds
        //ScrollBar.vertical.policy: ScrollBar.AlwaysOn


        //ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        //ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        
        //Flickable {
        //id: flickableItem
        //contentWidth: grid_layout.width
        //contentHeight: grid_layout.height
        //boundsBehavior: Flickable.StopAtBounds

        GridView{
            id: grid_layout
            property int padding: parent.width*0.005
            width: parent.width
            height: parent.height
            ScrollBar.vertical: ScrollBar {
                visible: true
            }
            // focus: true
            model: Modbus_list_model{
                pMBList: MBDiagnosticDataContext
            }
            anchors.horizontalCenter: parent.horizontalCenter
            cellHeight: height * 0.2
            cellWidth: width / _numberCol
            keyNavigationEnabled: true
            keyNavigationWraps: true
            clip: true
            interactive: true
            delegate:mbSensor_delegate
            currentIndex: 0
            flow: GridView.FlowLeftToRight
            highlightRangeMode: GridView.ApplyRange
            snapMode: GridView.SnapOneRow

            onCurrentIndexChanged: {
                console.log(currentIndex)
            }
            Component{
                id: mbSensor_delegate
                Item {
                    width: grid_layout.cellWidth
                    height: grid_layout.cellHeight
                    Rectangle{
                        width: grid_layout.cellWidth - grid_layout.padding
                        height: grid_layout.cellHeight - grid_layout.padding
                        color: getColorStatus(model.value)
                        radius: 5
                        anchors{
                            verticalCenter: parent.verticalCenter
                            horizontalCenter: parent.horizontalCenter
                        }
                    }

                    Text{
                        id: text
                        text: model.description
                        color: "black"
                        font.family: _fontFamily
                        font.pointSize: _fontSize
                        font.bold: true
                        anchors.centerIn: parent
                        width: grid_layout.cellWidth - grid_layout.padding
                        height: parent.height*0.8
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WrapAnywhere
                    }

                    // MouseArea {
                    //     anchors.fill: parent
                    //     onClicked: {
                    //         grid_layout.currentIndex = index
                    //     }
                    // }
                }
            }
        

        //}
       
    }
}
