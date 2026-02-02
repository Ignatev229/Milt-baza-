import QtQuick 2.15
import "Component"
import ConfigView 1.0

Item {
    id: bottom_bar_root
    property string _fontFamily: ConfigView.fontFamily
    property int _fontSize: 14
    property color _textColor: "white"
    property color _statusColor: ConfigView.addLightBlueColor
    property color _warningColor: "#F6BD1D"
    property color _errorColor: "#E73F32"


    property var statusInfos: [
        // Info
        // 1000
        qsTr("Auto mode"), //0
        qsTr("HMI mode"), //1
        qsTr("Ready for automatic cycle"), //2
        qsTr("Not ready for automatic cycle"), //3
        qsTr("Automatic cycle"), //4
        qsTr("Return machine to original state"), //5
        qsTr(""), //6
        qsTr(""), //7
        qsTr(""), //8
        qsTr(""), //9
        qsTr(""), //10
        qsTr(""), //11
        qsTr(""), //12
        qsTr(""), //13
        qsTr(""), //14
        qsTr(""), //15

        // Warning
        // 1001
        qsTr("Warning summary"), //16
        qsTr("No warnings"), //17
        qsTr("Thermostat high temperature in control box"), // 18
        qsTr("Compressed air pressure is low"), // 19
        qsTr("Conveyor warning"), //20
        qsTr("Infeed cylinder 1 warning"), //21
        qsTr("Infeed cylinder 2 warning"), //22
        qsTr("Outfeed cylinder warning"), //23
        qsTr("Rotate cylinder warning"), //24
        qsTr("Scale pusher warning"), //25
        qsTr("Table pusher warning"), //26
        qsTr("Table (turning) warning"), //27
        qsTr("Table (lifting) warning"), //28
        qsTr("Camera adjustment warning"), //29
        qsTr("Scales warning"), //30
        qsTr("Step timeout warning"), //31

        // Error
        // 1002
        qsTr("Error summary"), //32
        qsTr("No errors"), //33
        qsTr("EmergencyStop"), //34
        qsTr("Safety relay tripped"), //35
        qsTr(""), //36
        qsTr(""), //37
        qsTr(""), //38
        qsTr("Voltage relay. Voltage is low"), //39
        qsTr("Compressed air supply is turned off"), //40
        qsTr("Conveyor error"), //41
        qsTr("Infeed cylinder 1 error"), //42
        qsTr("Infeed cylinder 2 error"), //43
        qsTr("Outfeed cylinder error"), //44
        qsTr("Rotate cylinder error"), //45
        qsTr("Scale pusher error"), //46
        qsTr("Table pusher error"), //47

        // 1003
        qsTr("Table (turning) error"), //48
        qsTr("Table (lifting) error"), //49
        qsTr("Camera adjustment error"), //50
        qsTr("Scales error"), //51
        qsTr("Step timeout error"), //52
        qsTr("Modbus TCP device A1. Communication error"),
        qsTr("Modbus TCP device A2. Communication error"),
        qsTr("Modbus TCP device A3. Communication error"),
        qsTr("Modbus TCP device A4. Communication error"),
        qsTr("Modbus TCP device G1. Communication error"),
        qsTr("Modbus RTU device (Conveyor drive). Communication error"),
        qsTr("Modbus RTU device (Scales). Communication error"),
        qsTr(""), //
        qsTr(""), //
        qsTr(""), //
        qsTr(""), // 63

        // Warning
        // 1025
        qsTr("Modbus TCP device A1. Communication warning"), //64
        qsTr("Modbus TCP device A2. Communication warning"),
        qsTr("Modbus TCP device A3. Communication warning"),
        qsTr("Modbus TCP device A4. Communication warning"),
        qsTr("Modbus TCP device G1. Communication warning"),
        qsTr("Modbus RTU device (Conveyor drive). Communication warning"),
        qsTr("Modbus RTU device (Scales). Communication warning"),
        qsTr("Left door open"),
        qsTr("Middle door open"),
        qsTr("Right door open"),
        qsTr(""),
        qsTr(""),
        qsTr(""),
        qsTr(""),
        qsTr(""),
        qsTr(""), // 79

    ]
    function setCurrentMachineStatus(index) {
        if(index < 0)
        {
            return;
        }

        status.text = statusInfos[index]
        // status
        if(index <= 15)
        {
            status_layout.color = bottom_bar_root._statusColor
            header_status.text = qsTr("Status") + ": "
            header_status.color = _textColor
            status.color = _textColor
            return
        }

        // warning
        else if(index <= 31) // bit 16
        {
            status_layout.color = bottom_bar_root._warningColor
            header_status.text = qsTr("Warning") + ": "
            header_status.color = "black"
            status.color = "black"
            return
        }

        // error
        else if(index <= 63)
        {
            status_layout.color = bottom_bar_root._errorColor
            header_status.text = qsTr("Error") + ": "
            header_status.color = _textColor
            status.color = _textColor
            return
        }

        // warning 1025 5*16-1
        else if(index <= 79)
        {
            status_layout.color = bottom_bar_root._warningColor
            header_status.text = qsTr("Warning") + ": "
            header_status.color = "black"
            status.color = "black"
            return
        }
    }

    Rectangle{
        id: status_layout
        width: parent.width
        height: parent.height/2
        color: ConfigView.addLightBlueColor
        anchors.top: parent.top
        Text {
            id: header_status
            text: qsTr("Status") + ": "
            width: contentWidth
            height: parent.height
            font.family: _fontFamily
            font.pointSize: _fontSize
            font.bold: true
            color: _textColor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: parent.width*0.02
        }

        Text {
            id: status
            text: qsTr("Close door. Push start button")
            width: contentWidth
            height: parent.height
            font.family: _fontFamily
            font.pointSize: _fontSize
            font.bold: true
            color: _textColor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

    }

    Rectangle{
        width: parent.width
        height: parent.height/2
        color: ConfigView.mainBlueColor
        anchors.bottom: parent.bottom
        Row {
            width: parent.width
            height: parent.height
            Text {
                text: qsTr("Copyright 2024")
                width: parent.width*0.6
                height: parent.height
                font.family: _fontFamily
                font.pointSize: _fontSize
                font.bold: true
                color: _textColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle{
                width: 3
                height: parent.height
                anchors.bottom: parent.bottom
                color: ConfigView.addLightBlueColor
            }

            Text {
                text: qsTr(ConfigView.listDay[ConfigView.currentDay])
                width: parent.width*0.1
                height: parent.height
                font.family: _fontFamily
                font.pointSize: _fontSize
                font.bold: true
                color: _textColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle{
                width: 3
                height: parent.height
                anchors.bottom: parent.bottom
                color: ConfigView.addLightBlueColor
            }

            Text {
                text: ConfigView.currentDate
                width: parent.width*0.15
                height: parent.height
                font.family: _fontFamily
                font.pointSize: _fontSize
                font.bold: true
                color: _textColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle{
                width: 3
                height: parent.height
                anchors.bottom: parent.bottom
                color: ConfigView.addLightBlueColor
            }

            Text {
                text: ConfigView.currentTime
                width: parent.width*0.15
                height: parent.height
                font.family: _fontFamily
                font.pointSize: _fontSize
                font.bold: true
                color: _textColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }


    Connections {
        target: masterApp
        function onMachineStatusChanged(index)
        {
            setCurrentMachineStatus(index)
        }
    }
}
