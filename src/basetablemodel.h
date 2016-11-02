#pragma once

#include "precompiled.h"


template<typename T>
class BaseTableModel : public QAbstractTableModel {
public:
    inline BaseTableModel(QObject* parent = nullptr)
        : QAbstractTableModel(parent) {
    }

    inline virtual ~BaseTableModel() {
        clear();
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

    inline void add(T* item) {
        int index = _items.size();
        beginInsertRows(QModelIndex(), index, index);
        _items.append(item);
        endInsertRows();
    }

    inline T* at(int row) const {
        Q_ASSERT(row >= 0 && row < _items.size());
        return _items.at(row);
    }

    inline virtual int rowCount(const QModelIndex &parent = QModelIndex()) const {
        Q_UNUSED(parent);
        return _items.size();
    }

protected:
    QList<T*> _items;
};
