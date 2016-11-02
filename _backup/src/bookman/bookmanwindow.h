#pragma once

#include "precompiled.h"
#include "toolwindow.h"
#include "dirbutton.h"
#include "loglist.h"
#include "bookmanconfig.h"


class BookManageWindow : public ToolWindow {
    Q_OBJECT
public:
    BookManageWindow();

protected:
    virtual void createChildren();
    virtual void loadConfig();
    virtual void saveConfig();

private:
    QLineEdit*        _dirEdit;
    DirectoryButton*  _dirBtn;
    QPushButton*      _processBtn;
    LogList*          _logList;

    BookManageConfig* _config;

    void              showRunning(bool running);

private slots:
    void              on_process();
    void              on_thread_finished();
};
