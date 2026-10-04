# SysGuard – Linux System Health Monitor

SysGuard is a Linux-only C++ command-line system monitoring tool designed to demonstrate Linux system programming, computer architecture concepts, process/resource monitoring, and user-space/kernel-space communication.

## Features

- Linux system and kernel information
- CPU architecture and CPU usage monitoring
- RAM and swap usage
- Disk usage
- Process count and process listing
- Process search
- Process termination using Linux signals
- System health assessment
- Optional Linux character device driver: `/dev/sysguard`
- Logging of monitoring snapshots
- Modular C++ design
- Make-based build

## Technology

- Operating System: Linux
- Language: C++17 for the application
- Kernel module: C
- Build: GNU Make / g++
- Version control: Git

## Project Architecture

```text
+-----------------------------+
|       SysGuard C++ CLI      |
+--------------+--------------+
               |
       Linux system interfaces
               |
   +-----------+-----------+
   |           |           |
 /proc       /sys      statvfs()
   |           |           |
   +-----------+-----------+
               |
          Linux Kernel
               |
      +--------+--------+
      |                 |
     CPU              Memory
      |
    Storage / Processes

Optional driver path:

SysGuard C++ -> /dev/sysguard -> Linux character driver -> Kernel
```

## Project Structure

```text
SysGuard/
├── src/
│   ├── main.cpp
│   ├── cpu_monitor.cpp
│   ├── memory_monitor.cpp
│   ├── process_monitor.cpp
│   ├── disk_monitor.cpp
│   ├── system_info.cpp
│   └── health_monitor.cpp
├── include/
│   ├── cpu_monitor.hpp
│   ├── memory_monitor.hpp
│   ├── process_monitor.hpp
│   ├── disk_monitor.hpp
│   ├── system_info.hpp
│   └── health_monitor.hpp
├── driver/
│   ├── sysguard_driver.c
│   └── Makefile
├── docs/
├── tests/
├── Makefile
└── README.md
```

## Build

Install the basic development tools on Debian/Ubuntu:

```bash
sudo apt update
sudo apt install build-essential g++ make git
```

Then:

```bash
make
./sysguard
```

## Run

```bash
./sysguard
```

The application provides a menu for system information, CPU, memory, disk, processes, process search/termination, health status, and logging.

## Optional Kernel Driver

The `driver/` directory contains a small Linux character device driver using the misc-device interface.

Install matching kernel headers:

```bash
sudo apt install linux-headers-$(uname -r)
```

Build:

```bash
cd driver
make
```

Load:

```bash
sudo insmod sysguard_driver.ko
ls -l /dev/sysguard
```

Test:

```bash
cat /dev/sysguard
```

Unload:

```bash
sudo rmmod sysguard_driver
```

If `/dev/sysguard` is not created automatically on a particular distribution, inspect:

```bash
dmesg | tail
ls -l /dev/sysguard
```

## Safety Note

The process termination option sends a signal to a PID selected by the user. Do not terminate essential system processes. Use a harmless test process during demonstration.

## Example Output

```text
============================================================
                    SYSGUARD
             LINUX SYSTEM HEALTH MONITOR
============================================================

System: Linux
Kernel: 6.x
Architecture: x86_64

CPU Usage: 34.7%
Memory Usage: 48.2%
Disk Usage: 57.4%
Processes: 214

Health Status: HEALTHY
============================================================
```

The exact values depend on the machine on which SysGuard is executed.

## Stage Documentation

See:

- `docs/STAGE1_INTRODUCTION.md`
- `docs/STAGE2_REQUIREMENTS.md`
- `docs/STAGE3_DESIGN.md`
- `docs/STAGE4_IMPLEMENTATION.md`
- `docs/STAGE5_TESTING.md`
- `docs/STAGE6_FINAL.md`

## Limitations

- CPU usage is sampled over a short interval.
- Process CPU percentages are based on Linux `/proc` data.
- Hardware temperature monitoring is not enabled because sensor availability varies between systems.
- The optional kernel module requires matching Linux kernel headers and sufficient privileges.

## Future Improvements

- ncurses dashboard
- Configurable alert thresholds
- Historical CSV logging
- Network monitoring
- Hardware temperature/fan monitoring
- More driver `ioctl()` commands
- Unit-test framework integration
