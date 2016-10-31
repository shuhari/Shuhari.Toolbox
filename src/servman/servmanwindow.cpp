#include "precompiled.h"
#include "servmanwindow.h"
#include "resources.h"


ServiceManageWindow::ServiceManageWindow()
    : ToolWindow() {
}


void ServiceManageWindow::createChildren() {
    createActions();
    createToolbar();
    createCentral();
    reloadServices();
}


void ServiceManageWindow::loadConfig() {

}


void ServiceManageWindow::saveConfig() {

}


void ServiceManageWindow::createActions() {
    QStyle* style = qApp->style();
    QIcon reloadIcon = style->standardIcon(QStyle::SP_BrowserReload);
    QIcon startIcon = style->standardIcon(QStyle::SP_MediaPlay);
    QIcon stopIcon = style->standardIcon(QStyle::SP_MediaStop);
    QIcon pauseIcon = style->standardIcon(QStyle::SP_MediaPause);

    _refreshAction = new QAction(reloadIcon, strings::refresh(), this);
    _startAction = new QAction(startIcon, strings::start(), this);
    _stopAction = new QAction(stopIcon, strings::stop(), this);
    _pauseAction = new QAction(pauseIcon, strings::pause(), this);

    _startTypeAutoAction = createStartTypeAction(strings::service_autoStart(), SERVICE_AUTO_START);
    _startTypeDemandAction = createStartTypeAction(strings::service_demandStart(), SERVICE_DEMAND_START);
    _startTypeDisabledAction = createStartTypeAction(strings::service_disabled(), SERVICE_DISABLED);

    connect(_refreshAction, &QAction::triggered, this, &ServiceManageWindow::on_refresh);
    connect(_startAction, &QAction::triggered, this, &ServiceManageWindow::on_start);
    connect(_stopAction, &QAction::triggered, this, &ServiceManageWindow::on_stop);
    connect(_pauseAction, &QAction::triggered, this, &ServiceManageWindow::on_pause);

    connect(_startTypeAutoAction, &QAction::triggered, this, &ServiceManageWindow::on_startType);
    connect(_startTypeDemandAction, &QAction::triggered, this, &ServiceManageWindow::on_startType);
    connect(_startTypeDisabledAction, &QAction::triggered, this, &ServiceManageWindow::on_startType);
}


QAction* ServiceManageWindow::createStartTypeAction(const QString &name, int type) {
    auto action = new QAction(name, this);
    action->setCheckable(true);
    action->setData(QVariant::fromValue(type));
    return action;
}


void ServiceManageWindow::createToolbar() {
    _searchEdit = new QLineEdit();
    _searchEdit->setFixedWidth(150);

    auto toolbar = addToolBar("main");
    toolbar->addWidget(_searchEdit);
    toolbar->addSeparator();
    toolbar->addAction(_refreshAction);

    connect(_searchEdit, &QLineEdit::textChanged, this, &ServiceManageWindow::on_searchEdit_textChanged);
}


void ServiceManageWindow::createCentral() {
    _table = new QTableView();
    _table->setSelectionBehavior(QTableView::SelectRows);
    _table->setSelectionMode(QTableView::SingleSelection);

    _table->setContextMenuPolicy(Qt::ActionsContextMenu);
    _table->addAction(_startAction);
    _table->addAction(_stopAction);
    _table->addAction(_pauseAction);
    auto sep = new QAction(this);
    sep->setSeparator(true);
    _table->addAction(sep);
    _table->addAction(_startTypeAutoAction);
    _table->addAction(_startTypeDemandAction);
    _table->addAction(_startTypeDisabledAction);

    _model = new ServiceModel(_table);
    _table->setModel(_model);

    _detail = new QTextBrowser();
    _detail->setFixedWidth(250);

    auto hbox = new QHBoxLayout();
    hbox->addWidget(_table);
    hbox->addWidget(_detail);
    setCentralLayout(hbox);

    // selectionChanged connect(_table, &QTableView::s)
}


void ServiceManageWindow::reloadServices() {

}


void ServiceManageWindow::on_refresh() {

}


void ServiceManageWindow::on_searchEdit_textChanged() {

}

void ServiceManageWindow::on_table_itemSelectionChanged() {

}

void ServiceManageWindow::updateActionStatus() {

}

ServiceItem ServiceManageWindow::selectedService() {
    return ServiceItem();
}

void ServiceManageWindow::applyFilter() {

}


void ServiceManageWindow::on_start() {

}


void ServiceManageWindow::on_stop() {

}

void ServiceManageWindow::on_pause() {

}


void ServiceManageWindow::on_startType() {

}




