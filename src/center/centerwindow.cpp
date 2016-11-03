#include "precompiled.h"
#include "centerwindow.h"
#include "resources.h"
#include "shared/common.h"
#include "cleandir/cleandirwindow.h"


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
    _itemList->setModel(_itemModel);
    /*
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
                                []() { return new ServiceManageWindow(); }));*/
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

