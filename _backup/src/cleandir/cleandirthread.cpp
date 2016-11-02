#include "precompiled.h"
#include "cleandirthread.h"
#include "resources.h"


CleanDirThread::CleanDirThread(const QString& dirName, QObject *parent)
    : QThread(parent)  {
    _dir = QDir(dirName);
    _deleteFilePatterns << "thumbs.db";
}


void CleanDirThread::run() {
    cleanDir(_dir);
}


void CleanDirThread::cleanDir(const QDir &dir) {
    emit log(L_INFO, strings::processing_directory().arg(dir.absolutePath()));

    foreach(QFileInfo dirInfo, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot,
                                           QDir::Name | QDir::IgnoreCase))  {
        QDir subdir(dirInfo.absoluteFilePath());
        cleanDir(subdir);
    }

    foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files,
                                                  QDir::Name | QDir::IgnoreCase))  {
        QString filePath = fileInfo.absoluteFilePath();
        if (QDir::match(_deleteFilePatterns, fileInfo.fileName()))  {
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


void CleanDirThread::logResult(const QString &path, bool success, const QString &errorString) {
    QString successFormat = strings::delete_success(),
            failedFormat = strings::delete_failed();
    QString msg;
    if (success) {
        msg = successFormat.arg(path);
        emit log(L_INFO, msg);
    } else {
        msg = failedFormat.arg(path).arg(errorString);
        emit log(L_ERROR, msg);
    }
}


bool CleanDirThread::isEmptyDir(const QDir& dir) {
    auto entries = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    return entries.size() == 0;
}
