#include "process_monitor.hpp"
#include <csignal>
#include <dirent.h>
#include <fstream>
#include <cerrno>

std::vector<ProcessInfo> list_processes() {
    std::vector<ProcessInfo> result;
    DIR* dir = opendir("/proc");
    if (!dir) return result;

    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type != DT_DIR) continue;

        std::string name(entry->d_name);
        if (name.empty() || name.find_first_not_of("0123456789") != std::string::npos)
            continue;

        int pid = std::stoi(name);
        std::ifstream stat("/proc/" + name + "/stat");
        std::string comm;
        char state;
        if (stat >> pid >> comm >> state) {
            if (comm.size() >= 2 && comm.front() == '(' && comm.back() == ')')
                comm = comm.substr(1, comm.size() - 2);
            result.push_back({pid, comm, state});
        }
    }
    closedir(dir);
    return result;
}

std::vector<ProcessInfo> find_processes(const std::string& query) {
    std::vector<ProcessInfo> result;
    for (const auto& p : list_processes()) {
        if (p.name.find(query) != std::string::npos)
            result.push_back(p);
    }
    return result;
}

bool terminate_process(int pid) {
    if (pid <= 1) return false;
    return kill(pid, SIGTERM) == 0;
}

std::string process_state_name(char state) {
    switch (state) {
        case 'R': return "Running";
        case 'S': return "Sleeping";
        case 'D': return "Disk Sleep";
        case 'T': return "Stopped";
        case 'Z': return "Zombie";
        case 'I': return "Idle";
        default: return "Unknown";
    }
}
