import QtQuick 2.15

import ConfigView 1.0
import "../../Component"

Item {
    id: setout_item
    property string _fontFamily: ConfigView.fontFamily
    property color _textColor: ConfigView.textColor
    property int _fontSizeText: 12
    property int _rowNumber: 0
    property int _itemWidth: width*0.96
    property int _itemHeight
    property int _spacing
    property bool _enable: false
    signal numberChanged_Signals()

    function getColor(index){
        if(index === 0){
            return "#D1D1D1" // empty
        }
        else if(index === 1){
            return "#269645" // pass
        }
        if(index === 2){
            return "#FBC013" // warning
        }
        if(index === 3){
            return "#E33C2F" // fail
        }
        return "#D1D1D1" // empty
    }

    function getNumberMold(){
        return number_mold_text.getText()
    }

    function setMoldNumberValue(values){
        number_mold_text.setText(values.length)
        for(var i = 0; i < values.length; i++){
            if(i >= repeater_item.count)
                return
            repeater_item.itemAt(i).color = getColor(values[i])
        }
    }

    function setSerialValue(index, result){
        repeater_item.itemAt(index).color = getColor(result)
    }

    function clear() {
        number_mold_text.setText("0")
    }

    function updateItemModel(numberItem){
        if(_inputItemModel.count > numberItem){
            var number = _inputItemModel.count - numberItem
            _inputItemModel.remove(_inputItemModel.count - number, number);
        }
        else if(_inputItemModel.count < numberItem)
        {
            var number = numberItem - _inputItemModel.count
            for(var i = 0; i < number; i++){
               _inputItemModel.append({
                  "value": 0
              });
            };
        }
    }

    ListModel {
        id: _inputItemModel
    }

    Column {
        id: column_layout
        width: _itemWidth
        spacing: _spacing
        anchors.horizontalCenter: parent.horizontalCenter

        InputText{
            id: number_mold_text
            enabled: _enable
            opacity: enabled ? 1 : 0.5
            _width: setout_item._itemWidth
            _height: setout_item._itemHeight
            _fontSizeText: _fontSizeText
            _text: "0"
            _leftMagin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            textHorizontalAlignment: TextInput.AlignHCenter
            _reg: RegExpValidator { regExp: /^([0-9]\d*)$/ }
            _inputMethodHints: Qt.ImhFormattedNumbersOnly
            onTextChanged_Signals: (value) => {
                setout_item._rowNumber = Number(value);
                setout_item.numberChanged_Signals();
                // if(_inputItemModel.count > setout_item._rowNumber){
                //     var number = _inputItemModel.count - setout_item._rowNumber
                //     _inputItemModel.remove(_inputItemModel.count - number, number);
                // }
                // else if(_inputItemModel.count < setout_item._rowNumber)
                // {
                //     var number = setout_item._rowNumber - _inputItemModel.count
                //     for(var i = 0; i < number; i++){
                //        _inputItemModel.append({
                //           "value": 0
                //       });
                //     };
                // }
                // _inputItemModel.clear();
            }
        }

        Repeater {
            id: repeater_item
            width: parent.width
            model: _inputItemModel
            delegate:
                Rectangle{
                    width: column_layout.width
                    height: setout_item._itemHeight
                    color: getColor(value)
                    radius: 5
                    anchors{
                        horizontalCenter: parent.horizontalCenter
                    }

                    Text {
                        text: index >= _rowNumber ? "" : (index + 1)
                        font.pointSize: _fontSizeText
                        color: "black"
                        font.family: _fontFamily
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.horizontalAlignment
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter: parent.horizontalCenter
                    }


            }
        }
    }

}
