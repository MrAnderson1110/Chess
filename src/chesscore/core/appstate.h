#ifndef APPSTATE_H
#define APPSTATE_H

#define appState AppState::instance()

#include <QObject>

#include <BasicPiece>

#include "chesscore_global.h"

class QQmlEngine;
class QJSEngine;

class CHESSCORE_EXPORT AppState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool checkToBlack READ checkToBlack WRITE setCheckToBlack NOTIFY checkToBlackChanged)
    Q_PROPERTY(bool checkToWhite READ checkToWhite WRITE setCheckToWhite NOTIFY checkToWhiteChanged)
    Q_PROPERTY(bool mateToBlack READ mateToBlack WRITE setMateToBlack NOTIFY mateToBlackChanged)
    Q_PROPERTY(bool mateToWhite READ mateToWhite WRITE setMateToWhite NOTIFY mateToWhiteChanged)
    Q_PROPERTY(int currentCommand READ currentCommand WRITE setCurrentCommand NOTIFY currentCommandChanged)
public:
    static AppState *instance();
    static QObject *singletonTypeProvider(QQmlEngine *, QJSEngine *);

    void resetChecks();

    bool checkToBlack() const;
    void setCheckToBlack(bool newCheckToBlack);

    bool checkToWhite() const;
    void setCheckToWhite(bool newCheckToWhite);

    bool mateToWhite() const;
    void setMateToWhite(bool newMateToWhite);

    bool mateToBlack() const;
    void setMateToBlack(bool newMateToBlack);

    int currentCommand() const;
    void setCurrentCommand(int newCurrentCommand);

signals:
    void checkToBlackChanged();
    void checkToWhiteChanged();
    void mateToWhiteChanged();
    void mateToBlackChanged();

    void currentCommandChanged();

private:
    explicit AppState(QObject *parent = nullptr);

private:
    static AppState *m_instance;
    bool m_checkToBlack;
    bool m_checkToWhite;
    bool m_mateToWhite;
    bool m_mateToBlack;
    int m_currentCommand;
};

#endif // APPSTATE_H
