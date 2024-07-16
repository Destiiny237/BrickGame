QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../brick_game/snake/controller.cc \
    ../../brick_game/snake/model.cc \
    ../../brick_game/snake/snake.cc \
    ../../brick_game/tetris/model/tetris_model.c \
    ../../brick_game/tetris/bonus/bonus.c \
    ../../brick_game/tetris/controller/tetris_controller.c \
    ../../brick_game/tetris/model/backend.c \
    desktopView.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../../brick_game/snake/headers/controller.h \
    ../../brick_game/snake/headers/IObserver.h \
    ../../brick_game/snake/headers/model.h \
    ../../brick_game/snake/headers/snake.h \
    ../../brick_game/tetris/model/tetris_model.h \
    ../../brick_game/tetris/bonus/bonus.h \
    ../../brick_game/tetris/controller/tetris_controller.h \
    ../../brick_game/tetris/model/backend.h \
    desktopView.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
