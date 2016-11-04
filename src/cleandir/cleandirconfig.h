#pragma once

#include "precompiled.h"
#include "shared/baseconfig.h"


class CleanDirConfig : public BaseConfig {
    Q_OBJECT
public:
    CleanDirConfig(const QString& group, QObject* parent);

    inline QString directory()
        { return _directory->stringValue(); }
    inline void setDirectory(const QString& directory)
        { _directory->setValue(directory); }

private:
    ConfigItem* _directory;
};
