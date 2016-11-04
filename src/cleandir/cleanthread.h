#pragma once

#include "precompiled.h"


class CleanThread : public QThread {
    Q_OBJECT
public:
    CleanThread(const QString& dir, QObject* parent = nullptr);

protected:
    virtual void run();

private:
    QDir             _dir;
    QStringList      _deletePatterns;

    void             cleanDir(const QDir& dir);
    bool             isEmptyDir(const QDir& dir);
    void             logResult(const QString& dirName, bool success, const QString& errorString);

signals:
    void             log(int level, const QString& msg);
};
