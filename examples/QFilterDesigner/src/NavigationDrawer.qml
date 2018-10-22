import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.0

ColumnLayout {
    spacing: 5

    ComboBox {
        Layout.fillWidth: true
        id: designer_type
        width: parent.width * 0.9
        model: [
            "Butterworth",
            "Chebyshev",
            "I. Chebyshev",
            "Bessel",
            "Elliptic"
        ]
    }

    ComboBox {
        Layout.fillWidth: true
        id: filter_type
        width: parent.width * 0.9
        model: [
            "LowPass",
            "HighPass",
            "BandPass",
            "BandStop",
            "AllPass"
        ]
    }

    RowLayout {
        Layout.fillWidth: true
        Slider {
            id: sample_rate
            from: 8000
            to: 120000
            value: 11000
        }

        Text {
            Layout.fillHeight: true
            id: label
            text : Math.round(sample_rate.value) + " Hz"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            renderType: Text.QtRendering
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Slider {
            id: order
            from: 0
            to: 50
            value: 10
        }

        Text {
            Layout.fillHeight: true
            text : Math.round(order.value) + " Order"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            renderType: Text.QtRendering
        }
    }

    ToolSeparator {
        Layout.fillWidth: true
        orientation: Qt.Horizontal
    }


    FrequencyTunning {
        pMinimum: sample_rate.from
        pMaximum: sample_rate.to
    }

    ToolSeparator {
        Layout.fillWidth: true
        orientation: Qt.Horizontal
    }

    Switch {
        width: parent.width
        id: enable_shelving
        text: qsTr("Shelving Filter")
    }

    Switch {
        width: parent.width
        id: enable_psd
        text: qsTr("Power Spectral Density")
    }



}


/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
