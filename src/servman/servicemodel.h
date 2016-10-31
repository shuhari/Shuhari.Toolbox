#pragma once

#include "precompiled.h"


class ServiceItem {
public:
    inline DWORD type()  { return _type; }
    inline DWORD startType() { return _startType; }
    inline const QString& name()        { return _name; }
    inline const QString& displayName() { return _displayName; }
    inline const QString& description() { return _description; }
    inline const QString& startName()   { return _startName; }

    QString typeName();
    QString startTypeName();
    QString statusName();
    bool match(const QString& name);

    // void load(ServiceContext& ctx, ENUM_SERVICE_STATUS_PROCESS* ssp);
    // bool setStartType(DWORD startType, QString& errorMsg);

private:
    QString _name;
    QString _displayName;
    QString _description;
    QString _pathName;
    QString _startName;

    DWORD   _type;
    DWORD   _startType;
    DWORD   _state;
    DWORD   _waitHint;
    DWORD   _processId;
    DWORD   _flags;
};


class ServiceModel : public QAbstractTableModel {
    Q_OBJECT
public:
    ServiceModel(QObject* parent = nullptr);
    virtual ~ServiceModel();

    virtual int rowCount(const QModelIndex&) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void clear();
    ServiceItem* at(int row);
    void reload();

private:
    QList<ServiceItem*> _items;
};
