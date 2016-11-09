#include "precompiled.h"
#include "servmanwindow.h"
#include "resources.h"
#include "servicemodel.h"
#include "servicectx.h"


ServiceManageWindow::ServiceManageWindow()
    : ToolWindow() {
}


ToolItem* ServiceManageWindow::define() {
    return new ToolItem("servman",
                        strings::servman_name(),
                        ":/servman",
                        strings::servman_tooltip(),
                        []() { return new ServiceManageWindow(); });
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
    _startAction = new QAction(startIcon, strings::servman_start(), this);
    _stopAction = new QAction(stopIcon, strings::servman_stop(), this);
    _pauseAction = new QAction(pauseIcon, strings::servman_pause(), this);

    _startTypeAutoAction = createStartTypeAction(strings::servman_autoStart(), SERVICE_AUTO_START);
    _startTypeDemandAction = createStartTypeAction(strings::servman_demandStart(), SERVICE_DEMAND_START);
    _startTypeDisabledAction = createStartTypeAction(strings::servman_disabled(), SERVICE_DISABLED);

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

    connect(_table, &QTableView::clicked, this, &ServiceManageWindow::on_table_clicked);
}


void ServiceManageWindow::reloadServices() {
    _table->setColumnWidth(0, 100);
    _table->setColumnWidth(0, 100);
    _table->setColumnWidth(1, 100);
    _table->setColumnWidth(2, 200);
    _table->setColumnWidth(3, 100);
    _table->setColumnWidth(4, 100);
    _table->setColumnWidth(5, 100);
    _table->setColumnWidth(6, 100);
    _table->verticalHeader()->hide();

    _model->reload();
}


void ServiceManageWindow::on_refresh() {
    reloadServices();
}


void ServiceManageWindow::on_searchEdit_textChanged() {
    applyFilter();
}


void ServiceManageWindow::on_table_clicked() {
    updateActionStatus();
}


void ServiceManageWindow::updateActionStatus() {
    ServiceItem* item = selectedService();
    if (item) {
        _startTypeAutoAction->setChecked(item->startType() == SERVICE_AUTO_START);
        _startTypeDemandAction->setChecked(item->startType() == SERVICE_DEMAND_START);
        _startTypeDisabledAction->setChecked(item->startType() == SERVICE_DISABLED);
    } else {
        _startTypeAutoAction->setChecked(false);
        _startTypeDemandAction->setChecked(false);
        _startTypeDisabledAction->setChecked(false);
    }
}

ServiceItem* ServiceManageWindow::selectedService() {
    int rowCount = _model->rowCount(QModelIndex());
    auto selModel = _table->selectionModel();
    for (int row=0; row<rowCount; row++) {
        if (selModel->isRowSelected(row, QModelIndex()))
            return _model->at(row);
    }
    return nullptr;
}


void ServiceManageWindow::applyFilter() {
    QString name = _searchEdit->text().trimmed();
    for (int i=0; i<_model->rowCount(QModelIndex()); i++) {
        bool visible = _model->at(i)->match(name);
        _table->setRowHidden(i, !visible);
    }
}


void ServiceManageWindow::on_start() {

}


void ServiceManageWindow::on_stop() {

}

void ServiceManageWindow::on_pause() {

}


void ServiceManageWindow::on_startType() {
    auto action = qobject_cast<QAction*>(sender());
    if (action) {
        DWORD startType = action->data().toInt();
        auto item = selectedService();
        if (item) {
            QString errorMsg;
            bool success = ServiceContext::changeStartType(item->name(), startType, errorMsg);
            if (success) {
                _model->setStartType(item->name(), startType);
            }
            else
                warn(strings::prompt_setStartType_failed()
                     .arg(item->name())
                     .arg(startType)
                     .arg(errorMsg));
            updateActionStatus();
        }
    }
}




