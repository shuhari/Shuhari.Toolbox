#include "precompiled.h"
#include "toolitemmodel.h"
#include "toolwindow.h"


ToolItem::ToolItem(const QString& id,
                   const QString& iconName,
                   const QString& name,
                   const QString& tooltip,
                   std::function<ToolWindow*(void)> factory) {
    _id = id;
    _name = name;
    _tooltip = tooltip;
    _icon = QIcon(iconName);
    _factory = factory;
    _window = nullptr;
}


ToolWindow* ToolItem::window() {
    if (!_window) {
        _window = _factory();
        _window->setTool(this);
    }
    return _window;
}


union ToolItemUnion
{
    int       value;
    ToolItem* pointer;
};


int ToolItem::toPointer() {
    ToolItemUnion tiu;
    tiu.pointer = this;
    return tiu.value;
}


ToolItem* ToolItem::fromPointer(int value) {
    ToolItemUnion tiu;
    tiu.value = value;
    return tiu.pointer;
}


ToolItemModel::ToolItemModel()
    : QAbstractListModel() {

}


ToolItemModel::~ToolItemModel() {

}


int ToolItemModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _items.size();
}


QVariant ToolItemModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    if (row >= 0 && row < _items.size()) {
        ToolItem* item = _items[row];
        switch (role) {
        case Qt::DisplayRole: return item->name();
        case Qt::DecorationRole: return item->icon();
        case Qt::ToolTipRole: return item->tooltip();
        case Qt::UserRole: return item->toPointer();
        }
    }
    return QVariant();
}


void ToolItemModel::add(ToolItem* item) {
    _items.append(item);
    int row = _items.size() - 1;
    insertRow(row, QModelIndex());
}
