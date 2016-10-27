#pragma once

#include "precompiled.h"


namespace strings {
    inline QString toolbox()          { return qApp->translate("", "Shuhari's toolbox"); }
    inline QString directory()        { return qApp->translate("", "Directory"); }
    inline QString clean()            { return qApp->translate("", "clean"); }

    inline QString cleandir_name()    { return qApp->translate("", "Directory Clean"); }
    inline QString cleandir_tooltip() { return qApp->translate("", "Cleaning directory"); }

    inline QString bookman_name()     { return qApp->translate("", "Book Manage"); }
    inline QString bookman_tooltip()  { return qApp->translate("", "Manage downloaded books"); }

    inline QString encdec_name()      { return qApp->translate("", "Encode/Decode"); }
    inline QString encdec_tooltip()   { return qApp->translate("", "Encode/Decode"); }

    inline QString renamer_name()     { return qApp->translate("", "File Renamer"); }
    inline QString renamer_tooltip()  { return qApp->translate("", "Rename file/directory"); }

    inline QString servman_name()     { return qApp->translate("", "Service Management"); }
    inline QString servman_tooltip()  { return qApp->translate("", "Manage system services"); }

    inline QString browse_text()      { return qApp->translate("", "Browse..."); }
    inline QString browse_title()     { return qApp->translate("", "Choose an existing directory"); }
};

