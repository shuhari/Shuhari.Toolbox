#pragma once

#include "precompiled.h"
#include "renameritem.h"


class RenamerModel : public QAbstractTableModel {
    Q_OBJECT
public:
    RenamerModel(QObject* parent = nullptr);
    virtual ~RenamerModel();

    void clear();
    int add(RenamerItem* item);
    RenamerItem* at(int row);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setState(int row, RenamerItem::ItemState state);

private:
    QList<RenamerItem*> _items;
};
