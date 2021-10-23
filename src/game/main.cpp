#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
#ifdef QT_DEBUG
    engine.addImportPath(QGuiApplication::applicationDirPath() + QStringLiteral("/../plugins"));
    engine.addImportPath(QGuiApplication::applicationDirPath() + QStringLiteral("/../libs"));
#else
    engine.addImportPath(QGuiApplication::applicationDirPath() + QStringLiteral("/libs"));
#endif
    MainWindow window(&engine);

    QUrl appUrl(MAIN_QML);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [&appUrl](QObject *obj, const QUrl &objUrl) {
        if (!obj && appUrl == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    return app.exec();
}
