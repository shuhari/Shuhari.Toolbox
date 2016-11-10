#pragma once

#include "precompiled.h"
#include "shared/toolitem.h"
#include "shared/toolwindow.h"


class SpaceEyeWindow : public ToolWindow {
    Q_OBJECT
public:
    SpaceEyeWindow();

    static ToolItem* define();

protected:
    virtual void createChildren();
};
