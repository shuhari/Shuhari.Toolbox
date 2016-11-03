#pragma once

#include "precompiled.h"


class ToolItem;


class ToolWindow : public QMainWindow {
    Q_OBJECT
public:
    ToolWindow();

    inline ToolItem* tool() const          { return _tool; }
    void setTool(ToolItem* tool);

    // Initialize after tool set
    virtual void initialize();

protected:
    // Create child controls
    virtual void createChildren();

    // Load configuration
    virtual void loadConfig();

    // Save configuration
    virtual void saveConfig();

    // Event filter
    virtual void closeEvent(QCloseEvent* event);

    void setCentralLayout(QLayout* layout);
    void warn(const QString& msg);

private:
    ToolItem* _tool;

    QString geometryKey();
};
