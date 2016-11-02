#include "precompiled.h"
#include "mainwindow.h"
#include "resources.h"
#include "cleandirwindow.h"
#include "bookmanwindow.h"
#include "encdecwindow.h"
#include "renamerwindow.h"
#include "servmanwindow.h"
#include "common.h"


MainWindow::MainWindow()
    : QWidget(nullptr) {
    setWindowIcon(QIcon(":/toolbox"));
    setWindowTitle(strings::toolbox());

    createChildren();
    loadItems();
}


void MainWindow::createChildren() {
    _list = new QListView();
    _list->setViewMode(QListView::IconMode);
    _list->setResizeMode(QListView::Adjust);
    _list->setModel(&_itemModel);

    auto vbox = new QVBoxLayout();
    vbox->addWidget(_list);
    setLayout(vbox);

    connect(_list, &QListView::doubleClicked, this, &MainWindow::on_list_doubleClicked);

    resize(contentsRect().size());
}


void MainWindow::loadItems() {
    _itemModel.add(new ToolItem("cleandir",
                                ":/clean",
                                strings::cleandir_name(),
                                strings::cleandir_tooltip(),
                                []() { return new CleanDirWindow(); }));
    _itemModel.add(new ToolItem("bookman",
                                ":/book",
                                strings::bookman_name(),
                                strings::bookman_tooltip(),
                                []() { return new BookManageWindow(); }));
    _itemModel.add(new ToolItem("encdec",
                                ":/encode",
                                strings::encdec_name(),
                                strings::encdec_tooltip(),
                                []() { return new EncodeDecodeWindow(); }));
    _itemModel.add(new ToolItem("renamer",
                                ":/rename",
                                strings::renamer_name(),
                                strings::renamer_tooltip(),
                                []() { return new RenamerWindow(); }));
    _itemModel.add(new ToolItem("servman",
                                ":/service",
                                strings::servman_name(),
                                strings::servman_tooltip(),
                                []() { return new ServiceManageWindow(); }));
}


void MainWindow::on_list_doubleClicked(const QModelIndex &index) {
    auto item = (ToolItem*)varToPointer(_list->model()->data(index, Qt::UserRole));
    if (item) {
        ToolWindow* window = item->window();
        qDebug() << "tool window" << window;
        window->show();
        window->raise();
        window->activateWindow();
    }
}
