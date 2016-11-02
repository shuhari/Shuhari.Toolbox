#pragma once

#include "precompiled.h"


class DirectoryButton : public QPushButton {
    Q_OBJECT
public:
    DirectoryButton(QLineEdit* buddy, QWidget* parent = nullptr);

    QString    currentDirectory();

private:
    QLineEdit* _buddy;

    void       setDirectory(const QString& dir);

private slots:
    void       on_clicked();
};
