#ifndef PAWN_H
#define PAWN_H

#include "basicpiece.h"

class CHESSCORE_EXPORT Pawn : public BasicPiece
{
    Q_OBJECT
public:
    MAKE_VISITABLE(exept_func)

    explicit Pawn(QQuickItem *parent = nullptr);
    virtual ~Pawn();
};

#endif // PAWN_H
