#include "movehelper.h"

#include "../apphistory.h"

#include <BasicPiece>
#include <BasicBoard>
#include <BasicGridCell>

#include <King>
#include <Rook>

MoveHelper::MoveHelper(BasicBoard *board)
    : m_board(board)
    , m_pieces()
{

}

MoveHelper::~MoveHelper()
{
    qDeleteAll(m_pieces);
}

BasicPiece *MoveHelper::fight(BasicPiece *initiator, BasicGridCell *fighted)
{
    if(!fighted->piece())
        return nullptr;

    if(fighted->piece()->type() == BasicPiece::King)
        return nullptr;

    Move fightedMove(fighted->rowIndex(), fighted->columnIndex());
    if(!initiator->fightMovesContains(fightedMove))
        return nullptr;

    BasicPiece *fightPiece = initiator->getFightPair(fightedMove).first;
    m_pieces.append(fightPiece);
    m_board->erasePiece(fightPiece);
    fightPiece->setVisible(false);
    fightPiece->setRowIndex(-1);
    fightPiece->setColumnIndex(-1);
    BasicGridCell *cell = m_board->cell(fightedMove.x(), fightedMove.y());
    cell->setPiece(nullptr);

    return fightPiece;
}

void MoveHelper::checkCastling(BasicPiece *initiator, const Move &prevPoint)
{
    Q_ASSERT(initiator != nullptr);

    if(appHistory->size() == 0)
        return;

    Snapshot *snap = appHistory->pop();

    Q_ASSERT(snap->states().size() == 1);


    State *rookState = castling(initiator, prevPoint);
    if(rookState != nullptr)
        snap->add(rookState);

    appHistory->push(snap);
}

void MoveHelper::storePieceToCell(BasicPiece *piece, BasicGridCell *cell, bool addHistory)
{
    Q_ASSERT(piece != nullptr && cell != nullptr);

    BasicPiece *fighted = fight(piece, cell);

    if(addHistory) {
        Snapshot *snap = new Snapshot;
        Move from(piece->rowIndex(), piece->columnIndex());
        Move to(cell->rowIndex(), cell->columnIndex());
        bool moved = false;
        King *king = dynamic_cast<King *>(piece);
        if(king != nullptr) {
            moved = king->moved();
            king->setMoved(true);
        }
        Rook *rook = dynamic_cast<Rook *>(piece);
        if(rook != nullptr) {
            moved = rook->moved();
            rook->setMoved(true);
        }
        snap->add(new State(piece, from, to, moved, fighted));
        appHistory->push(snap);
    }

    if(cell->piece() != nullptr
            && cell->piece()->type() == BasicPiece::King
            && piece != cell->piece()) {
        resetMove();
        return;
    }

    m_board->cell(piece->rowIndex(), piece->columnIndex())->setPiece(nullptr);

    piece->setRowIndex(cell->rowIndex());
    piece->setColumnIndex(cell->columnIndex());
    piece->setGeometry(cell->geometry());
    cell->setPiece(piece);
    piece->setParentItem(cell);
}

void MoveHelper::resetMove()
{
    Snapshot *snap = appHistory->pop();
    State *state = dynamic_cast<State *>(snap->next());
    while(state != nullptr) {
        BasicPiece *initiator = state->owner();
        if(state->from() != state->to()) {
            BasicGridCell *initiatorCell = m_board->cell(state->from().x(), state->from().y());
            storePieceToCell(initiator, initiatorCell, false);
        }

        resetFight(state->defeated(), state->to());

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

void MoveHelper::resetFight(BasicPiece *defeated, const Move &prevMove)
{
    if(!defeated)
        return;

    defeated->setRowIndex(prevMove.x());
    defeated->setColumnIndex(prevMove.y());
    BasicGridCell *cell = m_board->cell(prevMove.x(), prevMove.y());
    cell->setPiece(defeated);

    m_pieces.removeOne(defeated);
    m_board->insertPiece(defeated);
    defeated->setVisible(true);
}

State *MoveHelper::castling(BasicPiece *piece, const Move &prevPoint)
{
    // Todo нельзя делать рокировку через битый ход!
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
                storePieceToCell(leftRook, rookCell, false);
                leftRook->setMoved(true);
                rookState = new State(leftRook, prevPoint, Move(leftRook->rowIndex(), leftRook->columnIndex()), false);
            }
            else if(rightCstrling && rightRook != nullptr) {
                Move prevPoint(rightRook->rowIndex(), rightRook->columnIndex());
                BasicGridCell *rookCell = m_board->cell(rightRook->rowIndex(), king->columnIndex() - 1);
                storePieceToCell(rightRook, rookCell, false);
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
