import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

Item {

    MessageDialog {
        id: no_license_dialog
        title: qsTr("No License")
        icon: StandardIcon.Warning
        text: qsTr("No License Found !!!")
        standardButtons: StandardButton.Yes
        onYes: {
            Qt.quit();
            no_license_dialog.close()
        }
    }

    Connections {
        target: checkLicense
        function onCloseApplication_Signal() {
            console.log("-----No license-----")
            no_license_dialog.open()
        }
    }

}




