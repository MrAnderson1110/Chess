#include "boardplugin.h"

#include <QtQml>

#include <AppState>
#include <AppHistory>

#include <BasicBoard>
#include <BasicGridCell>
#include <BasicPiece>

#include <King>
#include <Queen>
#include <Bishop>
#include <Knight>
#include <Rook>
#include <Pawn>

void BoardPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("qmlplugins"));

    qmlRegisterType<BasicBoard>(uri, 1, 0, "BasicBoard");
    qmlRegisterType<BasicGridCell>(uri, 1, 0, "BasicGridCell");

    qmlRegisterUncreatableType<BasicPiece>(uri, 1, 0, "BasicPiece", "must be create from C++ only");

    qmlRegisterType<King>(uri, 1, 0, "King");
    qmlRegisterType<Queen>(uri, 1, 0, "Queen");
    qmlRegisterType<Bishop>(uri, 1, 0, "Bishop");
    qmlRegisterType<Knight>(uri, 1, 0, "Knight");
    qmlRegisterType<Rook>(uri, 1, 0, "Rook");
    qmlRegisterType<Pawn>(uri, 1, 0, "Pawn");

    qmlRegisterSingletonType<AppState>(uri, 1, 0, "AppState", &AppState::singletonTypeProvider);
    qmlRegisterSingletonType<AppHistory>(uri, 1, 0, "AppHistory", &AppHistory::singletonTypeProvider);

    qmlRegisterUncreatableType<Snapshot>(uri, 1, 0, "Snapshot", "Must be create from C++ side only");
}
