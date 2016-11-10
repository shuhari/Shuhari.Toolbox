#include "precompiled.h"
#include "centerwindow.h"
#include "resources.h"
#include "shared/common.h"
#include "cleandir/cleandirwindow.h"
#include "bookman/bookmanwindow.h"
#include "encode/encodewindow.h"
#include "renamer/renamerwindow.h"
#include "servman/servmanwindow.h"
#include "spaceeye/spaceeyewindow.h"


CenterWindow::CenterWindow()
    : QWidget(nullptr) {
    setWindowTitle(strings::toolbox());
    setWindowIcon(QIcon(":/toolbox"));

    createChildren();
    loadItems();
}


void CenterWindow::createChildren() {
    _itemList = new QListView();
    _itemList->setViewMode(QListView::IconMode);
    _itemList->setResizeMode(QListView::Adjust);

    auto vbox = new QVBoxLayout();
    vbox->addWidget(_itemList);
    setLayout(vbox);

    connect(_itemList, &QListView::doubleClicked, this, &CenterWindow::on_list_doubleClicked);

    resize(contentsRect().size());
}


void CenterWindow::loadItems() {
    _itemModel = new ToolModel(this);
    _itemModel->add(CleanDirWindow::define());
    _itemModel->add(BookManageWindow::define());
    _itemModel->add(EncodeWindow::define());
    _itemModel->add(RenamerWindow::define());
    _itemModel->add(ServiceManageWindow::define());
    _itemModel->add(SpaceEyeWindow::define());
    _itemList->setModel(_itemModel);
}


void CenterWindow::on_list_doubleClicked(const QModelIndex &index) {
    auto item = (ToolItem*)varToPointer(_itemList->model()->data(index, Qt::UserRole));
    if (item) {
        auto window = item->window();
        window->show();
        window->raise();
        window->activateWindow();
    }
}

