#include "precompiled.h"
#include "spaceeyewindow.h"
#include "resources.h"
#include "resources.h"
#include "searchthread.h"


#define RADIOTYPE_DRIVE      1
#define RADIOTYPE_DIR        2


SpaceEyeWindow::SpaceEyeWindow()
    : ToolWindow() {
}


ToolItem* SpaceEyeWindow::define() {
    return new ToolItem("spaceeye",
                        strings::spaceeye_name(),
                        ":/spaceeye",
                        strings::spaceeye_tooltip(),
                        []() { return new SpaceEyeWindow(); });
}


void SpaceEyeWindow::createChildren() {
    createOptionDock();
    createDirTree();
    statusBar()->showMessage("");
}


void SpaceEyeWindow::createOptionDock() {
    _optionDock = new QDockWidget();
    _optionDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    _optionDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    _optionDock->setWindowTitle(strings::options());
    addDockWidget(Qt::LeftDockWidgetArea, _optionDock);

    auto vbox = new QVBoxLayout();
    auto widget = new QWidget();
    widget->setLayout(vbox);
    _optionDock->setWidget(widget);

    auto label = new QLabel("Select drive/directory to inspect");
    _dirGroup = new QButtonGroup(this);
    vbox->addWidget(label);
    foreach (QFileInfo driveInfo, QDir::drives()) {
        auto radio = new QRadioButton(driveInfo.filePath());
        radio->setProperty("path", driveInfo.filePath());
        radio->setProperty("type", RADIOTYPE_DRIVE);
        _dirGroup->addButton(radio);
        vbox->addWidget(radio);
    }

    _dirRadio = new QRadioButton("Or browse for directory");
    _dirRadio->setProperty("type", RADIOTYPE_DIR);
    _dirGroup->addButton(_dirRadio);
    _dirEdit = new DirectoryEdit();
    auto dirBox = new QHBoxLayout();
    dirBox->addWidget(_dirRadio);
    dirBox->addWidget(_dirEdit, 1);
    vbox->addLayout(dirBox);

    _startBtn = new QPushButton("Start");
    connect(_startBtn, &QPushButton::clicked, this, &SpaceEyeWindow::on_start);
    auto btnBox = new QHBoxLayout();
    btnBox->addStretch();
    btnBox->addWidget(_startBtn);
    vbox->addLayout(btnBox);
    vbox->addStretch();
}


void SpaceEyeWindow::createDirTree() {
    _dirTree = new QTreeView();
    setCentralWidget(_dirTree);
}


void SpaceEyeWindow::on_start() {
    auto radio = _dirGroup->checkedButton();
    if (!radio) {
        warn("You have not selected any drive/directory");
        return;
    }
    _dirName = "";
    auto type = radio->property("type").toInt();
    if (type == RADIOTYPE_DRIVE)
        _dirName = radio->property("path").toString();
    else if (type == RADIOTYPE_DIR)
        _dirName = _dirEdit->currentDir();

    if (_dirName.isEmpty() || !QDir(_dirName).exists()) {
        warn("You have not selected any valid drive/directory");
        return;
    }

    showRunning(true);
    auto thread = new SearchThread(_dirName, this);
    connect(thread, &SearchThread::statusLog, this, &SpaceEyeWindow::on_search_statusLog);
    connect(thread, &SearchThread::modelFinished, this, &SpaceEyeWindow::on_search_modelFinished);
    connect(thread, &SearchThread::finished, this, &SpaceEyeWindow::on_search_finished);
    thread->start();
}


void SpaceEyeWindow::on_search_statusLog(const QString &msg) {
    statusBar()->showMessage(msg);
}


void SpaceEyeWindow::on_search_modelFinished(QAbstractItemModel *model) {
    auto prevModel = _dirTree->model();
    _dirTree->setModel(model);
    if (prevModel) {
        delete prevModel;
    }
}


void SpaceEyeWindow::on_search_finished() {
    showRunning(false);
}


void SpaceEyeWindow::showRunning(bool running) {
    _startBtn->setEnabled(!running);
}

