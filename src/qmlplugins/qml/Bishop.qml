import QtQuick 2.0
import qmlplugins 1.0

BasicPiece {
    id: root
    type: IPiece.Bishop

    ColorizedImage {
        id: icon
        anchors.fill: parent
        color: command === IPiece.White ? "white" : "black"
    }
}
