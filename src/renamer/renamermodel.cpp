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


int RenamerModel::add(RenamerItem *item) {
    int row = _items.size();
    beginInsertRows(QModelIndex(), row, row);
    _items.append(item);
    endInsertRows();
    return row;
}

RenamerItem* RenamerModel::at(int row) {
    Q_ASSERT(row >= 0 && row < _items.size());
    return _items.at(row);
}

int RenamerModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return _items.size();
}


int RenamerModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return COLUMN_COUNT;
}


QVariant RenamerModel::data(const QModelIndex &index, int role) const {
    qDebug() << "data, row=" << index.row() << ", role=" << role << ", size=" << _items.size();
    int row = index.row();
    if (row >= 0 && row < _items.size()) {
        auto item = _items.at(row);
        qDebug() << "item=" << item->originName();
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
        else if (role == Qt::BackgroundColorRole) {
            if (item->state() == RenamerItem::SuccessState)
                return QColor(0, 0x80, 0);
            else if (item->state() == RenamerItem::ErrorState)
                return QColor(0xff, 0, 0);
        }
    }
    return QVariant();
}


QVariant RenamerModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case COLUMN_ORIGIN_NAME: return strings::renamer_origin_name();
        case COLUMN_NEW_NAME:    return strings::renamer_new_name();
        case COLUMN_DIRECTORY:   return strings::browse_label();
        }
    }
    return QVariant();
}


void RenamerModel::setState(int row, RenamerItem::ItemState state) {
    auto item = at(row);
    item->setState(state);
    QModelIndex startCell = index(row, 0);
    QModelIndex endCell = index(row, columnCount() - 1);
    QVector<int> roles;
    roles << Qt::BackgroundColorRole;
    emit dataChanged(startCell, endCell, roles);
}
