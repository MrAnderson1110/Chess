#ifndef MOVEHELPER_H
#define MOVEHELPER_H

#include "chesscore_global.h"

class BasicBoard;
class BasicPiece;
class State;
class BasicGridCell;

class MoveHelper
{
public:
    MoveHelper(BasicBoard *board);
    ~MoveHelper();

    void checkCastling(BasicPiece *initiator, const Move &prevPoint);
    void storePieceToCell(BasicPiece *piece, BasicGridCell *cell, bool addHistory = true);
    void resetMove();

private:
    void resetFight(BasicPiece *defeated, const Move &prevMove);
    State *castling(BasicPiece *piece, const Move &prevPoint);
    BasicPiece *fight(BasicPiece *initiator, BasicGridCell *fighted);

private:
    BasicBoard *m_board;
    QList<BasicPiece *> m_pieces;
};

#endif // MOVEHELPER_H
