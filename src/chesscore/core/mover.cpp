#include "mover.h"

#include "private/movehelper.h"

#include <BasicBoard>
#include <BasicGridCell>
#include <BasicPiece>

#include <QCursor>

Mover::Mover(BasicBoard *board)
    : m_board(board)
    , m_movingPiece(nullptr)
    , m_helper(new MoveHelper(board))
{

}

Mover::~Mover()
{
    delete m_helper;
}

void Mover::startMove(BasicPiece *piece)
{
    if(piece == m_movingPiece || m_movingPiece != nullptr)
        return;

    QPointF pieceTopLeftCor = m_board->mapFromItem(piece, piece->geometry().topLeft());
    piece->setParentItem(m_board);
    piece->setGeometry(QRectF(pieceTopLeftCor, piece->size()));

    m_movingPiece = piece;
}

void Mover::move(BasicPiece *piece, const QRectF &geometry)
{
    if(m_movingPiece != piece || !geometry.isValid())
        return;

    piece->setGeometry(geometry);
}

void Mover::finishMove(BasicPiece *piece)
{
    if(m_movingPiece != piece)
        return;

    BasicGridCell *cell = m_board->cellUnderMouse(piece->geometry().center());
    if(!cell)
        cell = m_board->cell(piece->rowIndex(), piece->columnIndex());

    Move prevPoint(piece->rowIndex(), piece->columnIndex());
    m_helper->storePieceToCell(piece, cell);
    // NOTE перенесено в MoveHalper::storePieceToCell(...)
//    m_helper->checkCastling(piece, prevPoint);

    m_movingPiece = nullptr;
}

void Mover::reset()
{
    m_helper->resetMove();
}
