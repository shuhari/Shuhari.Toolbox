#pragma once

#include "precompiled.h"
#include "toolwindow.h"
#include "dirbutton.h"
#include "loglist.h"
#include "cleandirconfig.h"


class CleanDirWindow : public ToolWindow {
    Q_OBJECT
public:
    CleanDirWindow();

protected:
    virtual void createChildren();
    virtual void loadConfig();
    virtual void saveConfig();

private:
    QLineEdit*       _dirEdit;
    DirectoryButton* _dirBtn;
    QPushButton*     _cleanBtn;
    LogList*         _logList;
    CleanDirConfig*  _config;

    void showRunning(bool running);

private slots:
    void on_clean();
    void on_thread_finished();
};
