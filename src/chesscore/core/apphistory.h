#ifndef APPHISTORY_H
#define APPHISTORY_H

#include "chesscore_global.h"

class CHESSCORE_EXPORT State
{
public:
    State(BasicPiece *owner,
          const Move &from,
          const Move &to,
          bool m_moved = false,
          BasicPiece *defeated = nullptr);
    ~State();

    BasicPiece *owner() const;
    Move from() const;
    Move to() const;
    bool moved() const;
    BasicPiece *defeated() const;

private:
    BasicPiece *m_owner;
    BasicPiece *m_defeated;
    bool m_moved;
    Move m_from;
    Move m_to;
};

class CHESSCORE_EXPORT Snapshot : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString move READ move CONSTANT)
public:
    explicit Snapshot(QObject *parent = nullptr);
    Snapshot(State *state);
    ~Snapshot();

    void add(State *state);
    State *next();
    void reset();
    bool castlingSnapshot() const;

    QList<State *> states() const;

    QString move() const;

private:
    QList<State *> m_states;
    QList<State *>::iterator m_internal;
};

#include <QAbstractListModel>
#include <QStack>

#define appHistory AppHistory::instance()

class QQmlEngine;
class QJSEngine;

class CHESSCORE_EXPORT AppHistory : public QAbstractListModel
{
public:
    enum Roles
    {
        SnapRole = Qt::UserRole + 1
    };

    static AppHistory *instance();
    static QObject *singletonTypeProvider(QQmlEngine *, QJSEngine *);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    Snapshot *pop();
    void push(Snapshot *snapshot);
    int size() const;

private:
    explicit AppHistory(QObject *parent = nullptr);

private:
    static AppHistory *m_instance;
    QList<Snapshot *> m_history;
};

#endif // APPHISTORY_H
