import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import ConfigView 1.0


Item {

    id: pixel_ruler_layout
    property int _fontSizeText: 10
    property string _fontFamily: ConfigView.fontFamily
    property QtObject _model: QtObject{}
    property color _textActivateColor: "white"//"#90CAF9"
    property color headerColor: "#FF083A6A"
    property color columnColor: "#007ACC"
    property string _headerName: qsTr("Pixel Ruler")


    property int previousX
    property int previousY


    function updateData(prePosX, prePosY, posX, posY, trackIndex){
        var diffX = posX - prePosX
        direct_x.text = diffX.toFixed(2) + " " + qsTr("pixel")
        var diffY = posY - prePosY
        direct_y.text = diffY.toFixed(2) + " " + qsTr("pixel")
        var angle = Math.atan2(diffY, diffX)
        angle_rad.text = angle.toFixed(2) + " " + qsTr("rad")
        angle_deg.text = (angle*180/Math.PI).toFixed(2) + " " + qsTr("deg")
        var distance = Math.sqrt(diffX*diffX + diffY*diffY)
        distance_pixel.text = distance.toFixed(2) + " " + qsTr("pixel")
        distance_um.text = (distance*mainHomeVM.resolutions[trackIndex]).toFixed(2) + " " + qsTr("um")
    }

    function startToChangeLanguage(){
        var stringArray = direct_x.text.split(" ")
        direct_x.text = stringArray[0] + " " + qsTr("pixel")
        stringArray = direct_y.text.split(" ")
        direct_y.text = stringArray[0] + " " + qsTr("pixel")
        stringArray = angle_rad.text.split(" ")
        angle_rad.text = stringArray[0] + " " + qsTr("rad")
        stringArray = angle_deg.text.split(" ")
        angle_deg.text = stringArray[0] + " " + qsTr("deg")
        stringArray = distance_pixel.text.split(" ")
        distance_pixel.text = stringArray[0] + " " + qsTr("pixel")
        stringArray = distance_um.text.split(" ")
        distance_um.text = stringArray[0] + " " + qsTr("um")
    }


    opacity: 0.7

    Column{
        anchors.fill: parent
        anchors.centerIn: parent
        Rectangle{
            //header
            id: header
            width:  parent.width
            height: parent.height*0.2
            color: headerColor
            clip : true

            Text {
                text: _headerName
                width: parent.width
                height: parent.height
                font.family: _fontFamily
                font.pointSize: _fontSizeText + 1
                font.bold: true
                color: _textActivateColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }



            MouseArea{
                anchors.fill: parent
                onPressed: {
                    previousX = mouseX
                    previousY = mouseY
                }
                onMouseXChanged: {
                    var dx = mouseX - previousX
                    pixel_ruler_dialog.x = (pixel_ruler_dialog.x + dx)
                }
                onMouseYChanged: {
                    var dy = mouseY - previousY
                    pixel_ruler_dialog.y = (pixel_ruler_dialog.y + dy)
                }
            }
        }


        Rectangle{
            id: content
            width:  parent.width
            height: parent.height - header.height
            color: "transparent"
            clip : true
            Row{
                anchors.fill: parent
                Column {
                    width:  parent.width/3
                    height: parent.height

                    spacing:  parent.height*0.01
                    Text {
                        text: qsTr("Direction")
                        width: parent.width
                        height: parent.height*0.32
                        font.family: _fontFamily + 1
                        font.pointSize: _fontSizeText
                        font.bold: true
                        color: columnColor
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        id: direct_x
                        text: qsTr("X") + ": __ " + qsTr("pixel")
                        width: parent.width
                        height: parent.height*0.32
                        font.family: _fontFamily
                        font.pointSize: _fontSizeText
                        font.bold: true
                        color: _textActivateColor
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        id: direct_y
                        text: qsTr("Y") + ": __ " + qsTr("pixel")
                        width: parent.width
                        height: parent.height*0.32
                        font.family: _fontFamily
                        font.pointSize: _fontSizeText
                        font.bold: true
                        color: _textActivateColor
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                Column {
                    width:  parent.width/3
                    height: parent.height

                    spacing:  parent.height*0.01
                    Text {
                        text: qsTr("Angle")
                        width: parent.width
                        height: parent.height*0.32
                        font.family: _fontFamily + 1
                        font.pointSize: _fontSizeText
                        font.bold: true
                        color: columnColor
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        id: angle_deg
                        text: "__ " +  qsTr("deg")
                        width: parent.width
                        height: parent.height*0.32
                        font.family: _fontFamily
                        font.pointSize: _fontSizeText
                        font.bold: true
                        color: _textActivateColor
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        id: angle_rad
                        text: "__ " + qsTr("rad")
                        width: parent.width
                        height: parent.height*0.32
                        font.family: _fontFamily
                        font.pointSize: _fontSizeText
                        font.bold: true
                        color: _textActivateColor
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                Column {
                width:  parent.width/3
                height: parent.height

                spacing:  parent.height*0.01
                Text {
                    text: qsTr("Distance")
                    width: parent.width
                    height: parent.height*0.32
                    font.family: _fontFamily + 1
                    font.pointSize: _fontSizeText
                    font.bold: true
                    color: columnColor
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    id: distance_pixel
                    text: "__ " +  qsTr("pixel")
                    width: parent.width
                    height: parent.height*0.32
                    font.family: _fontFamily
                    font.pointSize: _fontSizeText
                    font.bold: true
                    color: _textActivateColor
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    id: distance_um
                    text: "__ " + qsTr("um")
                    width: parent.width
                    height: parent.height*0.32
                    font.family: _fontFamily
                    font.pointSize: _fontSizeText
                    font.bold: true
                    color: _textActivateColor
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }
            }
        }

    }

}

