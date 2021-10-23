#include "king.h"

King::King(QQuickItem *parent)
    : BasicPiece(parent)
    , m_moved(false)
{
    setType(BasicPiece::King);    
}

King::~King()
{

}

bool King::moved() const
{
    return m_moved;
}

void King::setMoved(bool newMoved)
{
    if (m_moved == newMoved)
        return;

    m_moved = newMoved;
    emit movedChanged(m_moved);
}
