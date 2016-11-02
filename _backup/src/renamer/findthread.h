#pragma once

#include "precompiled.h"
#include "renamerconfig.h"
#include "renameritem.h"


class FindThread : public QThread
{
    Q_OBJECT
public:
    FindThread(RenamerConfig* config, QObject* parent = nullptr);

protected:
    virtual void run();

signals:
    void log(int level, const QString& msg);
    void found(RenamerItem* item);

private:
    RenamerConfig* _config;

    void findDir(const QDir& dir);
    QString getNewName(const QString& name);
};
