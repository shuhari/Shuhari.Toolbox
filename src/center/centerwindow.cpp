#include "precompiled.h"
#include "centerwindow.h"
#include "resources.h"


CenterWindow::CenterWindow()
    : QWidget(nullptr) {
    setWindowTitle(strings::toolbox());
    setWindowIcon(QIcon(":/toolbox"));
}
