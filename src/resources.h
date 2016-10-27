#pragma once

#include "precompiled.h"


namespace strings {
    QString toolbox()          { return qApp->translate("", "Shuhari's toolbox"); }

    QString cleandir_name()    { return qApp->translate("", "Directory Clean"); }
    QString cleandir_tooltip() { return qApp->translate("", "Cleaning directory"); }

    QString bookman_name()     { return qApp->translate("", "Book Manage"); }
    QString bookman_tooltip()  { return qApp->translate("", "Manage downloaded books"); }

    QString encdec_name()      { return qApp->translate("", "Encode/Decode"); }
    QString encdec_tooltip()   { return qApp->translate("", "Encode/Decode"); }

    QString renamer_name()     { return qApp->translate("", "File Renamer"); }
    QString renamer_tooltip()  { return qApp->translate("", "Rename file/directory"); }

    QString servman_name()     { return qApp->translate("", "Service Management"); }
    QString servman_tooltip()  { return qApp->translate("", "Manage system services"); }

};

