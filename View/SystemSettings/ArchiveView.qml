import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.3

import ConfigView 1.0


import "../../View"
import "../../Component"

Item {

    id: layout
    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.textColor
    property int _fontSize: 12

    Row {
        width: parent.width*0.6
        height: parent.height*0.3
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: parent.width*0.2

        ButtonMaterialTextHorizontal{
            height: parent.height*0.5
            width: parent.width/3
            _size: height*0.8
            _text: qsTr("Archive")
            _iconSourceOn: "archiveArrowDown"
            anchors.verticalCenter: parent.verticalCenter
            _fontFamily: _fontFamily
            _textRatio: 0.2
            _colorIconDefault: ConfigView.mainBlueColor
            _colorIconMouseOver: _colorIconDefault
            _colorIconHigh: ConfigView.mainBlueColor
            onClicked: {
                zip_file_dialog.open()

            }
        }

        ButtonMaterialTextHorizontal{
            height: parent.height*0.5
            width: parent.width/3
            _size: height*0.8
            _text: qsTr("Unarchive")
            _iconSourceOn: "archiveArrowUp"
            anchors.verticalCenter: parent.verticalCenter
            _fontFamily: _fontFamily
            _textRatio: 0.2
            _colorIconDefault: ConfigView.mainBlueColor
            _colorIconMouseOver: _colorIconDefault
            _colorIconHigh: ConfigView.mainBlueColor
            onClicked: {
                unzip_file_dialog.open()
            }
        }

    }


    FileDialog {
        id: zip_file_dialog
        title: qsTr("Select Save Zip File")
        selectExisting: false
        selectMultiple: false
        nameFilters: ["Zip Files (*.zip)"]
        onAccepted: {
            var raw_text = String(zip_file_dialog.fileUrl);
            var path = Qt.platform.os === "windows" ?
                        raw_text.substring(8, raw_text.length) :
                        raw_text.substring(7, raw_text.length)


            var extension = ".zip"
            if (!path.endsWith(extension)) {
                path += extension; // Add '.zip' if not present
            }

            _viewModel.zipFolder_Qml_Slot(path)
            zip_file_dialog.close()
        }
    }

    FileDialog {
        id: unzip_file_dialog
        title: qsTr("Select Extract Zip File")
        selectExisting: true
        selectMultiple: false
        nameFilters: ["Zip Files (*.zip)"]
        onAccepted: {
            var raw_text = String(unzip_file_dialog.fileUrl);
            var path = Qt.platform.os === "windows" ?
                        raw_text.substring(8, raw_text.length) :
                        raw_text.substring(7, raw_text.length)


            var extension = ".zip"
            if (!path.endsWith(extension)) {
                path += extension; // Add '.zip' if not present
            }

            _viewModel.unZipFolder_Qml_Slot(path)
            unzip_file_dialog.close()
        }
    }

}
