#include "precompiled.h"
#include "renamerconfig.h"


RenamerConfig::RenamerConfig(const QString &group, QObject *parent)
    : BaseConfig(group, parent) {
    _directory = define("directory");
    _originText = define("originText");
    _replaceText = define("replaceText");
    _type = define("type", (int)Type::FixedString);
    _target = define("target", (int)Target::File);
    _options = define("options", (int)Options::DecodeUrl);
}
