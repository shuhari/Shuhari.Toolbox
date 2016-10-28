#include "precompiled.h"
#include "renamermodel.h"
#include "resources.h"

#define COLUMN_COUNT           3
#define COLUMN_ORIGIN_NAME     0
#define COLUMN_NEW_NAME        1
#define COLUMN_DIRECTORY       2


RenamerModel::RenamerModel(QObject *parent)
    : QAbstractTableModel(parent) {
}


RenamerModel::~RenamerModel() {
    clear();
}


void RenamerModel::clear() {
    int count = _items.size();
    if (count > 0) {
        beginRemoveRows(QModelIndex(), 0, count - 1);
        qDeleteAll(_items);
        _items.clear();
        endRemoveRows();
    }
}


void RenamerModel::add(RenamerItem *item) {
    int index = _items.size();
    beginInsertRows(QModelIndex(), index, index);
    _items.append(item);
    endInsertRows();
}


int RenamerModel::rowCount(const QModelIndex &parent) const {
    return _items.size();
}


int RenamerModel::columnCount(const QModelIndex &parent) const {
    return COLUMN_COUNT;
}


QVariant RenamerModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    if (row >= 0 && row < _items.size()) {
        auto item = _items.at(row);
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
            case COLUMN_ORIGIN_NAME: return item->originName();
            case COLUMN_NEW_NAME: return item->newName();
            case COLUMN_DIRECTORY: return item->directory();
            }
        }
        else if (role == Qt::DecorationRole && index.column() == 0) {
            if (item->type() == RenamerItem::File)
                return qApp->style()->standardIcon(QStyle::SP_FileIcon);
            else
                return qApp->style()->standardIcon(QStyle::SP_DirIcon);
        }
    }
    return QVariant();
}


QVariant RenamerModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case COLUMN_ORIGIN_NAME: return strings::origin_name();
        case COLUMN_NEW_NAME:    return strings::new_name();
        case COLUMN_DIRECTORY:   return strings::directory();
        }
    }
    return QVariant();
}
