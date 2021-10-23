#ifndef CHESS_H
#define CHESS_H

#include <QQmlExtensionPlugin>

class BoardPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    void registerTypes(const char *uri);
};

#endif // CHESS_H
