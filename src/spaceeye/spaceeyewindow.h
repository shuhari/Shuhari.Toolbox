#pragma once

#include "precompiled.h"
#include "shared/toolitem.h"
#include "shared/toolwindow.h"
#include "shared/diredit.h"


class SpaceEyeWindow : public ToolWindow {
    Q_OBJECT
public:
    SpaceEyeWindow();

    static ToolItem* define();

protected:
    virtual void createChildren();

private:
    QDockWidget*    _optionDock;
    QButtonGroup*   _dirGroup;
    QTreeView*      _dirTree;
    QString         _dirName;
    QRadioButton*   _dirRadio;
    DirectoryEdit*  _dirEdit;
    QPushButton*    _startBtn;

    void            createOptionDock();
    void            createDirTree();
    void            showRunning(bool running);

private slots:
    void on_start();
    void on_search_statusLog(const QString& msg);
    void on_search_modelFinished(QAbstractItemModel* model);
    void on_search_finished();
};
