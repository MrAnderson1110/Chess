#include "movevisitor.h"

#include <BasicBoard>
#include <King>
#include <Queen>
#include <Bishop>
#include <Knight>
#include <Rook>
#include <Pawn>

MovesVisitor::MovesVisitor()
    : BaseVisitor()
    , Visitor<King>()
    , Visitor<Queen>()
    , Visitor<Bishop>()
    , Visitor<Knight>()
    , Visitor<Rook>()
    , Visitor<Pawn>()
{

}

void MovesVisitor::visit(King *king)
{
    AvailableMoves availableMoves;
    int row = king->rowIndex();
    int column = king->columnIndex();

    Q_ASSERT(!(row < 0 || row >= 8 || column < 0 || column >= 8));

    // Top left
    int tempRow = row - 1;
    int tempCol = column - 1;
    if(tempRow < 8 && tempRow >= 0)
        availableMoves[TopLeft] << Move(tempRow, tempCol);

    // Top
    tempRow = row - 1;
    tempCol = column;
    if(tempRow < 8 && tempRow >= 0)
        availableMoves[Top] << Move(tempRow, tempCol);

    // Top right
    tempRow = row - 1;
    tempCol = column + 1;
    if(tempRow < 8 && tempRow >= 0)
        availableMoves[TopRight] << Move(tempRow, tempCol);

    // Right
    tempRow = row;
    tempCol = column + 1;
    if(tempRow < 8 && tempRow >= 0)
        availableMoves[Right] << Move(tempRow, tempCol);

    // Bottom right
    tempRow = row + 1;
    tempCol = column + 1;
    if(tempRow < 8 && tempRow >= 0)
        availableMoves[BottomRight] << Move(tempRow, tempCol);

    // Bottom
    tempRow = row + 1;
    tempCol = column;
    if(tempRow < 8 && tempRow >= 0)
        availableMoves[Bottom] << Move(tempRow, tempCol);

    // Bottom Left
    tempRow = row + 1;
    tempCol = column - 1;
    if(tempRow < 8 && tempRow >= 0)
        availableMoves[BottomLeft] << Move(tempRow, tempCol);

    // Left
    tempRow = row;
    tempCol = column - 1;
    if(tempRow < 8 && tempRow >= 0)
        availableMoves[Left] << Move(tempRow, tempCol);

    king->setAvailableMoves(availableMoves);

    if(king->moved())
        return;

    bool leftRookMoved = true;
    bool rightRookMoved = true;
    QList<BasicPiece *> pieces = king->board()->pieces();
    for(BasicPiece *piece : pieces) {
        Rook *rook = dynamic_cast<Rook *>(piece);
        if(!rook || rook->command() != king->command())
            continue;

        if(!rook->moved()) {
            if(rook->columnIndex() == 0)
                leftRookMoved = false;
            else if(rook->columnIndex() == 7)
                rightRookMoved = false;
            Q_ASSERT(rook->columnIndex() == 0 || rook->columnIndex() == 7);
        }
    }

    // Left castling
    tempRow = row;
    tempCol = column - 2;
    if(tempRow < 8 && tempRow >= 0 && !leftRookMoved)
        king->addAvailableMove(Move(tempRow, tempCol), Left);

    // Right castling
    tempRow = row;
    tempCol = column + 2;
    if(tempRow < 8 && tempRow >= 0  && !rightRookMoved)
        king->addAvailableMove(Move(tempRow, tempCol), Right);
}

void MovesVisitor::visit(Queen *queen)
{
    AvailableMoves availableMoves;
    int row = queen->rowIndex();
    int column = queen->columnIndex();

    Q_ASSERT(!(row < 0 || row >= 8 || column < 0 || column >= 8));

    {
        Rook *fakeRook = new Rook;
        fakeRook->setRowIndex(queen->rowIndex());
        fakeRook->setColumnIndex(queen->columnIndex());
        fakeRook->accept(this);
        CORE_GLOBAL::unite(availableMoves, fakeRook->availableMoves());
        availableMoves.unite(fakeRook->availableMoves());
        delete fakeRook;
    }

    {
        Bishop *fakeBishop = new Bishop;
        fakeBishop->setRowIndex(queen->rowIndex());
        fakeBishop->setColumnIndex(queen->columnIndex());
        fakeBishop->accept(this);
        CORE_GLOBAL::unite(availableMoves, fakeBishop->availableMoves());
        delete fakeBishop;
    }

    queen->setAvailableMoves(availableMoves);
}

void MovesVisitor::visit(Bishop *bishop)
{
    AvailableMoves availableMoves;
    int row = bishop->rowIndex();
    int column = bishop->columnIndex();

    Q_ASSERT(row >= 0 && row < 8 && column >= 0 && column < 8);

    // По диагонали в верхний правый угол
    for(int r = row - 1, c = column + 1; r >= 0 && c < 8; --r, ++c)
        availableMoves[TopRight] << Move(r, c);

    // По диагонали в нижний правый угол
    for(int r = row + 1, c = column + 1; r < 8 && c < 8; ++r, ++c)
        availableMoves[BottomRight] << Move(r, c);

    // По диагонали в нижний лувый угол
    for(int r = row + 1, c = column - 1; r < 8 && c >= 0; ++r, --c)
        availableMoves[BottomLeft] << Move(r, c);

    // По диагонали в верхний левый угол
    for(int r = row - 1, c = column - 1; r >= 0 && c >= 0; --r, --c)
        availableMoves[TopLeft] << Move(r, c);

    bishop->setAvailableMoves(availableMoves);
}

void MovesVisitor::visit(Knight *knight)
{
    AvailableMoves availableMoves;
    int row = knight->rowIndex();
    int column = knight->columnIndex();

    Q_ASSERT(!(row < 0 || row >= 8 || column < 0 || column >= 8));

    // Левый верхний угол
    int tempRow = row - 1;
    int tempCol = column - 2;
    if(tempRow >= 0 && tempCol >= 0)
        availableMoves[Unspecified] << Move(tempRow, tempCol);

    tempRow = row - 2;
    tempCol = column - 1;
    if(tempRow >= 0 && tempCol >= 0)
        availableMoves[Unspecified] << Move(tempRow, tempCol);

    // Правый верхний угол
    tempRow = row - 1;
    tempCol = column + 2;
    if(tempRow >= 0 && tempCol < 8)
        availableMoves[Unspecified] << Move(tempRow, tempCol);

    tempRow = row - 2;
    tempCol = column + 1;
    if(tempRow >= 0 && tempCol < 8)
        availableMoves[Unspecified] << Move(tempRow, tempCol);

    // Правый нижний угол
    tempRow = row + 1;
    tempCol = column + 2;
    if(tempRow < 8 && tempCol < 8)
        availableMoves[Unspecified] << Move(tempRow, tempCol);

    tempRow = row + 2;
    tempCol = column + 1;
    if(tempRow < 8 && tempCol < 8)
        availableMoves[Unspecified] << Move(tempRow, tempCol);

    // Левый нижний угол
    tempRow = row + 1;
    tempCol = column - 2;
    if(tempRow < 8 && tempCol >= 0)
        availableMoves[Unspecified] << Move(tempRow, tempCol);

    tempRow = row + 2;
    tempCol = column - 1;
    if(tempRow < 8 && tempCol >= 0)
        availableMoves[Unspecified] << Move(tempRow, tempCol);

    knight->setAvailableMoves(availableMoves);
}

void MovesVisitor::visit(Rook *rook)
{
    AvailableMoves availableMoves;
    int row = rook->rowIndex();
    int column = rook->columnIndex();

    Q_ASSERT(row >= 0 && row < 8 && column >= 0 && column < 8);

    {
        // Вниз
        int tempRow = row + 1;
        while(tempRow < 8)
            availableMoves[Bottom] << Move(tempRow++, column);

        // Вверх
        tempRow = row - 1;
        while(tempRow >= 0)
            availableMoves[Top] << Move(tempRow--, column);
    }
    {
        // Вправо
        int tempCol = column + 1;
        while(tempCol < 8)
            availableMoves[Right] << Move(row, tempCol++);

        // Влево
        tempCol = column - 1;
        while(tempCol >= 0)
            availableMoves[Left] << Move(row, tempCol--);
    }

    rook->setAvailableMoves(availableMoves);
}

void MovesVisitor::visit(Pawn *pawn)
{
    AvailableMoves availableMoves;
    int row = pawn->rowIndex();
    int column = pawn->columnIndex();

    Q_ASSERT(row >= 0 && row < 8 && column >= 0 && column < 8);

    int direction = pawn->command();
    if(pawn->board()->inverted())
        direction *= -1;

    Moves moves;
    int tempRow = row + direction;
    auto atEndFunc = [&](int row) { return direction < 0 ? row < 0 : row >= 8; };
    while(!atEndFunc(tempRow)) {
        moves << Move(tempRow, column);
        tempRow += direction;
    }

    MoveDirection currentDirection = direction > 0 ? Bottom : Top;
    availableMoves[currentDirection] << moves;
    pawn->setAvailableMoves(availableMoves);
}
