#include "basicgridcell.h"
#include "basicpiece.h"

BasicGridCell::BasicGridCell(QQuickItem *parent)
    : GraphicItem(parent)
    , m_piece(nullptr)
    , m_selected(false)
    , m_hovered(false)
    , m_underFire(false)
{

}

BasicPiece *BasicGridCell::piece() const
{
    return m_piece;
}

void BasicGridCell::polishContent()
{
    if(m_piece) {
        Q_ASSERT(m_piece->parentItem() == this);
        m_piece->setX(0);
        m_piece->setY(0);
        m_piece->setWidth(width());
        m_piece->setHeight(height());
    }

    GraphicItem::polishContent();
}

void BasicGridCell::setPiece(BasicPiece *newPiece)
{
    if (m_piece == newPiece)
        return;

    m_piece = newPiece;

    if(newPiece)
        newPiece->setParentItem(this);

    polishContent();

    emit pieceChanged(m_piece);
}

bool BasicGridCell::selected() const
{
    return m_selected;
}

void BasicGridCell::setSelected(bool newSelected)
{
    if (m_selected == newSelected)
        return;

    m_selected = newSelected;
    emit selectedChanged(m_selected);
}

bool BasicGridCell::hovered() const
{
    return m_hovered;
}

void BasicGridCell::setHovered(bool newHovered)
{
    if (m_hovered == newHovered)
        return;

    m_hovered = newHovered;
    emit hoveredChanged(m_hovered);
}

bool BasicGridCell::underFire() const
{
    return m_underFire;
}

void BasicGridCell::setUnderFire(bool newUnderFire)
{
    if (m_underFire == newUnderFire)
        return;

    m_underFire = newUnderFire;
    emit underFireChanged(m_underFire);
}
