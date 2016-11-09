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
    inline QString file()             { return qApp->translate("common", "File"); }
    inline QString directory()        { return qApp->translate("common", "Directory"); }
    inline QString target()           { return qApp->translate("common", "Target"); }
    inline QString options()          { return qApp->translate("common", "Options"); }
    inline QString select()           { return qApp->translate("common", "Select"); }
    inline QString all()              { return qApp->translate("common", "All"); }
    inline QString none()             { return qApp->translate("common", "None"); }
    inline QString revert()           { return qApp->translate("common", "Revert"); }
    inline QString find()             { return qApp->translate("common", "Find"); }
    inline QString apply()            { return qApp->translate("common", "Apply"); }
    inline QString refresh()          { return qApp->translate("common", "Refresh"); }
    inline QString unknown()          { return qApp->translate("common", "Unknown"); }
    inline QString name()             { return qApp->translate("common", "Name"); }
    inline QString displayName()      { return qApp->translate("common", "Display Name"); }
    inline QString description()      { return qApp->translate("common", "Description"); }
    inline QString startType()        { return qApp->translate("common", "Start Type"); }
    inline QString loginAs()          { return qApp->translate("common", "Login As"); }
    inline QString status()           { return qApp->translate("common", "Status"); }

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

    inline QString renamer_name()          { return qApp->translate("renamer", "File Renamer"); }
    inline QString renamer_tooltip()       { return qApp->translate("renamer", "Rename directories and files"); }
    inline QString renamer_origin_name()   { return qApp->translate("renamer", "Original Name"); }
    inline QString renamer_new_name()      { return qApp->translate("renamer", "New Name"); }
    inline QString renamer_type_fixed()    { return qApp->translate("renamer", "Fixed String"); }
    inline QString renamer_type_wildcard() { return qApp->translate("renamer", "Wildcard"); }
    inline QString renamer_type_regex()    { return qApp->translate("renamer", "Regular Expressions"); }
    inline QString renamer_option_recursive()    { return qApp->translate("renamer", "Recursive"); }
    inline QString renamer_option_decodeUrl()    { return qApp->translate("renamer", "Decode Url"); }

    inline QString servman_name()     { return qApp->translate("servman", "Service Management"); }
    inline QString servman_tooltip()  { return qApp->translate("servman", "Manage system services"); }
    inline QString servman_start()    { return qApp->translate("servman", "Start"); }
    inline QString servman_stop()     { return qApp->translate("servman", "Stop"); }
    inline QString servman_pause()     { return qApp->translate("servman", "Pause"); }
    inline QString servman_autoStart()      { return qApp->translate("servman", "Automatic"); }
    inline QString servman_demandStart()    { return qApp->translate("servman", "Demand"); }
    inline QString servman_disabled()       { return qApp->translate("servman", "Disabled"); }
    inline QString servman_type_fs()        { return qApp->translate("servman", "FS Driver"); }
    inline QString servman_type_kernel()        { return qApp->translate("servman", "Kernel Driver"); }
    inline QString servman_type_win32own()      { return qApp->translate("servman", "Win32 Own Process"); }
    inline QString servman_type_win32share()    { return qApp->translate("servman", "Win32 Share Process"); }
    inline QString servman_startType_auto()    { return qApp->translate("servman", "Automatic"); }
    inline QString servman_startType_boot()    { return qApp->translate("servman", "Boot"); }
    inline QString servman_startType_demand()  { return qApp->translate("servman", "Demand"); }
    inline QString servman_startType_disabled() { return qApp->translate("servman", "Disabled"); }
    inline QString servman_startType_sys() { return qApp->translate("servman", "System"); }
    inline QString servman_state_continuePending() { return qApp->translate("servman", "Continue Pending"); }
    inline QString servman_state_pausePending() { return qApp->translate("servman", "Pause Pending"); }
    inline QString servman_state_stopped() { return qApp->translate("servman", "Stopped"); }
    inline QString servman_state_running() { return qApp->translate("servman", "Running"); }
    inline QString servman_state_startPending() { return qApp->translate("servman", "Start Pending"); }
    inline QString servman_state_paused() { return qApp->translate("servman", "Paused"); }

    inline QString prompt_invalid_directory()     { return qApp->translate("prompt", "The selected directory is invalid."); }
    inline QString prompt_processing_directory()  { return qApp->translate("prompt", "Processing directory: %1"); }
    inline QString prompt_process_finished()      { return qApp->translate("prompt", "Process finished"); }
    inline QString prompt_delete_success()        { return qApp->translate("prompt", "Delete file/directory [%1] success"); }
    inline QString prompt_delete_failed()         { return qApp->translate("prompt", "Delete file/directory [%1] failed: %2"); }
    inline QString prompt_decompress_success()    { return qApp->translate("prompt", "Decompress [%1] success"); }
    inline QString prompt_decompress_failed()     { return qApp->translate("prompt", "Decompress [%1] failed"); }
    inline QString prompt_rename_success()        { return qApp->translate("prompt", "Rename [%1] => [%2] success"); }
    inline QString prompt_rename_failed()         { return qApp->translate("prompt", "Rename [%1] => [%2] failed"); }
    inline QString prompt_invalid_originText()    { return qApp->translate("prompt", "Orign Text is invalid."); }
    inline QString prompt_invalid_target()        { return qApp->translate("prompt", "Target is invalid."); }
    inline QString prompt_setStartType_failed()   { return qApp->translate("prompt", "Set StartType failed."); }
    inline QString prompt_openManager_failed()    { return qApp->translate("prompt", "Open Service Manager failed."); }
    inline QString prompt_openService_failed()    { return qApp->translate("prompt", "Open Service failed."); }
};

