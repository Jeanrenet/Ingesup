import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

Window {
    visible: true

    width: 300
    height: 400

    MainForm {
        connectButton.onClicked: {
            BLEDiscover.start();
            pageLoader.source = "MainPage.qml"
        }
        connectButton {
            font.pointSize:  25;
        }

        anchors.fill: parent

        Loader { id: pageLoader }
    }
}
