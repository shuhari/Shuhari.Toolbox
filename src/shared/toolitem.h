#pragma once


#include "precompiled.h"
#include "functional"


class ToolWindow;
typedef std::function<ToolWindow*(void)> ToolWindowFn;


class ToolItem {
public:
    ToolItem(const QString& id,
             const QString& name,
             const QString& iconName,
             const QString& tooltip,
             ToolWindowFn fn);

    inline QString id() const             { return _id; }
    inline QString name() const           { return _name; }
    inline QString tooltip() const        { return _tooltip; }
    inline QIcon   icon() const           { return _icon; }

    ToolWindow*    window();

private:
    QString      _id;
    QString      _name;
    QString      _tooltip;
    QIcon        _icon;
    ToolWindowFn _fn;
    ToolWindow*  _window;
};
