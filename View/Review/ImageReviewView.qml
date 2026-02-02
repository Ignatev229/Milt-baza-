import QtQuick 2.0
import QtQuick.Layouts 1.0

// My import
import ImageWriter 1.0
import ConfigView 1.0
import "../../Component"

Item {
    id: image_view

    property QtObject _viewModel: QtObject{}


    property color _textDefaultColor: ConfigView.textColor
    property color _textActivateColor: ConfigView.mainWhiteColor
    property double fontSize: image_view_name.height*0.3
    property string _fontFamily: ConfigView.fontFamily
    signal imageViewMouseAction_Signal(type: int) //
    Rectangle{
        anchors.fill: parent
        anchors.centerIn: parent
        color: "transparent"

        Rectangle{
            //header
            id: header
            width:  parent.width
            height: parent.height*0.04
            color: ConfigView.addLightBlueColor
            clip : true

            Text {
                id: image_view_name
                text: _viewModel.docName
                width: parent.width*0.18
                height: parent.height
                font.family: _fontFamily
                font.pointSize: fontSize
                font.bold: true
                color: _textActivateColor
                verticalAlignment: Text.AlignVCenter
                anchors.left: parent.left
                anchors.leftMargin: parent.width*0.02
            }

            Rectangle{
                width: parent.width*0.25
                height: parent.height
                color: "transparent"
                anchors.right: parent.right
                anchors.rightMargin: parent.width*0.02
                ToggleButtonMaterial{
                    id: overlay_button
                    _width: parent.height*0.9
                    _height: parent.height*0.9
                    _size: _height*1.3
                    _iconSourceOn: "cardOutline"
                    _iconSourceOff: "cardOffOutline"
                    _colorBorder: " transparent"
                    _isClicked: true
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: parent.width*0
                }
            }


        }

        Rectangle{
            width: parent.width
            height:parent.height - header.height
            anchors.top: header.bottom
            color: "transparent"
            Rectangle{
                id: image_container
                width: parent.width
                height:parent.height
                y: header.height
                color: ConfigView.addThinBlueColor
                visible: _viewModel.isConnectCam
                anchors{
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                }

                Flickable{
                    id: flick
                    width: parent.width
                    height: parent.height*(zoomTool.sectorViewMode ? 0.7 : 1)
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    contentHeight: height
                    contentWidth: width
                    boundsBehavior: Flickable.StopAtBounds
                    clip: true
                    PinchArea{
                       id: pinch
                       anchors.fill: parent

                       property real initialWidth
                       property real initialHeight

                       onPinchStarted: {
                           initialWidth = flick.contentWidth
                           initialHeight = flick.contentHeight
                       }

                       onPinchUpdated: {
                           flick.contentX += pinch.previousCenter.x - pinch.center.x
                           flick.contentY += pinch.previousCenter.y - pinch.center.y
                           flick.resizeContent(initialWidth * pinch.scale, initialHeight * pinch.scale, pinch.center)
                       }

                       onPinchFinished: {
                           flick.returnToBounds()
                        }
                    }


                    ImageWriter {
                       id: image_writer
                       width: flick.contentWidth
                       height: flick.contentHeight
                       ui_image: overlay_button._isClicked ? _viewModel.imageOverlay : _viewModel.image
                       opacity: _viewModel.isShowBelowImage ? 0.5 : 1
                       onUpdateSourceImage:{
                            zoomTool.sizeChanged()
                       }

                       MouseArea {
                           id: zoomTool
                           focus: true
                           property int zoomTime: 0
                           property int currentScale: 1
                           property bool pressDoc: false
                           property var flickQueue: []
                           property bool isCtrlPress: false
                           property bool isKeySToggle: false
                           property double scaleX4Flick
                           property double scaleY4Flick
                           x: image_writer.ui_left
                           y: image_writer.ui_top
                           width: image_writer.ui_width
                           height: image_writer.ui_height
                           signal sizeChanged()
                           acceptedButtons: Qt.LeftButton | Qt.RightButton
                           hoverEnabled: true


                           onWheel:{
                                if(zoomTool.zoomTime > 10 && wheel.angleDelta.y > 0) {/*zoomTool.doZoomFit(); */return;}
                                // if(wheel.angleDelta.y/120 > 1 || wheel.angleDelta.y/120 < -1)
                                //     console.warn("Scroll mouse too fast, pls slow donw")
                                // else{
                                 if (wheel.angleDelta.y/120*flick.contentWidth*0.1+flick.contentWidth > flick.width &&
                                         wheel.angleDelta.y/120*flick.contentHeight*0.1+flick.contentHeight > flick.height){

                                     if((wheel.angleDelta.y > 0) ){
                                         activeFlick((mouseX + (image_writer.width - image_writer.ui_width)/2)/flick.contentWidth,
                                                     (mouseY + (image_writer.height - image_writer.ui_height)/2)/flick.contentHeight,
                                                     false)
                                     }
                                     if((wheel.angleDelta.y < 0)){
                                         activeFlick((mouseX + (image_writer.width - image_writer.ui_width)/2)/flick.contentWidth,
                                                     (mouseY + (image_writer.height - image_writer.ui_height)/2)/flick.contentHeight,
                                                     true)
                                     }

                                     zoomTool.currentScale = 1 + 0.25*zoomTool.zoomTime
                                 }
                                 else {
                                     flick.resizeContent(flick.width, flick.height, Qt.point(flick.width/2, flick.height/2))
                                     flick.returnToBounds()
                                     zoomTool.zoomTime = 0
                                     zoomTool.currentScale = 1
                                  }
                                // }
                            }


                           onClicked:{
                               if(mouse.button == Qt.RightButton){
                                   zoomTool.doZoomFit()
                               }
                               else if (mouse.button == Qt.LeftButton){
                                   image_view.imageViewMouseAction_Signal(ConfigView.MOUSE_ACTION.LEFT_CLICK)
                               }
                           }

                           onDoubleClicked: {
                               if(mouse.button === Qt.LeftButton){
                                   image_view.imageViewMouseAction_Signal(ConfigView.MOUSE_ACTION.LEFT_DOUBLE_CLICK)
                               }
                               else if(mouse.button === Qt.RightButton){
                               }
                               else{console.log("Mouse double click action fail")}
                           }

                           function activeFlick(scaleX, scaleY, isZoomIn){

                              scaleX4Flick = scaleX
                              scaleY4Flick = scaleY

                              if (isZoomIn){
                                  zoomInFunction(scaleX4Flick*flick.contentWidth, scaleY4Flick*flick.contentHeight)
                              } else {
                                  zoomOutFunction(scaleX4Flick*flick.contentWidth, scaleY4Flick*flick.contentHeight)
                              }
                           }

                           function zoomRequest(scaleX, scaleY, zoomValue){

                               while (zoomValue !== 0){
                                   if (zoomValue > 0){
                                       zoomOutFunction(scaleX*flick.contentWidth,scaleY*flick.contentHeight)
                                       zoomValue--;
                                   } else {
                                       zoomInFunction(scaleX*flick.contentWidth,scaleY*flick.contentHeight)
                                       zoomValue++;
                                   }
                               }
                           }

                           function zoomOutFunction(pointX, pointY){
                               flick.resizeContent(flick.contentWidth*1.25, flick.contentHeight*1.25, Qt.point(pointX, pointY))
                               flick.returnToBounds()
                               zoomTool.zoomTime += 1
                           }

                           function zoomInFunction(pointX, pointY){
                               flick.resizeContent(flick.contentWidth*(1/1.25), flick.contentHeight*(1/1.25), Qt.point(pointX, pointY))
                               flick.returnToBounds()
                               zoomTool.zoomTime -= 1
                           }

                           function doZoomFit(){
                               flick.resizeContent(flick.width, flick.height, Qt.point(flick.width/2, flick.height/2))
                               flick.contentX = 0
                               flick.contentY = 0

                               zoomTool.zoomTime = 0
                               zoomTool.currentScale = 1
                           }
                       }
                    }
                    // TODO: create overlay layer

                }


            }

        }
    }
}
