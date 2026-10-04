#include "memory_monitor.hpp"
#include <fstream>
#include <string>

MemoryInfo read_memory_info() {
    std::ifstream file("/proc/meminfo");
    MemoryInfo info;
    std::string key;
    unsigned long long value;
    std::string unit;

    while (file >> key >> value >> unit) {
        if (key == "MemTotal:") info.total_kb = value;
        else if (key == "MemAvailable:") info.available_kb = value;
        else if (key == "SwapTotal:") info.swap_total_kb = value;
        else if (key == "SwapFree:") info.swap_free_kb = value;
    }
    return info;
}

double memory_usage_percent(const MemoryInfo& info) {
    if (info.total_kb == 0) return 0.0;
    return 100.0 * static_cast<double>(info.total_kb - info.available_kb) /
           static_cast<double>(info.total_kb);
}

double swap_usage_percent(const MemoryInfo& info) {
    if (info.swap_total_kb == 0) return 0.0;
    return 100.0 * static_cast<double>(info.swap_total_kb - info.swap_free_kb) /
           static_cast<double>(info.swap_total_kb);
}
