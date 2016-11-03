#pragma once


#include "precompiled.h"
#include "shared/toolitem.h"
#include "shared/toolwindow.h"


class BookManageWindow : public ToolWindow {
    Q_OBJECT
public:
    BookManageWindow();

    static ToolItem* define();
};
