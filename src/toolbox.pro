TEMPLATE = app
QT += core gui widgets winextras
TARGET = toolbox
CONFIG += embed_manifest_exe
DESTDIR = $$_PRO_FILE_PWD_/../build

INCLUDEPATH += . ./cleandir ./bookman ./encdec ./renamer ./servman

SOURCES += main.cpp \
           common.cpp \
           app.cpp \
           mainwindow.cpp \
           toolitemmodel.cpp \
           toolwindow.cpp \
           dirbutton.cpp \
           loglist.cpp \
           config.cpp \
           cleandir/cleandirwindow.cpp \
           cleandir/cleandirconfig.cpp \
           cleandir/cleandirthread.cpp \
           bookman/bookmanwindow.cpp \
           bookman/bookmanconfig.cpp \
           bookman/processthread.cpp \
           bookman/rarcommand.cpp \
           encdec/encdecwindow.cpp \
           encdec/encoders.cpp \
           renamer/renamerwindow.cpp \
           renamer/renameritem.cpp \
           renamer/renamerconfig.cpp \
           renamer/renamermodel.cpp \
           renamer/findthread.cpp \
           servman/servmanwindow.cpp \
           servman/servicemodel.cpp \
           servman/servicecontext.cpp \

HEADERS += precompiled.h \
           common.h \
           app.h \
           resources.h \
           mainwindow.h \
           toolitemmodel.h \
           toolwindow.h \
           dirbutton.h \
           loglist.h \
           config.h \
           cleandir/cleandirwindow.h \
           cleandir/cleandirconfig.h \
           cleandir/cleandirthread.h \
           bookman/bookmanwindow.h \
           bookman/bookmanconfig.h \
           bookman/processthread.h \
           bookman/rarcommand.h \
           encdec/encdecwindow.h \
           encdec/encoders.h \
           renamer/renamerwindow.h \
           renamer/renameritem.h \
           renamer/renamerconfig.h \
           renamer/renamermodel.h \
           renamer/findthread.h \
           servman/servmanwindow.h \
           servman/servicemodel.h \
           servman/servicecontext.h \

RESOURCES = ../resources/toolbox.qrc
RC_FILE = ../resources/toolbox.rc
TRANSLATIONS += ../translations/toolbox.zh_CN.ts \

# PRECOMPILED_HEADER = precompiled.h

win32 {
    LIBS += libversion \
}

CONFIG(debug, debug|release) {
    TARGET = toolboxd
    CONFIG += console
    MOC_DIR = $$DESTDIR/debug/moc
    OBJECTS_DIR = $$DESTDIR/debug/obj
    RCC_DIR = $$DESTDIR/debug/rcc
    UI_DIR = $$DESTDIR/debug/ui
} else {
    MOC_DIR = $$DESTDIR/release/moc
    OBJECTS_DIR = $$DESTDIR/release/obj
    RCC_DIR = $$DESTDIR/release/rcc
    UI_DIR = $$DESTDIR/release/ui
}
