#include "appstate.h"
AppState *AppState::m_instance = nullptr;

AppState *AppState::instance()
{
    if(!m_instance)
        m_instance = new AppState;

    return m_instance;
}

QObject *AppState::singletonTypeProvider(QQmlEngine *, QJSEngine *)
{
    return instance();
}

void AppState::resetChecks()
{
    setCheckToBlack(false);
    setCheckToWhite(false);
}

AppState::AppState(QObject *parent)
    : QObject(parent)
    , m_checkToBlack(false)
    , m_checkToWhite(false)
    , m_mateToWhite(false)
    , m_mateToBlack(false)
    , m_currentCommand(BasicPiece::White)
{

}


bool AppState::checkToBlack() const
{
    return m_checkToBlack;
}

void AppState::setCheckToBlack(bool newCheckToBlack)
{
    if(m_checkToBlack == newCheckToBlack)
        return;

    m_checkToBlack = newCheckToBlack;
    emit checkToBlackChanged(m_checkToBlack);
}

bool AppState::checkToWhite() const
{
    return m_checkToWhite;
}

void AppState::setCheckToWhite(bool newCheckToWhite)
{
    if(m_checkToWhite == newCheckToWhite)
        return;

    m_checkToWhite = newCheckToWhite;
    emit checkToWhiteChanged(m_checkToWhite);
}

bool AppState::mateToWhite() const
{
    return m_mateToWhite;
}

void AppState::setMateToWhite(bool newMateToWhite)
{
    if(m_mateToWhite == newMateToWhite)
        return;

    m_mateToWhite = newMateToWhite;
    emit mateToWhiteChanged(m_mateToWhite);
}

bool AppState::mateToBlack() const
{
    return m_mateToBlack;
}

void AppState::setMateToBlack(bool newMateToBlack)
{
    if(m_mateToBlack == newMateToBlack)
        return;

    m_mateToBlack = newMateToBlack;
    emit mateToBlackChanged(m_mateToBlack);
}

int AppState::currentCommand() const
{
    return m_currentCommand;
}

void AppState::setCurrentCommand(int newCurrentCommand)
{
    if (m_currentCommand == newCurrentCommand)
        return;

    m_currentCommand = newCurrentCommand;
    emit currentCommandChanged(m_currentCommand);
}

bool AppState::stalemate() const
{
    return m_stalemate;
}

void AppState::setStalemate(bool newStalemate)
{
    if (m_stalemate == newStalemate)
        return;

    m_stalemate = newStalemate;
    emit stalemateChanged(m_stalemate);
}
