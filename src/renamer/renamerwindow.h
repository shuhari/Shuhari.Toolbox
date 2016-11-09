#pragma once


#include "precompiled.h"
#include "shared/toolitem.h"
#include "shared/toolwindow.h"
#include "shared/diredit.h"
#include "renamerconfig.h"
#include "renamermodel.h"


class RenamerWindow : public ToolWindow {
    Q_OBJECT
public:
    RenamerWindow();

    static ToolItem* define();

protected:
    virtual void createChildren();
    virtual void loadConfig();
    virtual void saveConfig();

private:
    QTableView*       _table;
    DirectoryEdit*   _dirEdit;
    QLineEdit*       _originEdit;
    QLineEdit*       _replaceEdit;
    QRadioButton*    _typeFixedRadio;
    QRadioButton*    _typeWildcardRadio;
    QRadioButton*    _typeRegexRadio;
    QCheckBox*       _targetFileCheck;
    QCheckBox*       _targetDirCheck;
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
