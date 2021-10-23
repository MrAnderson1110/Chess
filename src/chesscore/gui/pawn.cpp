#include "pawn.h"

Pawn::Pawn(QQuickItem *parent)
    : BasicPiece(parent)
{
    setType(BasicPiece::Pawn);
}

Pawn::~Pawn()
{

}
