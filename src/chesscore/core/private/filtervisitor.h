#ifndef FILTERVISITOR_H
#define FILTERVISITOR_H

#include "chesscore_global.h"

#include "../basevisitor.h"

class Pawn;
class Knight;

class CHESSCORE_EXPORT FilterVisitor
        : public BaseVisitor
        , public Visitor<BasicPiece>
        , public Visitor<Pawn>
        , public Visitor<Knight>
{
public:
    FilterVisitor();

    void visit(BasicPiece *base) override;
    void visit(Pawn *pawn) override;
    void visit(Knight *knight) override;
};


#endif // FILTERVISITOR_H
