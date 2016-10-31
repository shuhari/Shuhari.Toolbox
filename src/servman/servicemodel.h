#pragma once

#include "precompiled.h"


class ServiceItem {

};


class ServiceModel : public QAbstractTableModel {
    Q_OBJECT
public:
    ServiceModel(QObject* parent = nullptr);

    virtual int rowCount(const QModelIndex&) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};
