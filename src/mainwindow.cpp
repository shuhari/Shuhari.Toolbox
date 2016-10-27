#include "precompiled.h"
#include "mainwindow.h"
#include "resources.h"


MainWindow::MainWindow()
    : QWidget(nullptr) {
    setWindowIcon(QIcon(":/toolbox"));
    setWindowTitle(strings::toolbox());
}
