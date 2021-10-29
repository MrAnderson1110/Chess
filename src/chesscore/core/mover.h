#ifndef MOVER_H
#define MOVER_H

#include <QRectF>

#include "chesscore_global.h"

class BasicPiece;
class BasicBoard;
class MoveHelper;

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
    BasicBoard *m_board;
    BasicPiece *m_movingPiece;
    MoveHelper *m_helper;
};

#endif // MOVER_H
