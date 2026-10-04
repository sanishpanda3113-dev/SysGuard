#include "cpu_monitor.hpp"
#include "memory_monitor.hpp"
#include "disk_monitor.hpp"
#include "system_info.hpp"
#include "process_monitor.hpp"
#include "health_monitor.hpp"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <thread>
#include <unistd.h>

void line(char c='=', int n=60) {
    std::cout << std::string(n, c) << '\n';
}

double current_cpu_usage() {
    auto first = read_cpu_snapshot();
    std::this_thread::sleep_for(std::chrono::milliseconds(350));
    auto second = read_cpu_snapshot();
    return calculate_cpu_usage(first, second);
}

void dashboard() {
    const double cpu = current_cpu_usage();
    const auto mem = read_memory_info();
    const auto disk = read_disk_info();
    const auto processes = list_processes();
    const double memory = memory_usage_percent(mem);
    const double disk_use = disk_usage_percent(disk);
    const double load = load_average();

    line();
    std::cout << "                 SYSGUARD\n";
    std::cout << "          LINUX SYSTEM HEALTH MONITOR\n";
    line();

    std::cout << "System\n";
    line('-', 60);
    std::cout << "OS              : " << operating_system() << '\n';
    std::cout << "Kernel          : " << kernel_version() << '\n';
    std::cout << "Architecture    : " << architecture() << '\n';
    std::cout << "Hostname        : " << hostname() << '\n';
    std::cout << "Uptime          : " << uptime_string() << '\n';

    std::cout << "\nCPU\n";
    line('-', 60);
    std::cout << "Model           : " << cpu_model() << '\n';
    std::cout << "Cores           : " << cpu_core_count() << '\n';
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Usage           : " << cpu << "%\n";
    std::cout << "Load Average    : " << load << '\n';

    std::cout << "\nMemory\n";
    line('-', 60);
    std::cout << "Total           : " << mem.total_kb / 1024 << " MB\n";
    std::cout << "Available       : " << mem.available_kb / 1024 << " MB\n";
    std::cout << "Usage           : " << memory << "%\n";
    std::cout << "Swap Usage      : " << swap_usage_percent(mem) << "%\n";

    std::cout << "\nStorage (/)\n";
    line('-', 60);
    std::cout << "Total           : " << to_gb(disk.total_bytes) << " GB\n";
    std::cout << "Available       : " << to_gb(disk.available_bytes) << " GB\n";
    std::cout << "Usage           : " << disk_use << "%\n";

    std::cout << "\nProcesses\n";
    line('-', 60);
    std::cout << "Total processes : " << processes.size() << '\n';

    std::cout << "\nSystem Health   : " << health_status(cpu, memory, disk_use, load) << '\n';
    line();
}

void show_system_info() {
    std::cout << "\n--- SYSTEM INFORMATION ---\n";
    std::cout << "OS           : " << operating_system() << '\n';
    std::cout << "Kernel       : " << kernel_version() << '\n';
    std::cout << "Architecture : " << architecture() << '\n';
    std::cout << "Hostname     : " << hostname() << '\n';
    std::cout << "CPU Model    : " << cpu_model() << '\n';
    std::cout << "CPU Cores    : " << cpu_core_count() << '\n';
    std::cout << "Uptime       : " << uptime_string() << '\n';
}

void show_processes() {
    auto processes = list_processes();
    std::cout << "\nPID\tSTATE\t\tNAME\n";
    line('-', 60);
    int shown = 0;
    for (const auto& p : processes) {
        std::cout << p.pid << '\t' << process_state_name(p.state) << "\t\t" << p.name << '\n';
        if (++shown >= 30) break;
    }
    std::cout << "\nShowing up to 30 processes. Total: " << processes.size() << "\n";
}

void search_process() {
    std::string query;
    std::cout << "Process name to search: ";
    std::cin >> query;
    auto results = find_processes(query);
    std::cout << "\nPID\tSTATE\t\tNAME\n";
    line('-', 60);
    for (const auto& p : results)
        std::cout << p.pid << '\t' << process_state_name(p.state) << "\t\t" << p.name << '\n';
    std::cout << "Matches: " << results.size() << '\n';
}

void terminate_process_menu() {
    int pid;
    std::cout << "Enter PID to terminate: ";
    std::cin >> pid;
    if (terminate_process(pid))
        std::cout << "SIGTERM sent to PID " << pid << ".\n";
    else
        std::cout << "Unable to terminate PID " << pid << ". Check permissions and PID.\n";
}

void log_snapshot() {
    const double cpu = current_cpu_usage();
    const auto mem = read_memory_info();
    const auto disk = read_disk_info();
    const double memory = memory_usage_percent(mem);
    const double disk_use = disk_usage_percent(disk);

    std::ofstream log("sysguard.log", std::ios::app);
    log << std::fixed << std::setprecision(2)
        << "CPU=" << cpu
        << ", MEMORY=" << memory
        << ", DISK=" << disk_use
        << ", STATUS=" << health_status(cpu, memory, disk_use, load_average())
        << '\n';
    std::cout << "Snapshot written to sysguard.log\n";
}

int main() {
    while (true) {
        std::cout << "\n";
        line();
        std::cout << "                 SYSGUARD MENU\n";
        line();
        std::cout << "1. System dashboard\n";
        std::cout << "2. System information\n";
        std::cout << "3. List processes\n";
        std::cout << "4. Search process\n";
        std::cout << "5. Terminate process\n";
        std::cout << "6. Save health snapshot to log\n";
        std::cout << "0. Exit\n";
        line('-', 60);
        std::cout << "Choice: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: dashboard(); break;
            case 2: show_system_info(); break;
            case 3: show_processes(); break;
            case 4: search_process(); break;
            case 5: terminate_process_menu(); break;
            case 6: log_snapshot(); break;
            case 0: return 0;
            default: std::cout << "Invalid choice.\n";
        }
    }
}
