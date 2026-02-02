import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtMultimedia 5.15
import QtQuick.Dialogs 1.3

ApplicationWindow {
    id: mainWindow
    width: 1280
    height: 720
    visible: true
    title: qsTr("Bottle")
    flags: Qt.Window | Qt.FramelessWindowHint
    // visibility: Qt.WindowFullScreen
    // flags: Qt.WindowStaysOnTopHint

    Item{
        anchors.fill: parent
        TabControlBar{
            id: tab_bar
            anchors.fill: parent
        }
    }

    onClosing: {
        close.accepted = false
        onTriggered: exit_message_dialog_id.open()
    }



    MessageDialog {
        id: exit_message_dialog_id
        title: qsTr("Close App?")
        icon: StandardIcon.Question
        text: qsTr("Do you want close application ?")
        standardButtons: StandardButton.Yes |StandardButton.No
        onYes: {
            Qt.quit();
            exit_message_dialog_id.close()
            mainVM.appClose()
        }

    }

    Component.onCompleted: {
        console.log("All Component Loaded")
        mainVM.allComponentLoaded()
    }

}
