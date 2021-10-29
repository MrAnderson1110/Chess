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
    , m_whiteHasProtected(true)
    , m_blackHasProtected(true)
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

    checkState();
}

void MoveChecker::checkOnMate()
{
    if(!appState->checkToBlack() && !appState->checkToWhite())
        return;

    QList<BasicPiece *> pieces = m_board->pieces();

    King *whiteKing = nullptr;
    King *blackKing = nullptr;

    for(BasicPiece *piece : pieces) {
        King *king = dynamic_cast<King *>(piece);
        if(!king)
            continue;

        switch (king->command()) {
        case BasicPiece::White:
            whiteKing = king;
            break;
        case BasicPiece::Black:
            blackKing = king;
            break;
        }
    }

    Q_ASSERT(whiteKing != nullptr && blackKing != nullptr);

    if(appState->checkToWhite()) {
        qDebug() << "white:" << m_whiteHasProtected << whiteKing->availableMoves().isEmpty();
        if(!m_whiteHasProtected
                && whiteKing->availableMoves().isEmpty())
            appState->setMateToWhite(true);
    }
    else if(appState->checkToBlack()) {
        qDebug() << "black:" << m_blackHasProtected << blackKing->availableMoves().size();
        if(!m_blackHasProtected
                && blackKing->availableMoves().isEmpty())
            appState->setMateToBlack(true);
    }
}

void MoveChecker::checkState()
{
    QList<BasicPiece *> pieces = m_board->pieces();

    appState->resetChecks();

    for(BasicPiece *piece : pieces)
        piece->setMovable(true);

    King *whiteKing = nullptr;
    King *blackKing = nullptr;

    for(BasicPiece *piece : pieces) {
        King *king = dynamic_cast<King *>(piece);
        if(!king)
            continue;

        switch (king->command()) {
        case BasicPiece::White:
            whiteKing = king;
            break;
        case BasicPiece::Black:
            blackKing = king;
            break;
        }
    }

    Q_ASSERT(whiteKing != nullptr && blackKing != nullptr);

    for(BasicPiece *piece : pieces) {
        if(piece->type() == BasicPiece::King)
            continue;

        if(piece->fightMovesContains(whiteKing)) {
            appState->setCheckToWhite(true);
            m_whiteHasProtected = protectKings(whiteKing, piece);
        }

        if(piece->fightMovesContains(blackKing)) {
            appState->setCheckToBlack(true);
            m_blackHasProtected = protectKings(blackKing, piece);
        }
    }
}

bool MoveChecker::protectKings(BasicPiece *king, BasicPiece *striker)
{
    bool hasProtection = false;
    Move kingMove(king->rowIndex(), king->columnIndex());

    bool canBlockCheck = striker->type() == BasicPiece::Bishop
            || striker->type() == BasicPiece::Queen
            || striker->type() == BasicPiece::Rook;

    QList<BasicPiece *> pieces = m_board->pieces();
    for(BasicPiece *piece : pieces) {
        if(piece->command() != king->command())
            continue;

        if(piece == king)
            continue;

        Moves protectedMoves;
        // Если можно съесть - оставить только этот ход
        if(piece->fightMovesContains(striker))
            protectedMoves.append(Move(striker->rowIndex(), striker->columnIndex()));

        // Если можно заблокировать - оставить только этот ход
        if(canBlockCheck) {
            const AvailableMoves &strikerMoves = striker->availableMoves();
            for(const Moves &moves : strikerMoves) {
                if(!moves.contains(kingMove))
                    continue;

                for(const Move &move : moves) {
                    if(piece->availableMovesContains(move))
                        protectedMoves.append(move);
                }
            }
        }

        if(protectedMoves.isEmpty())
            // Иначе - запретить ход
            piece->setMovable(false);
        else {
            AvailableMoves moves;
            moves[Unspecified] = protectedMoves;
            piece->setAvailableMoves(moves);
            hasProtection = true;
            qDebug() << "has protection" << piece->type();
            FightMoves fightMoves;
            for(const Moves &moves : piece->availableMoves())
                for(const Move &move : moves)
                    if(piece->fightMovesContains(move))
                        fightMoves << piece->getFightPair(move);

            piece->setFightMoves(fightMoves);

        }
    }

    return hasProtection;
}
