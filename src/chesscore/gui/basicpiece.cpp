#include "basicpiece.h"
#include "basicgridcell.h"
#include "basicboard.h"

#include "../core/gamemediator.h"

BasicPiece::BasicPiece(QQuickItem *parent)
    : GraphicItem(parent)
    , m_board(nullptr)
    , m_command(Black)
    , m_type(Pawn)
    , m_fightMoves()
    , m_availableMoves()
    , m_movable(true)
{

}

BasicPiece::Command BasicPiece::command() const
{
    return m_command;
}

void BasicPiece::setCommand(Command newCommand)
{
    if (m_command == newCommand)
        return;

    m_command = newCommand;
    emit commandChanged(m_command);
}

BasicPiece::Type BasicPiece::type() const
{
    return m_type;
}

void BasicPiece::setType(Type newType)
{
    if (m_type == newType)
        return;

    m_type = newType;
    emit typeChanged(m_type);
}

void BasicPiece::setFightMoves(const FightMoves &moves)
{
    m_fightMoves = moves;
}

void BasicPiece::addFigntMove(const FightPair &move)
{
    if(m_fightMoves.contains(move))
        return;

    m_fightMoves << move;
}

void BasicPiece::removeFightMove(const Move &move)
{
    FightPair moveForRemote = { nullptr, INVALID_POINT };
    for(const FightPair &fightMove : qAsConst(m_fightMoves))
        if(fightMove.second == move) {
            moveForRemote = fightMove;
            break;
        }

    m_fightMoves.removeOne(moveForRemote);
}

void BasicPiece::removeFightMove(BasicPiece *initiator)
{
    FightPair moveForRemote = { nullptr, INVALID_POINT };
    for(const FightPair &fightMove : qAsConst(m_fightMoves))
        if(fightMove.first == initiator) {
            moveForRemote = fightMove;
            break;
        }

    m_fightMoves.removeOne(moveForRemote);
}

void BasicPiece::removeFightMove(const FightPair &move)
{
    m_fightMoves.removeOne(move);
}

bool BasicPiece::fightMovesContains(const Move &move)
{
    for(const FightPair &fightMove : qAsConst(m_fightMoves))
        if(fightMove.second == move)
            return true;

    return false;
}

bool BasicPiece::fightMovesContains(BasicPiece *piece)
{
    for(const FightPair &fightMove : qAsConst(m_fightMoves))
        if(fightMove.first == piece)
            return true;

    return false;
}

void BasicPiece::setAvailableMoves(const AvailableMoves &moves)
{
    m_availableMoves = moves;
}

void BasicPiece::removeAvailableMove(const Move &move)
{
    for(Moves &moves : m_availableMoves)
        moves.removeOne(move);
}

void BasicPiece::addAvailableMove(const Move &move, MoveDirection dir)
{
    if(m_availableMoves.value(dir).contains(move))
        return;

    m_availableMoves[dir] << move;
}

bool BasicPiece::availableMovesContains(const Move &move)
{
    for(const Moves &moves : qAsConst(m_availableMoves))
        if(moves.contains(move))
            return true;

    return false;
}

const Moves &BasicPiece::predictedMoves() const
{
    return m_predictedMoves;
}

void BasicPiece::setPredictedMoves(const Moves &moves)
{
    m_predictedMoves = moves;
}

bool BasicPiece::predictedMovesContains(const Move &move)
{
    return m_predictedMoves.contains(move);
}

BasicBoard *BasicPiece::board() const
{
    return m_board;
}

const FightMoves &BasicPiece::fightMoves() const
{
    return m_fightMoves;
}

const AvailableMoves &BasicPiece::availableMoves() const
{
    return m_availableMoves;
}

void BasicPiece::setBoard(BasicBoard *board)
{
    m_board = board;
}

void BasicPiece::startMove()
{
    m_board->observer()->startMove(this);
}

void BasicPiece::move(const QRectF &geometry)
{
    m_board->observer()->move(this, geometry);
}

void BasicPiece::finishMove()
{
    m_board->observer()->finishMove(this);
}

bool BasicPiece::movable() const
{
    return m_movable;
}

void BasicPiece::setMovable(bool newMovable)
{
    if (m_movable == newMovable)
        return;

    m_movable = newMovable;
    emit movableChanged(m_movable);
}
