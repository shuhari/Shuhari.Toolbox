#include "precompiled.h"
#include "bookmanwindow.h"
#include "resources.h"
#include "resources.h"
#include "app.h"
#include "processthread.h"


BookManageWindow::BookManageWindow()
    : ToolWindow() {
}


ToolItem* BookManageWindow::define() {
    return new ToolItem("bookman",
                        strings::bookman_name(),
                        ":/bookman",
                        strings::bookman_tooltip(),
                        []() { return new BookManageWindow(); });
}


void BookManageWindow::createChildren() {
    auto dirLabel = new QLabel(strings::browse_label());
    _dirEdit = new DirectoryEdit();
    _processBtn = new QPushButton(strings::process());
    _processBtn->setIcon(qApp->style()->standardIcon(QStyle::SP_MediaPlay));

    auto hbox = new QHBoxLayout();
    hbox->addWidget(dirLabel);
    hbox->addWidget(_dirEdit, 1);
    hbox->addWidget(_processBtn);

    _logList = new LogList();

    auto vbox = new QVBoxLayout();
    vbox->addLayout(hbox);
    vbox->addWidget(_logList, 1);
    setCentralLayout(vbox);

    connect(_processBtn, &QPushButton::clicked, this, &BookManageWindow::on_process);
}


void BookManageWindow::loadConfig() {
    _config = new BookManageConfig(tool()->id(), this);
    _config->load(appSettings());

    _dirEdit->setDir(_config->directory());
}


void BookManageWindow::saveConfig() {
    _config->setDirectory(_dirEdit->currentDir());
    _config->save(appSettings());
}


void BookManageWindow::showRunning(bool running) {
    _processBtn->setEnabled(!running);
}


void BookManageWindow::on_process() {
    auto dirName = _dirEdit->currentDir(true);
    if (!dirName.isEmpty()) {
        showRunning(true);
        _logList->clear();
        auto thread = new ProcessThread(dirName, this);
        connect(thread, &ProcessThread::finished, this, &BookManageWindow::on_process_finished);
        connect(thread, &ProcessThread::log, _logList, LogList::log);
        thread->start();
    }
}


void BookManageWindow::on_process_finished() {
    _logList->info(strings::prompt_process_finished());
    showRunning(false);
}
