#include "precompiled.h"
#include "toolwindow.h"
#include "toolitemmodel.h"
#include "app.h"
#include "resources.h"


ToolWindow::ToolWindow()
    : QMainWindow() {

}


void ToolWindow::setTool(ToolItem *tool) {
    _tool = tool;
    setWindowIcon(tool->icon());
    setWindowTitle(tool->name());
}


void ToolWindow::initialize() {
    // Restore geometry on activate
    auto geometry = appSettings()->value(geometryKey()).toByteArray();
    restoreGeometry(geometry);

    createChildren();
    loadConfig();
}


void ToolWindow::createChildren() {

}


void ToolWindow::loadConfig() {

}


void ToolWindow::saveConfig() {

}


QString ToolWindow::geometryKey() {
    if (_tool) {
        return QString("%1/geometry").arg(_tool->id());
    }
    return "";
}


bool ToolWindow::event(QEvent *event) {
    if (event->type() == QEvent::Close) {
        // Hide on close, and save geometry
        if (_tool) {
            auto geometry = saveGeometry();
            appSettings()->setValue(geometryKey(), geometry);
            saveConfig();
        }
        hide();
        event->ignore();
        return true;
    }

    return QMainWindow::event(event);
}


void ToolWindow::setCentralLayout(QLayout *layout) {
    auto central = new QWidget();
    central->setLayout(layout);
    setCentralWidget(central);
}


void ToolWindow::warn(const QString &msg) {
    QMessageBox::warning(this, strings::warning(), msg);
}
