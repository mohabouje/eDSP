import QtQuick 2.0
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0

TabButton {
    id: tabButton
    property color pHighlight:  Qt.red
    property color pNormal: Qt.blue
    property string pIcon: "";

    contentItem: Rectangle {
        anchors.fill: parent
        Image {
            id: image
            anchors.centerIn: parent
            source: pIcon
            sourceSize: Qt.size(0.80 * parent.height,  0.80 * parent.height)
            smooth: true
            visible: false
        }
        ColorOverlay {
            anchors.fill: image
            source: image
            color: (tabButton.checked) ? pHighlight : pNormal;
        }
    }
}
