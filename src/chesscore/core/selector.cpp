#include "selector.h"

#include <BasicBoard>
#include <BasicPiece>
#include <BasicGridCell>

Selector::Selector(BasicBoard *board)
    : m_board(board)
    , m_hoveredCell(nullptr)
    , m_selectionList()
{

}

void Selector::updateSelection(BasicPiece *initiator)
{
    for(BasicGridCell *cell : qAsConst(m_selectionList)) {
        cell->setSelected(false);
        cell->setUnderFire(false);
    }

    m_selectionList.clear();
    if(!initiator)
        return;

    {
        Move selfPoint(initiator->rowIndex(), initiator->columnIndex());
        BasicGridCell *selfCell = m_board->cell(selfPoint.x(), selfPoint.y());
        selfCell->setSelected(true);
        m_selectionList.append(selfCell);
    }

    for(const Moves &moves : initiator->availableMoves()) {
        for(Move move : qAsConst(moves)) {
            BasicGridCell *cell = m_board->cell(move.x(), move.y());
            m_selectionList.append(cell);
            cell->setSelected(true);
        }
    }

    for(const FightPair &fightMove : initiator->fightMoves()) {
        const Move &move = fightMove.second;
        BasicGridCell *cell = m_board->cell(move.x(), move.y());
        Q_ASSERT(m_selectionList.contains(cell));
        cell->setUnderFire(true);
    }
}

QPoint Selector::hoveredPoint() const
{
    if(!m_hoveredCell)
        return INVALID_POINT;

    return { m_hoveredCell->rowIndex(), m_hoveredCell->columnIndex() };
}

void Selector::updateHover(const QRectF &pieceGeometry)
{
    if(m_hoveredCell != nullptr)
        m_hoveredCell->setHovered(false);

    m_hoveredCell = m_board->cellUnderMouse(pieceGeometry.center());

    if(m_hoveredCell != nullptr && m_selectionList.contains(m_hoveredCell))
        m_hoveredCell->setHovered(true);
}

