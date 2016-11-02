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
        return strings::service_type_fs();
    else if (_type == SERVICE_KERNEL_DRIVER)
        return strings::service_type_kernel();
    else if ((_type & SERVICE_WIN32_OWN_PROCESS) == SERVICE_WIN32_OWN_PROCESS)
        return strings::service_type_win32own();
    else if ((_type & SERVICE_WIN32_SHARE_PROCESS) == SERVICE_WIN32_SHARE_PROCESS)
        return strings::service_type_win32share();
    else
        return strings::unknown();
}


QString ServiceItem::startTypeName()
{
    switch (_startType)
    {
    case SERVICE_AUTO_START: return strings::service_startType_auto();
    case SERVICE_BOOT_START: return strings::service_startType_boot();
    case SERVICE_DEMAND_START: return strings::service_startType_demand();
    case SERVICE_DISABLED: return strings::service_startType_disabled();
    case SERVICE_SYSTEM_START: return strings::service_startType_sys();
    default: return strings::unknown();
    }
}


QString ServiceItem::statusName()
{
    switch (_state)
    {
    case SERVICE_CONTINUE_PENDING: return strings::service_state_continuePending();
    case SERVICE_PAUSE_PENDING: return strings::service_state_pausePending();
    case SERVICE_PAUSED: return strings::service_state_paused();
    case SERVICE_RUNNING: return strings::service_state_running();
    case SERVICE_START_PENDING: return strings::service_state_startPending();
    case SERVICE_STOP_PENDING: return strings::service_state_stopped();
    case SERVICE_STOPPED: return strings::service_state_stopped();
    default: return strings::unknown();
    }
}


ServiceModel::ServiceModel(QObject *parent)
    : BaseTableModel<ServiceItem>(parent) {

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
                        add(si);
                    }
                }
                pService ++;
            }
        }
        scmCtx.free(pStart);
    }
}


int ServiceModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return COLUMN_COUNT;
}


QVariant ServiceModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    if (row >= 0 && row < _items.size()) {
        ServiceItem* item = at(row);
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
