#ifndef ROOK_H
#define ROOK_H

#include "basicpiece.h"

class CHESSCORE_EXPORT Rook : public BasicPiece
{
    Q_OBJECT
    Q_PROPERTY(bool moved READ moved WRITE setMoved NOTIFY movedChanged)
public:
    MAKE_VISITABLE(exept_func)

    explicit Rook(QQuickItem *parent = nullptr);
    virtual ~Rook();

    bool moved() const;    
    void setMoved(bool newMoved);

signals:
    void movedChanged(bool);

private:
    bool m_moved;
};

#endif // ROOK_H
