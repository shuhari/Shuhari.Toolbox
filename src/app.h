#pragma once

#include "precompiled.h"


class App : public QApplication
{
    Q_OBJECT
public:
    App(int argc, char** argv);
    int run();
};

