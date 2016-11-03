#include "precompiled.h"
#include "toolwindow.h"
#include "toolitem.h"
#include "app.h"
#include "resources.h"


ToolWindow::ToolWindow()
    : QMainWindow(nullptr) {
}


void ToolWindow::setTool(ToolItem *tool) {
    Q_ASSERT(tool != nullptr);
    _tool = tool;
    setWindowIcon(tool->icon());
    setWindowTitle(tool->name());
}


QString ToolWindow::geometryKey() {
    Q_ASSERT(_tool != nullptr);
    return QString("%1/geometry").arg(_tool->id());
}


void ToolWindow::initialize() {
    auto geometry = appSettings()->value(geometryKey()).toByteArray();
    restoreGeometry(geometry);

    createChildren();
    loadConfig();
}


void ToolWindow::closeEvent(QCloseEvent *event) {
    // Hide on close, and save geometry
    if (_tool) {
        auto geometry = saveGeometry();
        appSettings()->setValue(geometryKey(), geometry);
        saveConfig();
    }

    hide();
    event->ignore();
}


void ToolWindow::createChildren() {

}


void ToolWindow::loadConfig() {

}

void ToolWindow::saveConfig() {

}


void ToolWindow::setCentralLayout(QLayout *layout) {
    auto central = new QWidget();
    central->setLayout(layout);
    setCentralWidget(central);
}


void ToolWindow::warn(const QString& msg) {
    QMessageBox::warning(this, strings::warning(), msg);
}
