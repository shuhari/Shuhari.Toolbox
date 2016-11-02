#include "precompiled.h"
#include "cleandirconfig.h"


CleanDirConfig::CleanDirConfig(const QString &group, QObject *parent)
    : Config(group, parent) {
    _directory = define("directory");
}
