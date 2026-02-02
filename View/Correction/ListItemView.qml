import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import ConfigView 1.0

Rectangle  {
    id: list_view_layout
    property QtObject _dataModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.textColor
    property int _fontSize: 12

    signal currentIndexChanged_Signal(type: int)

    radius: 5
    color: ConfigView.addThinBlueColor
    border.color: "transparent"

    function getIndex(){
        return list_view.currentIndex
    }

    function setIndex(idx){
        list_view.currentIndex = idx
    }

    ListView{
        id: list_view
        anchors.fill: parent
        model: _dataModel
        clip: true
        currentIndex: -1  // No selection initially


        delegate: Rectangle {
            property bool hovered: false  // Track hover state
            width: ListView.view.width
            height: 50
            radius: 5
            border.color: ConfigView.mainBlueColor
            color: hovered ? "lightgray" : (ListView.isCurrentItem ? "lightblue" : "transparent")  // Highlight selected item


            Text {
                anchors.centerIn: parent
                text: displayText
                font.pointSize: _fontSize
                font.family: _fontFamily
                color: ConfigView.addLightBlueColor
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true  // Enable hover detection
                onEntered: parent.hovered = true
                onExited: parent.hovered = false
                onClicked: {
                    list_view.currentIndex = index  // Set selected index
                    list_view_layout.currentIndexChanged_Signal(idx)
                }
            }
            Behavior on color {
                ColorAnimation { duration: 200 }
            }
        }

        // Enable vertical scrolling
        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.ScrollBarAsNeeded
        }
    }
}
