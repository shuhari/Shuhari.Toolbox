#pragma once

#include "precompiled.h"
#include "toolwindow.h"
#include "dirbutton.h"
#include "renamerconfig.h"
#include "renamermodel.h"
#include "renameritem.h"


class RenamerWindow : public ToolWindow {
    Q_OBJECT
public:
    RenamerWindow();

protected:
    virtual void createChildren();
    virtual void loadConfig();
    virtual void saveConfig();

private:
    QTableView*      _table;
    QLineEdit*       _dirEdit;
    QLineEdit*       _fromEdit;
    QLineEdit*       _toEdit;
    DirectoryButton* _dirBtn;
    QRadioButton*    _typeFixedRadio;
    QRadioButton*    _typeWildcardRadio;
    QRadioButton*    _typeRegexRadio;
    QCheckBox*       _targetFileCheck;
    QCheckBox*       _targetDirectoryCheck;
    QCheckBox*       _recursiveCheck;
    QCheckBox*       _decodeUrlCheck;
    QPushButton*     _selectBtn;
    QPushButton*     _findBtn;
    QPushButton*     _applyBtn;

    RenamerConfig*   _config;
    RenamerModel*    _model;

    void             showRunning(bool running);

private slots:
    void             on_find();
    void             on_apply();
    void             on_selectAll();
    void             on_selectNone();
    void             on_selectRevert();
    void             on_find_found(RenamerItem* item);
    void             on_find_finished();
};
