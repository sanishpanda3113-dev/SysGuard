#include "cpu_monitor.hpp"
#include <fstream>
#include <sstream>
#include <thread>
#include <unistd.h>

CpuSnapshot read_cpu_snapshot() {
    std::ifstream file("/proc/stat");
    std::string cpu;
    CpuSnapshot s;
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
    if (file >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal) {
        s.idle = idle + iowait;
        s.total = user + nice + system + idle + iowait + irq + softirq + steal;
    }
    return s;
}

double calculate_cpu_usage(const CpuSnapshot& first, const CpuSnapshot& second) {
    const auto total_delta = second.total - first.total;
    const auto idle_delta = second.idle - first.idle;
    if (total_delta == 0) return 0.0;
    return 100.0 * static_cast<double>(total_delta - idle_delta) /
           static_cast<double>(total_delta);
}

std::string cpu_model() {
    std::ifstream file("/proc/cpuinfo");
    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind("model name", 0) == 0) {
            const auto pos = line.find(':');
            if (pos != std::string::npos) return line.substr(pos + 2);
        }
    }
    return "Unknown";
}

unsigned int cpu_core_count() {
    return std::thread::hardware_concurrency();
}

double load_average() {
    std::ifstream file("/proc/loadavg");
    double value = 0.0;
    file >> value;
    return value;
}
