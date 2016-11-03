#pragma once

#include "precompiled.h"


/* Convert between QVariant and pointer */
QVariant varFromPointer(void* ptr);
void* varToPointer(QVariant v);
