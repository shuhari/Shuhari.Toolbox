#pragma once

#include "precompiled.h"
#include <windows.h>


class ServiceItem;


class ServiceContext {
public:
    ServiceContext();
    ~ServiceContext();

    inline SC_HANDLE handle()      { return _handle; }
    PBYTE alloc(DWORD size);
    void  free(PVOID buf);

    bool openManager(DWORD desiredAccess);
    bool openService(SC_HANDLE hSCManager, PCWSTR serviceName, DWORD desiredAccess);
    bool read(ENUM_SERVICE_STATUS_PROCESS *ssp, ServiceItem* item);

    static bool changeStartType(const QString& serviceName, DWORD startType, QString& errorMsg);

private:
    SC_HANDLE _handle;

    void close();
};
