#ifndef MOVER_H
#define MOVER_H

#include <QRectF>

#include "chesscore_global.h"

class BasicGridCell;
class BasicPiece;
class BasicBoard;
class State;

class CHESSCORE_EXPORT Mover
{
public:
    explicit Mover(BasicBoard *board);
    ~Mover();

    void startMove(BasicPiece *piece);
    void move(BasicPiece *piece, const QRectF &geometry);
    void finishMove(BasicPiece *piece);
    void reset();

private:
    State *checkCastling(BasicPiece *piece, const Move &prevPoint);
    void storePieceToCell(BasicPiece *piece, BasicGridCell *cell);

private:
    BasicBoard *m_board;
    BasicPiece *m_movingPiece;
};

#endif // MOVER_H
