#pragma once

#include "precompiled.h"
#include "toolitemmodel.h"


class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow();

private:
    QListView* _list;
    ToolItemModel _itemModel;

    void createChildren();
    void loadItems();

private slots:
    void on_list_doubleClicked(const QModelIndex &index);
};

