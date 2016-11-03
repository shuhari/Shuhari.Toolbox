#pragma once


#include "precompiled.h"
#include "shared/toolitem.h"
#include "shared/toolwindow.h"


class EncodeWindow : public ToolWindow {
    Q_OBJECT
public:
    EncodeWindow();

    static ToolItem* define();
};
