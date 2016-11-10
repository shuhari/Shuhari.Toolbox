#include "precompiled.h"
#include "searchthread.h"
#include "spaceeyemodel.h"


SearchThread::SearchThread(const QString &dirName, QObject *parent)
    : QThread(parent) {
    _model = new SpaceEyeModel();
    _model->setRoot(dirName);
}


void SearchThread::run() {
    search(_model->root(), _model->root()->name());
    emit modelFinished(_model);
}


void SearchThread::search(SpaceItem* item, const QDir &dir) {
    emit statusLog(QString("Searching %1 ...").arg(dir.absolutePath()));

    foreach(QFileInfo dirInfo, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot,
                                           QDir::Name | QDir::IgnoreCase))  {
        auto subdirItem = new SpaceItem(SpaceItem::Dir, dirInfo.fileName(), 0, item);
        item->append(subdirItem);
        QDir subdir(dirInfo.absoluteFilePath());
        search(subdirItem, subdir);
    }

    foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Files,
                                                  QDir::Name | QDir::IgnoreCase))  {
        auto fileItem = new SpaceItem(SpaceItem::File, fileInfo.fileName(), fileInfo.size(), item);
        item->append(fileItem);
    }
}
