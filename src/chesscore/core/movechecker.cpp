#include "movechecker.h"
#include "appstate.h"

#include <BasicPiece>
#include <BasicBoard>
#include <BasicGridCell>
#include <King>

#include "private/movevisitor.h"
#include "private/filtervisitor.h"
#include "private/postfiltervisitor.h"
#include "private/fightvisitor.h"

MoveChecker::MoveChecker(BasicBoard *board)
    : m_board(board)
    , m_movesVisitor(new MovesVisitor)
    , m_filterVisitor(new FilterVisitor)
    , m_fightVisitor(new FightVisitor)
    , m_postFilterVisitor(new PostFilterVisitor)
{

}

MoveChecker::~MoveChecker()
{
    delete m_movesVisitor;
    delete m_filterVisitor;
}

void MoveChecker::updateAvailableMoves(BasicPiece *initiator, const Move &sourcePoint)
{
    QList<BasicPiece *> pieces = m_board->pieces();
    for(BasicPiece *piece : pieces) {
        piece->accept(m_movesVisitor);
        piece->accept(m_filterVisitor);
    }
    m_fightVisitor->reset(initiator, sourcePoint);
    // Далее есть зависимость от availableMoves и predictedMoves, поэтому проходим еще один цикл
    for(BasicPiece *piece : pieces) {
        piece->accept(m_postFilterVisitor);
        piece->accept(m_fightVisitor);
    }
}
