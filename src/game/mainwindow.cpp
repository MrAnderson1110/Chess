#include "mainwindow.h"

#include <QQmlApplicationEngine>
#include <QQuickView>

MainWindow::MainWindow(QQmlApplicationEngine *engine, QObject *parent)
    : QObject(parent)
    , m_engine(engine)
{
    m_engine->load(MAIN_QML);
    connect(engine, &QQmlApplicationEngine::objectCreated,
            this, [](QObject *object, const QUrl &url){
        Q_ASSERT(object != nullptr);
        qDebug() << object->metaObject()->className() << url;

    });
}
