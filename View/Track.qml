import QtQuick 2.15
import QtQml 2.0

import ConfigView 1.0

Item {
    id: track

    property QtObject _viewModel: QtObject{
        id: trackInteral
    }
    property int _numVerticalCell: 0
    property int _numHorizontalCell: 0
    property int _currentIndex: 0
    property bool _isPickTrack: false
    property string _fontFamily: ConfigView.fontFamily
    property bool _isShowCalibGrib: false
    property bool _isShowImageViewInfo: true
    signal trackMouseAction_Signal(type: int)
    signal updateDataToPixelRuler_Signal(prePosX: double, prePosY: double, posX: double, posY: double)

    function updateCalibGrib() {
        for(var i = 0; i < image_view_grid.count; i++){
            image_view_grid.itemAtIndex(i).updateCalibGrib()
        }
    }

    QtObject{
        id: internalTrack
    }

    Rectangle{
        anchors.fill: parent
        anchors.centerIn: parent
        color: "transparent"
        GridView{
            id: image_view_grid
            property int padding: 0
            width: parent.width
            height: parent.height
            visible:true
            enabled: visible
            focus:true
            model: _viewModel.imageModel
            anchors{
                top:parent.top
                left: parent.left
            }
            cellHeight: height/_numVerticalCell
            cellWidth: width/_numHorizontalCell
            // keyNavigationEnabled: true
            keyNavigationWraps: true
            clip: true
            interactive: false
            delegate:contacts_delegate
            currentIndex: _currentIndex
            cacheBuffer: image_view_grid.cellHeight * 8
            flow: _numHorizontalCell ? GridView.FlowLeftToRight : _numVerticalCell ? GridView.FlowTopToBottom : GridView.FlowLeftToRight
            highlightRangeMode: GridView.ApplyRange
            snapMode: GridView.SnapOneRow

            onCurrentIndexChanged: {
            }
            Component{
                id: contacts_delegate
                ImageView{
                    width: image_view_grid.cellWidth - image_view_grid.padding
                    height: image_view_grid.cellHeight - image_view_grid.padding
                    _viewModel: imageViewVM
                    _isShowCalibGrib: track._isShowCalibGrib
                    _isShowImageViewInfo: track._isShowImageViewInfo
                    onImageViewMouseAction_Signal:(type) => {
                        track.trackMouseAction_Signal(type)
                    }
                    onUpdateDataToPixelRuler_Signal: (prePosX, prePosY, posX, posY) => {
                        track.updateDataToPixelRuler_Signal(prePosX, prePosY, posX, posY)
                    }
                }

            }
            add: Transition {
                ParallelAnimation{
                    NumberAnimation { properties: "x,y"; from: 100; duration: 1000 }
                    NumberAnimation {properties: "opacity"; from:0; to:1; duration: 1000}
                }

            }
            addDisplaced: Transition {
                NumberAnimation { properties: "x,y"; duration: 1000 }
            }
            move: Transition {
                NumberAnimation { properties: "x,y"; duration: 1000 }
            }
            moveDisplaced: Transition {
                NumberAnimation { properties: "x,y"; duration: 1000 }
            }
            Keys.onRightPressed: {
                moveCurrentIndexRight()
            }
            Keys.onLeftPressed: {
                moveCurrentIndexLeft()
            }
            Keys.onUpPressed: {
                moveCurrentIndexUp()
            }
            Keys.onDownPressed: {
                moveCurrentIndexDown()
            }
            Component.onCompleted: {
                image_view_grid.forceActiveFocus(Qt.MouseFocusReason)
            }
        }
    }
}
