#pragma once

#include "precompiled.h"
#include "shared/toolmodel.h"


class CenterWindow : public QWidget {
    Q_OBJECT
public:
    CenterWindow();

private:
    QListView*    _itemList;
    ToolModel*    _itemModel;

    void createChildren();
    void loadItems();

private slots:
    void on_list_doubleClicked(const QModelIndex &index);
};
