#include <hw/platform.h>
#if defined(HW_PLATFORM_WINDOWS_DESKTOP)

#include "hwfw/error.h"
#include <hw/error.h>
#include <windows.h>

void hwfw_error_push(int kind, const char* message, const char* file, int line)
{
    DWORD  error          = GetLastError();
    TCHAR* system_message = NULL;

    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                  FORMAT_MESSAGE_FROM_SYSTEM     |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  error,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPTSTR)&system_message, 0, NULL);

    if(system_message != NULL) {
#if 0
        char message[HW_TEMPORARY_STRING_LENGTH];

        snprintf(message, sizeof(message), "%s", system_message);
#endif
        hw_error_push(kind, system_message, file, line);

        LocalFree(system_message);
        system_message = NULL;
    }
}

#endif

