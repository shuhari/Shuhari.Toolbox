#pragma once

#include "precompiled.h"


class RenamerItem {
public:
    enum ItemType { File = 1, Directory = 2 };
    enum ItemState { PendingState = 0, SuccessState = 1, ErrorState = 2 };

    RenamerItem(ItemType type, const QString originName,
                const QString& newName, const QString& directory);

    inline ItemType type()                { return _type; }
    inline ItemState state()              { return _state; }
    inline QString originName()           { return _originName; }
    inline QString newName()              { return _newName; }
    inline QString directory()            { return _directory; }

    inline void setState(ItemState state) { _state = state; }

private:
    ItemType     _type;
    ItemState    _state;
    QString      _originName;
    QString      _newName;
    QString      _directory;
};
