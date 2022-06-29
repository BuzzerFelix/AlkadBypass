#include "main_proc.h"
#include <iostream>

using namespace std;
DWORD FindProcessId(const std::wstring& processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile))
    {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!processName.compare(processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}
int main() {
    cout << "Suspending Alkad AntiCheat..." << endl;
    DWORD alkad = FindProcessId(L"Alkad.exe");
    if (alkad == NULL) {
        cout << "Alkad AntiCheat Not Found... Please Open Rust.exe and Try Again" << endl;
        Sleep(5000);
        exit(554);
    }
    suspend(alkad);
	Sleep(1000);
    cout << "Successfully Suspended Alkad..." << endl;
    Sleep(4500);
    return 0;
}