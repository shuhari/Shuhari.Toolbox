#include "precompiled.h"
#include "servicemodel.h"
#include "resources.h"
#include "servicecontext.h"


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
    if (_items.size() > 0) {
        beginRemoveRows(QModelIndex(), 0, _items.size() - 1);
        qDeleteAll(_items);
        _items.clear();
        endRemoveRows();
    }
}


ServiceItem* ServiceModel::at(int row) {
    Q_ASSERT(row >= 0 && row < _items.size());
    return _items[row];
}


void ServiceModel::setStartType(const QString &name, DWORD startType) {
    for (int i=0; i<_items.size(); i++) {
        if (_items[i]->name() == name) {
            _items[i]->setStartType(startType);
            QModelIndex startIndex = index(i, COLUMN_STARTTYPE);
            QModelIndex endIndex = startIndex;
            QVector<int> roles;
            roles << Qt::DisplayRole;
            dataChanged(startIndex, endIndex, roles);
        }
    }
}


bool ServiceModel::shouldInclude(ENUM_SERVICE_STATUS_PROCESS *pService) {
    DWORD dwType = pService->ServiceStatusProcess.dwServiceType;
    if ((dwType & SERVICE_WIN32) == 0)
        return false;
    return true;
}


void ServiceModel::reload() {
    clear();

    ServiceContext scmCtx;
    if (!scmCtx.openManager(SC_MANAGER_ENUMERATE_SERVICE | GENERIC_READ))
        return;

    DWORD dwNeeded = 0, dwReturned = 0;
    BOOL bRet = EnumServicesStatusEx(scmCtx.handle(),
                                     SC_ENUM_PROCESS_INFO,
                                     SERVICE_DRIVER | SERVICE_WIN32,
                                     SERVICE_STATE_ALL,
                                     NULL, 0,
                                     &dwNeeded, &dwReturned,
                                     NULL, NULL);
    if (!bRet && GetLastError() == ERROR_MORE_DATA)
    {
        auto pService = (ENUM_SERVICE_STATUS_PROCESS*)scmCtx.alloc(dwNeeded);
        auto pStart = pService;
        bRet = EnumServicesStatusEx(scmCtx.handle(),
                                    SC_ENUM_PROCESS_INFO,
                                    SERVICE_DRIVER | SERVICE_WIN32,
                                    SERVICE_STATE_ALL,
                                    (PBYTE)pService, dwNeeded,
                                    &dwNeeded, &dwReturned,
                                    NULL, NULL);
        if (bRet)
        {
            for (DWORD i = 0; i < dwReturned; i++)
            {
                if (shouldInclude(pService))
                {
                    ServiceContext serviceCtx;
                    if (serviceCtx.openService(scmCtx.handle(),
                                               pService->lpServiceName,
                                               SERVICE_QUERY_CONFIG | SERVICE_QUERY_STATUS))
                    {
                        auto si = new ServiceItem();
                        serviceCtx.read(pService, si);
                        _items.append(si);
                    }
                }
                pService ++;
            }
        }
        scmCtx.free(pStart);
    }
    if (_items.size() > 0) {
        beginInsertRows(QModelIndex(), 0, _items.size() - 1);
        endInsertRows();
    }
}


int ServiceModel::rowCount(const QModelIndex &) const {
    return _items.size();
}


int ServiceModel::columnCount(const QModelIndex &parent) const {
    return COLUMN_COUNT;
}


QVariant ServiceModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    if (row >= 0 && row < _items.size()) {
        auto item = _items.at(row);
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
            case COLUMN_NAME: return item->name();
            case COLUMN_DISPLAYNAME: return item->displayName();
            case COLUMN_DESCRIPTON: return item->description();
            case COLUMN_TYPE: return item->typeName();
            case COLUMN_STARTTYPE: return item->startTypeName();
            case COLUMN_STATUS: return item->statusName();
            case COLUMN_LOGIN: return item->startName();
            }
        }
        else if (role == Qt::DecorationRole && index.column() == 0) {
        }
        else if (role == Qt::BackgroundColorRole) {
        }
    }
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
