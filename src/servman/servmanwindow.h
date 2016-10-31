#pragma once

#include "precompiled.h"
#include "toolwindow.h"
#include "servicemodel.h"


class ServiceManageWindow : public ToolWindow {
    Q_OBJECT
public:
    ServiceManageWindow();

protected:
    virtual void createChildren();
    virtual void loadConfig();
    virtual void saveConfig();

private:
    void createActions();
    void createToolbar();
    void createCentral();
    void reloadServices();
    void applyFilter();

    ServiceItem* selectedService();
    void updateActionStatus();
    QAction* createStartTypeAction(const QString& name, int type);

    QAction* _refreshAction;
    QAction* _startAction;
    QAction* _stopAction;
    QAction* _pauseAction;
    QAction* _startTypeAutoAction;
    QAction* _startTypeDemandAction;
    QAction* _startTypeDisabledAction;

    QLineEdit* _searchEdit;
    QTableView* _table;
    QTextBrowser* _detail;
    ServiceModel* _model;

private slots:
    void on_refresh();
    void on_searchEdit_textChanged();
    void on_table_itemSelectionChanged();
    void on_start();
    void on_stop();
    void on_pause();
    void on_startType();
};
