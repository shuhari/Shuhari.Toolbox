#include "precompiled.h"
#include "cleandirwindow.h"
#include "resources.h"
#include "app.h"


CleanDirWindow::CleanDirWindow()
    : ToolWindow() {
}


ToolItem* CleanDirWindow::define() {
    return new ToolItem("cleandir",
                        strings::cleandir_name(),
                        ":/cleandir",
                        strings::cleandir_tooltip(),
                        []() { return new CleanDirWindow(); });
}


void CleanDirWindow::createChildren() {
    auto dirLabel = new QLabel(strings::browse_label());
    _dirEdit = new DirectoryEdit();
    _cleanBtn = new QPushButton(strings::cleandir_clean());
    _cleanBtn->setIcon(QIcon(":/clean"));

    _logList = new LogList();

    auto hbox = new QHBoxLayout();
    hbox->addWidget(dirLabel);
    hbox->addWidget(_dirEdit, 1);
    hbox->addWidget(_cleanBtn);

    auto vbox = new QVBoxLayout();
    vbox->addLayout(hbox);
    vbox->addWidget(_logList);
    setCentralLayout(vbox);

    connect(_cleanBtn, &QPushButton::clicked, this, &CleanDirWindow::on_clean);
}


void CleanDirWindow::loadConfig() {
    _config = new CleanDirConfig(tool()->id(), this);
    _config->load(appSettings());

    _dirEdit->setDir(_config->directory());
}


void CleanDirWindow::saveConfig() {
    _config->setDirectory(_dirEdit->currentDir());

    _config->save(appSettings());
}


void CleanDirWindow::on_clean() {
    auto dir = _dirEdit->currentDir(true);
    if (!dir.isEmpty()) {
        showRunning(true);
        _logList->clear();
        auto thread = new CleanThread(dir, this);
        connect(thread, &CleanThread::finished, this, &CleanDirWindow::on_thread_finished);
        connect(thread, &CleanThread::log, _logList, &LogList::log);
        thread->start();
    }
}


void CleanDirWindow::on_thread_finished() {
    showRunning(false);
    _logList->info(strings::prompt_process_finished());
}


void CleanDirWindow::showRunning(bool running) {
    _cleanBtn->setEnabled(!running);
}
