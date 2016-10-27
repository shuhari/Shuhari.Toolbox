#include "precompiled.h"
#include "toolwindow.h"
#include "toolitemmodel.h"
#include "app.h"


ToolWindow::ToolWindow()
    : QMainWindow() {

}


void ToolWindow::setTool(ToolItem *tool) {
    _tool = tool;
    setWindowIcon(tool->icon());
    setWindowTitle(tool->name());
}


QString ToolWindow::geometryKey() {
    if (_tool) {
        return QString("%1/geometry").arg(_tool->id());
    }
    return "";
}


bool ToolWindow::event(QEvent *event) {
    if (event->type() == QEvent::WindowActivate) {
        // Restore geometry on activate
        if (_tool) {
            auto geometry = appSettings()->value(geometryKey()).toByteArray();
            restoreGeometry(geometry);
        }
    } else if (event->type() == QEvent::Close) {
        // Hide on close, and save geometry
        if (_tool) {
            auto geometry = saveGeometry();
            appSettings()->setValue(geometryKey(), geometry);
        }
        hide();
        event->ignore();
        return true;
    }

    return QMainWindow::event(event);
}

