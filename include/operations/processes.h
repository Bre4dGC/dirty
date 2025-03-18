#include <windows.h>
#include <tlhelp32.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int pid;             // Process ID
    char name[256];      // Process name
    double cpu_usage;    // CPU utilization
    double memory_usage; // Memory utilization
} process_t;

void start_process(const char *command);          // Start a new process
void terminate_process(int pid);                  // Terminate a process
process_t *get_process_list(int *count);          // Get a list of running processes
bool is_process_running(int pid);                 // Check if a process is running
void set_process_priority(int pid, int priority); // Set the priority of a process
process_t get_process_info(int pid);              // Get information about a process
void handle_process_error(int error_code);        // Handle process-related errors