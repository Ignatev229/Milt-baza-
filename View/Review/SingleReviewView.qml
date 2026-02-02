import QtQuick 2.12



import ImageWriter 1.0
import ConfigView 1.0

Item {
    id: single_review_view_id
    width: parent.width
    height: parent.height
    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property color chooseDocColor: ConfigView.addLightBlueColor
    property color passDocColor: ConfigView.acceptSignalColor
    property color failDocColor: ConfigView.cancelSignalColor
    property string _headerInfo: "Infomation"
    property color _textColor: "white"
    property int _fontSizeText: 12
    property int _docChoosed: -1
    property bool _isTrackChoosed: false
    signal imageViewChoosed_Signal(docIndex: int) //


    Rectangle{
        width: parent.width
        height: parent.height
        radius: 5
        gradient: Gradient {
            GradientStop { position: 0.0; color: _viewModel.info.toLowerCase() === "pass" ? passDocColor :
                                                (_viewModel.info.toLowerCase() === "none" ? chooseDocColor : failDocColor)}
            GradientStop { position: 0.22; color: _viewModel.info.toLowerCase() === "pass" ? passDocColor :
                                                (_viewModel.info.toLowerCase() === "none" ? chooseDocColor : failDocColor) }
            GradientStop { position: 0.221; color: ConfigView.addThinBlueColor }
            GradientStop { position: 1.0; color: ConfigView.addThinBlueColor }
        }

        Rectangle{
            //header
            id: header
            width:  parent.width
            height: parent.height*0.22
            color: "transparent"
            clip : true

            Text {
                text: _viewModel.info === "None" ? qsTr("None") : _viewModel.info //_headerInfo
                width: parent.width
                height: parent.height
                font.family: _fontFamily
                font.pointSize: _fontSizeText + 1
                font.bold: true
                color: _textColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        Grid {
            width: parent.width
            height: parent.height - header.height - parent.height*0.1
            rows: 1
            columns: 2
            spacing: parent.width*0.02
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height*0.05
            Repeater{
                model: 2
                delegate: Item{
                    width: parent.width*0.48
                    height: parent.height
                    Rectangle{
                        x: image_writer.ui_left - parent.width*0.01 + 1
                        y: image_writer.ui_top - parent.width*0.01 + 1
                        width: image_writer.ui_width + parent.width*0.02
                        height: image_writer.ui_height + parent.width*0.02
                        color: chooseDocColor
                        visible: _docChoosed === index && _isTrackChoosed
                    }
                    ImageWriter{
                        id: image_writer
                        width: parent.width
                        height: parent.height
                        ui_image: _viewModel.listImage[index]

                        MouseArea {
                            anchors.fill: parent
                            onClicked:{
                                single_review_view_id.imageViewChoosed_Signal(index)

                            }
                        }
                    }
                }
            }
        }



    }
}
