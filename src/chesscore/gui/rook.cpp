#include "rook.h"

Rook::Rook(QQuickItem *parent)
    : BasicPiece(parent)
    , m_moved(false)
{
    setType(BasicPiece::Rook);
}

Rook::~Rook()
{

}

bool Rook::moved() const
{
    return m_moved;
}

void Rook::setMoved(bool newMoved)
{
    if(m_moved == newMoved)
        return;

    m_moved = newMoved;
    emit movedChanged(m_moved);
}
