#include "queen.h"

Queen::Queen(QQuickItem *parent)
    : BasicPiece(parent)
{
    setType(BasicPiece::Queen);
}

Queen::~Queen()
{

}
