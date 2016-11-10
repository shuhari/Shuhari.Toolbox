#include "precompiled.h"
#include "spaceeyewindow.h"
#include "resources.h"


SpaceEyeWindow::SpaceEyeWindow()
    : ToolWindow() {
}


ToolItem* SpaceEyeWindow::define() {
    return new ToolItem("spaceeye",
                        strings::spaceeye_name(),
                        ":/spaceeye",
                        strings::spaceeye_tooltip(),
                        []() { return new SpaceEyeWindow(); });
}


void SpaceEyeWindow::createChildren() {
}
