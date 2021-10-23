#ifndef SERVICES_GLOBAL_H
#define SERVICES_GLOBAL_H

#include <QtGlobal>

#ifdef SERVICES_LIB
#   define SERVICES_EXPORT Q_DECL_EXPORT
#else
#   define SERVICES_EXPORT Q_DECL_IMPORT
#endif

#endif // QMLSURFACE_GLOBAL_H
