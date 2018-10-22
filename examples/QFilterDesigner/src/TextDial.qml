import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3


ColumnLayout {

    property string pText: "Example"
    property double pFrom: 0
    property double pTo: 100
    property double pValue: 50
    property double pScale: 0.30
    property string pUnit: "Hz"
    Dial {
        id: dial
        width: parent.width
        stepSize: 10
        from: pFrom
        to: pTo
        value: pValue
        Layout.fillWidth: true
    }

    Text {
        text: pText
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        Layout.fillWidth: true
    }

    Text {
        text: Math.round(dial.value) + " " + pUnit
        font.pointSize: 10
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        Layout.fillWidth: true
    }
}



/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
