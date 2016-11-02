#include "precompiled.h"
#include "cleandirwindow.h"
#include "resources.h"
#include "app.h"
#include "toolitemmodel.h"
#include "cleandirthread.h"


CleanDirWindow::CleanDirWindow()
    : ToolWindow() {
}


void CleanDirWindow::createChildren() {
    auto dirLabel = new QLabel(strings::directory());
    _dirEdit = new QLineEdit();
    _dirEdit->setReadOnly(true);
    _dirBtn = new DirectoryButton(_dirEdit);
    _cleanBtn = new QPushButton(strings::clean());
    _cleanBtn->setIcon(QIcon(":/clean"));

    auto hbox = new QHBoxLayout();
    hbox->addWidget(dirLabel);
    hbox->addWidget(_dirEdit);
    hbox->addWidget(_dirBtn);
    hbox->addWidget(_cleanBtn);

    _logList = new LogList();

    auto vbox = new QVBoxLayout();
    vbox->addLayout(hbox);
    vbox->addWidget(_logList, 1);
    setCentralLayout(vbox);

    connect(_cleanBtn, &QPushButton::clicked, this, &CleanDirWindow::on_clean);
}


void CleanDirWindow::loadConfig() {
    _config = new CleanDirConfig(tool()->id(), this);
    _config->load(appSettings());

    _dirEdit->setText(_config->directory());
}


void CleanDirWindow::saveConfig() {
    _config->setDirectory(_dirEdit->text().trimmed());
    _config->save(appSettings());
}


void CleanDirWindow::on_clean() {
    auto dir = _dirBtn->currentDirectory();
    if (dir.isEmpty() || !QDir(dir).exists()) {
        warn(strings::directory_invalid());
        return;
    }

    showRunning(true);
    _logList->clear();
    auto thread = new CleanDirThread(dir, this);
    connect(thread, &CleanDirThread::finished, this, &CleanDirWindow::on_thread_finished);
    connect(thread, &CleanDirThread::log, _logList, &LogList::log);
    thread->start();
}


void CleanDirWindow::on_thread_finished() {
    showRunning(false);
    _logList->info(strings::process_finished());
}


void CleanDirWindow::showRunning(bool running) {
    _dirBtn->setEnabled(!running);
    _cleanBtn->setEnabled(!running);
}

