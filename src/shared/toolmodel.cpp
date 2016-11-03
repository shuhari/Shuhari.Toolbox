#include "precompiled.h"
#include "toolmodel.h"
#include "common.h"


ToolModel::ToolModel(QObject *parent)
    : QAbstractListModel(parent) {

}


ToolModel::~ToolModel() {
    qDeleteAll(_items);
    _items.clear();
}


int ToolModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _items.size();
}


QVariant ToolModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    if (row >= 0 && row < _items.size()) {
        auto item = _items[row];
        switch (role) {
        case Qt::DisplayRole:    return item->name();
        case Qt::DecorationRole: return item->icon();
        case Qt::ToolTipRole:    return item->tooltip();
        case Qt::UserRole:       return varFromPointer(item);
        }
    }
    return QVariant();
}


void ToolModel::add(ToolItem* item) {
    _items.append(item);
    int row = _items.size() - 1;
    insertRow(row, QModelIndex());
}
