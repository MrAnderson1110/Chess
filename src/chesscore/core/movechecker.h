#ifndef MOVECHECKER_H
#define MOVECHECKER_H

#include <QList>

#include "chesscore_global.h"

class BasicBoard;
class BasicPiece;
class MovesVisitor;
class FilterVisitor;
class FightVisitor;
class PostFilterVisitor;

class CHESSCORE_EXPORT MoveChecker
{
public:
    explicit MoveChecker(BasicBoard *board);
    ~MoveChecker();

    void updateAvailableMoves(BasicPiece *initiator = nullptr,
                              const Move &sourcePoint = INVALID_POINT);

private:
    BasicBoard *m_board;
    MovesVisitor *m_movesVisitor;
    FilterVisitor *m_filterVisitor;
    FightVisitor *m_fightVisitor;
    PostFilterVisitor *m_postFilterVisitor;
};

#endif // MOVECHECKER_H
