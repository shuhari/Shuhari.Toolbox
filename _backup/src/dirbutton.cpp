#include "precompiled.h"
#include "dirbutton.h"
#include "resources.h"
#include "app.h"


DirectoryButton::DirectoryButton(QLineEdit *buddy, QWidget *parent)
    : QPushButton(parent) {
    _buddy = buddy;

    setIcon(QIcon(":/directory"));
    setText(strings::browse_text());
    connect(this, &QPushButton::clicked, this, &DirectoryButton::on_clicked);
}


QString DirectoryButton::currentDirectory() {
    return _buddy->text().trimmed();
}

void DirectoryButton::setDirectory(const QString &dir) {
    QString buddyDir = currentDirectory();
    if (buddyDir != dir) {
        _buddy->setText(dir);
    }
}


void DirectoryButton::on_clicked() {
    auto dir = QFileDialog::getExistingDirectory(this,
        strings::browse_title(),
        currentDirectory(),
        QFileDialog::ShowDirsOnly);
    if (!dir.isEmpty())
        setDirectory(dir);
}
