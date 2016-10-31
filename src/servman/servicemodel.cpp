#include "precompiled.h"
#include "servicemodel.h"
#include "resources.h"


#define COLUMN_COUNT         7
#define COLUMN_NAME          0
#define COLUMN_DISPLAYNAME   1
#define COLUMN_DESCRIPTON    2
#define COLUMN_TYPE          3
#define COLUMN_STARTTYPE     4
#define COLUMN_STATUS        5
#define COLUMN_LOGIN         6


bool ServiceItem::match(const QString &name) {
    if (!name.isEmpty()) {
        if (!_name.contains(name, Qt::CaseInsensitive) &&
            !_displayName.contains(name, Qt::CaseInsensitive) &&
            !_description.contains(name, Qt::CaseInsensitive))
            return false;
    }
    return true;
}


QString ServiceItem::typeName()
{
    if (_type == SERVICE_FILE_SYSTEM_DRIVER)
        return qApp->translate("", "FS Driver");
    else if (_type == SERVICE_KERNEL_DRIVER)
        return qApp->translate("", "Kernel Driver");
    else if ((_type & SERVICE_WIN32_OWN_PROCESS) == SERVICE_WIN32_OWN_PROCESS)
        return qApp->translate("", "Win32 Own Process");
    else if ((_type & SERVICE_WIN32_SHARE_PROCESS) == SERVICE_WIN32_SHARE_PROCESS)
        return qApp->translate("", "Win32 Share Process");
    else
        return qApp->translate("", "Unknown");
}


QString ServiceItem::startTypeName()
{
    switch (_startType)
    {
    case SERVICE_AUTO_START: return qApp->translate("", "Auto Start");
    case SERVICE_BOOT_START: return qApp->translate("", "Boot Start");
    case SERVICE_DEMAND_START: return qApp->translate("", "Demand Start");
    case SERVICE_DISABLED: return qApp->translate("", "Disabled");
    case SERVICE_SYSTEM_START: return qApp->translate("", "System Start");
    default: return qApp->translate("", "Unknown");
    }
}


QString ServiceItem::statusName()
{
    switch (_state)
    {
    case SERVICE_CONTINUE_PENDING: return qApp->translate("", "Continue Pending");
    case SERVICE_PAUSE_PENDING: return qApp->translate("", "Pause Pending");
    case SERVICE_PAUSED: return qApp->translate("", "Paused");
    case SERVICE_RUNNING: return qApp->translate("", "Running");
    case SERVICE_START_PENDING: return qApp->translate("", "Start Pending");
    case SERVICE_STOP_PENDING: return qApp->translate("", "Stop Pending");
    case SERVICE_STOPPED: return qApp->translate("", "Stopped");
    default: return qApp->translate("", "Unknown");
    }
}


ServiceModel::ServiceModel(QObject *parent)
    : QAbstractTableModel(parent) {

}


ServiceModel::~ServiceModel() {
    clear();
}


void ServiceModel::clear() {
    qDeleteAll(_items);
    _items.clear();
}


ServiceItem* ServiceModel::at(int row) {
    Q_ASSERT(row >= 0 && row < _items.size());
    return _items[row];
}


void ServiceModel::reload() {

}


int ServiceModel::rowCount(const QModelIndex &) const {
    return 0;
}


int ServiceModel::columnCount(const QModelIndex &parent) const {
    return COLUMN_COUNT;
}


QVariant ServiceModel::data(const QModelIndex &index, int role) const {
    return QVariant();
}


QVariant ServiceModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case COLUMN_NAME:           return strings::name();
        case COLUMN_DISPLAYNAME:    return strings::displayName();
        case COLUMN_DESCRIPTON:     return strings::description();
        case COLUMN_TYPE:           return strings::type();
        case COLUMN_STARTTYPE:      return strings::startType();
        case COLUMN_STATUS:         return strings::status();
        case COLUMN_LOGIN:          return strings::loginAs();
        }
    }
    return QVariant();
}
