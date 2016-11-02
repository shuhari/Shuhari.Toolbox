#include "precompiled.h"
#include "processthread.h"
#include "rarcommand.h"
#include "loglist.h"
#include "resources.h"


ProcessThread::ProcessThread(const QString &dirName, QObject *parent)
    : QThread(parent) {
    _dir = QDir(dirName);
    _cmdPath = "C:\\Program Files\\WinRAR\\RAR.exe";
    _namePatterns << "*.pdf" << "*.epub" << "*.mobi" << "*.azw" << "*.azw4" << "*.azw3";
}


void ProcessThread::run() {
    emit log(L_INFO, strings::processing_directory().arg(_dir.absolutePath()));

    unrar();
    deleteUseless();
    cleanSuffix();
    // self.deleteMultiFiles()
}


void ProcessThread::unrar() {
    QStringList nameFilters;
    nameFilters << "*.rar";
    RarCommand rarcmd(_cmdPath);

    foreach(QFileInfo fileInfo, _dir.entryInfoList(nameFilters, QDir::Files,
                                                   QDir::Name | QDir::IgnoreCase)) {
        QString filePath = fileInfo.absoluteFilePath();
        bool success = rarcmd.extract(filePath, _dir.absolutePath(), RarCommand::OVERWRITE);
        if (success) {
            emit log(L_INFO, strings::decompress_success().arg(filePath));
            deleteFile(fileInfo.absoluteFilePath());
        } else {
            emit log(L_ERROR, strings::decompress_failed().arg(filePath));
        }
    }
}


void ProcessThread::deleteUseless() {
    QStringList nameFilters;
    nameFilters << "foxebook.net.txt";
    foreach(QFileInfo fileInfo, _dir.entryInfoList(nameFilters, QDir::Files,
                                                   QDir::Name | QDir::IgnoreCase))
    {
        deleteFile(fileInfo.absoluteFilePath());
    }
}


void ProcessThread::deleteFile(const QString &path) {
    QFile file(path);
    if (file.remove())
        emit log(L_INFO, strings::delete_success().arg(path));
    else
        emit log(L_ERROR, strings::delete_failed().arg(path).arg(file.errorString()));
}


void ProcessThread::cleanSuffix() {
    QRegExp re("(\\.[0-9A-Z]{10})\\.(pdf|epub|mobi|azw4|azw3|azw)$");
    foreach (QFileInfo fileInfo, _dir.entryInfoList(_namePatterns, QDir::Files,
                                                    QDir::Name | QDir::IgnoreCase)) {
        QString fileName = fileInfo.fileName();
        if (re.indexIn(fileName, 0) >= 0) {
            QString match = re.cap(1);
            QString newName = fileName;
            newName.replace(match, "");
            if (newName != fileName) {
                QString newPath = QDir(fileInfo.absolutePath()).absoluteFilePath(newName);
                if (QFile(fileInfo.absoluteFilePath()).rename(newPath))
                    emit log(L_INFO, strings::rename_success().arg(fileName).arg(newName));
                else
                    emit log(L_ERROR, strings::rename_failed().arg(fileName).arg(newName));
            }
        }
    }
}

