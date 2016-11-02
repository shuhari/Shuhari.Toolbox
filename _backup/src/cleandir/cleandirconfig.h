#pragma once

#include "precompiled.h"
#include "config.h"


class CleanDirConfig : public Config {
    Q_OBJECT
public:
    CleanDirConfig(const QString& group, QObject* parent);

    inline QString directory()
        { return _directory->value().toString(); }
    inline void setDirectory(const QString& dir)
        { _directory->setValue(dir); }

private:
    ConfigItem* _directory;
};
