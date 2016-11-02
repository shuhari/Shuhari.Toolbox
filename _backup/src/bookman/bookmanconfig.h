#include "precompiled.h"
#include "config.h"


class BookManageConfig : public Config {
    Q_OBJECT
public:
    BookManageConfig(const QString& group, QObject* parent);

    inline QString directory()
        { return _directory->value().toString(); }
    inline void setDirectory(const QString& dir)
        { _directory->setValue(dir); }

private:
    ConfigItem* _directory;
};
