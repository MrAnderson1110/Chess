#ifndef QUEEN_H
#define QUEEN_H

#include "basicpiece.h"

class CHESSCORE_EXPORT Queen : public BasicPiece
{
    Q_OBJECT
public:
    MAKE_VISITABLE(exept_func)

    explicit Queen(QQuickItem *parent = nullptr);
    virtual ~Queen();
};

#endif // QUEEN_H
