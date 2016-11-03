TEMPLATE = app
QT += core gui widgets
TARGET = shuhari.toolbox
CONFIG += embed_manifest_exe
DESTDIR = $$_PRO_FILE_PWD_/../build
PRECOMPILED_HEADER = precompiled.h

INCLUDEPATH += .

SOURCES += main.cpp \

HEADERS += precompiled.h \
        
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
