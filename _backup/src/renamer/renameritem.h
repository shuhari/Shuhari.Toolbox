#pragma once

#include "precompiled.h"


class RenamerItem {
public:
    enum ItemType { File = 1, Directory = 2 };
    enum State { PendingState = 0, SuccessState = 1, ErrorState = 2 };

    RenamerItem();
    RenamerItem(ItemType type, const QString& originName, const QString& newName, const QString& directory);
    RenamerItem(const RenamerItem& src);
    RenamerItem& operator=(const RenamerItem& src);

    inline ItemType type()              { return _type; }
    inline QString originName()         { return _originName; }
    inline QString newName()            { return _newName; }
    inline QString directory()          { return _directory; }
    inline State   state()              { return _state; }

    inline void    setState(State state) { _state = state; }

private:
    ItemType _type;
    QString  _originName;
    QString  _newName;
    QString  _directory;
    State    _state;

    void     copy(const RenamerItem& src);
};

