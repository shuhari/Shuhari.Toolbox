#include "precompiled.h"
#include "diredit.h"
#include "resources.h"


DirectoryEdit::DirectoryEdit(QWidget *parent)
    : QWidget(parent) {
    _edit = new QLineEdit();

    _browseBtn = new QPushButton();
    _browseBtn->setIcon(qApp->style()->standardIcon(QStyle::SP_DirIcon));
    _browseBtn->setToolTip(strings::browse_tooltip());

    auto hbox = new QHBoxLayout();
    hbox->setContentsMargins(0, 0, 0, 0);
    hbox->addWidget(_edit, 1);
    hbox->addWidget(_browseBtn);
    setLayout(hbox);

    connect(_browseBtn, &QPushButton::clicked, this, &DirectoryEdit::on_browse);
}


QString DirectoryEdit::currentDir(bool warn) {
    QString dir = _edit->text().trimmed();
    if (dir.isEmpty() || !QDir(dir).exists())
        dir = "";
    if (warn && dir.isEmpty()) {
        QMessageBox::warning(this, strings::warning(),
                             strings::prompt_invalid_directory());
    }
    return dir;
}


void DirectoryEdit::setDir(const QString& dir) {
    QString currentDir = _edit->text().trimmed();
    if (currentDir != dir) {
        _edit->setText(dir);
    }
}


void DirectoryEdit::on_browse() {
    auto dir = QFileDialog::getExistingDirectory(this,
        strings::browse_title(),
        currentDir(false),
        QFileDialog::ShowDirsOnly);
    if (!dir.isEmpty())
        setDir(dir);
}
