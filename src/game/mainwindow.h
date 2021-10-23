#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>

/*
 * Псевдо окно приложения.
 * Так как MainWindow создается из QML, данный класс выполняет функцию "инициализатора" и точки остчета приложения
 * Класс содержит глобальные объекты приложения (Шахматная доска, TCP-сокеты и пр.), а также методы изх взаимодействия
 * между собой
 */

class QQmlApplicationEngine;
class QQuickView;

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QQmlApplicationEngine *engine,
                        QObject *parent = nullptr);

private:
    QQmlApplicationEngine *m_engine;
};

#endif // MAINWINDOW_H
