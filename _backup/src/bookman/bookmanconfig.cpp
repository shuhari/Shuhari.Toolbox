#include "precompiled.h"
#include "bookmanconfig.h"


BookManageConfig::BookManageConfig(const QString &group, QObject *parent)
    : Config(group, parent) {
    _directory = define("directory");
}
