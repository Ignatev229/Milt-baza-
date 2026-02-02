import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.3

Item {
    id: main_layout
    property QtObject _viewModel: QtObject{}
    property string title: ""
    property string content: ""
    property var icon: StandardIcon.Information
    property var buttonType: StandardButton.Yes
    width: 400
    property int index: 0
    signal buttonClicked_Signal(buttonType: var)

    function openDialog(title, content, icon, buttonType){
        message_info_dialog.title = title
        message_info_dialog.text = content
        message_info_dialog.icon = icon
        message_info_dialog.standardButtons = buttonType
        message_info_dialog.open()
    }


    MessageDialog {
        id: message_info_dialog
        title: _viewModel.title
        icon: main_layout.icon 
        text: _viewModel.content
        standardButtons:  main_layout.buttonType
   

        onYes: {
            buttonClicked_Signal(StandardButton.Yes)
            message_info_dialog.close()
        }
        onNo: {
            buttonClicked_Signal(StandardButton.No)
            message_info_dialog.close()
        }


    }
    Connections{
        target: _viewModel
        function onOpenMessageInfo_Signal(iconIndex){

            if(iconIndex === 1)
            {
                main_layout.icon = StandardIcon.Information
            }
            else if(iconIndex === 2)
            {
                main_layout.icon = StandardIcon.Warning
            }
            else if(iconIndex === 3)
            {
                main_layout.icon = StandardIcon.Critical
            }
            else if(iconIndex === 4)
            {
                main_layout.icon = StandardIcon.Question
            }
            else
            {
                main_layout.icon = StandardIcon.Information
            }
            
            message_info_dialog.open()
        }
    }
}
