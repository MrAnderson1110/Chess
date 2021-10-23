#ifndef MOVEVISITOR_H
#define MOVEVISITOR_H

#include "chesscore_global.h"

#include "../basevisitor.h"

class King;
class Queen;
class Bishop;
class Rook;
class Pawn;
class Knight;

class CHESSCORE_EXPORT MovesVisitor
        : public BaseVisitor
        , public Visitor<King>
        , public Visitor<Queen>
        , public Visitor<Bishop>
        , public Visitor<Knight>
        , public Visitor<Rook>
        , public Visitor<Pawn>
{
public:
    MovesVisitor();

    void visit(King *king) override;
    void visit(Queen *queen) override;
    void visit(Bishop *bishop) override;
    void visit(Knight *knight) override;
    void visit(Rook *rook) override;
    void visit(Pawn *pawn) override;
};


#endif // MOVEVISITOR_H
