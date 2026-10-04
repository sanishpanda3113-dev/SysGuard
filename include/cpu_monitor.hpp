#pragma once
#include <string>

struct CpuSnapshot {
    unsigned long long total = 0;
    unsigned long long idle = 0;
};

CpuSnapshot read_cpu_snapshot();
double calculate_cpu_usage(const CpuSnapshot& first, const CpuSnapshot& second);
std::string cpu_model();
unsigned int cpu_core_count();
double load_average();
