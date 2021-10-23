#------------------------------------------------------------------------------#

ROOT_DIR = $${PWD}/../..                        # путь к корневой директории проекта
SRC_DIR = $${ROOT_DIR}/src                      # путь к исходным текстам
3RDPARTY_DIR = $${SRC_DIR}/sipcore/3rdparty     # путь к исходным текстам 3rdparty
LIBS_DIR = $${ROOT_DIR}/libs                    # путь к собранным библиотекам
PLUGINS_DIR = $${ROOT_DIR}/plugins              # путь к собранным плагинам
PRO_NAME = chesscore                            # имя модуля

#------------------------------------------------------------------------------#

TARGET = $${PRO_NAME}

QT += core qml quick

include($${PRO_NAME}.pri)
include(gui/gui.pri)
include(core/core.pri)

INCLUDEPATH += $${SRC_DIR}/$${PRO_NAME}/include

#------------------------------------------------------------------------------#

TEMPLATE = lib
CONFIG -= debug_and_release debug_and_release_target
DESTDIR = $$LIBS_DIR
DEFINES += $${upper($$TARGET)}_LIB

unix:MOC_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
unix:OBJECTS_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
unix:UI_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}

#------------------------------------------------------------------------------#

