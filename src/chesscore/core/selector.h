#ifndef SELECTOR_H
#define SELECTOR_H

#include <QList>

#include "chesscore_global.h"

class BasicBoard;
class BasicPiece;
class BasicGridCell;

struct MoveDesctiption;

class CHESSCORE_EXPORT Selector
{
public:
    explicit Selector(BasicBoard *board);

    void updateHover(const QRectF &pieceGeometry);
    /// piece === nullptr - сбрасывает все выделение
    void updateSelection(BasicPiece *initiator);
    QPoint hoveredPoint() const;

private:
    BasicBoard *m_board;
    BasicGridCell *m_hoveredCell;
    QList<BasicGridCell *> m_selectionList;
};

#endif // SELECTOR_H
