#include "disk_monitor.hpp"
#include <sys/statvfs.h>

DiskInfo read_disk_info(const char* path) {
    struct statvfs fs{};
    DiskInfo info;
    if (statvfs(path, &fs) == 0) {
        info.total_bytes = static_cast<unsigned long long>(fs.f_blocks) * fs.f_frsize;
        info.free_bytes = static_cast<unsigned long long>(fs.f_bfree) * fs.f_frsize;
        info.available_bytes = static_cast<unsigned long long>(fs.f_bavail) * fs.f_frsize;
    }
    return info;
}

double disk_usage_percent(const DiskInfo& info) {
    if (info.total_bytes == 0) return 0.0;
    return 100.0 * static_cast<double>(info.total_bytes - info.available_bytes) /
           static_cast<double>(info.total_bytes);
}

double to_gb(unsigned long long bytes) {
    return static_cast<double>(bytes) / (1024.0 * 1024.0 * 1024.0);
}
