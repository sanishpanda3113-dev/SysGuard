#include "health_monitor.hpp"

std::string health_status(double cpu, double memory, double disk, double load) {
    if (cpu >= 90.0 || memory >= 90.0 || disk >= 90.0 || load >= 8.0)
        return "CRITICAL";
    if (cpu >= 75.0 || memory >= 80.0 || disk >= 80.0 || load >= 4.0)
        return "WARNING";
    return "HEALTHY";
}
