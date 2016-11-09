#include "precompiled.h"
#include "renameritem.h"


RenamerItem::RenamerItem(ItemType type, const QString originName,
                         const QString &newName, const QString& directory) {
    _type = type;
    _state = PendingState;
    _originName = originName;
    _newName = newName;
    _directory = directory;
}
