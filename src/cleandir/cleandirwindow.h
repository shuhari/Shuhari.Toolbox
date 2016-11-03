#pragma once


#include "precompiled.h"
#include "shared/toolitem.h"
#include "shared/toolwindow.h"


class CleanDirWindow : public ToolWindow {
    Q_OBJECT
public:
    CleanDirWindow();

    static ToolItem* define();
};
