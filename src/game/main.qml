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


    visible: true
    title: qsTr("Chess")

    background: Rectangle {
        id: back
        color: board.oddColor
        anchors.fill: parent
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0
        ChessBoard {
            id: board
            Layout.preferredHeight: root.minimumHeight
            Layout.preferredWidth: height

            Rook {
                id: blackRook_1
                command: BasicPiece.Black
                background: PieceStyle { piece: blackRook_1 }
                rowIndex: 7
                columnIndex: 0
                moved: false
            }
            Knight {
                id: blackKnight_1
                command: BasicPiece.Black
                background: PieceStyle { piece: blackKnight_1 }
                rowIndex: 7
                columnIndex: 1
            }
            Bishop {
                id: blackBishop_1
                command: BasicPiece.Black
                background: PieceStyle { piece: blackBishop_1 }
                rowIndex: 7
                columnIndex: 2
            }
            Queen {
                id: blackQueen
                command: BasicPiece.Black
                background: PieceStyle { piece: blackQueen }
                rowIndex: 7
                columnIndex: 3
            }
            King {
                id: blackKing
                command: BasicPiece.Black
                background: PieceStyle { piece: blackKing }
                rowIndex: 7
                columnIndex: 4
                moved: false
            }
            Bishop {
                id: blackBishop_2
                command: BasicPiece.Black
                background: PieceStyle { piece: blackBishop_2 }
                rowIndex: 7
                columnIndex: 5
            }
            Knight {
                id: blackKnight_2
                command: BasicPiece.Black
                background: PieceStyle { piece: blackKnight_2 }
                rowIndex: 7
                columnIndex: 6
            }
            Rook {
                id: blackRook_2
                command: BasicPiece.Black
                background: PieceStyle { piece: blackRook_2 }
                rowIndex: 7
                columnIndex: 7
                moved: false
            }

            Pawn {
                id: blackRookPawn_1
                command: BasicPiece.Black
                background: PieceStyle { piece: blackRookPawn_1 }
                rowIndex: 6
                columnIndex: 0
            }
            Pawn {
                id: blackKnightPawn_1
                command: BasicPiece.Black
                background: PieceStyle { piece: blackKnightPawn_1 }
                rowIndex: 6
                columnIndex: 1
            }
            Pawn {
                id: blackBishopPawn_1
                command: BasicPiece.Black
                background: PieceStyle { piece: blackBishopPawn_1 }
                rowIndex: 6
                columnIndex: 2
            }
            Pawn {
                id: blackQueenPawn
                command: BasicPiece.Black
                background: PieceStyle { piece: blackQueenPawn }
                rowIndex: 6
                columnIndex: 3
            }
            Pawn {
                id: blackKingPawn
                command: BasicPiece.Black
                background: PieceStyle { piece: blackKingPawn }
                rowIndex: 6
                columnIndex: 4
            }
            Pawn {
                id: blackBishopPawn_2
                command: BasicPiece.Black
                background: PieceStyle { piece: blackBishopPawn_2 }
                rowIndex: 6
                columnIndex: 5
            }
            Pawn {
                id: blackKnightPawn_2
                command: BasicPiece.Black
                background: PieceStyle { piece: blackKnightPawn_2 }
                rowIndex: 6
                columnIndex: 6
            }
            Pawn {
                id: blackRookPawn_2
                command: BasicPiece.Black
                background: PieceStyle { piece: blackRookPawn_2 }
                rowIndex: 6
                columnIndex: 7
            }

            Rook {
                id: whiteRook_1
                command: BasicPiece.White
                background: PieceStyle { piece: whiteRook_1 }
                rowIndex: 0
                columnIndex: 0
                moved: false
            }
            Knight {
                id: whiteKnight_1
                command: BasicPiece.White
                background: PieceStyle { piece: whiteKnight_1 }
                rowIndex: 0
                columnIndex: 1
            }
            Bishop {
                id: whiteBishop_1
                command: BasicPiece.White
                background: PieceStyle { piece: whiteBishop_1 }
                rowIndex: 0
                columnIndex: 2
            }
            Queen {
                id: whiteQueen
                command: BasicPiece.White
                background: PieceStyle { piece: whiteQueen }
                rowIndex: 0
                columnIndex: 3
            }
            King {
                id: whiteKing
                command: BasicPiece.White
                background: PieceStyle { piece: whiteKing }
                rowIndex: 0
                columnIndex: 4
                moved: false
            }
            Bishop {
                id: whiteBishop_2
                command: BasicPiece.White
                background: PieceStyle { piece: whiteBishop_2 }
                rowIndex: 0
                columnIndex: 5
            }
            Knight {
                id: whiteKnight_2
                command: BasicPiece.White
                background: PieceStyle { piece: whiteKnight_2 }
                rowIndex: 0
                columnIndex: 6
            }
            Rook {
                id: whiteRook_2
                command: BasicPiece.White
                background: PieceStyle { piece: whiteRook_2 }
                rowIndex: 0
                columnIndex: 7
                moved: false
            }

            Pawn {
                id: whiteRookPawn_1
                command: BasicPiece.White
                background: PieceStyle { piece: whiteRookPawn_1 }
                rowIndex: 1
                columnIndex: 0
            }
            Pawn {
                id: whiteKnightPawn_1
                command: BasicPiece.White
                background: PieceStyle { piece: whiteKnightPawn_1 }
                rowIndex: 1
                columnIndex: 1
            }
            Pawn {
                id: whiteBishopPawn_1
                command: BasicPiece.White
                background: PieceStyle { piece: whiteBishopPawn_1 }
                rowIndex: 1
                columnIndex: 2
            }
            Pawn {
                id: whiteQueenPawn
                command: BasicPiece.White
                background: PieceStyle { piece: whiteQueenPawn }
                rowIndex: 1
                columnIndex: 3
            }
            Pawn {
                id: whiteKingPawn
                command: BasicPiece.White
                background: PieceStyle { piece: whiteKingPawn }
                rowIndex: 1
                columnIndex: 4
            }
            Pawn {
                id: whiteBishopPawn_2
                command: BasicPiece.White
                background: PieceStyle { piece: whiteBishopPawn_2 }
                rowIndex: 1
                columnIndex: 5
            }
            Pawn {
                id: whiteKnightPawn_2
                command: BasicPiece.White
                background: PieceStyle { piece: whiteKnightPawn_2 }
                rowIndex: 1
                columnIndex: 6
            }
            Pawn {
                id: whiteRookPawn_2
                command: BasicPiece.White
                background: PieceStyle { piece: whiteRookPawn_2 }
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
