#pragma once

#include "precompiled.h"


namespace strings {
    inline QString toolbox()          { return qApp->translate("common", "Shuhari's toolbox"); }

    inline QString warning()          { return qApp->translate("diagnostic", "Warning"); }
    inline QString info()             { return qApp->translate("diagnostic", "Information"); }

    inline QString cleandir_name()    { return qApp->translate("cleandir", "Clean Directory"); }
    inline QString cleandir_tooltip() { return qApp->translate("cleandir", "Clean directory for unused files"); }
};

