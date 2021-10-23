#ifndef KNIGHT_H
#define KNIGHT_H

#include "basicpiece.h"

class CHESSCORE_EXPORT Knight : public BasicPiece
{
    Q_OBJECT
public:
    MAKE_VISITABLE(exept_func)

    explicit Knight(QQuickItem *parent = nullptr);
    virtual ~Knight();
};

#endif // KNIGHT_H
