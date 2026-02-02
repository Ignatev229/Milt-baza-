import QtQuick 2.0
import QtQuick.Layouts 1.0

import QtQuick.Dialogs 1.3 as QDialog

// My import
import ImageWriter 1.0
import ConfigView 1.0
import "../Component"

Item {
    id: image_view

    property QtObject _viewModel: QtObject{}


    property color _textDefaultColor: ConfigView.addGrayColor
    property color _textActivateColor: ConfigView.addThinBlueColor
    property double fontSize: 11.5//image_view_name.height*0.25
    property string _fontFamily: ConfigView.fontFamily
    property bool _isShowCalibGrib: false
    property bool _isShowImageViewInfo: true

    signal imageViewMouseAction_Signal(type: int) //
    signal updateDataToPixelRuler_Signal(prePosX: double, prePosY: double, posX: double, posY: double)


    function updateCalibGrib() {
        grid_calib.updateCanvasPosition();
    }

    Rectangle{
        anchors.fill: parent
        anchors.centerIn: parent
        color: "transparent"

        Rectangle{
            //header
            id: header
            width:  parent.width
            height: parent.height*0.11
            color: ConfigView.addLightBlueColor
            clip : true
            Row{
                //Text and image
                width: parent.width
                height: parent.height
                spacing: parent.width*0.02
                anchors.left: parent.left
                anchors.leftMargin: 5
                Text {
                    id: image_view_name
                    text: _viewModel.docName
                    width: parent.width*0.2
                    height: parent.height
                    font.family: _fontFamily
                    font.pointSize: fontSize
                    font.bold: true
                    color: /*(zoomTool.containsMouse | (track._isPickTrack))*/ track._isPickTrack ? _textActivateColor : _textDefaultColor
                    verticalAlignment: Text.AlignVCenter
                }

                Row{
                    id: serial_number_id
                    width: parent.width*0.48
                    height: parent.height
                    spacing: parent.width*0.03
                    visible: image_view_name.visible && _isShowImageViewInfo
                    Text {
                        text: _viewModel.inspectFunctionName
                        width: contentWidth
                        height: parent.height
                        font.family: _fontFamily
                        font.pointSize: fontSize
                        font.bold: false
                        color: _textDefaultColor
                        verticalAlignment: Text.AlignVCenter
                    }

                    Text {
                        text: qsTr("S/N") + ": " + _viewModel.serialNumber
                        width: contentWidth
                        height: parent.height
                        font.family: _fontFamily
                        font.pointSize: fontSize
                        font.bold: false
                        color: _viewModel.serialNumber !== qsTr("N/A") ? _textActivateColor : _textDefaultColor
                        verticalAlignment: Text.AlignVCenter
                    }

                    Text {
                        text: qsTr("Inspection Cycle")+ ": " + _viewModel.inspectionCycleInfo
                        width: contentWidth
                        height: parent.height
                        font.family: _fontFamily
                        font.pointSize: fontSize
                        font.bold: false
                        color: _textDefaultColor
                        verticalAlignment: Text.AlignVCenter
                        visible: _viewModel.inspectionCycleInfo !== 0
                    }

                    Text {
                        text: qsTr("Inspection Folder")+ ": " + _viewModel.inspectionFolderInfo
                        width: contentWidth
                        height: parent.height
                        font.family: _fontFamily
                        font.pointSize: fontSize
                        font.bold: false
                        color: _textDefaultColor
                        verticalAlignment: Text.AlignVCenter
                        visible: _viewModel.inspectionFolderInfo !== ""
                    }

                    Text {
                        text: qsTr("Process Time") + ": " + _viewModel.processedTime + " " + qsTr("ms")
                        width: contentWidth
                        height: parent.height
                        font.family: _fontFamily
                        font.pointSize: fontSize
                        font.bold: false
                        color: _textDefaultColor
                        verticalAlignment: Text.AlignVCenter
                        visible: _viewModel.processedTime !== 0
                    }

                    Text {
                        text: _viewModel.inspectionInfo
                        width: contentWidth
                        height: parent.height
                        font.family: _fontFamily
                        font.pointSize: fontSize
                        font.bold: false
                        color: _textDefaultColor
                        verticalAlignment: Text.AlignVCenter
                    }

                }

                Rectangle {
                    visible: !serial_number_id.visible
                    width: parent.width*0.48
                    height: parent.height
                    color: "transparent"
                }

                // save button for each doc
                Rectangle {
                    width: parent.width*0.07
                    height: parent.height
                    color: "transparent"
                    ButtonMaterial {
                        id: save_btn
                        width: parent.width
                        height: parent.height
                        _iconSourceOn: "contentSaveAll"
                         // _colorBorder: "#797979"
                         _size: height*0.8
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        _colorBorder: "transparent"
                        _colorIconDefault: ConfigView.mainWhiteColor
                        _colorIconMouseOver: _colorIconDefault
                        _colorBGDefault: "transparent"
                        _colorBGMouseOver: _colorBGDefault
                        _toolTip: "Save Image"
                        onClicked: {

                            save_image_dialog.open()
                        }
                    }
                }

                // Snap button for each doc
                Rectangle {
                    width: parent.width*0.07
                    height: parent.height
                    color: "transparent"
                    ButtonMaterial {
                        width: parent.width
                        height: parent.height
                        _iconSourceOn: "cameraIris"
                         // _colorBorder: "#797979"
                         _size: save_btn._size
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        _colorBorder: "transparent"
                        _toolTip: "Snap"
                        _colorIconDefault: ConfigView.mainWhiteColor
                        _colorIconMouseOver: _colorIconDefault
                        _colorBGDefault: "transparent"
                        _colorBGMouseOver: _colorBGDefault
                        onClicked: {
                            _viewModel.doSnapImage()
                        }
                    }

                }

                Rectangle{
                    width: parent.width*0.07
                    height: parent.height
                    color: "transparent"
                    ToggleButtonMaterial{
                        id: overlay_button
                        _width: parent.width
                        _height: parent.width
                        _size: save_btn._size
                        _iconSourceOn: "cardOutline"
                        _iconSourceOff: "cardOffOutline"
                        _colorBorder: " transparent"
                        _colorIconDefault: ConfigView.addThinBlueColor
                        _colorIconMouseOver: _colorIconDefault
                        _colorIconHigh: _colorIconDefault
                        _isClicked: true
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
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
                color: "#D0CECF"
                visible: _viewModel.isConnectCam
                anchors{
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                }

                Flickable{
                    id: flick
                    width: parent.width
                    height: parent.height
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
                           property double currentScale: 1
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
                           property double scale: 1.25

                           // Keys.onPressed: {}


                           // Keys.onReleased:{}

                           // onWidthChanged: {
                           //     sizeChanged()
                           // }

                           // onHeightChanged: {
                           //     sizeChanged()
                           // }

                           onWheel:{
                               console.log(image_writer.width, image_writer.ui_width, image_writer.img_width)
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

                                    pixel_ruler.updateCanvasPosition()
                                 }
                                 else {
                                     flick.resizeContent(flick.width, flick.height, Qt.point(flick.width/2, flick.height/2))
                                     flick.returnToBounds()
                                     zoomTool.zoomTime = 0
                                     zoomTool.currentScale = 1
                                  }
                                // }
                            }

                           // onEntered: {
                           //      zoomTool.forceActiveFocus(Qt.MouseFocusReason)
                           // }

                           // onExited: {
                           //     zoomTool.forceActiveFocus(Qt.MouseFocusReason)

                           // }

                           onPositionChanged: {
                                pixel_ruler.updatePixelRulerPoint(mouseX + (image_writer.width - image_writer.ui_width)/2, mouseY + (image_writer.height - image_writer.ui_height)/2, false)
                           }

                           // onPressed: {
                           //      if(isCtrlPress && (mouse.button === Qt.LeftButton)){

                           //      }
                           //      else if (isCtrlPress && (mouse.button === Qt.RightButton)){
                           //          zoomTool.doZoomFit()
                           //      }
                           // }

                           onClicked:{
                               if(mouse.button === Qt.RightButton){
                                   zoomTool.doZoomFit()
                               }
                               else if (mouse.button === Qt.LeftButton){
                                   image_view.imageViewMouseAction_Signal(ConfigView.MOUSE_ACTION.LEFT_CLICK)
                                   pixel_ruler.updatePixelRulerPoint(mouseX + (image_writer.width - image_writer.ui_width)/2, mouseY + (image_writer.height - image_writer.ui_height)/2, true)
                               }
                           }

                           onDoubleClicked: {
                               if(mouse.button === Qt.LeftButton){
                                    image_view.imageViewMouseAction_Signal(ConfigView.MOUSE_ACTION.LEFT_DOUBLE_CLICK)

                               }
                               else if(mouse.button === Qt.RightButton){
                               }
                               else{
                                   console.log("Mouse double click action fail")
                               }
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

                           function zoomOutFunction(pointX, pointY){
                               zoomTool.zoomTime += 1
                               zoomTool.currentScale *= zoomTool.scale
                               flick.resizeContent(flick.contentWidth*zoomTool.scale, flick.contentHeight*zoomTool.scale, Qt.point(pointX, pointY))
                               flick.returnToBounds()
                           }

                           function zoomInFunction(pointX, pointY){
                               zoomTool.zoomTime -= 1
                               zoomTool.currentScale /= zoomTool.scale
                               flick.resizeContent(flick.contentWidth/zoomTool.scale, flick.contentHeight/zoomTool.scale, Qt.point(pointX, pointY))
                               flick.returnToBounds()
                           }

                           function doZoomFit(){
                               flick.resizeContent(flick.width, flick.height, Qt.point(flick.width/2, flick.height/2))
                               flick.contentX = 0
                               flick.contentY = 0
                               zoomTool.zoomTime = 0
                               zoomTool.currentScale = 1
                               pixel_ruler.updateCanvasPosition()
                           }
                       }

                    }

                    // TODO: create overlay layer
                    // pixel ruler
                    Canvas {
                        id: pixel_ruler
                        anchors.fill: parent
                        renderTarget: Canvas.Image
                        renderStrategy: Canvas.Immediate
                        visible: ConfigView.isShowPixelRuler
                        property double posX : 0
                        property double posY : 0
                        property double prePosX : 0
                        property double prePosY : 0
                        property double dPosX : 0
                        property double dPosY : 0
                        property double preDPosX : 0
                        property double preDPosY : 0
                        property bool isDrawing: false


                        function updatePixelRulerPoint(x, y, isClick) {
                            if(!pixel_ruler.visible)
                                return
                            if(!isDrawing && isClick) {
                                // first point
                                clear_canvas()
                                pixel_ruler.prePosX = x
                                pixel_ruler.prePosY = y
                                pixel_ruler.posX = x
                                pixel_ruler.posY = y

                                // calculate default pos
                                pixel_ruler.preDPosX = x/zoomTool.currentScale
                                pixel_ruler.preDPosY = y/zoomTool.currentScale
                                pixel_ruler.dPosX = x/zoomTool.currentScale
                                pixel_ruler.dPosY = y/zoomTool.currentScale

                                isDrawing = true
                            }
                            else if(isDrawing) {
                                clear_canvas()
                                pixel_ruler.posX = x
                                pixel_ruler.posY = y
                                pixel_ruler.requestPaint()
                                if(isClick) {
                                    isDrawing = false
                                }

                                // calculate default pos
                                pixel_ruler.dPosX = x/zoomTool.currentScale
                                pixel_ruler.dPosY = y/zoomTool.currentScale

                                // update pixel ruler dialog
                                var scaleX = image_writer.img_width/(image_writer.ui_width/zoomTool.currentScale)
                                var scaleY = image_writer.img_height/(image_writer.ui_height/zoomTool.currentScale)
                                image_view.updateDataToPixelRuler_Signal(pixel_ruler.preDPosX*scaleX, pixel_ruler.preDPosY*scaleY, pixel_ruler.dPosX*scaleX, pixel_ruler.dPosY*scaleY)


                            }
                        }


                        function updateCanvasPosition() {
                            if(!pixel_ruler.visible)
                                return
                            clear_canvas()
                            pixel_ruler.prePosX = pixel_ruler.preDPosX*zoomTool.currentScale
                            pixel_ruler.prePosY = pixel_ruler.preDPosY*zoomTool.currentScale
                            pixel_ruler.posX = pixel_ruler.dPosX*zoomTool.currentScale
                            pixel_ruler.posY = pixel_ruler.dPosY*zoomTool.currentScale

                            pixel_ruler.requestPaint()


                        }
                        onVisibleChanged: {

                        }
                        onPaint: {
                            var ctx = getContext('2d')
                            ctx.fillStyle = "blue"
                            ctx.fillRect(pixel_ruler.prePosX-3, pixel_ruler.prePosY-3, 7, 7)
                            ctx.fillRect(pixel_ruler.posX-3, pixel_ruler.posY-3, 7, 7)
                            ctx.lineWidth = 2;
                            ctx.strokeStyle = "red"
                            ctx.beginPath()
                            ctx.moveTo(pixel_ruler.prePosX, pixel_ruler.prePosY)
                            ctx.lineTo(pixel_ruler.posX, pixel_ruler.posY)
                            ctx.stroke()

                        }

                        function clear_canvas() {
                            var ctx = getContext("2d");
                            ctx.reset();
                            pixel_ruler.requestPaint();
                        }
                    }

                }


                Canvas {
                    id: grid_calib
                    anchors.fill: parent
                    renderTarget: Canvas.Image
                    renderStrategy: Canvas.Immediate
                    visible: _isShowCalibGrib
                    onPaint: {
                        var ctx = getContext("2d");
                            ctx.clearRect(0, 0, width, height);
                            ctx.strokeStyle = "red";
                            ctx.lineWidth = 3;

                            // Set the line dash pattern: [10, 5]
                            ctx.setLineDash([4, 2]);

                            // Horizontal line
                            ctx.beginPath();
                            ctx.moveTo(0, height / 2);
                            ctx.lineTo(width, height / 2);
                            ctx.stroke();

                            // Vertical line
                            ctx.beginPath();
                            ctx.moveTo(width / 2, 0);
                            ctx.lineTo(width / 2, height);
                            ctx.stroke();
                            // Reset line dash pattern to solid
                           ctx.setLineDash([]);

                    }

                    function updateCanvasPosition() {
                        if(!grid_calib.visible)
                            return
                        clear_canvas()
                        grid_calib.requestPaint()
                    }

                    function clear_canvas() {
                        var ctx = getContext("2d");
                        ctx.reset();
                        grid_calib.requestPaint();
                    }
                }


            }

        }
    }

    QDialog.FileDialog {
        id: save_image_dialog
        title: qsTr("Select Save Image Path")
        selectMultiple: false
        selectExisting: false
        onAccepted: {
            var raw_text = String(save_image_dialog.fileUrl);
            var path = Qt.platform.os === "windows" ?
                        raw_text.substring(8, raw_text.length) :
                        raw_text.substring(7, raw_text.length)
            _viewModel.doSaveImage(path)
            save_image_dialog.close()
        }
    }
}
