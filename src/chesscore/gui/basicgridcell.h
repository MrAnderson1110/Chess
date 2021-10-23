#ifndef BASICGRIDCELL_H
#define BASICGRIDCELL_H

#include "graphicitem.h"

/*!
 *  Базовый компонент клетки шахматной доски
 *
 *  Содержит описание клетки:
 *      координаты,
 *      фигура, находящяяся в данной клетке
 *  Содержит методы доступа к фигуре в данной клетке
 */

class BasicPiece;

class CHESSCORE_EXPORT BasicGridCell : public GraphicItem
{
    Q_OBJECT
    Q_PROPERTY(BasicPiece *piece READ piece WRITE setPiece NOTIFY pieceChanged)
    Q_PROPERTY(bool selected READ selected NOTIFY selectedChanged)
    Q_PROPERTY(bool hovered READ hovered WRITE setHovered NOTIFY hoveredChanged)
    Q_PROPERTY(bool underFire READ underFire WRITE setUnderFire NOTIFY underFireChanged)

public:
    MAKE_VISITABLE(base_exept_func<BasicGridCell>)

    explicit BasicGridCell(QQuickItem *parent = nullptr);

    virtual void polishContent() override;

    BasicPiece *piece() const;
    bool hovered() const;
    bool selected() const;
    bool underFire() const;

    void setHovered(bool newHovered);
    void setPiece(BasicPiece *newPiece);
    void setSelected(bool newSelected);
    void setUnderFire(bool newUnderFire);

signals:
    void pieceChanged(BasicPiece *);
    void selectedChanged(bool);
    void hoveredChanged(bool);
    void underFireChanged(bool);

private:
    BasicPiece *m_piece;
    bool m_selected;
    bool m_hovered;
    bool m_underFire;
};

#endif // BASICGRIDCELL_H
