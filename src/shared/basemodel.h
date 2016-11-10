#pragma once

#include "precompiled.h"


class ModelColumn {
public:
    inline ModelColumn(const QString& name) {
        _name = name;
    }

    inline QString name()          { return _name; }

private:
    QString           _name;
};


template<typename T>
class BaseTableModel : public QAbstractTableModel {
public:
    inline BaseTableModel(QObject* parent = nullptr)
        : QAbstractTableModel(parent) {
    }

    inline virtual ~BaseTableModel() {
        clear();
        clearColumns();
    }

    inline void clear() {
        int count = _items.size();
        if (count > 0) {
            beginRemoveRows(QModelIndex(), 0, count - 1);
            qDeleteAll(_items);
            _items.clear();
            endRemoveRows();
        }
    }

    inline void clearColumns() {
        int count = _columns.size();
        if (count > 0) {
            beginRemoveColumns(QModelIndex(), 0, count - 1);
            qDeleteAll(_columns);
            _columns.clear();
            endRemoveColumns();
        }
    }

    inline int add(T* item) {
        int row = _items.size();
        beginInsertRows(QModelIndex(), row, row);
        _items.append(item);
        endInsertRows();
        return row;
    }

    inline T* at(int row) const {
        Q_ASSERT(row >= 0 && row < _items.size());
        return _items.at(row);
    }

    inline virtual int rowCount(const QModelIndex &parent = QModelIndex()) const {
        Q_UNUSED(parent);
        return _items.size();
    }

    inline virtual int columnCount(const QModelIndex &parent = QModelIndex()) const {
        Q_UNUSED(parent);
        return _columns.size();
    }

    inline virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const {
        if (orientation == Qt::Horizontal && section >= 0 && section < _columns.size()) { //  role == Qt::DisplayRole) {
            auto column = _columns.at(section);
            switch (role) {
            case Qt::DisplayRole: return column->name();
            }
        }
        return QVariant();
    }

    inline virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {
        int row = index.row();
        if (row >= 0 && row < _items.size()) {
            auto item = _items.at(row);
            return cellData(row, index.column(), role, item);
        }
        return miscData(index, role);
    }

    inline virtual QVariant cellData(int row, int column, int role, T* item) const {
        Q_UNUSED(row);
        Q_UNUSED(column);
        Q_UNUSED(role);
        Q_UNUSED(item);
        return QVariant();
    }

    inline virtual QVariant miscData(const QModelIndex& model, int role) const {
        Q_UNUSED(model);
        Q_UNUSED(role);
        return QVariant();
    }

protected:
    QList<T*>           _items;
    QList<ModelColumn*> _columns;

    inline void addColumn(const QString& name) {
        auto column = new ModelColumn(name);
        _columns.append(column);
    }
};
