#ifndef BISHOP_H
#define BISHOP_H

#include "basicpiece.h"

class CHESSCORE_EXPORT Bishop : public BasicPiece
{
    Q_OBJECT
public:
    MAKE_VISITABLE(exept_func)

    explicit Bishop(QQuickItem *parent = nullptr);
    virtual ~Bishop();
};

#endif // BISHOP_H
