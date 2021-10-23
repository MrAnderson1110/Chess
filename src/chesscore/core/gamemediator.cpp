#include "gamemediator.h"
#include "mover.h"
#include "selector.h"
#include "movechecker.h"
#include "appstate.h"

#include <BasicBoard>

GameMediator::GameMediator(BasicBoard *board)
    : m_board(board)
    , m_mover(new Mover(board))
    , m_selector(new Selector(board))
    , m_moveChecker(new MoveChecker(board))
{

}

GameMediator::~GameMediator()
{
    delete m_moveChecker;
    delete m_selector;
    delete m_mover;
}

void GameMediator::initialize()
{
    m_moveChecker->updateAvailableMoves();
}

void GameMediator::startMove(BasicPiece *piece)
{
    if(!movable(piece))
        return;

    m_selector->updateSelection(piece);
    m_selector->updateHover(piece->geometry());
    m_mover->startMove(piece);
}

void GameMediator::move(BasicPiece *piece, const QRectF &geometry)
{
    if(!movable(piece))
        return;

    m_selector->updateHover(geometry);
    m_mover->move(piece, geometry);
}

void GameMediator::finishMove(BasicPiece *piece)
{
    if(!movable(piece))
        return;

    Move targetPoint = m_selector->hoveredPoint();
    Move sourcePoint(piece->rowIndex(), piece->columnIndex());

    m_mover->finishMove(piece);
    if(!piece->availableMovesContains(targetPoint)
            || targetPoint == sourcePoint) {
        m_mover->reset();
        return;
    }

    clearSelection();
    m_moveChecker->updateAvailableMoves(piece, sourcePoint);
    chooseCommand();
}

void GameMediator::clearSelection()
{
    m_selector->updateSelection(nullptr);
    m_selector->updateHover(INVALID_GEOMETRY);
}

void GameMediator::chooseCommand()
{
    switch (appState->currentCommand()) {
    case BasicPiece::White:
        appState->setCurrentCommand(BasicPiece::Black);
        break;
    case BasicPiece::Black:
        appState->setCurrentCommand(BasicPiece::White);
        break;
    }
}

bool GameMediator::movable(BasicPiece *piece) const
{
    //    if(piece->command() != appState->currentCommand())
    //        return false;

    return true;
}

