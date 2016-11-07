#pragma once

#include "precompiled.h"


class RarCommand {
public:
    RarCommand(const QString& exePath);

    enum OverwriteMode {
        DontCare = 0,
        Ask = 1,
        Overwrite = 2,
        Skip = 3,
    };

    bool extract(const QString& rarPath, const QString& path, OverwriteMode override);

private:
    QString _exePath;
};
