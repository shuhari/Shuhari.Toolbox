#pragma once


#include "precompiled.h"
#include "bookmanconfig.h"
#include "shared/toolitem.h"
#include "shared/toolwindow.h"
#include "shared/diredit.h"
#include "shared/loglist.h"


class BookManageWindow : public ToolWindow {
    Q_OBJECT
public:
    BookManageWindow();

    static ToolItem* define();

protected:
    virtual void createChildren();
    virtual void loadConfig();
    virtual void saveConfig();

private:
    DirectoryEdit* _dirEdit;
    QPushButton*   _processBtn;
    LogList*       _logList;
    BookManageConfig* _config;

    void           showRunning(bool running);

private slots:
    void           on_process();
    void           on_process_finished();
};
