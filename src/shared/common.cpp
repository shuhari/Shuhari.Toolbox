#include "precompiled.h"
#include "common.h"

union PointerUnion
{
    qint64       value;
    void*        pointer;
};


QVariant varFromPointer(void* ptr) {
    PointerUnion pu;
    pu.pointer = ptr;
    return QVariant(pu.value);
}


void* varToPointer(QVariant v) {
    PointerUnion pu;
    pu.value = v.toLongLong();
    return pu.pointer;
}
