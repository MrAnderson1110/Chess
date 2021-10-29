import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQml 2.11
import QtQuick.Layouts 1.11
import QtQuick.Window 2.11
import qmlplugins 1.0

ApplicationWindow {
    id: root
    height: minimumHeight
    width: minimumWidth
    minimumHeight: 480
    minimumWidth: 750
    maximumHeight: minimumHeight
    maximumWidth: minimumWidth

    property bool gameOver: AppState.mateToWhite || AppState.mateToBlack


    visible: true
    title: qsTr("Chess")

    background: Rectangle {
        id: back
        color: board.oddColor
        anchors.fill: parent
    }

    Text {
        visible: gameOver
        anchors.centerIn: parent
        text: "Game over for " +
              (AppState.mateToWhite ? "White" : "Black")
        z: 999
        font.bold: true
        font.pointSize: 20

        PropertyAnimation on opacity {
            running: gameOver
            from: 0.0
            to: 1.0
            easing.type: Easing.InOutQuad
        }

    }

    RowLayout {
        id: mainBoard
        opacity: gameOver ? 0.3 : 1.0
        anchors.fill: parent
        spacing: 0        

        PropertyAnimation on opacity {
            running: gameOver
            from: 1.0
            to: 0.3
            easing.type: Easing.InOutQuad
        }

        ChessBoard {
            id: board
            Layout.preferredHeight: root.minimumHeight
            Layout.preferredWidth: height
            inverted: true

            Rook {
                id: whiteRook_1
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteRook_1 }
                rowIndex: 7
                columnIndex: 0
                moved: false
            }
            Knight {
                id: whiteKnight_1
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteKnight_1 }
                rowIndex: 7
                columnIndex: 1
            }
            Bishop {
                id: whiteBishop_1
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteBishop_1 }
                rowIndex: 7
                columnIndex: 2
            }
            Queen {
                id: whiteQueen
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteQueen }
                rowIndex: 7
                columnIndex: 3
            }
            King {
                id: whiteKing
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteKing }
                rowIndex: 7
                columnIndex: 4
                moved: false
            }
            Bishop {
                id: whiteBishop_2
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteBishop_2 }
                rowIndex: 7
                columnIndex: 5
            }
            Knight {
                id: whiteKnight_2
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteKnight_2 }
                rowIndex: 7
                columnIndex: 6
            }
            Rook {
                id: whiteRook_2
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteRook_2 }
                rowIndex: 7
                columnIndex: 7
                moved: false
            }

            Pawn {
                id: whiteRookPawn_1
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteRookPawn_1 }
                rowIndex: 6
                columnIndex: 0
            }
            Pawn {
                id: whiteKnightPawn_1
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteKnightPawn_1 }
                rowIndex: 6
                columnIndex: 1
            }
            Pawn {
                id: whiteBishopPawn_1
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteBishopPawn_1 }
                rowIndex: 6
                columnIndex: 2
            }
            Pawn {
                id: whiteQueenPawn
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteQueenPawn }
                rowIndex: 6
                columnIndex: 3
            }
            Pawn {
                id: whiteKingPawn
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteKingPawn }
                rowIndex: 6
                columnIndex: 4
            }
            Pawn {
                id: whiteBishopPawn_2
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteBishopPawn_2 }
                rowIndex: 6
                columnIndex: 5
            }
            Pawn {
                id: whiteKnightPawn_2
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteKnightPawn_2 }
                rowIndex: 6
                columnIndex: 6
            }
            Pawn {
                id: whiteRookPawn_2
                command: board.inverted ? BasicPiece.White : BasicPiece.Black
                background: PieceStyle { piece: whiteRookPawn_2 }
                rowIndex: 6
                columnIndex: 7
            }

            Rook {
                id: blackRook_1
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackRook_1 }
                rowIndex: 0
                columnIndex: 0
                moved: false
            }
            Knight {
                id: blackKnight_1
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackKnight_1 }
                rowIndex: 0
                columnIndex: 1
            }
            Bishop {
                id: blackBishop_1
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackBishop_1 }
                rowIndex: 0
                columnIndex: 2
            }
            Queen {
                id: blackQueen
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackQueen }
                rowIndex: 0
                columnIndex: 3
            }
            King {
                id: blackKing
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackKing }
                rowIndex: 0
                columnIndex: 4
                moved: false
            }
            Bishop {
                id: blackBishop_2
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackBishop_2 }
                rowIndex: 0
                columnIndex: 5
            }
            Knight {
                id: blackKnight_2
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackKnight_2 }
                rowIndex: 0
                columnIndex: 6
            }
            Rook {
                id: blackRook_2
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackRook_2 }
                rowIndex: 0
                columnIndex: 7
                moved: false
            }

            Pawn {
                id: blackRookPawn_1
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackRookPawn_1 }
                rowIndex: 1
                columnIndex: 0
            }
            Pawn {
                id: blackKnightPawn_1
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackKnightPawn_1 }
                rowIndex: 1
                columnIndex: 1
            }
            Pawn {
                id: blackBishopPawn_1
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackBishopPawn_1 }
                rowIndex: 1
                columnIndex: 2
            }
            Pawn {
                id: blackQueenPawn
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackQueenPawn }
                rowIndex: 1
                columnIndex: 3
            }
            Pawn {
                id: blackKingPawn
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackKingPawn }
                rowIndex: 1
                columnIndex: 4
            }
            Pawn {
                id: blackBishopPawn_2
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackBishopPawn_2 }
                rowIndex: 1
                columnIndex: 5
            }
            Pawn {
                id: blackKnightPawn_2
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackKnightPawn_2 }
                rowIndex: 1
                columnIndex: 6
            }
            Pawn {
                id: blackRookPawn_2
                command: board.inverted ? BasicPiece.Black : BasicPiece.White
                background: PieceStyle { piece: blackRookPawn_2 }
                rowIndex: 1
                columnIndex: 7
            }
        }

        History {
            id: history
            Layout.preferredHeight: root.minimumHeight - 40
            Layout.fillWidth: true
        }
    }
}
