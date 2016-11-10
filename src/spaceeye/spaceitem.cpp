#include "precompiled.h"
#include "spaceitem.h"


SpaceItem::SpaceItem(ItemType type, const QString &name, long size, SpaceItem *parent) {
    _type = type;
    _name = name;
    _parent = parent;
    _size = 0;
    _childrenSize = 0;

    updateSize(size);
}


SpaceItem::~SpaceItem() {
    qDeleteAll(_children);
    _children.clear();
}


SpaceItem* SpaceItem::childAt(int row) {
    Q_ASSERT(row >= 0 && row < _children.size());
    return _children.at(row);
}


void SpaceItem::append(SpaceItem *child) {
    _children.append(child);
    child->setRow(_children.size() - 1);
}


int SpaceItem::indexOf(SpaceItem *child) {
    return _children.indexOf(child);
}


void SpaceItem::updateSize(long size) {
    if (_type == ItemType::File) {
        _size = size;
    } else {
        _childrenSize += size;
    }
    if (_parent)
        _parent->updateSize(size);
}


SpaceItem* SpaceItem::getRoot() {
    SpaceItem* current = this;
    while (current->parent()) {
        current = current->parent();
    }
    return current;
}


QString SpaceItem::localPercentString() {
    if (!parent())
        return "";
    long thisSize = (_type == ItemType::Dir) ? childrenSize() : _size;
    return QString("%1/%2").arg(thisSize).arg(parent()->childrenSize());
}


QString SpaceItem::globalPercentString() {
    if (!parent())
        return "";
    auto root = getRoot();
    long thisSize = (_type == ItemType::Dir) ? childrenSize() : _size;
    return QString("%1/%2").arg(thisSize).arg(root->childrenSize());
}
