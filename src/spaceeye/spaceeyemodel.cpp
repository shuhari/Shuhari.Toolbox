#include "precompiled.h"
#include "spaceeyemodel.h"


SpaceEyeModel::SpaceEyeModel(QObject *parent)
    : QAbstractItemModel(parent) {
    _root = nullptr;
}


SpaceEyeModel::~SpaceEyeModel() {
    clear();
}


Qt::ItemFlags SpaceEyeModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return 0;
    return QAbstractItemModel::flags(index);
}


void SpaceEyeModel::clear() {
    if (_root) {
        delete _root;
        _root = nullptr;
    }
}


void SpaceEyeModel::setRoot(const QString &dirName) {
    clear();
    _root = new SpaceItem(SpaceItem::Dir, dirName, 0, nullptr);
}


int SpaceEyeModel::columnCount(const QModelIndex &parent) const {
    return 3;
}


int SpaceEyeModel::rowCount(const QModelIndex &parent) const {
    if (parent.column() > 0)
        return 0;

    SpaceItem* item = parent.isValid() ?
                (SpaceItem*)parent.internalPointer() : _root;
    return item->childCount();
}


QVariant SpaceEyeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && section >= 0 && section < 3) {
        if (role == Qt::DisplayRole) {
            switch (section) {
            case 0: return "Name";
            case 1: return "Size in parent";
            case 2: return "Size total";
            }
        }
    }
    return QVariant();
}


QModelIndex SpaceEyeModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    SpaceItem* parentItem = parent.isValid() ?
                (SpaceItem*)parent.internalPointer() : _root;
    if (parentItem) {
        SpaceItem* child = parentItem->childAt(row);
        return child ? createIndex(row, column, child) : QModelIndex();
    }
    return QModelIndex();
}


QModelIndex SpaceEyeModel::parent(const QModelIndex &child) const {
    if (!child.isValid())
        return QModelIndex();

    SpaceItem* childItem = (SpaceItem*)child.internalPointer();
    if (childItem) {
        SpaceItem* parentItem = childItem->parent();
        if (parentItem) {
            if (parentItem == _root)
                return QModelIndex();
            else
                return createIndex(parentItem->row(), 0, parentItem);
        }
    }
    return QModelIndex();
}


QVariant SpaceEyeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    SpaceItem* item = (SpaceItem*)index.internalPointer();
    if (!item)
        return QVariant();

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0: return item->name();
        case 1: return item->localPercentString();
        case 2: return item->globalPercentString();
        }
    } else if (role == Qt::DecorationRole && index.column() == 0) {
        if (item->type() == SpaceItem::Dir)
            return qApp->style()->standardIcon(QStyle::SP_DirIcon);
        else
            return qApp->style()->standardIcon(QStyle::SP_FileIcon);
    }
    return QVariant();
}


