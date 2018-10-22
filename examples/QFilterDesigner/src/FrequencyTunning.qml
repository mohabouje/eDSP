import QtQuick 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3


RowLayout {
    property double pMinimum: 8000
    property double pMaximum: 42000
    property double pLower: 100
    property double pUpper: 500
    property double pCutoff: 1000

    TextDial {
        pText: qsTr("Cut-Off")
        pFrom: pMinimum
        pTo: pMaximum
        pValue: pCutoff
    }

    TextDial {
        pText: qsTr("Lower")
        pFrom: pMinimum
        pTo: pMaximum
        pValue: pLower
    }

    TextDial {
        pText: qsTr("Upper")
        pFrom: pMinimum
        pTo: pMaximum
        pValue: pUpper
    }

    TextDial {
        pText: qsTr("Ripple")
        pFrom: 1
        pTo: 100
        pValue: 10
        pUnit: "dB"
    }

}




/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
