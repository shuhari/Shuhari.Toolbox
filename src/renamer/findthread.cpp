#include "precompiled.h"
#include "findthread.h"
#include "resources.h"
#include "loglist.h"


FindThread::FindThread(RenamerConfig *config, QObject *parent)
    : QThread(parent) {
    _config = config;
}


void FindThread::run() {
    findDir(QDir(_config->directory()));
}


void FindThread::findDir(const QDir &dir) {
    int options = _config->options();
    int target = _config->target();
    emit log(L_INFO, strings::processing_directory().arg(dir.absolutePath()));

    if ((options & RenamerConfig::Recursive) == RenamerConfig::Recursive) {
        foreach (QFileInfo di, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot,
                                                 QDir::Name | QDir::IgnoreCase)) {
            findDir(QDir(di.absoluteFilePath()));
        }
    }

    if ((target & RenamerConfig::File) == RenamerConfig::File) {
        foreach (QFileInfo fi, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot,
                                                 QDir::Name | QDir::IgnoreCase)) {
            QString fileName = fi.fileName();
            QString newName = getNewName(fileName);
            if (newName != fileName) {
                auto item = new RenamerItem(RenamerItem::File, fileName, newName,  dir.absolutePath());
                emit found(item);
            }
        }
    }

    if ((target & RenamerConfig::Directory) == RenamerConfig::Directory) {
        QString dirName = dir.dirName();
        QString newName = getNewName(dirName);
        if (newName != dirName) {
            QDir parent = dir;
            parent.cdUp();
            auto item = new RenamerItem(RenamerItem::Directory, dirName, newName, parent.absolutePath());
            emit found(item);
        }
    }
}


QString FindThread::getNewName(const QString &name) {
    QString newName = name;

    QRegExp::PatternSyntax syntax = QRegExp::FixedString;
    if (_config->type() == RenamerConfig::Wildcard)
        syntax = QRegExp::Wildcard;
    else if (_config->type() == RenamerConfig::Regex)
        syntax = QRegExp::RegExp;
    QRegExp re(_config->originText(), Qt::CaseInsensitive, syntax);
    newName.replace(re, _config->replaceText());

    if ((_config->options() & RenamerConfig::DecodeUrl) == RenamerConfig::DecodeUrl) {
        QTextCodec* codec = QTextCodec::codecForLocale();
        newName = QUrl::fromPercentEncoding(codec->fromUnicode(newName));
    }
    newName = newName.trimmed();
    return newName;
}
