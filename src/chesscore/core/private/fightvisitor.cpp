#include "fightvisitor.h"

#include "../appstate.h"

#include <BasicPiece>
#include <BasicBoard>
#include <BasicGridCell>

#include <Pawn>
#include <King>

FightVisitor::FightVisitor()
    : BaseVisitor()
    , Visitor<Pawn>()
    , Visitor<BasicPiece>()
{

}

void FightVisitor::reset(BasicPiece *initiator, const Move &prevInitiatorPoint)
{
    m_initiator = initiator;
    m_prevInitiatorPoint = prevInitiatorPoint;
    appState->resetChecks();
}

void FightVisitor::visit(BasicPiece *base)
{
    FightMoves fightMoves;
    for(const Moves &moves : base->availableMoves()) {
        for(const Move &move : moves) {
            const QList<BasicPiece *> pieces = base->board()->pieces();
            for(BasicPiece *piece : pieces) {
                if(piece != base && piece->command() != base->command()
                        && move == Move(piece->rowIndex(), piece->columnIndex())) {
                    fightMoves << FightPair(piece, move);
                    checkKings(piece);
                }
            }
        }
    }

    base->setFightMoves(fightMoves);
}

void FightVisitor::visit(Pawn *pawn)
{
    int direction = pawn->command();
    int nextRow = pawn->rowIndex() + direction;
    if(nextRow < 0 || nextRow >= 8)
        return;

    pawn->setFightMoves(FightMoves());
    BasicBoard *board = pawn->board();

    // Левый противник
    int leftCol = pawn->columnIndex() - 1;
    if(leftCol >= 0) {
        BasicPiece *leftenemy = board->cell(nextRow, leftCol)->piece();
        if(leftenemy != nullptr && leftenemy->command() != pawn->command()) {
            Move move(nextRow, leftCol);
            pawn->addAvailableMove(move, Unspecified);
            pawn->addFigntMove(FightPair(leftenemy, move));
            checkKings(leftenemy);
        }
    }

    // Правый противник
    int rightCol = pawn->columnIndex() + 1;
    if(rightCol < 8) {
        BasicPiece *rightenemy = board->cell(nextRow, rightCol)->piece();
        if(rightenemy != nullptr && rightenemy->command() != pawn->command()) {
            Move move(nextRow, rightCol);
            pawn->addAvailableMove(move, Unspecified);
            pawn->addFigntMove(FightPair(rightenemy, move));
            checkKings(rightenemy);
        }
    }

    // Проверка на проход через битое поле
    if(m_initiator != nullptr
            && m_prevInitiatorPoint != INVALID_POINT
            && m_initiator != pawn
            && m_initiator->command() != pawn->command()
            && m_initiator->type() == BasicPiece::Pawn
            && m_initiator->rowIndex() + direction * 2 == m_prevInitiatorPoint.x()
            && pawn->rowIndex() == m_initiator->rowIndex()
            && (m_initiator->columnIndex() == leftCol
                || m_initiator->columnIndex() == rightCol)) {
        Move move(m_prevInitiatorPoint.x() - direction, m_prevInitiatorPoint.y());
        pawn->addAvailableMove(move, Unspecified);
        pawn->addFigntMove(FightPair(m_initiator, move));
    }
}

void FightVisitor::checkKings(BasicPiece *underFight)
{
    King *king = dynamic_cast<King *>(underFight);
    if(!king)
        return;

    switch (king->command()) {
    case BasicPiece::White:
        appState->setCheckToWhite(true);
    case BasicPiece::Black:
        appState->setCheckToBlack(true);
    }
}

