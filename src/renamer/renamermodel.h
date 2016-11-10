#pragma once

#include "precompiled.h"
#include "renameritem.h"
#include "shared/basemodel.h"


class RenamerModel : public BaseTableModel<RenamerItem> {
    Q_OBJECT
public:
    RenamerModel(QObject* parent = nullptr);
    virtual ~RenamerModel();
    virtual QVariant cellData(int row, int column, int role, RenamerItem* item) const;

    void setState(int row, RenamerItem::ItemState state);
};
