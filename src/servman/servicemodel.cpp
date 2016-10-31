#include "precompiled.h"
#include "servicemodel.h"


ServiceModel::ServiceModel(QObject *parent)
    : QAbstractTableModel(parent) {

}


int ServiceModel::rowCount(const QModelIndex &) const {
    return 0;
}


int ServiceModel::columnCount(const QModelIndex &parent) const {
    return 0;
}


QVariant ServiceModel::data(const QModelIndex &index, int role) const {
    return QVariant();
}
