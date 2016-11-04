#include "precompiled.h"
#include "cleandirconfig.h"


CleanDirConfig::CleanDirConfig(const QString &group, QObject *parent)
    : BaseConfig(group, parent) {
    _directory = define("directory");
}
