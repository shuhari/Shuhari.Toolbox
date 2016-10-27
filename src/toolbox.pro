TEMPLATE = app
QT += core gui widgets winextras
TARGET = toolbox
CONFIG += embed_manifest_exe
DESTDIR = $$_PRO_FILE_PWD_/../build

INCLUDEPATH += . ./cleandir ./bookman ./encdec ./renamer ./servman

SOURCES += main.cpp \
           app.cpp \
           mainwindow.cpp \
           toolitemmodel.cpp \
           toolwindow.cpp \
           dirbutton.cpp \
           loglist.cpp \
           config.cpp \
           cleandir/cleandirwindow.cpp \
           cleandir/cleandirconfig.cpp \
           bookman/bookmanwindow.cpp \
           encdec/encdecwindow.cpp \
           renamer/renamerwindow.cpp \
           servman/servmanwindow.cpp \

HEADERS += app.h \
           precompiled.h \
           resources.h \
           mainwindow.h \
           toolitemmodel.h \
           toolwindow.h \
           dirbutton.h \
           loglist.h \
           config.h \
           cleandir/cleandirwindow.h \
           cleandir/cleandirconfig.h \
           bookman/bookmanwindow.h \
           encdec/encdecwindow.h \
           renamer/renamerwindow.h \
           servman/servmanwindow.h \

RESOURCES = ../resources/toolbox.qrc
RC_FILE = ../resources/toolbox.rc
TRANSLATIONS += ../translations/toolbox.zh_CN.ts \
PRECOMPILED_HEADER = precompiled.h

win32 {
    LIBS += libversion \
}
debug {
    TARGET = toolboxd
    CONFIG += console
    MOC_DIR = $$DESTDIR/debug/moc
    OBJECTS_DIR = $$DESTDIR/debug/obj
    RCC_DIR = $$DESTDIR/debug/rcc
    UI_DIR = $$DESTDIR/debug/ui
}
release {
    MOC_DIR = $$DESTDIR/release/moc
    OBJECTS_DIR = $$DESTDIR/release/obj
    RCC_DIR = $$DESTDIR/release/rcc
    UI_DIR = $$DESTDIR/release/ui
}
