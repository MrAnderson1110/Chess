import QtQuick 2.11
import QtQml 2.11

import qmlplugins 1.0

Rectangle {
    id: root
    property color whiteColor: "white"
    property color blackColor: "black"
    property var piece: null

    color: "transparent"

    ColorizedImage {
        id: img
        anchors.fill: parent
        color: piece.command === BasicPiece.White ? whiteColor : blackColor
        source: {
            switch(piece.type) {
            case BasicPiece.King:
                return "./resources/king.svg"
            case BasicPiece.Queen:
                return "./resources/queen.svg"
            case BasicPiece.Bishop:
                return "./resources/bishop.svg"
            case BasicPiece.Knight:
                return "./resources/knight.svg"
            case BasicPiece.Rook:
                return "./resources/rook.svg"
            case BasicPiece.Pawn:
                return "./resources/pawn.svg"
            }
        }
    }

    MoveManipulator {
        anchors.fill: parent
        basePiece: piece
        onStarted: if(!!piece) piece.startMove()
        onMoved: if(!!piece) piece.move(geometry)
        onFinsihed: if(!!piece) piece.finishMove()
    }
}
