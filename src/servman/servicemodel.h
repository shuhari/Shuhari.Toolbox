#pragma once

#include "precompiled.h"
#include <windows.h>


class ServiceItem {
public:
    inline DWORD type()  { return _type; }
    inline DWORD startType() { return _startType; }
    inline const QString& name()        { return _name; }
    inline const QString& displayName() { return _displayName; }
    inline const QString& description() { return _description; }
    inline const QString& startName()   { return _startName; }

    inline void setType(DWORD type)       { _type = type; }
    inline void setStartType(DWORD type)  { _startType = type; }
    inline void setName(QString name) { _name = name; }
    inline void setDisplayName(QString name) { _displayName = name; }
    inline void setDescription(QString desc) { _description = desc; }
    inline void setStartName(QString name)   { _startName = name; }
    inline void setWaitHint(DWORD hint)      { _waitHint = hint; }
    inline void setProcessId(DWORD id)       { _processId = id; }
    inline void setFlags(DWORD flags)        { _flags = flags; }
    inline void setState(DWORD state)        { _state = state; }
    inline void setPathName(QString name)    { _pathName = name; }

    QString typeName();
    QString startTypeName();
    QString statusName();
    bool match(const QString& name);

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

    ServiceItem* at(int row) const;
    void clear();
    int add(ServiceItem* item);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void reload();
    void setStartType(const QString& name, DWORD startType);

private:
    QList<ServiceItem*> _items;

    bool shouldInclude(ENUM_SERVICE_STATUS_PROCESS* pService);
};
