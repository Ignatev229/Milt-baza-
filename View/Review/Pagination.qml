import QtQuick 2.12
import QtQuick.Controls 2.12
import ConfigView 1.0

import "../../Component"

Rectangle {
    id: control

    signal requestPage(int page, int count)

    property int pageCurrent: 0
    property int itemCount: 0
    property int pageCount: itemCount > 0 ? Math.ceil(itemCount/__itemPerPage):0
    property int __itemPerPage: 1
    property int pageButtonCount: 5
    property int __pageButtonHalf: Math.floor(pageButtonCount/2)+1
    property font font
    font{
        pixelSize: 14
        family: "Microsoft YaHei"
    }
    property color textColor: ConfigView.mainBlueColor
    property color highlightedColor: ConfigView.mainBlueColor
    property color elementBorderColor: "#DCDFE6"
    property int elementHeight: height*0.6
    // property alias padding: content_row.padding

    implicitHeight: 40
    implicitWidth: content_row.width

    Rectangle{
        id: content_row
        height: control.height
        width: control.width
        color: ConfigView.addThinBlueColor
        anchors.horizontalCenter: parent.horizontalCenter
        Text{
            anchors.verticalCenter: parent.verticalCenter
            font: control.font
            color: control.textColor
            text: qsTr("Total") + ": " + control.itemCount
            width: parent.width*0.
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.02
        }

        Row{
            spacing: parent.width*0.03
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width*0.4
            //左侧前一页，应该使用图片，这里仅作演示
            PageButton{
                visible: control.pageCount > 1
                enabled: control.pageCurrent > 1
                anchors.verticalCenter: parent.verticalCenter
                width: control.elementHeight*1.2
                height: control.elementHeight
                font: control.font
                textColor: control.textColor
                text: "<"
                onClicked: {
                    control.calcNewPage(control.pageCurrent-1);
                }
            }
            //中间显示页码
            Row{
                spacing: parent.width*0.03
                anchors.verticalCenter: parent.verticalCenter
                //第一页
                PageButton{
                    visible: control.pageCount > 0
                    width: control.elementHeight*1.2
                    height: control.elementHeight
                    font: control.font
                    textColor: control.textColor
                    pageNumber: 1
                    pageCurrent: control.pageCurrent
                    onClicked: {
                        control.calcNewPage(1);
                    }
                }
                Text {
                    //pageCount<btnCount不用显示
                    //当前页在前countHalf页不用显示
                    visible: (control.pageCount > control.pageButtonCount &&
                              control.pageCurrent > control.__pageButtonHalf)
                    text: "..."
                    font: control.font
                    color: control.textColor
                    height: control.elementHeight
                }
                //中间的页码由Repeater根据设置的pageButtonCount创建
                Repeater{
                    id: button_repeator
                    model: (control.pageCount<2)
                           ?0
                           :(control.pageCount>=control.pageButtonCount)
                             ?(control.pageButtonCount-2)
                             :(control.pageCount-2)
                    delegate: PageButton{
                        width: control.elementHeight*1.2
                        height: control.elementHeight
                        font: control.font
                        textColor: control.textColor
                        //在首或者尾相连时，值要连续，避免和首尾重复
                        pageNumber: (control.pageCurrent<=control.__pageButtonHalf)
                                    ?(2+index)
                                    :(control.pageCount-control.pageCurrent<=control.pageButtonCount-control.__pageButtonHalf)
                                      ?(control.pageCount-button_repeator.count+index)
                                      :(control.pageCurrent+2+index-control.__pageButtonHalf)
                        pageCurrent: control.pageCurrent
                        onClicked: {
                            control.calcNewPage(pageNumber);
                        }
                    }
                }
                Text {
                    id: page_moreright
                    //pageCount<btnCount不用显示
                    //当前页在倒数countHalf页不用显示
                    visible: (control.pageCount>control.pageButtonCount&&
                              control.pageCount-control.pageCurrent>control.pageButtonCount-control.__pageButtonHalf)
                    text: "..."
                    font: control.font
                    color: control.textColor
                    height: control.elementHeight
                }
                //最后一页
                PageButton{
                    visible: control.pageCount>1
                    width: control.elementHeight*1.2
                    height: control.elementHeight
                    font: control.font
                    textColor: control.textColor
                    pageNumber: control.pageCount
                    pageCurrent: control.pageCurrent
                    onClicked: {
                        control.calcNewPage(pageNumber);
                    }
                }
            }
            //右侧下一页，应该使用图片，这里仅作演示
            PageButton{
                visible: control.pageCount>1
                enabled: control.pageCurrent<control.pageCount
                anchors.verticalCenter: parent.verticalCenter
                width: control.elementHeight*1.2
                height: control.elementHeight
                font: control.font
                textColor: control.textColor
                text: ">"
                onClicked: {
                    control.calcNewPage(control.pageCurrent+1);
                }
            }
        }
        //页码跳转
        Row{
            spacing: 5
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width*0.2
            anchors.right: parent.right
            anchors.rightMargin: parent.width*0.02
            InputMaterialText{
                id: edit_goto_page
                _width: parent.width*0.8
                _height: control.elementHeight
                _fontSizeText: control.font
                anchors.verticalCenter: parent.verticalCenter
                _text: ""
                _placeholderText: ""
                _iconSourceOn: "cardSearch"
                focus: true
                _reg: RegExpValidator{regExp: /\d+/}
                _inputMethodHints: Qt.ImhFormattedNumbersOnly
                Keys.onPressed: {
                    //enter小键盘enter
                    //return主键盘enter
                    if(event.key===Qt.Key_Enter||event.key===Qt.Key_Return){
                        focus=false;
                        if(edit_goto_page.getText()){
                            //编辑结束就去请求该页数据
                            control.requestPage(Number(edit_goto_page.getText()),control.__itemPerPage);
                        }
                    }
                }
            }

        }
    }

    //翻页计算
    function calcNewPage(page)
    {
        if(!page)
            return;
        let page_num=Number(page);
        //超出范围或者为当前页就返回
        if(page_num<1||page_num>control.pageCount||page_num===control.pageCurrent)
            return;
        control.pageCurrent=page_num;
        control.requestPage(page_num,control.__itemPerPage)
    }
}
