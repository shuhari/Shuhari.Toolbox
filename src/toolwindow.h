#pragma once

#include "precompiled.h"

class ToolItem;


class ToolWindow : public QMainWindow {
    Q_OBJECT
public:
    ToolWindow();

    inline ToolItem* tool() { return _tool; }
    void setTool(ToolItem* tool);
    // create child controls and initialize
    virtual void initialize();

protected:
    virtual void createChildren();
    virtual void loadConfig();
    virtual void saveConfig();
    virtual bool event(QEvent *event);

    void setCentralLayout(QLayout* layout);

private:
    ToolItem* _tool;

    QString geometryKey();
};
