import QtQuick 2.15
import QtQuick.Controls 2.0
import Qt.labs.qmlmodels 1.0
import QtQuick.Controls 1.4 as QtC1
import QtQuick.Controls.Styles 1.1
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.3

import "../../Component"
import "../Dialog"

import ConfigView 1.0

Item {
    id: delete_recipe_view
    property QtObject _viewModel: QtObject{}
    property string _fontFamily: ConfigView.fontFamily
    property color _backgroundColor: ConfigView.mainWhiteColor
    property color _headerColor: ConfigView.addLightBlueColor
    property color _borderColor: ConfigView.mainBlueColor
    property int _fontSizeText: 11
    property int _borderSize: 1
    property color _textColor: ConfigView.textColor
    property int _numberColumn: 14
    property int _numberRow: 17
    property int _selectedRow: 1
    property string filterString: ""

    Popup{
        id: cloneRecipePopUp
        width: 350
        height: 150
        modal: true
        focus: true
        anchors.centerIn: parent
        Column {
            width: parent.width
            height: parent.height
            spacing: 10

            Rectangle{
                width: parent.width
                height: parent.height*0.1
                anchors.horizontalCenter: parent.horizontalCenter
                color: "transparent"

            }
            InputText {
                id: recipeNameInput
                _width: parent.width*0.9
                _placeholderText: qsTr("New Recipe Name")
                _text: ""
                _leftMagin: 0
                anchors.horizontalCenter: parent.horizontalCenter
                _fontSizeText: delete_recipe_view._fontSizeText
            }

            Rectangle{
                width: parent.width*0.9
                height: parent.height*0.5
                anchors.horizontalCenter: parent.horizontalCenter
                color: "transparent"
                
                ButtonMaterialTextHorizontal {
                    width: parent.width*0.45
                    height: width*0.4
                    _size: height*0.8
                    _text: qsTr("OK")
                    _fontFamily: delete_recipe_view.fontFamily
                    _iconSourceOn: "checkBold"
                    _textRatio: 0.27
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {

                        _viewModel.doCloneRecipe(recipeNameInput.getText(), recipe_model.get(tableview.currentRow).recipeName)
                        cloneRecipePopUp.close()
                    }
                }

                ButtonMaterialTextHorizontal {
                    width: parent.width*0.45
                    height: width*0.4
                    _size: height*0.8
                    _textRatio: 0.27
                    _text: qsTr("Cancel")
                    _iconSourceOn: "cancel"
                    _fontFamily: delete_recipe_view.fontFamily
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        cloneRecipePopUp.close()
                    }
                }
            }
        }
    }


    ListModel{
        id: recipe_model

    }


    ListModel{
        id: recipe_model_total

    }

    function filterRecipe(){
        recipe_model.clear()
        for(var i = 0; i < recipe_model_total.count; i++){
            if(recipe_model_total.get(i).recipeName.includes(filterString)){
                recipe_model.append(recipe_model_total.get(i))
            }
        }
    }

    Connections {
        target: _viewModel
        function onAddData(index, recipeName, dateCreated, dateModify)
        {
            // clear before starting add everything
            if(index === 0)
            {
                recipe_model.clear()
                recipe_model_total.clear()
            }

            if(recipeName.includes(filterString))
            {

                recipe_model.append({
                    "no": index + 1,
                    "recipeName": recipeName,
                    "dateTimeCreated": dateCreated,
                    "dateLastModified": dateModify
                })
            }

            recipe_model_total.append({
                "no": index + 1,
                "recipeName": recipeName,
                "dateTimeCreated": dateCreated,
                "dateLastModified": dateModify
            })
        }
    }

    QtObject{
        id: tableObjectID
        property int widthCell: (tableview.width)/(delete_recipe_view._numberColumn) + delete_recipe_view._borderSize
        property int heightCell: (tableview.height)/(delete_recipe_view._numberRow + 2)
    }

    Column {
        height: parent.height*0.96
        width: parent.width*0.96
        anchors.centerIn: parent

        Row {
            width: parent.width
            height: parent.height*0.14
            spacing: width*0.03

            InputText{
                id: filter_text
                _width: parent.width*0.3
                _height: parent.height*0.6
                _fontSizeText: _fontSizeText
                anchors.verticalCenter: parent.verticalCenter
                _leftMagin: 0
                textHorizontalAlignment: TextInput.AlignLeft
            }

            ButtonMaterialTextHorizontal{
                width: parent.width*0.13
                height: parent.height*0.6
                _size: height*0.8
                _text: qsTr("Filter")
                _iconSourceOn: "filter"
                anchors.verticalCenter: parent.verticalCenter
                _fontFamily: delete_recipe_view._fontFamily
                _textRatio: 0.4
                _colorIconDefault: ConfigView.warningSignalColor
                _colorIconMouseOver: _colorIconDefault
                onClicked: {
                    filterString = filter_text.getText()
                    filterRecipe()
                }
            }

        }

        QtC1.TableView {
            id: tableview
            height: parent.height*0.86
            width: parent.width
            clip: true
            alternatingRowColors: true
            model: recipe_model
            horizontalScrollBarPolicy: ScrollBar.AlwaysOff
            verticalScrollBarPolicy: ScrollBar.AsNeeded
            backgroundVisible: true

            style: TableViewStyle{
                textColor: "white"
                alternateBackgroundColor: "#222222"
            }

            QtC1.TableViewColumn {
                role: "no"
                title: qsTr("No")
                width: tableObjectID.widthCell*0.5
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "recipeName"
                title: qsTr("Recipe Name")
                width: tableObjectID.widthCell*2.5
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "dateTimeCreated"
                title: qsTr("Created")
                width: tableObjectID.widthCell*2.5
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "dateLastModified"
                title: qsTr("Last Modified")
                width: tableObjectID.widthCell*2.5
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "load"
                title: qsTr("Load")
                width: tableObjectID.widthCell*2
                horizontalAlignment: Text.AlignHCenter
            }
            QtC1.TableViewColumn {
                role: "clone"
                title: qsTr("Clone")
                width: tableObjectID.widthCell*2
                horizontalAlignment: Text.AlignHCenter
            }

            QtC1.TableViewColumn {
                role: "remove"
                title: qsTr("Delete")
                width: tableObjectID.widthCell*2
                horizontalAlignment: Text.AlignHCenter
            }

            headerDelegate:Rectangle{
                color: _headerColor
                height: tableObjectID.heightCell
                border.width: _borderSize
                border.color: _borderColor
                Text{
                    anchors.centerIn : parent
                    text: styleData.value
                    color: _textColor
                    font.pointSize: _fontSizeText + 1
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

            }
            rowDelegate: Rectangle {
                height: tableObjectID.heightCell
            }

            itemDelegate: Rectangle {
                id: item_id
                height: tableObjectID.heightCell
                border.width: _borderSize
                border.color: _borderColor
                color: ConfigView.mainWhiteColor
                Text {
                    visible: styleData.role !== "load" &&
                             styleData.role !== "clone" &&
                             styleData.role !== "edit" &&
                             styleData.role !== "remove"
                    id: content_text
                    width: parent.width
                    height: parent.height
                    text: {
                        return styleData.value
                    }
                    font.pointSize: _fontSizeText
                    anchors.centerIn : parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WrapAnywhere
                    color: ConfigView.mainBlueColor
                }

                ButtonMaterial{
                    visible: styleData.role === "load"
                    _width: parent.height
                    _height: parent.height
                    _size: _height*0.8
                    _iconSourceOn: "uploadMultiple"
                    _colorIconHigh: ConfigView.mainBlueColor
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {
                        _viewModel.doLoadRecipe(recipe_model.get(tableview.currentRow).recipeName, true)
                    }
                }

                ButtonMaterial{
                    visible: styleData.role === "clone"
                    _width: parent.height
                    _height: parent.height
                    _size: _height*0.8
                    _iconSourceOn: "contentCopy"
                    _colorIconHigh: ConfigView.mainBlueColor
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {
                        // get current recipe name
                        cloneRecipePopUp.open()
                    }
                }

                ButtonMaterial{
                    visible: styleData.role === "edit"
                    _width: parent.height
                    _height: parent.height
                    _size: _height*0.8
                    _iconSourceOn: "commentEdit"
                    _colorIconHigh: ConfigView.mainBlueColor
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {

                    }
                }

                ButtonMaterial{
                    visible: styleData.role === "remove"
                    _width: parent.height
                    _height: parent.height
                    _size: _height*0.8
                    _iconSourceOn: "deleteForever"
                    _colorIconHigh: ConfigView.mainBlueColor
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    onClicked: {

                        if(recipe_model.get(tableview.currentRow).recipeName === "CalToolTest")
                        {
                            message_dialog.openDialog(qsTr("Delete Recipe"),
                                                    qsTr("Cannot delete CalToolTest Job"),
                                                    StandardIcon.Information, StandardButton.Yes)
                            message_dialog.index = 0

                            return
                        }

                        message_dialog.openDialog (qsTr("Delete Recipe"),
                                    qsTr("Do you want to delete recipe ") + styleData.value + "?",
                                    StandardIcon.Question, StandardButton.Yes | StandardButton.No)
                        message_dialog.index = 1
                    }
                }
            }

        }

    }

    DialogView {
        id: message_dialog
        onButtonClicked_Signal: (buttonType)=>{

            if(buttonType === StandardButton.Yes){
                if(message_dialog.index === 1)
                    delete_recipe_view._viewModel.doDeleteRecipe(recipe_model.get(tableview.currentRow).recipeName)
            }
            else if(buttonType === StandardButton.No){

            }
        }
    }


}
