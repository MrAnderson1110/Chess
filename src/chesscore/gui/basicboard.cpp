#include "basicboard.h"
#include "basicgridcell.h"
#include "rook.h"
#include "king.h"

#include "../core/gamemediator.h"

BasicBoard::BasicBoard(QQuickItem *parent)
    : QQuickItem(parent)
    , m_grid()
    , m_pieces()
    , m_inverted(false)
    , m_mediator(new GameMediator(this))
{

}

BasicBoard::~BasicBoard()
{
    delete m_mediator;
}

void BasicBoard::componentComplete()
{
    QList<QQuickItem *> children = childItems();
    bool hasUncheckedChildren = true;
    while(hasUncheckedChildren) {
        QList<QQuickItem *> newChildren;
        for(QQuickItem *child : qAsConst(children)) {
            if(!child)
                continue;

            BasicGridCell *cell = qobject_cast<BasicGridCell *>(child);
            BasicPiece *piece = qobject_cast<BasicPiece *>(child);

            if(cell != nullptr && m_grid[cell->rowIndex()][cell->columnIndex()] == nullptr) {
                m_grid[cell->rowIndex()][cell->columnIndex()] = cell;
                continue;
            }
            else if(piece != nullptr) {
                m_pieces.append(piece);
                continue;
            }
            else
                newChildren.append(child->childItems());
        }
        if(children.isEmpty())
            hasUncheckedChildren = false;

        children = newChildren;
    }

    for(BasicPiece *piece : qAsConst(m_pieces)) {
        if(!piece)
            continue;

        King *king = dynamic_cast<King *>(piece);
        if(king != nullptr)
            king->setMoved(false);

        Rook *rook = dynamic_cast<Rook *>(piece);
        if(rook != nullptr)
            rook->setMoved(false);

        piece->setBoard(this);
        BasicGridCell *cell = m_grid[piece->rowIndex()][piece->columnIndex()];
        cell->setPiece(piece);
    }

    Q_ASSERT_X(m_pieces.size() == 32,
               "BasicBoard::componentComplete()",
               "BasicBoard initialized " + QString::number(m_pieces.size()).toLatin1() + " pieces");

    m_mediator->initialize();
    QQuickItem::componentComplete();
}

BasicGridCell *BasicBoard::cell(int rowIndex, int columnIndex)
{
    if(m_grid.size() <= rowIndex)
        return nullptr;

    const QHash<int, BasicGridCell *> &column = m_grid.value(rowIndex);

    if(rowIndex < 0 || columnIndex < 0 || column.size() == 0
            || rowIndex >= 8 || columnIndex >= 8)
        return nullptr;

    Q_ASSERT(column.value(columnIndex) != nullptr);

    return column.value(columnIndex);
}

BasicGridCell *BasicBoard::cellUnderMouse(const QPointF &mouse)
{
    for(const QHash<int, BasicGridCell *> &celles : qAsConst(m_grid)) {
        for(BasicGridCell *cell : celles) {
            if(cell->geometry().contains(mouse))
                return cell;
        }
    }

    return nullptr;
}

GameMediator *BasicBoard::observer() const
{
    return m_mediator;
}

void BasicBoard::clearSelection()
{
    m_mediator->clearSelection();
}

const QList<BasicPiece *> &BasicBoard::pieces() const
{
    return m_pieces;
}

void BasicBoard::erasePiece(BasicPiece *piece)
{
    m_pieces.removeOne(piece);
}

void BasicBoard::insertPiece(BasicPiece *piece)
{
    m_pieces.append(piece);
}

bool BasicBoard::inverted() const
{
    return m_inverted;
}

void BasicBoard::setInverted(bool newInverted)
{
    if (m_inverted == newInverted)
        return;

    m_inverted = newInverted;
    emit invertedChanged(m_inverted);
}
