#include "precompiled.h"
#include "cleandirwindow.h"
#include "resources.h"


CleanDirWindow::CleanDirWindow()
    : ToolWindow() {
}


ToolItem* CleanDirWindow::define() {
    return new ToolItem("cleandir",
                        strings::cleandir_name(),
                        ":/cleandir",
                        strings::cleandir_tooltip(),
                        []() { return new CleanDirWindow(); });
}
