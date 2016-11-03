#include "precompiled.h"
#include "encodewindow.h"
#include "resources.h"


EncodeWindow::EncodeWindow()
    : ToolWindow() {
}


ToolItem* EncodeWindow::define() {
    return new ToolItem("encode",
                        strings::encode_name(),
                        ":/encode",
                        strings::encode_tooltip(),
                        []() { return new EncodeWindow(); });
}
