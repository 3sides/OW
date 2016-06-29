QT += qml quick sql

CONFIG += c++11

SOURCES += main.cpp \
    SqlQueryUserConfigModel.cpp

RESOURCES += qml.qrc

HEADERS += \
    SqlQueryUserConfigModel.h

INCLUDEPATH += $$PWD/../UserConfig $$PWD/../common

LIBS += -L$$PWD"/../x64/Debug" -lUserConfig

DISTFILES +=
