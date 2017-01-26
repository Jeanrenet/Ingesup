import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3
import QtQuick.Extras 1.4
import QtQuick.Window 2.2

Rectangle {
    id: rectangle1

    width: 300
    height: 400
    property alias connectButton: connectButton

    gradient: Gradient {
        GradientStop {
            position: 0
            color: "#ffffff"
        }

        GradientStop {
            position: 0.252
            color: "#ffffff"
        }

        GradientStop {
            position: 0.507
            color: "#000000"
        }

        GradientStop {
            position: 0.863
            color: "#ffffff"
        }
    }

    Button {
        id: connectButton
        width: 150
        height: 50
        text: qsTr("Connect")
        anchors.right: parent.right
        anchors.rightMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 50
        anchors.verticalCenter: parent.verticalCenter
        checkable: true
        checked: false
        highlighted: false
    }
}
