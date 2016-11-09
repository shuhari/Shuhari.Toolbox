#pragma once

#include "precompiled.h"


namespace strings {
    inline QString toolbox()          { return qApp->translate("common", "Shuhari's toolbox"); }
    inline QString copy()             { return qApp->translate("common", "Copy"); }
    inline QString clear()            { return qApp->translate("common", "Clear"); }
    inline QString process()          { return qApp->translate("common", "Process"); }
    inline QString type()             { return qApp->translate("common", "Type"); }
    inline QString direction()        { return qApp->translate("common", "Direction"); }
    inline QString input()            { return qApp->translate("common", "Input"); }
    inline QString output()           { return qApp->translate("common", "Output"); }
    inline QString codec()            { return qApp->translate("common", "Codec"); }
    inline QString swap()             { return qApp->translate("common", "Swap"); }

    inline QString debug()            { return qApp->translate("diagnostic", "Debug"); }
    inline QString error()            { return qApp->translate("diagnostic", "Error"); }
    inline QString info()             { return qApp->translate("diagnostic", "Information"); }
    inline QString warning()          { return qApp->translate("diagnostic", "Warning"); }

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
    inline QString encode_encode()    { return qApp->translate("encode", "Encode"); }
    inline QString encode_decode()    { return qApp->translate("encode", "Decode"); }

    inline QString renamer_name()     { return qApp->translate("renamer", "File Renamer"); }
    inline QString renamer_tooltip()  { return qApp->translate("renamer", "Rename directories and files"); }

    inline QString servman_name()     { return qApp->translate("servman", "Service Management"); }
    inline QString servman_tooltip()  { return qApp->translate("servman", "Manage system services"); }

    inline QString prompt_invalid_directory()     { return qApp->translate("prompt", "The selected directory is invalid."); }
    inline QString prompt_processing_directory()  { return qApp->translate("prompt", "Processing directory: %1"); }
    inline QString prompt_process_finished()      { return qApp->translate("prompt", "Process finished"); }
    inline QString prompt_delete_success()        { return qApp->translate("prompt", "Delete file/directory [%1] success"); }
    inline QString prompt_delete_failed()         { return qApp->translate("prompt", "Delete file/directory [%1] failed: %2"); }
    inline QString prompt_decompress_success()    { return qApp->translate("prompt", "Decompress [%1] success"); }
    inline QString prompt_decompress_failed()     { return qApp->translate("prompt", "Decompress [%1] failed"); }
    inline QString prompt_rename_success()        { return qApp->translate("prompt", "Rename [%1] => [%2] success"); }
    inline QString prompt_rename_failed()         { return qApp->translate("prompt", "Rename [%1] => [%2] failed"); }
};

