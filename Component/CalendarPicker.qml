import QtQuick 2.15
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4
import ConfigView 1.0

Item {
    id: layout
    signal calendarSelected_Signals(startDate: string, endDate: string)

    Calendar {
        id: calendar
        width: parent.width
        height: parent.height
        frameVisible: true
        weekNumbersVisible: true
        focus: true
        property var startDate: undefined
        property var stopDate: undefined


        style: CalendarStyle {
            gridVisible: false
            background: Rectangle {
                color: ConfigView.addLightBlueColor
                radius: 10
            }
            weekNumberDelegate: Rectangle {
                color: ConfigView.mainWhiteColor
            }

            // navigationBar: Rectangle { color: "#083A6A" }
            dayDelegate: Rectangle {
                readonly property color sameMonthDateTextColor: ConfigView.mainBlueColor
                readonly property color differentMonthDateTextColor: "#777777"
                readonly property color selectedStartDateColor: "#1982F6"
                readonly property color selectedEndDateColor: ConfigView.acceptSignalColor
                readonly property color invalidDatecolor: "#dddddd"
                property var dateOnFocus: styleData.date

                color: ConfigView.mainWhiteColor
                Rectangle {
                    anchors.fill: parent
                    border.color: "transparent"
                    color: styleData.date !== undefined && styleData.selected ? selectedStartDateColor : "transparent"
                    radius: parent.width

                }

                Rectangle{
                    id:fl
                    anchors.fill: parent
                    property bool flag: false
                    color: ((dateOnFocus>calendar.startDate) && (dateOnFocus< calendar.stopDate))?"#556666":
                           (calendar.startDate !== undefined && dateOnFocus.getTime() === calendar.startDate.getTime())?selectedEndDateColor:"transparent"
                    radius: ((dateOnFocus>calendar.startDate) && (dateOnFocus< calendar.stopDate)) ? 0:parent.height
                }


                MouseArea{
                    anchors.fill: parent
                    propagateComposedEvents: true
                    onPressed: {

                        if(calendar.startDate===undefined){
                            calendar.startDate=styleData.date
                        }
                        else if(calendar.stopDate=== undefined){
                            calendar.stopDate=styleData.date
                            layout.calendarSelected_Signals(Qt.formatDate(calendar.startDate,"yyyy-MM-dd"), Qt.formatDate(calendar.stopDate,"yyyy-MM-dd"))
                        }
                        else{
                            calendar.startDate=styleData.date
                            calendar.stopDate= undefined
                        }

                        if(calendar.stopDate<=calendar.startDate){
                            calendar.startDate=styleData.date
                            calendar.stopDate= undefined
                        }

                        mouse.accepted = false
                    }
                }

                Label {
                    id: dayDelegateText
                    text: styleData.date.getDate()
                    anchors.centerIn: parent
                    color: {
                        var color = sameMonthDateTextColor;
                        if (styleData.valid) {
                            // Date is within the valid range.
                            color = styleData.visibleMonth ? sameMonthDateTextColor : differentMonthDateTextColor;
                            // if (styleData.selected) {
                            //     color = selectedDateTextColor;
                            // }
                            // else if (dateOnFocus.getTime()===calendar.startDate.getTime()) {
                            //     color = selectedDateTextColor;
                            // }
                        }

                        color;
                    }
                }
            }
        }

    }
}
