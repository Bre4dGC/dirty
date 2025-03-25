#include "operations/processes.h"

// Start a new process
void start_process(const char *command) {
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

    if (CreateProcess(NULL, (LPSTR)command, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        printf("Process started with PID: %d\n", pi.dwProcessId);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        printf("Failed to start process. Error: %lu\n", GetLastError());
    }
}

// Terminate a process
void terminate_process(int pid) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess) {
        if (TerminateProcess(hProcess, 0)) {
            printf("Process with PID %d terminated.\n", pid);
        } else {
            printf("Failed to terminate process. Error: %lu\n", GetLastError());
        }
        CloseHandle(hProcess);
    } else {
        printf("Failed to open process. Error: %lu\n", GetLastError());
    }
}

// Get a list of running processes
process_t *get_process_list(int *count) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        printf("Failed to create process snapshot. Error: %lu\n", GetLastError());
        *count = 0;
        return NULL;
    }

    PROCESSENTRY32 pe32 = {0};
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hSnapshot, &pe32)) {
        printf("Failed to retrieve process list. Error: %lu\n", GetLastError());
        CloseHandle(hSnapshot);
        *count = 0;
        return NULL;
    }

    process_t *processes = malloc(sizeof(process_t) * 1024); // Assume a maximum of 1024 processes
    int index = 0;

    do {
        processes[index].pid = pe32.th32ProcessID;
        strncpy(processes[index].name, pe32.szExeFile, sizeof(processes[index].name) - 1);
        processes[index].name[sizeof(processes[index].name) - 1] = '\0';
        processes[index].cpu_usage = 0.0;    // CPU usage can be calculated separately
        processes[index].memory_usage = 0.0; // Memory usage can be calculated separately
        index++;
    } while (Process32Next(hSnapshot, &pe32) && index < 1024);

    CloseHandle(hSnapshot);
    *count = index;
    return processes;
}

// Check if a process is running
bool is_process_running(int pid) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (hProcess) {
        DWORD exitCode;
        if (GetExitCodeProcess(hProcess, &exitCode)) {
            CloseHandle(hProcess);
            return exitCode == STILL_ACTIVE;
        }
        CloseHandle(hProcess);
    }
    return false;
}

// Set the priority of a process
void set_process_priority(int pid, int priority) {
    HANDLE hProcess = OpenProcess(PROCESS_SET_INFORMATION, FALSE, pid);
    if (hProcess) {
        if (SetPriorityClass(hProcess, priority)) {
            printf("Priority of process %d set successfully.\n", pid);
        } else {
            printf("Failed to set process priority. Error: %lu\n", GetLastError());
        }
        CloseHandle(hProcess);
    } else {
        printf("Failed to open process. Error: %lu\n", GetLastError());
    }
}

// Get information about a process
process_t get_process_info(int pid) {
    process_t process = {0};
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        printf("Failed to create process snapshot. Error: %lu\n", GetLastError());
        return process;
    }

    PROCESSENTRY32 pe32 = {0};
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (pe32.th32ProcessID == pid) {
                process.pid = pid;
                strncpy(process.name, pe32.szExeFile, sizeof(process.name) - 1);
                process.name[sizeof(process.name) - 1] = '\0';
                process.cpu_usage = 0.0;    // CPU usage can be calculated separately
                process.memory_usage = 0.0; // Memory usage can be calculated separately
                break;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    return process;
}

// Handle process-related errors
void handle_process_error(int error_code)
{
    switch (error_code) {
        case ERROR_ACCESS_DENIED:
            printf("Access denied.\n");
            break;
        case ERROR_INVALID_HANDLE:
            printf("Invalid handle.\n");
            break;
        case ERROR_INVALID_PARAMETER:
            printf("Invalid parameter.\n");
            break;
        default:
            printf("Unknown error.\n");
            break;
    }
}