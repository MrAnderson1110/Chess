#------------------------------------------------------------------------------#

ROOT_DIR = $${PWD}/../..                        # путь к корневой директории проекта
SRC_DIR = $${ROOT_DIR}/src                      # путь к исходным текстам
LIBS_DIR = $${ROOT_DIR}/libs                    # путь к собранным библиотекам
PLUGINS_DIR = $${ROOT_DIR}/plugins              # путь к собранным плагинам
PRO_NAME = game                                 # имя модуля

#------------------------------------------------------------------------------#

TARGET = $${PRO_NAME}

TEMPLATE = app
QT += core gui qml widgets quick
CONFIG += c++11
QMAKE_CXXFLAGS += -std=gnu++11

CONFIG -= debug_and_release debug_and_release_target
DESTDIR = $${ROOT_DIR}/app
DEFINES += $${upper($$TARGET)}_LIB
DEFINES += MAIN_QML+=\\\"qrc:/main.qml\\\"

include($${PRO_NAME}.pri)

LIBS += -L$${LIBS_DIR}/ -lchesscore
INCLUDEPATH += $${SRC_DIR}/chesscore
INCLUDEPATH += $${SRC_DIR}/chesscore/include

LIBS += -L$${LIBS_DIR}/ -lservices
INCLUDEPATH += $${SRC_DIR}/services

MOC_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
OBJECTS_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
UI_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
