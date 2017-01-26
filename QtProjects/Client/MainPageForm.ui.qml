import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Extras 1.4

Item {
    id: item1
    width: 300
    height: 400
    property alias switch1: switch1
    property alias rectangle1: rectangle1
    property alias temperature: temperature

    Rectangle {
        id: rectangle1
        width: 300
        color: "#ffffff"
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout1
            anchors.fill: parent


            Text {
                id: text1
                text: qsTr("Temperature")
                anchors.right: parent.right
                anchors.rightMargin: 70
                anchors.left: parent.left
                anchors.leftMargin: 70
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 25
            }
            Text {
                id: temperature
                text: qsTr("Text")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.right: parent.right
                anchors.rightMargin: 70
                anchors.left: parent.left
                anchors.leftMargin: 70
                font.pixelSize: 25
            }

            RowLayout {
                id: rowLayout1
                width: 100
                height: 100
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                Switch {
                    id: switch1
                    width: 150
                    text: "Enabled"
                    checked: true
                    scale: 1.7
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                }
            }
        }
    }
}
