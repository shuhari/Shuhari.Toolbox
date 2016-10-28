#pragma once

#include "precompiled.h"
#include "functional"


class ToolWindow;


class ToolItem {
public:
    ToolItem(const QString& id,
             const QString& iconName,
             const QString& name,
             const QString& tooltip,
             std::function<ToolWindow*(void)> factory);

    inline QString id()      { return _id; }
    inline QString name()    { return _name; }
    inline QString tooltip() { return _tooltip; }
    inline QIcon icon()      { return _icon; }
    ToolWindow* window();

private:
    QString _id;
    QString _name;
    QString _tooltip;
    QIcon   _icon;
    std::function<ToolWindow*(void)> _factory;
    ToolWindow* _window;
};


class ToolItemModel : public QAbstractListModel {
    Q_OBJECT
public:
    ToolItemModel();
    ~ToolItemModel();

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void add(ToolItem* item);

private:
    QList<ToolItem*> _items;
};
