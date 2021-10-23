#ifndef CHESSCHESS_GLOBAL_H
#define CHESSCHESS_GLOBAL_H

#include <QtGlobal>
#include <QPoint>
#include <QList>

class BasicPiece;

// Направление обхода позиций от startPoint
enum MoveDirection
{
    Unspecified,
    StartPoint,     // { piece pos point } -> column && row
    TopLeft,        // { startPoint - 1, startPoint - 1 } -> column - 1 && row - 1
    Top,            // { startPoint - 1, startPoint     } -> column     && row - 1
    TopRight,       // { startPoint - 1, startPoint + 1 } -> column + 1 && row - 1
    Right,          // { startPoint,     startPoint + 1 } -> column + 1 && row
    BottomRight,    // { startPoint + 1, startPoint + 1 } -> column + 1 && row + 1
    Bottom,         // { startPoint + 1, startPoint     } -> column     && row + 1
    BottomLeft,     // { startPoint + 1, startPoint - 1 } -> column - 1 && row + 1
    Left            // { startPoint ,    startPoint - 1 } -> column - 1 && row
};

typedef QPoint Move;            // x == row && y == column
typedef QList<Move> Moves;
typedef QHash<MoveDirection, Moves> AvailableMoves;
typedef QPair<BasicPiece *, Move> FightPair;
typedef QList<FightPair> FightMoves;

#define INVALID_GEOMETRY QRect(-1, -1, 0, 0)
#define INVALID_POINT QPoint(-1, -1)

#ifdef CHESSCORE_LIB
#   define CHESSCORE_EXPORT Q_DECL_EXPORT
#else
#   define CHESSCORE_EXPORT Q_DECL_IMPORT
#endif

namespace CORE_GLOBAL {

void CHESSCORE_EXPORT unite(AvailableMoves &dest, const AvailableMoves &source);

}

#endif // QMLSURFACE_GLOBAL_H
