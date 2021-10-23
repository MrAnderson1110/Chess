#------------------------------------------------------------------------------#

ROOT_DIR = $${PWD}/../..                # путь к корневой директории проекта
SRC_DIR = $${ROOT_DIR}/src              # путь к исходным текстам
LIBS_DIR = $${ROOT_DIR}/libs            # путь к собранным библиотекам
PLUGINS_DIR = $${ROOT_DIR}/plugins      # путь к собранным плагинам
PRO_NAME = qmlplugins                   # имя модуля

#------------------------------------------------------------------------------#

TARGET = $${PRO_NAME}

QT += core qml quick
include($${PRO_NAME}.pri)

LIBS += -L$${LIBS_DIR}/ -lchesscore
INCLUDEPATH += $${SRC_DIR}/chesscore
INCLUDEPATH += $${SRC_DIR}/chesscore/include

#------------------------------------------------------------------------------#

TEMPLATE = lib
CONFIG += plugin
CONFIG -= debug_and_release debug_and_release_target
DESTDIR = $${PLUGINS_DIR}/$$TARGET
DEFINES += $${TARGET}_PLUGIN

for(var, $$list($$files(qmldir, true))) {
    LSOURCE_FILE = $$join(var,,$$QMAKE_DIR_SEP,)
    ABSOLUTE_SOURCE_FILE = $$quote($$join(LSOURCE_FILE,,$$PWD,))
    ABSOLUTE_DEST_FILE = $$join(LSOURCE_FILE,,$$DESTDIR,)
    ABSOLUTE_DEST = $$quote($$dirname(ABSOLUTE_DEST_FILE))
    qmldir.files = ABSOLUTE_SOURCE_FILE
    qmldir.path = ABSOLUTE_DEST
    INSTALLS += qmldir
    mkpath($$ABSOLUTE_DEST)
    isEmpty(QMAKE_POST_LINK) { } else { QMAKE_POST_LINK += & }
    QMAKE_POST_LINK += \
    $$QMAKE_COPY $$replace($$list($$ABSOLUTE_SOURCE_FILE $$ABSOLUTE_DEST), /, $$QMAKE_DIR_SEP)
}
for(var, $$list($$files($$quote(*.qml), true))) {
    LSOURCE_FILE = $$join(var,,$$QMAKE_DIR_SEP,)
    ABSOLUTE_SOURCE_FILE = $$quote($$join(LSOURCE_FILE,,$$PWD,))
    ABSOLUTE_DEST_FILE = $$join(LSOURCE_FILE,,$$DESTDIR,)
    ABSOLUTE_DEST = $$quote($$dirname(ABSOLUTE_DEST_FILE))
    qmlfiles.files = ABSOLUTE_SOURCE_FILE
    qmlfiles.path = ABSOLUTE_DEST
    INSTALLS += qmlfiles
    mkpath($$ABSOLUTE_DEST)
    isEmpty(QMAKE_POST_LINK) { } else { QMAKE_POST_LINK += & }
    QMAKE_POST_LINK += \
    $$QMAKE_COPY $$replace($$list($$ABSOLUTE_SOURCE_FILE $$ABSOLUTE_DEST), /, $$QMAKE_DIR_SEP)
}
for(var, $$list($$files($$quote(*.svg), true))) {
    LSOURCE_FILE = $$join(var,,$$QMAKE_DIR_SEP,)
    ABSOLUTE_SOURCE_FILE = $$quote($$join(LSOURCE_FILE,,$$PWD,))
    ABSOLUTE_DEST_FILE = $$join(LSOURCE_FILE,,$$DESTDIR,)
    ABSOLUTE_DEST = $$quote($$dirname(ABSOLUTE_DEST_FILE))
    qmlfiles.files = ABSOLUTE_SOURCE_FILE
    qmlfiles.path = ABSOLUTE_DEST
    INSTALLS += qmlfiles
    mkpath($$ABSOLUTE_DEST)
    isEmpty(QMAKE_POST_LINK) { } else { QMAKE_POST_LINK += & }
    QMAKE_POST_LINK += \
    $$QMAKE_COPY $$replace($$list($$ABSOLUTE_SOURCE_FILE $$ABSOLUTE_DEST), /, $$QMAKE_DIR_SEP)
}

MOC_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${PRO_NAME}
OBJECTS_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${PRO_NAME}
UI_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${PRO_NAME}

#------------------------------------------------------------------------------#
