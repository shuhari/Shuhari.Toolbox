#pragma once

#include "precompiled.h"


namespace strings {
    inline QString toolbox()          { return qApp->translate("", "Shuhari's toolbox"); }
    inline QString directory()        { return qApp->translate("", "Directory"); }
    inline QString file()             { return qApp->translate("", "File"); }
    inline QString clean()            { return qApp->translate("", "Clean"); }
    inline QString copy()             { return qApp->translate("", "Copy"); }
    inline QString clear()            { return qApp->translate("", "Clear"); }
    inline QString debug()            { return qApp->translate("", "Debug"); }
    inline QString info()             { return qApp->translate("", "Information"); }
    inline QString warning()          { return qApp->translate("", "Warning"); }
    inline QString error()            { return qApp->translate("", "Error"); }
    inline QString process()          { return qApp->translate("", "Process"); }
    inline QString input()            { return qApp->translate("", "Input"); }
    inline QString output()           { return qApp->translate("", "Output"); }
    inline QString type()             { return qApp->translate("", "Type"); }
    inline QString direction()        { return qApp->translate("", "Direction"); }
    inline QString codec()            { return qApp->translate("", "Codec"); }
    inline QString encode()           { return qApp->translate("", "Encode"); }
    inline QString decode()           { return qApp->translate("", "Decode"); }
    inline QString swap()             { return qApp->translate("", "Swap"); }
    inline QString target()           { return qApp->translate("", "Target"); }
    inline QString options()          { return qApp->translate("", "Options"); }
    inline QString select()           { return qApp->translate("", "Select"); }
    inline QString find()             { return qApp->translate("", "Find"); }
    inline QString apply()            { return qApp->translate("", "Apply"); }
    inline QString all()              { return qApp->translate("", "All"); }
    inline QString none()             { return qApp->translate("", "None"); }
    inline QString revert()           { return qApp->translate("", "Revert"); }
    inline QString refresh()          { return qApp->translate("", "Refresh"); }
    inline QString start()            { return qApp->translate("", "Start"); }
    inline QString stop()             { return qApp->translate("", "Stop"); }
    inline QString pause()            { return qApp->translate("", "Pause"); }
    inline QString service_autoStart()    { return qApp->translate("", "Automatic"); }
    inline QString service_demandStart()  { return qApp->translate("", "Demand"); }
    inline QString service_disabled()     { return qApp->translate("", "Disabled"); }

    inline QString origin_text()      { return qApp->translate("", "Original text"); }
    inline QString replace_with()     { return qApp->translate("", "Replace with"); }
    inline QString fixed_string()     { return qApp->translate("", "Fixed string"); }
    inline QString wildcard()         { return qApp->translate("", "Wildcard"); }
    inline QString regex()            { return qApp->translate("", "Regular expressions"); }
    inline QString recursive()        { return qApp->translate("", "Recursive"); }
    inline QString decode_url()       { return qApp->translate("", "Decode url"); }
    inline QString origin_name()      { return qApp->translate("", "Original name"); }
    inline QString new_name()         { return qApp->translate("", "New name"); }

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

    inline QString processing_directory() { return qApp->translate("", "Processing directory: %1"); }
    inline QString process_finished() { return qApp->translate("", "Process finished"); }
    inline QString delete_success()   { return qApp->translate("", "Delete file/directory [%1] success"); }
    inline QString delete_failed()    { return qApp->translate("", "Delete file/directory [%1] failed: %2"); }
    inline QString directory_invalid()    { return qApp->translate("", "Please select an existing directory"); }
    inline QString decompress_success()   { return qApp->translate("", "Decompress file success: %1"); }
    inline QString decompress_failed()    { return qApp->translate("", "Decompress failed: %1"); }
    inline QString rename_success()   { return qApp->translate("", "Rename %1 => %2 OK"); }
    inline QString rename_failed()    { return qApp->translate("", "Rename %1 => %2 Failed"); }
    inline QString rename_originText_invalid()   { return qApp->translate("", "Please input original text to replace"); }
    inline QString rename_target_invalid() { return qApp->translate("", "Please select at least one targets (file or directory)."); }
};

