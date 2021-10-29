#include "apphistory.h"

#include <QDebug>

AppHistory *AppHistory::m_instance = nullptr;

AppHistory *AppHistory::instance()
{
    if(!m_instance)
        m_instance = new AppHistory;

    return m_instance;
}

QObject *AppHistory::singletonTypeProvider(QQmlEngine *, QJSEngine *)
{
    return instance();
}

QModelIndex AppHistory::index(int row, int column, const QModelIndex &parent) const
{
    if(column != 0 || parent.isValid() || row >= m_history.size())
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex AppHistory::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int AppHistory::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return m_history.size();
}

int AppHistory::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return 1;
}

QVariant AppHistory::data(const QModelIndex &index, int role) const
{
    if(role != SnapRole)
        return QVariant();

    if(!index.isValid() || index.row() >= m_history.size() || index.column() != 0)
        return QVariant();

    return QVariant::fromValue<Snapshot *>(m_history.at(index.row()));
}

QHash<int, QByteArray> AppHistory::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SnapRole] = "snap";
    return roles;
}

Snapshot *AppHistory::pop()
{
    beginRemoveRows(QModelIndex(), rowCount() - 1, rowCount() - 1);
    Snapshot *snap = m_history.takeLast();
    endRemoveRows();
    return snap;
}

void AppHistory::push(Snapshot *snapshot)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_history.append(snapshot);
    endInsertRows();
}

int AppHistory::size() const
{
    return m_history.size();
}

AppHistory::AppHistory(QObject *parent)
    : QAbstractListModel(parent)
    , m_history()
{

}

#include <BasicPiece>
#include <Rook>

#include "appstate.h"

#include <cmath>

Snapshot::Snapshot(QObject *parent)
    : QObject(parent)
    , m_states()
    , m_internal()
{
    reset();
}

Snapshot::Snapshot(State *state)
    : m_states()
    , m_internal()
{
    m_states << state;
    reset();
}

Snapshot::~Snapshot()
{
    qDeleteAll(m_states);
}

void Snapshot::add(State *state)
{
    m_states << state;
    reset();
}

State *Snapshot::next()
{
    if(m_internal == m_states.end())
        return nullptr;

    State *cur = *m_internal;
    ++m_internal;
    return cur;
}

void Snapshot::reset()
{
    m_internal = m_states.begin();
}

bool Snapshot::castlingSnapshot() const
{
    return m_states.size() == 2;
}

QList<State *> Snapshot::states() const
{
    return m_states;
}

BasicPiece *State::owner() const
{
    return m_owner;
}

Move State::from() const
{
    return m_from;
}

Move State::to() const
{
    return m_to;
}

bool State::moved() const
{
    return m_moved;
}

BasicPiece *State::defeated() const
{
    return m_defeated;
}

State::State(BasicPiece *owner, const Move &from, const Move &to, bool moved, BasicPiece *defeated)
    : m_owner(owner)
    , m_defeated(defeated)
    , m_moved(moved)
    , m_from(from)
    , m_to(to)
{

}

State::~State()
{

}

QString Snapshot::move() const
{
    if(m_states.isEmpty())
        return "";

    State *state = m_states.first();

    QString pieceName;
    switch (state->owner()->type()) {
    case BasicPiece::King:
        pieceName = "K";
        break;
    case BasicPiece::Queen:
        pieceName = "Q";
        break;
    case BasicPiece::Bishop:
        pieceName = "B";
        break;
    case BasicPiece::Knight:
        pieceName = "N";
        break;
    case BasicPiece::Rook:
        pieceName = "R";
        break;
    case BasicPiece::Pawn:
        pieceName = "";
        break;
    default:
        return "";
    }

    QString move;
    QString separator = state->defeated() != nullptr ? "x" : "-";
    if(m_states.size() == 1) {
        QString fromMove;
        switch(state->from().y()) {
        case 0:
            fromMove = QString("A%1").arg(7 - state->from().x() + 1);
            break;
        case 1:
            fromMove = QString("B%1").arg(7 - state->from().x() + 1);
            break;
        case 2:
            fromMove = QString("C%1").arg(7 - state->from().x() + 1);
            break;
        case 3:
            fromMove = QString("D%1").arg(7 - state->from().x() + 1);
            break;
        case 4:
            fromMove = QString("E%1").arg(7 - state->from().x() + 1);
            break;
        case 5:
            fromMove = QString("F%1").arg(7 - state->from().x() + 1);
            break;
        case 6:
            fromMove = QString("G%1").arg(7 - state->from().x() + 1);
            break;
        case 7:
            fromMove = QString("H%1").arg(7 - state->from().x() + 1);
            break;
        default:
            return "";
        }

        QString toMove;
        switch(state->to().y()) {
        case 0:
            toMove = QString("A%1").arg(7 - state->to().x() + 1);
            break;
        case 1:
            toMove = QString("B%1").arg(7 - state->to().x() + 1);
            break;
        case 2:
            toMove = QString("C%1").arg(7 - state->to().x() + 1);
            break;
        case 3:
            toMove = QString("D%1").arg(7 - state->to().x() + 1);
            break;
        case 4:
            toMove = QString("E%1").arg(7 - state->to().x() + 1);
            break;
        case 5:
            toMove = QString("F%1").arg(7 - state->to().x() + 1);
            break;
        case 6:
            toMove = QString("G%1").arg(7 - state->to().x() + 1);
            break;
        case 7:
            toMove = QString("H%1").arg(7 - state->to().x() + 1);
            break;
        default:
            return "";
        }

        move = QString("%1%2%3").arg(fromMove).arg(separator).arg(toMove);
    }
    else {
        State *rookState = nullptr;
        for(State *state : m_states) {
            Rook *rook = dynamic_cast<Rook *>(state->owner());
            if(rook != nullptr) {
                rookState = state;
                break;
            }
        }

        Q_ASSERT(rookState != nullptr);
        if(std::abs(rookState->from().y() - rookState->to().y()) == 2)
            move = "0-0";
        else if(std::abs(rookState->from().y() - rookState->to().y()) == 3)
            move = "0-0-0";
        else
            return "";
    }

    QString str = QString("%1%2").arg(pieceName).arg(move);

    if(appState->mateToBlack() || appState->mateToWhite())
        str.append("#");
    else if(appState->checkToBlack() || appState->checkToWhite())
        str.append("+");

    return str;
}
