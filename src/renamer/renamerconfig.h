#pragma once

#include "precompiled.h"
#include "config.h"


class RenamerConfig : public Config {
    Q_OBJECT
public:
    RenamerConfig(const QString& group, QObject* parent);

    enum Type {
        FixedString = 1,
        Wildcard = 2,
        Regex = 3
    };
    enum Target {
        File = 0x1,
        Directory = 0x2,
    };
    enum Options {
        Recursive = 0x1,
        DecodeUrl = 0x2,
    };

    inline QString directory()       { return _directory->stringValue(); }
    inline QString originText()      { return _originText->stringValue(); }
    inline QString replaceText()     { return _replaceText->stringValue(); }
    inline Type type()               { return (Type)_type->intValue(); }
    inline int target()              { return (Target)_target->intValue(); }
    inline int options()             { return (Options)_options->intValue(); }

    inline void setDirectory(const QString& dir)    { _directory->setValue(dir); }
    inline void setOriginText(const QString& text)   { _originText->setValue(text); }
    inline void setReplaceText(const QString& text)  { _replaceText->setValue(text); }
    inline void setType(Type type)                   { _type->setValue((int)type); }
    inline void setTarget(int target)                { _target->setValue(target); }
    inline void setOptions(int options)              { _options->setValue(options); }

private:
    ConfigItem* _directory;
    ConfigItem* _originText;
    ConfigItem* _replaceText;
    ConfigItem* _type;
    ConfigItem* _target;
    ConfigItem* _options;
};
