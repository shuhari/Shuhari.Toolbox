#include "precompiled.h"
#include "resources.h"
#include "app.h"
#include "bookmanwindow.h"
#include "toolitemmodel.h"
#include "processthread.h"


BookManageWindow::BookManageWindow()
    : ToolWindow() {

}


void BookManageWindow::createChildren() {
    auto dirLabel = new QLabel(strings::browse_text());
    _dirEdit = new QLineEdit();
    _dirEdit->setReadOnly(true);
    _dirBtn = new DirectoryButton(_dirEdit);
    _processBtn = new QPushButton(strings::process());
    _processBtn->setIcon(qApp->style()->standardIcon(QStyle::SP_MediaPlay));

    auto hbox = new QHBoxLayout();
    hbox->addWidget(dirLabel);
    hbox->addWidget(_dirEdit, 1);
    hbox->addWidget(_dirBtn);
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

    _dirEdit->setText(_config->directory());
}


void BookManageWindow::saveConfig() {
    _config->setDirectory(_dirEdit->text().trimmed());
    _config->save(appSettings());
}



void BookManageWindow::showRunning(bool running) {
    _dirBtn->setEnabled(!running);
    _processBtn->setEnabled(!running);
}


void BookManageWindow::on_process() {
    auto dirName = _dirBtn->currentDirectory();
    QDir dir(dirName);
    if (dirName.isEmpty() || !QDir(dirName).exists()) {
        warn(strings::directory_invalid());
        return;
    }

    showRunning(true);
    _logList->clear();
    auto thread = new ProcessThread(dirName, this);
    connect(thread, &ProcessThread::finished, this, &BookManageWindow::on_thread_finished);
    connect(thread, &ProcessThread::log, _logList, &LogList::log);
    thread->start();
}


void BookManageWindow::on_thread_finished() {
    _logList->info(strings::process_finished());
    showRunning(false);
}

