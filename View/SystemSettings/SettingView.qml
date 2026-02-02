import QtQuick 2.15

import "../../Component"

Item {
    clip: true
    width: parent.width
    height: parent.height

    Rectangle{
        id: main_layout_id
        width: parent.width
        height: parent.height
        color: "#333333"
        anchors.centerIn: parent
        Row{
            anchors.fill: parent
            spacing: parent.width*0.01
            Rectangle{
                width: parent.width*0.15
                height: parent.height*0.96
                anchors.verticalCenter: parent.verticalCenter
                color: "transparent"
                ButtonMaterialTextHorizontal{
                    width: parent.width*0.8
                    height: width*0.4
                    _size: height*0.8
                    _text: "Apply"
                    _iconSourceOn: "contentSaveCog"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    onClicked: {
                        single_camera_setting_1.sendValueToVM()
                        common_setting.sendValueToVM()
                    }
                }

            }

            Column{
                width: parent.width*0.85
                height: parent.height*0.96
                spacing: parent.height*0.01
                anchors.verticalCenter: parent.verticalCenter
                CameraSettingView{
                    id: single_camera_setting_1
                    width: parent.width*0.98
                    height: parent.height*0.6
                    _fontSizeText: parent.height*0.03*internalTabControlBar.fontSizeScale
                    _viewModel: settingVM.listCameraSettingVM[0]
                    _spacing: parent.height*0.02
                }

                CommonSettingView{
                    id: common_setting
                    width: parent.width*0.98
                    height: parent.height*0.39
                    _fontSizeText: parent.height*0.03*internalTabControlBar.fontSizeScale
                    _viewModel: settingVM.commonSettingVM
                    _spacing: parent.height*0.02
                }
            }


        }


    }

}
