import QtQuick 2.12
import QtQuick.Controls 2.12
import ConfigView 1.0


//分页组件上的页码按钮 Page number button on the paging component //Кнопка с номером страницы на компоненте подкачки
//龚建波 2020-12-20
Button {
    id: control

    property int pageNumber: -2
    property int pageCurrent: -3
    property color textColor: ConfigView.mainWhiteColor
    property color highlightedColor: ConfigView.addThinBlueColor
    property color backgroundColor: ConfigView.mainWhiteColor


    implicitWidth: implicitContentWidth+leftPadding+rightPadding
    implicitHeight: implicitContentHeight+topPadding+bottomPadding
    padding: 0
    text: pageNumber

    contentItem: Text {
        text: control.text
        font: control.font
        color: pageNumber===pageCurrent ? control.textColor : ConfigView.mainBlueColor
        opacity: enabled ? 1.0 : 0.3
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        anchors.fill: parent
        radius: 5
        border.color: ConfigView.mainBlueColor
        color: pageNumber === pageCurrent ? control.highlightedColor : control.backgroundColor
    }
}
