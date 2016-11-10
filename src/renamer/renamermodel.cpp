#include "precompiled.h"
#include "renamermodel.h"
#include "resources.h"


#define COLUMN_ORIGIN_NAME     0
#define COLUMN_NEW_NAME        1
#define COLUMN_DIRECTORY       2


RenamerModel::RenamerModel(QObject *parent)
    : BaseTableModel<RenamerItem>(parent) {
    addColumn(strings::renamer_origin_name());
    addColumn(strings::renamer_new_name());
    addColumn(strings::browse_label());
}


RenamerModel::~RenamerModel() {
}


QVariant RenamerModel::cellData(int row, int column, int role, RenamerItem* item) const {
    Q_UNUSED(row);
    if (role == Qt::DisplayRole) {
        switch (column) {
        case COLUMN_ORIGIN_NAME: return item->originName();
        case COLUMN_NEW_NAME: return item->newName();
        case COLUMN_DIRECTORY: return item->directory();
        }
    } else if (role == Qt::DecorationRole && column == 0) {
        if (item->type() == RenamerItem::File)
            return qApp->style()->standardIcon(QStyle::SP_FileIcon);
        else
            return qApp->style()->standardIcon(QStyle::SP_DirIcon);
    } else if (role == Qt::BackgroundColorRole) {
        if (item->state() == RenamerItem::SuccessState)
            return QColor(0, 0x80, 0);
        else if (item->state() == RenamerItem::ErrorState)
            return QColor(0xff, 0, 0);
    }
    return QVariant();
}


void RenamerModel::setState(int row, RenamerItem::ItemState state) {
    auto item = at(row);
    item->setState(state);
    QModelIndex startCell = index(row, 0);
    QModelIndex endCell = index(row, columnCount() - 1);
    QVector<int> roles;
    roles << Qt::BackgroundColorRole;
    emit dataChanged(startCell, endCell, roles);
}
