#pragma once
#include <string>
#include <vector>

struct ProcessInfo {
    int pid = 0;
    std::string name;
    char state = '?';
};

std::vector<ProcessInfo> list_processes();
std::vector<ProcessInfo> find_processes(const std::string& query);
bool terminate_process(int pid);
std::string process_state_name(char state);
