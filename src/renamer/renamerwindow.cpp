#include "precompiled.h"
#include "renamerwindow.h"
#include "resources.h"


RenamerWindow::RenamerWindow()
    : ToolWindow() {
}


ToolItem* RenamerWindow::define() {
    return new ToolItem("renamer",
                        strings::renamer_name(),
                        ":/renamer",
                        strings::renamer_tooltip(),
                        []() { return new RenamerWindow(); });
}
