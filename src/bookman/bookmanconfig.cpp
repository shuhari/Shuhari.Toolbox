#include "precompiled.h"
#include "bookmanconfig.h"


BookManageConfig::BookManageConfig(const QString &group, QObject *parent)
    : BaseConfig(group, parent) {
    _directory = define("directory");
}
