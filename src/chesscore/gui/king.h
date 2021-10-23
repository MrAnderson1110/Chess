#ifndef KING_H
#define KING_H

#include "basicpiece.h"

class CHESSCORE_EXPORT King : public BasicPiece
{
    Q_OBJECT
    Q_PROPERTY(bool moved READ moved WRITE setMoved NOTIFY movedChanged)
public:
    MAKE_VISITABLE(exept_func)

    explicit King(QQuickItem *parent = nullptr);
    virtual ~King();

    bool moved() const;
    void setMoved(bool newMoved);

signals:
    void movedChanged(bool);

private:
    bool m_moved;
};

#endif // KING_H
