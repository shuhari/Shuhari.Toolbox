#pragma once

#include "precompiled.h"


class DirectoryEdit : public QWidget {
    Q_OBJECT
public:
    DirectoryEdit(QWidget* parent = nullptr);

    // Give selected directory
    // if warn=true and input directory is invalid then raise warning message
    // return valid directory or empty
    QString currentDir(bool warn = false);
    void    setDir(const QString& dir);

private:
    QLineEdit*       _edit;
    QPushButton*     _browseBtn;


private slots:
    void             on_browse();
};
