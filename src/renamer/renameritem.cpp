#include "precompiled.h"
#include "renameritem.h"


RenamerItem::RenamerItem() {

}


RenamerItem::RenamerItem(ItemType type, const QString &originName,
                         const QString &newName, const QString &directory) {
    _type = type;
    _originName = originName;
    _newName = newName;
    _directory = directory;
}


RenamerItem::RenamerItem(const RenamerItem &src) {
    copy(src);
}


RenamerItem& RenamerItem::operator =(const RenamerItem& src) {
    copy(src);
    return *this;
}


void RenamerItem::copy(const RenamerItem &src) {
    _type = src._type;
    _originName = src._originName;
    _newName = src._newName;
    _directory = src._directory;
}
