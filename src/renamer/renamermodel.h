#pragma once


#include "precompiled.h"
#include "renameritem.h"
#include "basetablemodel.h"


class RenamerModel : public BaseTableModel<RenamerItem> {
    Q_OBJECT
public:
    RenamerModel(QObject* parent = nullptr);

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void setState(int index, RenamerItem::State state);
};
