import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0


import ConfigView 1.0

import "../../../Component"

GroupBox{
    id: group_input_param
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.textColor
    property int _fontSizeText: 12

    property string _groupName
    property int _headerHeight
    property int _itemWidth
    property int _itemHeight
    property int _itemSpacing
    property int _itemColumnSpacing
    property int _itemColumn1Width
    property int _itemColumn2Width
    property string _imageName: ""
    property bool _isExpand: true

    property ListModel _inputItemModel: []

    // for backup state
    property var itemName: ""

    function doSwitchExpand(isExpand){
        _isExpand = isExpand;
        for(var i = 1; i < _inputItemModel.count; i++){
            input_items.itemAt(i).visible = _isExpand
        }
        if(isExpand)
            processValueChanged(itemName)
    }

    function getValues(){
        var values = []
        for(var i = 0; i < _inputItemModel.count; i++){
            if(input_items.itemAt(i)._type === "seperator")
                continue
            values.push(input_items.itemAt(i).getValue())
        }
        return values
    }

    function setValues(values){
        var k = 0;
        for(var i = 0; i < _inputItemModel.count; i++){
            if(input_items.itemAt(i)._type === "seperator")
                continue
            input_items.itemAt(i).setValue(values[k])
            k++;
        }
    }

    function processValueChangedAgain()
    {
        processValueChanged(itemName)
    }

    function processValueChanged(name){
        if(!_isExpand)
            return
        if((name === "Количественное измерение" || name === "Number Dimension") &&
                (group_input_param._groupName === "Проверка корпуса R" || group_input_param._groupName === "BodyR Inspect"))
        {
            itemName = "Number Dimension"
            var value = input_items.itemAt(1).getValue()
            console.log(itemName, value)
            var start = 2 + value*5
            for(var i = 0; i < _inputItemModel.count; i++){
                if(i < start)
                    input_items.itemAt(i).visible = true
                else
                    input_items.itemAt(i).visible = false
            }
        }

        if((name === "Shape" || name === "Форма" || name === "Number Dimension" || name === "Количественное измерение") &&
                (group_input_param._groupName === "Non-round Shape Inspect" ||
                    group_input_param._groupName === "Проверка некруглая форма"))
        {
            itemName = "Shape"
            var shapeType = input_items.itemAt(1).getValue() // 0: rect, 1: square, 2: ovl
            var numberDimension = input_items.itemAt(2).getValue() // 1-8

            console.log(itemName, shapeType, numberDimension)
            input_items.itemAt(0).visible = true
            input_items.itemAt(1).visible = true

            // hide all
            for(var i = 3; i < _inputItemModel.count; i++){
                input_items.itemAt(i).visible = false
            }

            // for each dimension to visible param
            for(var i = 0; i < numberDimension; i++){

                var startIndex = 3 + i*25 // each dimension have total item
                var endIndex = 3 + i*25 // each dimension have total item
                input_items.itemAt(startIndex).visible = true
                if(shapeType === 0) // rectangle
                {
                    startIndex = startIndex + 1;
                    endIndex = startIndex + 10;
                }
                else if(shapeType === 1) // square
                {
                    startIndex = startIndex + 11;
                    endIndex = startIndex + 7;
                }
                else if(shapeType === 2) // oval
                {
                    startIndex = startIndex + 18;
                    endIndex = startIndex + 7;
                }

                for(var k = startIndex; k < endIndex; k++){
                    input_items.itemAt(k).visible = true
                }
            }


        }
    }

    background:Rectangle{
        color: "transparent"
        width: parent.width
        height: parent.height
        border.width: 2
        border.color: ConfigView.addLightBlueColor

        MouseArea {
            id: mouseArea
            anchors.fill: parent

            onDoubleClicked: {
                doSwitchExpand(!_isExpand)
            }
        }
    }

    label:Rectangle{
        color: ConfigView.addLightBlueColor
        width: title.contentWidth*1.1
        radius: 5
        height: _headerHeight
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.top
        anchors.bottomMargin: -height/2
        Text {
            id: title
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 5
            verticalAlignment: Text.AlignVCenter
            text: _groupName
            color: _textColor
            font.bold: true
            font.pointSize: _fontSizeText + 2
            font.family: _fontFamily
        }
    }

    Row {
        width: group_input_param._itemWidth
        spacing: group_input_param._itemSpacing
        Column {
            id: column_layout
            width: group_input_param._itemWidth*0.68
            // height: parent.height
            spacing: group_input_param._itemSpacing
            Repeater {
                id: input_items
                model: group_input_param._inputItemModel
                delegate: InputItem {
                    id: item
                    visible: model.isVisible
                    width: parent.width
                    height: _itemHeight
                    _name: model.name
                    _type: model.type
                    _cbbModel: model.cbbModel
                    _imageName: (typeof model.image_path !== "undefined" && model.image_path !== null) ? model.image_path : ""
                    _imageHeight: model.image_height
                    _placeholderText: model.type.toUpperCase() + " " + model.range
                    _columnSpacing: group_input_param._itemColumnSpacing
                    _clumn1Width: group_input_param._itemColumn1Width
                    _clumn2Width: group_input_param._itemColumn2Width
                    onValueChanged_Signals: (name, value) => {
                        group_input_param.processValueChanged(name)
                    }
                }
            }
        }

        Rectangle {
            width: group_input_param._itemWidth*0.32
            height: column_layout.height
            color: "transparent"
            Image {
                visible: _imageName !== ""
                width: parent.width*0.5
                height: parent.height
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                source: _imageName === "" ? _imageName : ("../../../Resources/"  + _imageName)
                fillMode: Image.PreserveAspectFit
            }
        }
    }



}

