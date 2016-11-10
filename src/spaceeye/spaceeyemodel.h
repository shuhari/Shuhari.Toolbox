#pragma once

#include "precompiled.h"
#include "spaceitem.h"


class SpaceEyeModel : public QAbstractItemModel {
    Q_OBJECT
public:
    SpaceEyeModel(QObject* parent = nullptr);
    virtual ~SpaceEyeModel();

    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    QModelIndex index(int row, int column, const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex &child) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    void    setRoot(const QString& dirName);
    inline  SpaceItem* root()              { return _root; }

private:
    SpaceItem*    _root;

    void          clear();
};
