#pragma once


#include "precompiled.h"
#include "shared/toolitem.h"
#include "shared/toolwindow.h"


class RenamerWindow : public ToolWindow {
    Q_OBJECT
public:
    RenamerWindow();

    static ToolItem* define();
};
