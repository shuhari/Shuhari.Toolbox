#pragma once


#include "precompiled.h"
#include "shared/toolitem.h"
#include "shared/toolwindow.h"


class ServiceManageWindow : public ToolWindow {
    Q_OBJECT
public:
    ServiceManageWindow();

    static ToolItem* define();
};
