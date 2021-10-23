#include "graphicitem.h"

GraphicItem::GraphicItem(QQuickItem *parent)
    : QQuickItem(parent)
    , m_background(nullptr)
    , m_rowIndex(-1)
    , m_columnIndex(-1)
{

}

QQuickItem *GraphicItem::background() const
{
    return m_background;
}

void GraphicItem::polishContent()
{
    if(m_background) {
        Q_ASSERT(m_background->parentItem() == this);
        m_background->setX(0);
        m_background->setY(0);
        m_background->setWidth(width());
        m_background->setHeight(height());
    }
}

void GraphicItem::setBackground(QQuickItem *newBackground)
{
    if (m_background == newBackground)
        return;

    if(m_background != nullptr)
        delete m_background;

    m_background = newBackground;
    m_background->setParentItem(this);
    polishContent();

    emit backgroundChanged(m_background);
}

void GraphicItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    polishContent();
}

int GraphicItem::rowIndex() const
{
    return m_rowIndex;
}

QRectF GraphicItem::geometry() const
{
    return QRectF(x(), y(), width(), height());
}

void GraphicItem::setGeometry(const QRectF &geometry)
{
    setX(geometry.x());
    setY(geometry.y());
    setWidth(geometry.width());
    setHeight(geometry.height());

    polishContent();
}

void GraphicItem::setRowIndex(int newRowIndex)
{
    if (m_rowIndex == newRowIndex)
        return;

    m_rowIndex = newRowIndex;
    polishContent();
    emit rowIndexChanged(m_rowIndex);
}

int GraphicItem::columnIndex() const
{
    return m_columnIndex;
}

void GraphicItem::setColumnIndex(int newColumnIndex)
{
    if (m_columnIndex == newColumnIndex)
        return;

    m_columnIndex = newColumnIndex;
    polishContent();
    emit columnIndexChanged(m_columnIndex);
}
