#ifndef BASEVISITOR_H
#define BASEVISITOR_H

#include "chesscore_global.h"

class BasicPiece;
class BasicGridCell;

class CHESSCORE_EXPORT BaseVisitor
{
public:
    virtual ~BaseVisitor() {}
};

template<class T, typename R = void>
class CHESSCORE_EXPORT Visitor
{
public:
    typedef R ReturnType;
    virtual ReturnType visit(T *) = 0;
};

template<class T>
void (*base_exept_func)(T *visited, BaseVisitor *visitor) = nullptr;

template<typename R = void>
class CHESSCORE_EXPORT BaseVisitable
{
public:
    typedef R ReturnType;
    virtual ~BaseVisitable() {}
    virtual ReturnType accept(BaseVisitor *visitor) = 0;

protected:
    template<class T>
    static ReturnType acceptImpl(T *visited,
                                 BaseVisitor *visitor,
                                 void (*exept_func)(T *, BaseVisitor *))
    {
        Visitor<T> *castedVisitor = dynamic_cast<Visitor<T> *>(visitor);
        if(!castedVisitor) {
            if(exept_func)
                return exept_func(visited, visitor);

            return ReturnType();
        }

        return castedVisitor->visit(visited);
    }
};

#define MAKE_VISITABLE(exept_func) \
    virtual ReturnType accept(BaseVisitor *visitor) override { \
    return acceptImpl(this, visitor, exept_func); \
    }

#endif // BASEVISITOR_H
