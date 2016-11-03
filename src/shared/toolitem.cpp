#include "precompiled.h"
#include "toolitem.h"
#include "toolwindow.h"


ToolItem::ToolItem(const QString &id, const QString &name, const QString &iconName,
                   const QString &tooltip, ToolWindowFn fn) {
    _id = id;
    _name = name;
    _icon = QIcon(iconName);
    _tooltip = tooltip;
    _fn = fn;
    _window = nullptr;
}


ToolWindow* ToolItem::window() {
    if (!_window) {
        _window = _fn();
        _window->setTool(this);
        _window->initialize();
    }
    return _window;
}
