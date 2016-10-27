#pragma once

#include "precompiled.h"


class App : public QApplication {
    Q_OBJECT
public:
    App(int argc, char** argv);
    int run();

    inline QSettings* settings() { return _settings; }

private:
    QSettings* _settings;

    void installTranslators();
    void installTranslatorByName(const QString& name);
    void registerSettings();
};


QSettings* appSettings();
