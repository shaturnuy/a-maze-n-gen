QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += include \
               src

SOURCES += \
    src/main.cpp \
    src/cell.cpp \
    src/maze.cpp \
    src/gui/mainwindow.cpp \
    src/gui/basewidgetmenu.cpp \
    src/gui/algorithmgeneratormenu.cpp \
    src/gui/fieldsizemenu.cpp

HEADERS += \
    include/cell.h \
    include/maze.h \
    include/gui/algorithmgeneratormenu.h \
    include/gui/basewidgetmenu.h \
    include/gui/fieldsizemenu.h \
    include/gui/mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
