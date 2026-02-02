import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import ConfigView 1.0

import "MaterialDesign"

Item {


    property QtObject _model: QtObject{}
    property var _icon
    property int _fontSize: 12
    property string _fontFamily: "Segoe UI"
    property color _backgroundColor: ConfigView.mainWhiteColor
    property color _backgroundPopupColor: ConfigView.mainWhiteColor
    property color _boderColor: ConfigView.addLightBlueColor
    property color _boderPopupColor: ConfigView.addLightBlueColor
    property color _textColor: ConfigView.mainBlueColor
    property color _textPopupColor: _textColor
    property int _radius: 5

    property string _iconSourceOn: ""
    property string _iconSourceOff: ""
    property color _colorIconDefault : ConfigView.addLightBlueColor
    property color _colorIconMouseOver: ConfigView.addLightBlueColor
    property color _colorIconHigh : ConfigView.addLightBlueColor
    property int _size: height

    signal currentIndexChanged_Signal(index: int)

    function getIndex(){
        return control_list.currentIndex
    }

    function setIndex(value){
        control_list.currentIndex = value
    }

    MaterialDesignIcon {
        id: icon
        name: _iconSourceOn
        color: _colorIconDefault
        size: _size
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
    }
    Rectangle{
        anchors.left: icon.right
        anchors.leftMargin: parent.width*0.03
        anchors.verticalCenter: parent.verticalCenter
        implicitWidth: parent.width - _size - anchors.leftMargin
        implicitHeight: parent.height
        color: "transparent"
        ComboBox {
            id: control_list
            model: _model
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            currentIndex: 0
            width: parent.width
            height: parent.height
            delegate: ItemDelegate {
                width: control_list.width
                anchors.left: parent.left
                contentItem: Item {
                    anchors.fill: parent
                    Image {
                        id: icon_
                        visible: _icon ? true : false
                        source: _icon[index]
                        height: _icon ? control_list.height*0.6 : 0
                        width: height
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: parent.width*0.05
                    }
                    Text {
                        width: parent.width - icon_.width
                        height: parent.height
                        text: modelData
                        color: _textPopupColor
                        font.pointSize: _fontSize
                        font.family: _fontFamily
                        elide: Text.ElideRight
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: icon_.right
                        anchors.leftMargin: parent.width*0.05
                        // x: 10
                    }
                }

                highlighted: control_list.highlightedIndex === index

                required property int index
                required property var modelData
            }

            contentItem: Item {
                anchors.fill: parent
                Image {
                    id: icon__
                    visible: _icon ? true : false
                    source: _icon[control_list.currentIndex] ?  _icon[control_list.currentIndex] : ""
                    height: _icon ? control_list.height*0.6 : 0
                    width: height
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width*0.05
                }
                Text {
                    width: parent.width - icon__.width
                    height: parent.height
                    text: control_list.displayText
                    color: _textColor
                    font.pointSize: _fontSize
                    font.family: _fontFamily
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: icon__.right
                    anchors.leftMargin: parent.width*0.05
                    // x: 10
                }
            }


            background: Rectangle {
                implicitWidth: parent.width
                implicitHeight: parent.height
                color: _backgroundColor
                border.color: control_list.pressed ? _boderColor : _boderColor
                border.width: control_list.visualFocus ? 1 : 1
                radius: _radius
            }

            popup: Popup {
                y: control_list.height
                width: control_list.width
                // implicitHeight: contentItem.implicitHeight
                height: Math.min(500, contentHeight) // Limit the height of the popup
                padding: 1

                contentItem: ListView {
                    clip: true
                    implicitHeight: contentHeight
                    model: control_list.popup.visible ? control_list.delegateModel : null
                    currentIndex: control_list.highlightedIndex

                    ScrollIndicator.vertical: ScrollIndicator { }
                }

                background: Rectangle {
                    color: _backgroundPopupColor
                    border.color: _boderPopupColor
                    radius: _radius
                }
            }

            onCurrentIndexChanged: {
                currentIndexChanged_Signal(currentIndex)
            }
        }

    }

}

