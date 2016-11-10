#pragma once

#include "precompiled.h"


class SpaceItem {
public:
    enum ItemType { File = 1, Dir = 2 };
    SpaceItem(ItemType type, const QString& name, long size, SpaceItem* parent = nullptr);
    ~SpaceItem();

    inline SpaceItem* parent()        { return _parent; }
    inline QString name()             { return _name; }
    inline int childCount()           { return _children.size(); }
    inline int row()                  { return _row; }
    inline ItemType type()            { return _type; }
    inline long size()                { return _size; }
    inline long childrenSize()        { return _childrenSize; }

    inline void setRow(int row)       { _row = row; }

    SpaceItem* childAt(int row);
    void append(SpaceItem* child);
    int indexOf(SpaceItem* child);
    QString localPercentString();
    QString globalPercentString();

private:
    ItemType          _type;
    SpaceItem*        _parent;
    int               _row;
    QString           _name;
    QList<SpaceItem*> _children;
    long              _size;
    long              _childrenSize;

    void              updateSize(long size);
    SpaceItem*        getRoot();
};
