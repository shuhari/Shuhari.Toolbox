TEMPLATE = app
QT += core gui widgets winextras
TARGET = toolbox
CONFIG += embed_manifest_exe
DESTDIR = $$_PRO_FILE_PWD_/../build

INCLUDEPATH += .
SOURCES += main.cpp \
           app.cpp \
           mainwindow.cpp \

HEADERS += app.h \
           precompiled.h \
           mainwindow.h \

RESOURCES = ../resources/toolbox.qrc
RC_FILE = ../resources/toolbox.rc
TRANSLATIONS += ../translations/toolbox.zh_CN.ts \
# PRECOMPILED_HEADER = precompiled.h

win32 {
    LIBS += libversion \
}
debug {
    TARGET = toolboxd
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
