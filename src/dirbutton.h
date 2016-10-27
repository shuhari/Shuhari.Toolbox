#pragma once

#include "precompiled.h"


class DirectoryButton : public QPushButton {
    Q_OBJECT
public:
    DirectoryButton(QLineEdit* buddy, QWidget* parent = nullptr);

private:
    QLineEdit* _buddy;

    QString    currentDirectory();
    void       setDirectory(const QString& dir);

private slots:
    void       on_clicked();
};
