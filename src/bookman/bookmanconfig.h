#pragma once

#include "precompiled.h"
#include "shared/baseconfig.h"


class BookManageConfig : public BaseConfig {
    Q_OBJECT
public:
    BookManageConfig(const QString& group, QObject* parent = nullptr);

    inline QString directory()
        { return _directory->stringValue(); }
    inline void setDirectory(const QString& directory)
        { _directory->setValue(directory); }

private:
    ConfigItem* _directory;
};
