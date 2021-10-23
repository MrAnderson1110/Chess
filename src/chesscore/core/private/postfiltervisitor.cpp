#include "postfiltervisitor.h"

#include <BasicBoard>
#include <King>
#include <Pawn>

PostFilterVisitor::PostFilterVisitor()
    : BaseVisitor()
    , Visitor<King>()
{

}

void PostFilterVisitor::visit(King *king)
{
    const QList<BasicPiece *> pieces = king->board()->pieces();
    AvailableMoves availableMoves = king->availableMoves();
    for(const Moves &moves : availableMoves) {
        for(const Move &move : moves) {
            for(BasicPiece *piece : pieces) {
                if(piece->command() == king->command())
                    continue;

                if(piece->predictedMovesContains(move))
                    king->removeAvailableMove(move);
            }
        }
    }
}

