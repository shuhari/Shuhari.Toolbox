#pragma once

#include "precompiled.h"

class ToolItem;


class ToolWindow : public QMainWindow {
    Q_OBJECT
public:
    ToolWindow();

    inline ToolItem* tool() { return _tool; }
    void setTool(ToolItem* tool);

protected:
    virtual bool event(QEvent *event);

private:
    ToolItem* _tool;

    QString geometryKey();
};
