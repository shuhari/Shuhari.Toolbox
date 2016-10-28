#include "precompiled.h"
#include "renamerwindow.h"
#include "resources.h"
#include "app.h"
#include "toolitemmodel.h"
#include "findthread.h"


RenamerWindow::RenamerWindow()
    : ToolWindow() {
    // qRegisterMetaType<RenamerItem>("RenamerItem");
}


void RenamerWindow::createChildren() {
    auto dirLabel = new QLabel(strings::directory());
    _dirEdit = new QLineEdit();
    _dirEdit->setReadOnly(true);
    _dirBtn = new DirectoryButton(_dirEdit);

    auto fromLabel = new QLabel(strings::origin_text());
    _fromEdit = new QLineEdit();
    auto toLabel = new QLabel(strings::replace_with());
    _toEdit = new QLineEdit();

    auto typeLabel = new QLabel(strings::type());
    _typeFixedRadio = new QRadioButton(strings::fixed_string());
    _typeWildcardRadio = new QRadioButton(strings::wildcard());
    _typeRegexRadio = new QRadioButton(strings::regex());
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
    _targetDirectoryCheck = new QCheckBox(strings::directory());
    auto targetBox = new QHBoxLayout();
    targetBox->addWidget(_targetFileCheck);
    targetBox->addWidget(_targetDirectoryCheck);
    targetBox->addStretch();

    auto optionLabel = new QLabel(strings::options());
    _recursiveCheck = new QCheckBox(strings::recursive());
    _decodeUrlCheck = new QCheckBox(strings::decode_url());
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
    grid->addWidget(_dirBtn, 0, 2);
    grid->addWidget(fromLabel, 1, 0);
    grid->addWidget(_fromEdit, 1, 1, 1, 2);
    grid->addWidget(toLabel, 2, 0);
    grid->addWidget(_toEdit, 2, 1, 1, 2);
    grid->addWidget(typeLabel, 3, 0);
    grid->addLayout(typeBox, 3, 1, 1, 2);
    grid->addWidget(targetLabel, 4, 0);
    grid->addLayout(targetBox, 4, 1, 1, 2);
    grid->addWidget(optionLabel, 5, 0);
    grid->addLayout(optionBox, 5, 1, 1, 2);

    _table = new QTableView();
    _model = new RenamerModel(this);
    _table->setModel(_model);

    _table->verticalHeader()->hide();
    _table->setColumnWidth(0, 200);
    _table->setColumnWidth(1, 200);
    _table->setColumnWidth(2, 200);
    _table->setEditTriggers(QTableWidget::NoEditTriggers);
    _table->setSelectionBehavior(QTableWidget::SelectRows);

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

    _dirEdit->setText(_config->directory());
    _fromEdit->setText(_config->originText());
    _toEdit->setText(_config->replaceText());

    auto type = _config->type();
    switch (type) {
    case RenamerConfig::FixedString: _typeFixedRadio->setChecked(true); break;
    case RenamerConfig::Wildcard: _typeWildcardRadio->setChecked(true); break;
    case RenamerConfig::Regex: _typeRegexRadio->setChecked(true); break;
    }

    auto target = _config->target();
    _targetFileCheck->setChecked((target & RenamerConfig::File) == RenamerConfig::File);
    _targetDirectoryCheck->setChecked((target & RenamerConfig::Directory) == RenamerConfig::Directory);

    auto options = _config->options();
    _recursiveCheck->setChecked((options & RenamerConfig::Recursive) == RenamerConfig::Recursive);
    _decodeUrlCheck->setChecked((options & RenamerConfig::DecodeUrl) == RenamerConfig::DecodeUrl);
}


void RenamerWindow::saveConfig() {
    _config->setDirectory(_dirEdit->text().trimmed());
    _config->setOriginText(_fromEdit->text().trimmed());
    _config->setReplaceText(_toEdit->text().trimmed());

    RenamerConfig::Type type = RenamerConfig::FixedString;
    if (_typeWildcardRadio->isChecked())
        type = RenamerConfig::Wildcard;
    else if (_typeRegexRadio->isChecked())
        type = RenamerConfig::Regex;
    _config->setType(type);

    int target = 0;
    if (_targetFileCheck->isChecked())
        target |= RenamerConfig::File;
    if (_targetDirectoryCheck->isChecked())
        target |= RenamerConfig::Directory;
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
        warn(strings::directory_invalid());
        return;
    }
    if (_config->originText().isEmpty()) {
        warn(strings::rename_originText_invalid());
        return;
    }
    if (_config->target() == 0) {
        warn(strings::rename_target_invalid());
        return;
    }

    showRunning(false);
    _model->clear();
    auto thread = new FindThread(_config, this);
    connect(thread, &FindThread::found, this, &RenamerWindow::on_find_found);
    connect(thread, &FindThread::finished, this, &RenamerWindow::on_find_finished);
    thread->start();
}


void RenamerWindow::on_find_found(RenamerItem* item) {
    qDebug() << "founder renamer item:" << item->originName() << item->newName();
    _model->add(item);
}


void RenamerWindow::on_find_finished() {
    showRunning(false);
}


void RenamerWindow::on_apply() {

}
