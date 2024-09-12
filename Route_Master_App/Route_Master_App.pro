QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    algorithmwindow.cpp \
    astar.cpp \
    bfs.cpp \
    main.cpp \
    mainwindow.cpp \
    routemaster.cpp \
    startscreen.cpp \
    statswindow.cpp

HEADERS += \
    algorithmwindow.h \
    astar.h \
    bfs.h \
    mainwindow.h \
    routemaster.h \
    startscreen.h \
    statswindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Route_Master_App_en_PK.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    images/download.png
