#include "precompiled.h"
#include "bookmanwindow.h"
#include "resources.h"


BookManageWindow::BookManageWindow()
    : ToolWindow() {
}


ToolItem* BookManageWindow::define() {
    return new ToolItem("bookman",
                        strings::bookman_name(),
                        ":/bookman",
                        strings::bookman_tooltip(),
                        []() { return new BookManageWindow(); });
}
