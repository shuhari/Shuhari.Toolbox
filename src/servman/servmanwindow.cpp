#include "precompiled.h"
#include "servmanwindow.h"
#include "resources.h"


ServiceManageWindow::ServiceManageWindow()
    : ToolWindow() {
}


ToolItem* ServiceManageWindow::define() {
    return new ToolItem("servman",
                        strings::servman_name(),
                        ":/servman",
                        strings::servman_tooltip(),
                        []() { return new ServiceManageWindow(); });
}
