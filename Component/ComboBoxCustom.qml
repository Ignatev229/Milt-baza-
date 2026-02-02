import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import ConfigView 1.0

ComboBox {
    id: control_list
    property QtObject _model: QtObject{}
    property int _fontSize: 12
    property string _fontFamily: "Segoe UI"
    property color _backgroundColor: ConfigView.mainWhiteColor
    property color _boderColor: ConfigView.addLightBlueColor
    property color _textColor: ConfigView.mainBlueColor
    property color _backgroundDefaultColor: _backgroundColor
    property int _radius: 5


    model: _model
    currentIndex: 0
    width: parent.width
    height: parent.height
    delegate: ItemDelegate {
        width: control_list.width
        contentItem: Text {
            text: modelData
            color: _textColor
            font.pointSize: control_list._fontSize
            font.family: control_list._fontFamily
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
            x: 10
        }
        highlighted: control_list.highlightedIndex === index

        required property int index
        required property var modelData
    }

    contentItem: Text {
        leftPadding: 10
        text: control_list.displayText
        font.pointSize: control_list._fontSize
        font.family: control_list._fontFamily
        color: control_list.pressed ? _textColor : _textColor
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: parent.width
        implicitHeight: parent.height
        color: _backgroundDefaultColor
        border.color: control_list.pressed ? _boderColor : _boderColor
        border.width: control_list.visualFocus ? 1 : 1
        radius: _radius
    }

    popup: Popup {
        y: control_list.height - 1
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
            color: _backgroundColor
            border.color: _boderColor
            radius: _radius
        }
    }
}

