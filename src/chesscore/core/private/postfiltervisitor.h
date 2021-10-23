#ifndef POSTFILTERVISITOR_H
#define POSTFILTERVISITOR_H

#include "chesscore_global.h"

#include "../basevisitor.h"

class King;

class CHESSCORE_EXPORT PostFilterVisitor
        : public BaseVisitor
        , public Visitor<King>
{
public:
    PostFilterVisitor();

    void visit(King *king) override;
};


#endif // POSTFILTERVISITOR_H
