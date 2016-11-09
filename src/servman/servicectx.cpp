#include "precompiled.h"
#include "servicectx.h"
#include "resources.h"
#include "servicemodel.h"


ServiceContext::ServiceContext() {
    _handle = NULL;
}


ServiceContext::~ServiceContext() {
    close();
}


void ServiceContext::close() {
    if (_handle != NULL) {
        CloseServiceHandle(_handle);
        _handle = NULL;
    }
}


bool ServiceContext::openManager(DWORD desiredAccess) {
    close();
    _handle = OpenSCManager(NULL, NULL, desiredAccess);
    return _handle != NULL;
}


bool ServiceContext::openService(SC_HANDLE hSCManager, PCWSTR serviceName,
                                 DWORD desiredAccess) {
    close();
    _handle = OpenService(hSCManager, serviceName, desiredAccess);
    return _handle != NULL;
}


PBYTE ServiceContext::alloc(DWORD size) {
    return new BYTE[size];
}


void ServiceContext::free(PVOID buf) {
    delete [](PBYTE)buf;
}


bool ServiceContext::changeStartType(const QString &serviceName, DWORD startType,
                                     QString &errorMsg) {
    ServiceContext mgrCtx;
    if (!mgrCtx.openManager(SC_MANAGER_ALL_ACCESS | GENERIC_READ | GENERIC_WRITE)) {
        errorMsg = strings::prompt_openManager_failed();
        return false;
    }

    ServiceContext serviceCtx;
    wchar_t szName[_MAX_PATH];
    memset(szName, 0, sizeof(szName));
    serviceName.toWCharArray(szName);
    if (!serviceCtx.openService(mgrCtx.handle(), szName, SERVICE_CHANGE_CONFIG)) {
        qDebug() << "Open service failed:" << GetLastError();
        errorMsg = strings::prompt_openService_failed();
        return false;
    }
    BOOL success = ChangeServiceConfig(serviceCtx.handle(),
                                       SERVICE_NO_CHANGE,
                                       startType,
                                       SERVICE_NO_CHANGE,
                                       NULL, NULL, NULL,
                                       NULL, NULL, NULL, NULL);
    if (!success) {
        errorMsg = strings::prompt_setStartType_failed();
        return false;
    }

    return true;
}


bool ServiceContext::read(ENUM_SERVICE_STATUS_PROCESS *ssp, ServiceItem *item) {
    item->setName(QString::fromWCharArray(ssp->lpServiceName));
    item->setDisplayName(QString::fromWCharArray(ssp->lpDisplayName));

    SERVICE_STATUS_PROCESS& sspInfo = ssp->ServiceStatusProcess;
    item->setType(sspInfo.dwServiceType);
    item->setState(sspInfo.dwCurrentState);
    item->setWaitHint(sspInfo.dwWaitHint);
    item->setProcessId(sspInfo.dwProcessId);
    item->setFlags(sspInfo.dwServiceFlags);

    DWORD dwNeeded = 0;
    BOOL bRet = QueryServiceConfig(handle(), NULL, 0, &dwNeeded);
    if (!bRet && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
    {
        auto pConfig = (QUERY_SERVICE_CONFIG*)alloc(dwNeeded);
        bRet = QueryServiceConfig(handle(), pConfig, dwNeeded, &dwNeeded);
        item->setStartType(pConfig->dwStartType);
        item->setPathName(QString::fromWCharArray(pConfig->lpBinaryPathName));
        item->setStartName(QString::fromWCharArray(pConfig->lpServiceStartName));
        free(pConfig);
    }

    bRet = QueryServiceConfig2(handle(), SERVICE_CONFIG_DESCRIPTION,
                               NULL, 0, &dwNeeded);
    if (!bRet && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
    {
        auto pDesc = (SERVICE_DESCRIPTION*)alloc(dwNeeded);
        bRet = QueryServiceConfig2(handle(), SERVICE_CONFIG_DESCRIPTION,
                            (PBYTE)pDesc, dwNeeded, &dwNeeded);
        if (bRet)
            item->setDescription(QString::fromWCharArray(pDesc->lpDescription));
        free(pDesc);
    }
    return true;
}
