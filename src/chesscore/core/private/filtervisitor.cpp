#include "filtervisitor.h"

#include <BasicBoard>
#include <BasicPiece>
#include <Pawn>
#include <Knight>
#include <BasicGridCell>

// функции сравнения в зависимости от направления обхода позиций
// Подразумевается, что если функция вернет true, то next стоит после prev по направлению движения
inline bool comp_top(const Move &prevRow, const Move &nextRow) { return prevRow.x() > nextRow.x(); };
inline bool comp_left(const Move &prevCol, const Move &nextCol) { return prevCol.y() > nextCol.y(); };
inline bool comp_bottom(const Move &prevRow, const Move &nextRow) { return prevRow.x() < nextRow.x(); };
inline bool comp_right(const Move &prevCol, const Move &nextCol) { return prevCol.y() < nextCol.y(); };
inline bool comp_top_left(const Move &prev, const Move &next) { return prev.x() > next.x() && prev.y() > next.y(); };
inline bool comp_top_right(const Move &prev, const Move &next) { return prev.x() > next.x() && prev.y() < next.y(); };
inline bool comp_bottom_left(const Move &prev, const Move &next) { return prev.x() < next.x() && prev.y() > next.y(); };
inline bool comp_bottom_right(const Move &prev, const Move &next) { return prev.x() < next.x() && prev.y() < next.y(); };

// функция получения следующей по возрастанию позиции в moves
inline Move get_next(const Move &prev, const Move &max, const Moves &moves, bool(*compFunc)(const Move &next, const Move &prev))
{
    Move lastFoundVal = max;
    for(const Move &move : moves) {
        // ищем цепочку prev -> move -> lastFoundVal
        if(compFunc(prev, move) && compFunc(move, lastFoundVal))
            lastFoundVal = move;
    }
    return lastFoundVal;
}


FilterVisitor::FilterVisitor()
    : BaseVisitor()
    , Visitor<BasicPiece>()
    , Visitor<Pawn>()
    , Visitor<Knight>()
{

}

void FilterVisitor::visit(BasicPiece *base)
{
    // Основной указатель на функцию сравнения
    bool(*compFunc)(const Move &next, const Move &prev) = nullptr;

    BasicBoard *board = base->board();
    AvailableMoves filteredMoves;
    Moves predictedMoves;
    const AvailableMoves &availableMoves = base->availableMoves();
    for(AvailableMoves::const_iterator it = availableMoves.cbegin(); it != availableMoves.cend(); ++it) {
        switch (it.key()) {
        case Top:
            compFunc = comp_top;
            break;
        case Bottom:
            compFunc = comp_bottom;
            break;
        case Left:
            compFunc = comp_left;
            break;
        case Right:
            compFunc = comp_right;
            break;
        case TopLeft:
            compFunc = comp_top_left;
            break;
        case TopRight:
            compFunc = comp_top_right;
            break;
        case BottomLeft:
            compFunc = comp_bottom_left;
            break;
        case BottomRight:
            compFunc = comp_bottom_right;
            break;
        default:
            // Нет доступных ходов для данного направления - оставляем как есть
            filteredMoves[it.key()] = it.value();
            continue;
        }

        Move minValue = Move(base->rowIndex(), base->columnIndex());
        Move maxValue = *std::max_element(it->begin(), it->end(), compFunc);
        while(minValue != maxValue) {
            // Следующее значение в порядке обхода по данному направлению
            minValue = get_next(minValue, maxValue, it.value(), compFunc);
            if(minValue.y() >= 8 || minValue.y() < 0 || minValue.x() >= 8 || minValue.x() < 0)
                break;

            BasicPiece *piece = board->cell(minValue.x(), minValue.y())->piece();
            if(piece != nullptr && piece->command() == base->command()) {
                predictedMoves << minValue;
                break;
            }

            filteredMoves[it.key()] << minValue;
            predictedMoves << minValue;
            if(piece != nullptr)
                break;
        }
    }
    base->setAvailableMoves(filteredMoves);
    base->setPredictedMoves(predictedMoves);
}

void FilterVisitor::visit(Pawn *pawn)
{
    int direction = pawn->command();
    int nextRow = pawn->rowIndex() + direction;
    if(nextRow < 0 || nextRow >= 8)
        return;

    int moveCount = 1;
    if(pawn->rowIndex() == (direction > 0 ? 1 : 6))
        moveCount = 2;

    // Основной указатель на функцию сравнения
    bool(*compFunc)(const Move &next, const Move &prev) = nullptr;

    MoveDirection currentDirection = direction > 0 ? Bottom : Top;
    const AvailableMoves &availableMoves = pawn->availableMoves();

    switch (currentDirection) {
    case Top:
        compFunc = comp_top;
        break;
    case Bottom:
        compFunc = comp_bottom;
        break;
    default:        // Не может существовать, но чтобы clang не ругался добавлено
        Q_ASSERT_X(false,
                   "FilterVisitor::visit(Pawn *)",
                   "nonexistent switch branch");
    }

    AvailableMoves filteredMoves;
    const Moves &moves = availableMoves[currentDirection];
    BasicBoard *board = pawn->board();
    Move minValue = Move(pawn->rowIndex(), pawn->columnIndex());
    Move maxValue = *std::max_element(moves.cbegin(), moves.cend(), compFunc);
    while(minValue != maxValue && filteredMoves[currentDirection].size() < moveCount) {
        // Следующее значение в порядке обхода по данному направлению
        minValue = get_next(minValue, maxValue, moves, compFunc);
        BasicPiece *piece = board->cell(minValue.x(), minValue.y())->piece();
        if(piece != nullptr)
            break;

        filteredMoves[currentDirection] << minValue;
    }

    pawn->setAvailableMoves(filteredMoves);

    // Потенциально возможные ходы
    Moves predictionMoves;
    int leftCol = pawn->columnIndex() - 1;
    if(leftCol >= 0)
        predictionMoves << Move(nextRow, leftCol);

    int rightCol = pawn->columnIndex() + 1;
    if(rightCol < 8)
        predictionMoves << Move(nextRow, rightCol);

    pawn->setPredictedMoves(predictionMoves);
}

void FilterVisitor::visit(Knight *knight)
{
    AvailableMoves filteredMoves;
    Moves predictedMoves;
    BasicBoard *board = knight->board();
    const AvailableMoves &availableMoves = knight->availableMoves();
    for(AvailableMoves::const_iterator it = availableMoves.cbegin(); it != availableMoves.cend(); ++it) {
        for(const Move &move : it.value())  {
            BasicPiece *piece = board->cell(move.x(), move.y())->piece();
            predictedMoves << move;

            if(piece != nullptr && piece->command() == knight->command())
                continue;

            filteredMoves[it.key()] << move;
        }
    }

    knight->setAvailableMoves(filteredMoves);
    knight->setPredictedMoves(predictedMoves);
}


