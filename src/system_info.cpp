#include "system_info.hpp"
#include <fstream>
#include <sstream>
#include <sys/utsname.h>
#include <unistd.h>

std::string kernel_version() {
    struct utsname u{};
    if (uname(&u) == 0) return u.release;
    return "Unknown";
}

std::string operating_system() {
    std::ifstream file("/etc/os-release");
    std::string line;
    while (std::getline(file, line)) {
        if (line.rfind("PRETTY_NAME=", 0) == 0) {
            auto value = line.substr(13);
            if (!value.empty() && value.front() == '"') value.erase(0, 1);
            if (!value.empty() && value.back() == '"') value.pop_back();
            return value;
        }
    }
    return "Linux";
}

std::string architecture() {
    struct utsname u{};
    if (uname(&u) == 0) return u.machine;
    return "Unknown";
}

std::string hostname() {
    char name[256]{};
    if (gethostname(name, sizeof(name) - 1) == 0) return name;
    return "Unknown";
}

std::string uptime_string() {
    std::ifstream file("/proc/uptime");
    double seconds = 0;
    file >> seconds;
    long long s = static_cast<long long>(seconds);
    long long days = s / 86400; s %= 86400;
    long long hours = s / 3600; s %= 3600;
    long long minutes = s / 60; s %= 60;

    std::ostringstream out;
    if (days > 0) out << days << "d ";
    out << hours << "h " << minutes << "m " << s << "s";
    return out.str();
}
