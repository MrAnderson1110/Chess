#include "mover.h"
#include "apphistory.h"

#include <BasicBoard>
#include <BasicGridCell>
#include <BasicPiece>

#include <King>
#include <Rook>

#include <QCursor>

Mover::Mover(BasicBoard *board)
    : m_board(board)
    , m_movingPiece(nullptr)
{

}

Mover::~Mover()
{

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
    storePieceToCell(piece, cell);

    bool moved = false;
    King *king = dynamic_cast<King *>(piece);
    if(king != nullptr)
        moved = king->moved();

    State *rookState = checkCastling(piece, prevPoint);
    State *pieceState = new State(piece, prevPoint, Move(piece->rowIndex(), piece->columnIndex()), moved);

    Snapshot *snap = new Snapshot;
    snap->add(pieceState);
    if(rookState != nullptr)
        snap->add(rookState);

    appHistory->push(snap);

    m_movingPiece = nullptr;
}

void Mover::reset()
{
    Snapshot *snap = appHistory->pop();
    State *state = dynamic_cast<State *>(snap->next());
    while(state != nullptr) {
        BasicPiece *initiator = state->owner();
        if(state->from() != state->to()) {
            BasicGridCell *initiatorCell = m_board->cell(state->from().x(), state->from().y());
            storePieceToCell(initiator, initiatorCell);
        }


        King *king = dynamic_cast<King *>(initiator);
        if(king != nullptr)
            king->setMoved(state->moved());

        Rook *rook = dynamic_cast<Rook *>(initiator);
        if(rook != nullptr)
            rook->setMoved(state->moved());

        state = dynamic_cast<State *>(snap->next());
    }

    delete state;
    // После удаления state все его внутренние состояния фигур удалятся вместе с ним
}

State *Mover::checkCastling(BasicPiece *piece, const Move &prevPoint)
{
    Rook *rook = dynamic_cast<Rook *>(piece);
    if(rook != nullptr)
        rook->setMoved(true);

    State *rookState = nullptr;
    King *king = dynamic_cast<King *>(piece);
    // Слишком много конструкций if-else плохо, но пока что так
    if(king != nullptr && !king->moved()) {
        bool leftCastling = king->columnIndex() + 2 == prevPoint.y();
        bool rightCstrling = king->columnIndex() - 2 == prevPoint.y();
        if(leftCastling || rightCstrling) {
            Rook *leftRook = nullptr;
            Rook *rightRook = nullptr;
            QList<BasicPiece *> pieces = m_board->pieces();
            for(BasicPiece *piece : pieces) {
                Rook *rook = dynamic_cast<Rook *>(piece);
                if(!rook || rook->command() != king->command())
                    continue;

                if(!rook->moved()) {
                    if(rook->columnIndex() == 0)
                        leftRook = rook;
                    else if(rook->columnIndex() == 7)
                        rightRook = rook;
                    Q_ASSERT(rook->columnIndex() == 0 || rook->columnIndex() == 7);
                }
            }

            if(leftCastling && leftRook != nullptr) {
                Move prevPoint(leftRook->rowIndex(), leftRook->columnIndex());
                BasicGridCell *rookCell = m_board->cell(leftRook->rowIndex(), king->columnIndex() + 1);
                storePieceToCell(leftRook, rookCell);
                leftRook->setMoved(true);
                rookState = new State(leftRook, prevPoint, Move(leftRook->rowIndex(), leftRook->columnIndex()), false);
            }
            else if(rightCstrling && rightRook != nullptr) {
                Move prevPoint(rightRook->rowIndex(), rightRook->columnIndex());
                BasicGridCell *rookCell = m_board->cell(rightRook->rowIndex(), king->columnIndex() - 1);
                storePieceToCell(rightRook, rookCell);
                rightRook->setMoved(true);
                rookState = new State(rightRook, prevPoint, Move(rightRook->rowIndex(), rightRook->columnIndex()), false);
            }
            else
                Q_ASSERT_X(false,
                           "Mover::finishMove(BasicPiece *)",
                           "nonexistent castling direction");
        }

        king->setMoved(true);
    }

    return rookState;
}

void Mover::storePieceToCell(BasicPiece *piece, BasicGridCell *cell)
{
    Q_ASSERT(piece != nullptr && cell != nullptr);

    m_board->cell(piece->rowIndex(), piece->columnIndex())->setPiece(nullptr);

    piece->setRowIndex(cell->rowIndex());
    piece->setColumnIndex(cell->columnIndex());
    piece->setGeometry(cell->geometry());
    cell->setPiece(piece);
    piece->setParentItem(cell);
}
