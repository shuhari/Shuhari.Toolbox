#pragma once

#include "precompiled.h"
#include "toolitem.h"


class ToolModel : public QAbstractListModel {
    Q_OBJECT
public:
    ToolModel(QObject* parent = nullptr);
    virtual ~ToolModel();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void add(ToolItem* item);

private:
    QList<ToolItem*> _items;
};
