#include "bluescreen.hpp"

// from https://stackoverflow.com/questions/7034592/create-bsod-from-user-mode and chatgpt

#define BLUESCREEN

#include <iostream>
#ifdef BLUESCREEN
#include <Windows.h>
#include <winternl.h>
using namespace std;
typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(
    NTSTATUS ErrorStatus,
    ULONG NumberOfParameters,
    ULONG UnicodeStringParameterMask OPTIONAL,
    PULONG_PTR Parameters,
    ULONG ResponseOption,
    PULONG Response);
typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(
    ULONG Privilege,
    BOOLEAN Enable,
    BOOLEAN CurrentThread,
    PBOOLEAN Enabled);
#endif
void bluescreen() {
    std::cout << "bluescreen!!!" << std::endl;
#ifdef BLUESCREEN
    BOOLEAN bEnabled;
    ULONG uResp;

    // Correctly cast GetProcAddress results
    pdef_RtlAdjustPrivilege NtCall =
        (pdef_RtlAdjustPrivilege)GetProcAddress(
            LoadLibraryA("ntdll.dll"), "RtlAdjustPrivilege");

    pdef_NtRaiseHardError NtCall2 =
        (pdef_NtRaiseHardError)GetProcAddress(
            GetModuleHandleA("ntdll.dll"), "NtRaiseHardError");

    if (!NtCall || !NtCall2) {
        cout << "Failed to get function addresses." << endl;
        return;
    }

    NTSTATUS NtRet = NtCall(19, TRUE, FALSE, &bEnabled);
    NtCall2(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, 0, 6, &uResp);
#endif
}
