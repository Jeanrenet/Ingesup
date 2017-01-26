import QtQuick 2.4

MainPageForm {
    rectangle1 {
        color: BLEDiscover.connectionState?"green":"red"
    }
    switch1 {
        checked: BLEDiscover.enable
    }

    switch1.onClicked: {
        BLEDiscover.switchEnable(switch1.checked)
    }
    temperature {
        text: Math.round(BLEDiscover.temperature *10) /10.0 + " °C"
    }
}
