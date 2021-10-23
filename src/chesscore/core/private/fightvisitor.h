#ifndef FIGHTVISITOR_H
#define FIGHTVISITOR_H

#include "chesscore_global.h"

#include "../basevisitor.h"

class Pawn;

class CHESSCORE_EXPORT FightVisitor
        : public BaseVisitor
        , public Visitor<Pawn>
        , public Visitor<BasicPiece>
{
public:
    explicit FightVisitor();

    void reset(BasicPiece *initiator, const Move &prevInitiatorPoint);

    void visit(BasicPiece *base) override;
    void visit(Pawn *pawn) override;

    void checkKings(BasicPiece *underFight);

private:
    BasicPiece *m_initiator;
    Move m_prevInitiatorPoint;
};


#endif // FIGHTVISITOR_H
