import QtQuick 2.11
import QtQuick.Window 2.2
import QtCharts 2.2
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Universal 2.0


ApplicationWindow {
    id: window
    visible: true
    width: 1000
    height: 720
    title: qsTr("QFIRDesigner")

    header: ToolBar {
        id: toolBar;
        position: ToolBar.Header

        RowLayout {
            anchors.fill: parent
            TabButton {
                checkable: false
                icon.source:  "qrc:/menu.svg"
                icon.width: 0.45 * parent.height
                icon.height: 0.45 * parent.height
                onClicked: {
                    if (drawer.visible) {
                        drawer.close()
                    } else {
                        drawer.open()
                    }
                }
            }

            Label {
                id: toolbarTitle
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true

            }

            TabButton {
                checkable: false
                icon.source:  "qrc:more.png"
                icon.width: 0.45 * parent.height
                icon.height: 0.45 * parent.height
                onClicked: optionsMenu.open()

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: "Updates"
                    }

                    MenuItem {
                        text: "About"
                   }
                }
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        position: TabBar.Footer
        ImageTabButton {
            pHighlight: Universal.accent
            pNormal: Universal.foreground
            pIcon: "qrc:spectrum.png"
            text: qsTr("Frequency R.")
        }

        ImageTabButton {
            pHighlight: Universal.accent
            pNormal: Universal.foreground
            pIcon: "qrc:wave.png"
            text: qsTr("Impulse R.")
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        padding: 0

        Page {

        }

        Page {


        }
    }

    Drawer {
        id: drawer
        width: 0.3 * window.width
        height: window.height - header.height
        y: header.height

        Row {
            width: parent.width
            padding: 10
            NavigationDrawer {
                width: parent.width - 2 * parent.padding
                height: parent.height * 0.6
            }
        }

    }
}
