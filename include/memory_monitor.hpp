#pragma once
struct MemoryInfo {
    unsigned long long total_kb = 0;
    unsigned long long available_kb = 0;
    unsigned long long swap_total_kb = 0;
    unsigned long long swap_free_kb = 0;
};

MemoryInfo read_memory_info();
double memory_usage_percent(const MemoryInfo& info);
double swap_usage_percent(const MemoryInfo& info);
