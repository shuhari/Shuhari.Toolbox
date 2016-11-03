#pragma once

#include "precompiled.h"


namespace strings {
    inline QString toolbox()          { return qApp->translate("common", "Shuhari's toolbox"); }

    inline QString warning()          { return qApp->translate("diagnostic", "Warning"); }
    inline QString info()             { return qApp->translate("diagnostic", "Information"); }

    inline QString browse_label()     { return qApp->translate("browse", "Directory"); }
    inline QString browse_title()     { return qApp->translate("browse", "Bowse for directory"); }
    inline QString browse_tooltip()   { return qApp->translate("browse", "Select an existing directory"); }

    inline QString bookman_name()    { return qApp->translate("bookman", "Book Management"); }
    inline QString bookman_tooltip() { return qApp->translate("bookman", "Manage downloaded books"); }

    inline QString cleandir_name()    { return qApp->translate("cleandir", "Clean Directory"); }
    inline QString cleandir_tooltip() { return qApp->translate("cleandir", "Clean directory for unused files"); }
    inline QString cleandir_clean()   { return qApp->translate("cleandir", "Clean"); }

    inline QString encode_name()      { return qApp->translate("encode", "Encode/Decode"); }
    inline QString encode_tooltip()   { return qApp->translate("encode", "Encode and decode"); }

    inline QString renamer_name()     { return qApp->translate("renamer", "File Renamer"); }
    inline QString renamer_tooltip()  { return qApp->translate("renamer", "Rename directories and files"); }

    inline QString servman_name()     { return qApp->translate("servman", "Service Management"); }
    inline QString servman_tooltip()  { return qApp->translate("servman", "Manage system services"); }

    inline QString prompt_invalid_directory()     { return qApp->translate("prompt", "The selected directory is invalid."); }
};

