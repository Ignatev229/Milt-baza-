import QtQuick 2.15
import QtQuick.Controls 2.0

import ConfigView 1.0
import ImageWriter 1.0
import "../../View"

Item {
    id: review_view_id
    width: parent.width
    height: parent.height
    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property int _docChoosed: 0

    Rectangle{
        anchors.fill: parent
        color: ConfigView.mainWhiteColor
        Row {
            width: parent.width*0.99
            height: parent.height*0.98
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: parent.width*0.02
            Row {
                width: parent.width*0.55
                height: parent.height
                spacing: parent.width*0.02
                Grid {
                    width: parent.width
                    height: parent.height - pagination.height
                    rows: 4
                    columns: 1
                    spacing: parent.width*0.02
                    Repeater{
                        model: 4
                        delegate: SingleReviewView{
                            width: parent.width
                            height: parent.height*0.22
                            _fontFamily: review_view_id._fontFamily
                            _viewModel: review_view_id._viewModel.singleReviewListAt(index)
                            _isTrackChoosed: review_view_id._viewModel.trackChoosedIndex === index
                            _docChoosed: review_view_id._docChoosed
                            onImageViewChoosed_Signal: (docIndex) => {
                                review_view_id._docChoosed = docIndex
                                review_view_id._viewModel.docChoosedChanged_Qml_Slot(pagination.pageCurrent - 1, index, docIndex)
                            }
                        }
                    }
                }

                Pagination{
                    id: pagination
                    implicitHeight: 50
                    width: parent.width*0.7
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    border.color: "transparent"
                    radius: 5
                    pageCurrent: 1
                    itemCount: _viewModel.pageNumber + 1
                    onRequestPage: {
                        console.log("Pagination request page:", page, "count:", count)
                        if(page < 1){
                            pageCurrent=1
                        }
                        else if(page > pagination.itemCount){
                            pageCurrent=pagination.itemCount
                        }
                        else{
                            pageCurrent=page;
                        }
                        review_view_id._viewModel.reviewPageNumberChanged_Qml_Slot(pageCurrent - 1)
                    }
                }
            }

            Rectangle {
                width: parent.width*0.43
                height: parent.height
                color: "transparent"

                ImageReviewView{
                    width: parent.width
                    height: parent.height
                    _viewModel: review_view_id._viewModel.imageReviewVM
                    onImageViewMouseAction_Signal:(type) => {

                    }
                }
            }
        }

    }

}
