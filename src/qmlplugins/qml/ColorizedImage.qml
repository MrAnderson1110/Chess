import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: root

    property color color
    property alias asynchronous: image.asynchronous
    property alias cache: image.cache
    property alias fillMode: image.fillMode
    property alias horizontalAlignment: image.horizontalAlignment
    property alias mirror: image.mirror
    property alias paintedHeight: image.paintedHeight
    property alias paintedWidth: image.paintedWidth
    property alias progress: image.progress
    property alias smooth: image.smooth
    property alias source: image.source
    property alias sourceSize: image.sourceSize
    property alias status: image.status
    property alias verticalAlignment: image.verticalAlignment

    implicitWidth: image.implicitWidth
    implicitHeight: image.implicitHeight

    Image {
        anchors.fill: root
        id: image
        visible: root.color.a === 0
    }

    ColorOverlay {
        id: colorOverlay
        anchors.fill: root
        source: image
        color: root.color
        visible: root.color.a !== 0
    }
}
