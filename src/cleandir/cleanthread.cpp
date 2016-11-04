#include "precompiled.h"
#include "cleanthread.h"
#include "resources.h"
#include "shared/loglist.h"


CleanThread::CleanThread(const QString &dirName, QObject *parent)
    : QThread(parent) {
    _dir = QDir(dirName);
    _deletePatterns << "thumbs.db";
}


void CleanThread::run() {
    cleanDir(_dir);
}


void CleanThread::cleanDir(const QDir &dir) {
    emit log(LogInfo, strings::prompt_processing_directory().arg(dir.absolutePath()));

    foreach(QFileInfo dirInfo, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot,
                                           QDir::Name | QDir::IgnoreCase))  {
        QDir subdir(dirInfo.absoluteFilePath());
        cleanDir(subdir);
    }

    foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files,
                                                  QDir::Name | QDir::IgnoreCase))  {
        QString filePath = fileInfo.absoluteFilePath();
        if (QDir::match(_deletePatterns, fileInfo.fileName()))  {
            QFile file(filePath);
            bool success = file.remove();
            logResult(filePath, success, file.errorString());
        }
    }

    if (isEmptyDir(dir))
    {
        bool success = dir.rmdir(".");
        logResult(dir.absolutePath(), success, "?");
    }
}


void CleanThread::logResult(const QString &path, bool success, const QString &errorString) {
    QString successFormat = strings::prompt_delete_success(),
            failedFormat = strings::prompt_delete_failed();
    QString msg;
    if (success) {
        msg = successFormat.arg(path);
        emit log(LogInfo, msg);
    } else {
        msg = failedFormat.arg(path).arg(errorString);
        emit log(LogError, msg);
    }
}


bool CleanThread::isEmptyDir(const QDir& dir) {
    auto entries = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    return entries.size() == 0;
}
