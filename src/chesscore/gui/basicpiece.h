#ifndef BASICPIECE_H
#define BASICPIECE_H

#include "graphicitem.h"

template<class T>
void exept_func(T *visited, BaseVisitor *visitor)
{
    Visitor<BasicPiece> *castedVisitor = dynamic_cast<Visitor<BasicPiece> *>(visitor);
    if(!castedVisitor)
        return;
    castedVisitor->visit(visited);
}

class BasicBoard;

class CHESSCORE_EXPORT BasicPiece : public GraphicItem
{
    Q_OBJECT
    Q_PROPERTY(Command command READ command WRITE setCommand NOTIFY commandChanged)
    Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(bool movable READ movable WRITE setMovable NOTIFY movableChanged)

public:
    MAKE_VISITABLE(base_exept_func<BasicPiece>)

    enum Command
    {
        White = 1,
        Black = -1
    };
    Q_ENUM(Command)

    enum Type
    {
        King,
        Queen,
        Knight,
        Bishop,
        Rook,
        Pawn
    };
    Q_ENUM(Type)

    explicit BasicPiece(QQuickItem *parent = nullptr);

    bool movable() const;
    Command command() const;
    Type type() const;
    BasicBoard *board() const;

    void setMovable(bool newMovable);
    void setCommand(Command newCommand);
    void setBoard(BasicBoard *board);
    void setType(Type newType);

    const FightMoves &fightMoves() const;
    void setFightMoves(const FightMoves &moves);
    void addFigntMove(const FightPair &move);
    FightPair getFightPair(const Move &move);
    void removeFightMove(const Move &move);
    void removeFightMove(BasicPiece *piece);
    void removeFightMove(const FightPair &move);
    bool fightMovesContains(const Move &move);
    bool fightMovesContains(BasicPiece *piece);

    const AvailableMoves &availableMoves() const;
    void setAvailableMoves(const AvailableMoves &moves);
    void addAvailableMove(const Move &move, MoveDirection dir);
    bool availableMovesContains(const Move &move);
    void removeAvailableMove(const Move &move);

    const Moves &predictedMoves() const;
    void setPredictedMoves(const Moves &moves);
    bool predictedMovesContains(const Move &move);

public slots:
    virtual void startMove();
    virtual void move(const QRectF &geometry);
    virtual void finishMove();

signals:
    void movableChanged(bool);
    void commandChanged(Command);
    void typeChanged(Type);

private:
    BasicBoard *m_board;
    Command m_command;
    Type m_type;
    FightMoves m_fightMoves;
    AvailableMoves m_availableMoves;
    Moves m_predictedMoves;
//    AvailableMoves m_fullMoves;
    bool m_movable;
};

#endif // BASICPIECE_H
