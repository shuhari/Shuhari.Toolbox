#include "precompiled.h"
#include "renamerwindow.h"
#include "resources.h"
#include "resources.h"
#include "app.h"
#include "findthread.h"


RenamerWindow::RenamerWindow()
    : ToolWindow() {
}


ToolItem* RenamerWindow::define() {
    return new ToolItem("renamer",
                        strings::renamer_name(),
                        ":/renamer",
                        strings::renamer_tooltip(),
                        []() { return new RenamerWindow(); });
}


void RenamerWindow::createChildren() {
    auto dirLabel = new QLabel(strings::browse_label());
    _dirEdit = new DirectoryEdit();
    auto originLabel = new QLabel(strings::renamer_origin_name());
    _originEdit = new QLineEdit();
    auto replaceLabel = new QLabel(strings::renamer_new_name());
    _replaceEdit = new QLineEdit();
    auto typeLabel = new QLabel(strings::type());
    _typeFixedRadio = new QRadioButton(strings::renamer_type_fixed());
    _typeWildcardRadio = new QRadioButton(strings::renamer_type_wildcard());
    _typeRegexRadio = new QRadioButton(strings::renamer_type_regex());

    auto typeGroup = new QButtonGroup(this);
    typeGroup->addButton(_typeFixedRadio);
    typeGroup->addButton(_typeWildcardRadio);
    typeGroup->addButton(_typeRegexRadio);
    auto typeBox = new QHBoxLayout();
    typeBox->addWidget(_typeFixedRadio);
    typeBox->addWidget(_typeWildcardRadio);
    typeBox->addWidget(_typeRegexRadio);
    typeBox->addStretch();

    auto targetLabel = new QLabel(strings::target());
    _targetFileCheck = new QCheckBox(strings::file());
    _targetDirCheck = new QCheckBox(strings::directory());
    auto targetBox = new QHBoxLayout();
    targetBox->addWidget(_targetFileCheck);
    targetBox->addWidget(_targetDirCheck);
    targetBox->addStretch();

    auto optionLabel = new QLabel(strings::options());
    _recursiveCheck = new QCheckBox(strings::renamer_option_recursive());
    _decodeUrlCheck = new QCheckBox(strings::renamer_option_decodeUrl());
    auto optionBox = new QHBoxLayout();
    optionBox->addWidget(_recursiveCheck);
    optionBox->addWidget(_decodeUrlCheck);
    optionBox->addStretch();

    _selectBtn = new QPushButton(strings::select());
    auto selectMenu = new QMenu(_selectBtn);
    auto selectAllAction = new QAction(strings::all(), _selectBtn);
    auto selectNoneAction = new QAction(strings::none(), _selectBtn);
    auto selectRevertAction = new QAction(strings::revert(), _selectBtn);
    selectMenu->addAction(selectAllAction);
    selectMenu->addAction(selectNoneAction);
    selectMenu->addAction(selectRevertAction);
    _selectBtn->setMenu(selectMenu);

    _findBtn = new QPushButton(strings::find());
    _applyBtn = new QPushButton(strings::apply());
    auto btnBox = new QHBoxLayout();
    btnBox->addStretch();
    btnBox->addWidget(_findBtn);
    btnBox->addWidget(_selectBtn);
    btnBox->addWidget(_applyBtn);

    auto grid = new QGridLayout();
    grid->addWidget(dirLabel, 0, 0);
    grid->addWidget(_dirEdit, 0, 1);
    grid->addWidget(originLabel, 1, 0);
    grid->addWidget(_originEdit, 1, 1);
    grid->addWidget(replaceLabel, 2, 0);
    grid->addWidget(_replaceEdit, 2, 1);
    grid->addWidget(typeLabel, 3, 0);
    grid->addLayout(typeBox, 3, 1);
    grid->addWidget(targetLabel, 4, 0);
    grid->addLayout(targetBox, 4, 1);
    grid->addWidget(optionLabel, 5, 0);
    grid->addLayout(optionBox, 5, 1);

    _table = new QTableView();
    _model = new RenamerModel(this);
    _table->setModel(_model);

    _table->verticalHeader()->hide();
    _table->setColumnWidth(0, 200);
    _table->setColumnWidth(1, 200);
    _table->setColumnWidth(2, 200);
    _table->setEditTriggers(QTableView::NoEditTriggers);
    _table->setSelectionBehavior(QTableView::SelectRows);

    auto vbox = new QVBoxLayout();
    vbox->addLayout(grid);
    vbox->addLayout(btnBox);
    vbox->addWidget(_table, 1);
    setCentralLayout(vbox);

    connect(_findBtn, &QPushButton::clicked, this, &RenamerWindow::on_find);
    connect(_applyBtn, &QPushButton::clicked, this, &RenamerWindow::on_apply);
    connect(selectAllAction, &QAction::triggered, this, &RenamerWindow::on_selectAll);
    connect(selectNoneAction, &QAction::triggered, this, &RenamerWindow::on_selectNone);
    connect(selectRevertAction, &QAction::triggered, this, &RenamerWindow::on_selectRevert);
}


void RenamerWindow::loadConfig() {
    _config = new RenamerConfig(tool()->id(), this);
    _config->load(appSettings());

    _dirEdit->setDir(_config->directory());
    _originEdit->setText(_config->originText());
    _replaceEdit->setText(_config->replaceText());

    auto type = _config->type();
    switch (type) {
    case RenamerConfig::FixedString: _typeFixedRadio->setChecked(true); break;
    case RenamerConfig::Wildcard: _typeWildcardRadio->setChecked(true); break;
    case RenamerConfig::Regex: _typeRegexRadio->setChecked(true); break;
    }

    auto target = _config->target();
    _targetFileCheck->setChecked((target & RenamerConfig::File) == RenamerConfig::File);
    _targetDirCheck->setChecked((target & RenamerConfig::Dir) == RenamerConfig::Dir);

    auto options = _config->options();
    _recursiveCheck->setChecked((options & RenamerConfig::Recursive) == RenamerConfig::Recursive);
    _decodeUrlCheck->setChecked((options & RenamerConfig::DecodeUrl) == RenamerConfig::DecodeUrl);
}


void RenamerWindow::saveConfig() {
    _config->setDirectory(_dirEdit->currentDir());
    _config->setOriginText(_originEdit->text().trimmed());
    _config->setReplaceText(_replaceEdit->text().trimmed());

    RenamerConfig::Type type = RenamerConfig::FixedString;
    if (_typeWildcardRadio->isChecked())
        type = RenamerConfig::Wildcard;
    else if (_typeRegexRadio->isChecked())
        type = RenamerConfig::Regex;
    _config->setType(type);

    int target = 0;
    if (_targetFileCheck->isChecked())
        target |= RenamerConfig::File;
    if (_targetDirCheck->isChecked())
        target |= RenamerConfig::Dir;
    _config->setTarget(target);

    int options = 0;
    if (_decodeUrlCheck->isChecked())
        options |= RenamerConfig::DecodeUrl;
    if (_recursiveCheck->isChecked())
        options |= RenamerConfig::Recursive;
    _config->setOptions(options);

    _config->save(appSettings());
}

void RenamerWindow::showRunning(bool running) {
    _selectBtn->setEnabled(!running);
    _findBtn->setEnabled(!running);
    _applyBtn->setEnabled(!running);
}


void RenamerWindow::on_selectAll() {
    int rowCount = _model->rowCount(), colCount = _model->columnCount();
    auto selModel = _table->selectionModel();
    for (int row=0; row<rowCount; row++)
        for (int col=0; col<colCount; col++)
            selModel->select(_model->index(row, col), QItemSelectionModel::Select);
}

void RenamerWindow::on_selectNone() {
    int rowCount = _model->rowCount(), colCount = _model->columnCount();
    auto selModel = _table->selectionModel();
    for (int row=0; row<rowCount; row++)
        for (int col=0; col<colCount; col++)
            selModel->select(_model->index(row, col), QItemSelectionModel::Deselect);
}

void RenamerWindow::on_selectRevert() {
    int rowCount = _model->rowCount(), colCount = _model->columnCount();
    auto selModel = _table->selectionModel();
    for (int row=0; row<rowCount; row++) {
        QItemSelectionModel::SelectionFlag select = selModel->isRowSelected(row, QModelIndex()) ?
                    QItemSelectionModel::Deselect : QItemSelectionModel::Select;
        for (int col=0; col<colCount; col++)
            selModel->select(_model->index(row, col), select);
    }
}

void RenamerWindow::on_find() {
    saveConfig();

    if (_config->directory().isEmpty() || !QDir(_config->directory()).exists()) {
        warn(strings::prompt_invalid_directory());
        return;
    }
    if (_config->originText().isEmpty()) {
        warn(strings::prompt_invalid_originText());
        return;
    }
    if (_config->target() == 0) {
        warn(strings::prompt_invalid_target());
        return;
    }

    showRunning(false);
    _model->clear();
    auto thread = new FindThread(_config, this);
    connect(thread, &FindThread::found, this, &RenamerWindow::on_find_found);
    connect(thread, &FindThread::finished, this, &RenamerWindow::on_find_finished);
    thread->start();
}

void RenamerWindow::on_apply() {
    auto selModel = _table->selectionModel();
    for (int i=0; i<_model->rowCount(); i++) {
        auto item = _model->at(i);
        if (selModel->isRowSelected(i, QModelIndex())) {
            QDir dir(item->directory());
            bool success = dir.rename(item->originName(), item->newName());
            qDebug() << "renamer success" << success;
            _model->setState(i, success ? RenamerItem::SuccessState : RenamerItem::ErrorState);
        }
    }
    on_selectNone();
}

void RenamerWindow::on_find_finished() {
    showRunning(false);
}

void RenamerWindow::on_find_found(RenamerItem *item) {
    _model->add(item);
}
