#pragma once


#include "precompiled.h"
#include "loglist.h"


class CleanDirThread : public QThread {
    Q_OBJECT
public:
    CleanDirThread(const QString& dirName, QObject* parent = nullptr);

protected:
    virtual void run();

private:
    QDir        _dir;
    QStringList _deleteFilePatterns;

    void cleanDir(const QDir& dir);
    bool isEmptyDir(const QDir& dir);
    void logResult(const QString& path, bool success, const QString& errorString);

signals:
    void log(int level, const QString& msg);
};
