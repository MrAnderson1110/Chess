#------------------------------------------------------------------------------#

ROOT_DIR = $${PWD}/../..                        # путь к корневой директории проекта
SRC_DIR = $${ROOT_DIR}/src                      # путь к исходным текстам
LIBS_DIR = $${ROOT_DIR}/libs                    # путь к собранным библиотекам
PLUGINS_DIR = $${ROOT_DIR}/plugins              # путь к собранным плагинам
PRO_NAME = services                             # имя модуля

#------------------------------------------------------------------------------#

TARGET = $${PRO_NAME}

TEMPLATE = lib
QT += core
CONFIG -= debug_and_release debug_and_release_target
CONFIG += c++11
DESTDIR = $$LIBS_DIR
DEFINES += $${upper($$TARGET)}_LIB

include($${PRO_NAME}.pri)

INCLUDEPATH += $${SRC_DIR}/services

unix:MOC_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
unix:OBJECTS_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}
unix:UI_DIR = $${ROOT_DIR}/build-$${QT_VERSION}/$${TARGET}

#------------------------------------------------------------------------------#

