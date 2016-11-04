#pragma once


#include "precompiled.h"
#include "shared/toolitem.h"
#include "shared/toolwindow.h"
#include "shared/diredit.h"
#include "shared/loglist.h"
#include "cleandirconfig.h"
#include "cleanthread.h"


class CleanDirWindow : public ToolWindow {
    Q_OBJECT
public:
    CleanDirWindow();

    static ToolItem* define();

protected:
    virtual void createChildren();
    virtual void loadConfig();
    virtual void saveConfig();

private:
    DirectoryEdit*  _dirEdit;
    QPushButton*    _cleanBtn;
    LogList*        _logList;
    CleanDirConfig* _config;

    void            showRunning(bool running);

private slots:
    void            on_clean();
    void            on_thread_finished();
};
