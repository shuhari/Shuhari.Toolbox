#pragma once

#include "precompiled.h"


class RarCommand
{
public:
    RarCommand(const QString& exePath);

    enum OverrideMode
    {
        DONTCARE = 0,
        ASK = 1,
        OVERWRITE = 2,
        SKIP = 3,
    };

    bool extract(const QString& rarPath, const QString& path, OverrideMode override);

private:
    QString _exePath;
};
