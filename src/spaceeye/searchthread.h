#pragma once

#include "precompiled.h"
#include "spaceeyemodel.h"


class SearchThread : public QThread {
    Q_OBJECT
public:
    SearchThread(const QString& dirName, QObject* parent = nullptr);

protected:
    void run() Q_DECL_OVERRIDE;

private:
    SpaceEyeModel* _model;

    void    search(SpaceItem* item, const QDir& dir);

signals:
    void    modelFinished(QAbstractItemModel* model);
    void    statusLog(const QString& msg);
};
