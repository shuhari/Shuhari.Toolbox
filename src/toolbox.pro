TEMPLATE = app
QT += core gui widgets
TARGET = shuhari.toolbox
CONFIG += embed_manifest_exe
DESTDIR = $$_PRO_FILE_PWD_/../build
PRECOMPILED_HEADER = precompiled.h

INCLUDEPATH += .

SOURCES += main.cpp \
           app.cpp \
           shared/common.cpp \
           shared/toolitem.cpp \
           shared/toolmodel.cpp \
           shared/toolwindow.cpp \
           shared/diredit.cpp \
           shared/loglist.cpp \
           center/centerwindow.cpp \
           bookman/bookmanwindow.cpp \
           cleandir/cleandirwindow.cpp \
           encode/encodewindow.cpp \
           renamer/renamerwindow.cpp \
           servman/servmanwindow.cpp \

HEADERS += precompiled.h \
           resources.h \
           app.h \
           shared/common.h \
           shared/toolitem.h \
           shared/toolmodel.h \
           shared/toolwindow.h \
           shared/diredit.h \
           shared/loglist.h \
           center/centerwindow.h \
           bookman/bookmanwindow.h \
           cleandir/cleandirwindow.h \
           encode/encodewindow.h \
           renamer/renamerwindow.h \
           servman/servmanwindow.h \

RESOURCES = ../resources/toolbox.qrc
RC_FILE = ../resources/toolbox.rc

TRANSLATIONS += ../translations/toolbox.zh_CN.ts \ 

win32 {
    QT += winextras
    LIBS += libversion
}

CONFIG(debug, debug|release) {
    TARGET = shuhari.toolboxd
    CONFIG += config
    MOC_DIR = $$DESTDIR/debug/moc
    OBJECTS_DIR = $$DESTDIR/debug/obj
    RCC_DIR = $$DESTDIR/debug/rcc
    UI_DIR = $$DESTDIR/debug/ui
} ELSE {
    MOC_DIR = $$DESTDIR/release/moc
    OBJECTS_DIR = $$DESTDIR/release/obj
    RCC_DIR = $$DESTDIR/release/rcc
    UI_DIR = $$DESTDIR/release/ui
}
