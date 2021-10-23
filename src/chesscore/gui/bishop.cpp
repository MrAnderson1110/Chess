#include "bishop.h"

Bishop::Bishop(QQuickItem *parent)
    : BasicPiece(parent)
{
    setType(BasicPiece::Bishop);
}

Bishop::~Bishop()
{

}
