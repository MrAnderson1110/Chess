#ifndef BASICBOARD_H
#define BASICBOARD_H

#include <QQuickItem>

#include "chesscore_global.h"
#include "basicpiece.h"

/*!
 * Базовый компонент шахматной доски
 *
 * Содержит компоненты клеток доски, а также логику распределения клеток по доске.
 * Предоставляет доступ к клеткам доски во внешний мир.
 */

class BasicGridCell;
class BasicPiece;
class GameMediator;

class CHESSCORE_EXPORT BasicBoard : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool inverted READ inverted WRITE setInverted NOTIFY invertedChanged)

public:
    explicit BasicBoard(QQuickItem *parent = nullptr);
    ~BasicBoard();

    virtual void componentComplete() override final;

    BasicGridCell *cell(int rowIndex, int columnIndex);
    BasicGridCell *cellUnderMouse(const QPointF &mouse);
    const QList<BasicPiece *> &pieces() const;

    GameMediator *observer() const;

    // Для возможности снимать выделение нажатием на доску из QML
    Q_INVOKABLE void clearSelection();

    bool inverted() const;
    void setInverted(bool newInverted);

signals:
    void invertedChanged(bool);

private:
    QHash<int, QHash<int, BasicGridCell *>> m_grid;
    QList<BasicPiece *> m_pieces;
    bool m_inverted;
    GameMediator *m_mediator;
};

#endif // BASICBOARD_H
