#include "precompiled.h"
#include "app.h"
#include "mainwindow.h"


App::App(int argc, char** argv)
    : QApplication(argc, argv)
{

}


int App::run()
{
    auto window = new MainWindow();
    window->show();

    return exec();
}
