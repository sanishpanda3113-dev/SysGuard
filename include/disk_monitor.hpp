#pragma once
struct DiskInfo {
    unsigned long long total_bytes = 0;
    unsigned long long free_bytes = 0;
    unsigned long long available_bytes = 0;
};

DiskInfo read_disk_info(const char* path = "/");
double disk_usage_percent(const DiskInfo& info);
double to_gb(unsigned long long bytes);
