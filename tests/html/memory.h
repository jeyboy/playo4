#ifndef MEMORY_H
#define MEMORY_H

#include "qcoreapplication.h"
#ifdef Q_OS_WIN
    #include "windows.h"
    #include "psapi.h"
#endif

class Memory {
public:
    static quint64 usage() {
        qint64 pid = QCoreApplication::applicationPid();
        qint64 ms = 0;

        #ifdef Q_OS_WIN
            PROCESS_MEMORY_COUNTERS_EX pmc;
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);

            if (NULL == hProcess)
                return 0;

            if (GetProcessMemoryInfo(hProcess,  (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
                ms = pmc.PrivateUsage;
//                printf( "\tPageFaultCount: 0x%08X\n", pmc.PageFaultCount );
//                printf( "\tPeakWorkingSetSize: 0x%08X\n",
//                          pmc.PeakWorkingSetSize );
//                printf( "\tWorkingSetSize: 0x%08X\n", pmc.WorkingSetSize );
//                printf( "\tQuotaPeakPagedPoolUsage: 0x%08X\n",
//                          pmc.QuotaPeakPagedPoolUsage );
//                printf( "\tQuotaPagedPoolUsage: 0x%08X\n",
//                          pmc.QuotaPagedPoolUsage );
//                printf( "\tQuotaPeakNonPagedPoolUsage: 0x%08X\n",
//                          pmc.QuotaPeakNonPagedPoolUsage );
//                printf( "\tQuotaNonPagedPoolUsage: 0x%08X\n",
//                          pmc.QuotaNonPagedPoolUsage );
//                printf( "\tPagefileUsage: 0x%08X\n", pmc.PagefileUsage );
//                printf( "\tPeakPagefileUsage: 0x%08X\n",
//                          pmc.PeakPagefileUsage );
            }

            CloseHandle( hProcess );
        #elif Q_OS_MAC
            // нах надо
        #else
            // напиши меня
        #endif

        return ms;
    }

    static QString usageStr() {
        qint64 us = usage();
        return QString("%1 (%2 MB)").arg(us).arg(us / (1024.0 * 1024.0));
    }
};

#endif // MEMORY_H
