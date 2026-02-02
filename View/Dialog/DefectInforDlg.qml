import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: root
    color: "lightgray"

    visible: true
    required property string titleDescription

    signal moveByTitleBar(int xPos, int yPos)

    function clearData()
    {
        sectionedModel.clear();
    }

    function addData(header, description, pixelValue, mmValue)
    {
        sectionedModel.append({
            "name": description,
            "section": header,
            "pixelValue": pixelValue,
            "mmValue": mmValue
        });
    }

    // title bar
    Rectangle {
        id: titleBar
        width: parent.width
        height: 60
        color: "#404142"



        Text {
            id: titleBarText
            text: qsTr(titleDescription)
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 30
        }

        MouseArea {
            id: titleBarDragArea
            anchors.fill: parent

            property real dragStartX
            property real dragStartY

            onPressed: {

                dragStartX = mouseX
                dragStartY = mouseY
            }

            onPositionChanged: {
                root.moveByTitleBar(mouseX - dragStartX, mouseY - dragStartY)
            }

        }
    }


     // Model with a section identifier (like a category or group)
    ListModel {
        id: sectionedModel
        //ListElement { name: "Item 2"; section: "Header 1"; value: "12.4" }
        //ListElement { name: "Item 1"; section: "Header 1"; value: "12.3" }
        //ListElement { name: "Item 3"; section: "Header 1"; value: "12.5" }
        //ListElement { name: "Item 4"; section: "Header 2"; value: "12.6" }
        //ListElement { name: "Item 5"; section: "Header 2"; value: "12.7" }
        //ListElement { name: "Item 6"; section: "Header 2"; value: "12.8" }
        //ListElement { name: "Item 7"; section: "Header 3"; value: "12.9" }
        //ListElement { name: "Item 8"; section: "Header 3"; value: "12.10" }
        //ListElement { name: "Item 9"; section: "Header 3"; value: "12.11" }
    }


    Rectangle {
        anchors {
            top: titleBar.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

            // ListView to display items with section headers
            ListView {
                id: listView
                anchors.fill: parent
                model: sectionedModel
                clip: true

                // Define sections by the "section" property in the model
                section.property: "section"
                section.criteria: ViewSection.FullString // Full matching for section titles

                delegate: Item {
                    width: listView.width
                    height: 40

                    Rectangle {
                        width: parent.width
                        height: parent.height
                        color: "lightblue"
                        Text {
                            anchors.centerIn: parent
                            font.pointSize: 12
                            text: model.name + ": " + model.mmValue +
                                (model.name.toLowerCase().includes("angle") ? " deg" :
                                (model.name.toLowerCase().includes("weight") ? " gams" :
                                (model.name.toLowerCase().includes("code number") ? "" : " mm")))
                        }
                    }
                }

                // Section header delegate
                section.delegate: Rectangle {
                    width: listView.width
                    height: 40
                    color: "lightgray"

                    Text {
                        anchors.centerIn: parent
                        text: section // Displays the section name (like Header 1, Header 2)
                        font.bold: true
                        font.pointSize: 14
                    }
                }

                // Enable vertical scrolling
                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                }
            }
    }
}
