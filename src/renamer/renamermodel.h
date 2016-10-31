#pragma once

#include "precompiled.h"
#include "renameritem.h"

class RenamerModel : public QAbstractTableModel {
    Q_OBJECT
public:

    RenamerModel(QObject* parent = nullptr);
    ~RenamerModel();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void clear();
    void add(RenamerItem* item);
    RenamerItem* at(int index);
    void setState(int index, RenamerItem::State state);

private:
    QList<RenamerItem*> _items;
};
