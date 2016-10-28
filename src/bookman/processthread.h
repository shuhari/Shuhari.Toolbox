#pragma once

#include "precompiled.h"

class ProcessThread : public QThread {
    Q_OBJECT
public:
    ProcessThread(const QString& dirName, QObject* parent = nullptr);

protected:
    virtual void run();

private:
    QDir           _dir;
    QString        _cmdPath;
    QStringList    _namePatterns;

    void           unrar();
    void           deleteUseless();
    void           cleanSuffix();
    void           deleteFile(const QString& path);

signals:
    void            log(int level, const QString& msg);
};
