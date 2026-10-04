# SysGuard – Linux System Health Monitor

> A Linux-only C++ system monitoring and diagnostic tool demonstrating Linux system programming, process/resource monitoring, computer architecture concepts, and kernel/user-space interaction.

## Project Overview

**SysGuard** consolidates commonly needed Linux system-health information into one lightweight terminal application. It monitors CPU, memory, storage, processes, system information, and overall health status.

The project also includes a **minimal Linux character-device driver source** (`/dev/sysguard`) to demonstrate kernel-module and user-space/kernel-space concepts.

## Key Features

- System and kernel information
- CPU model, core count, utilization and load average
- RAM and swap monitoring
- Root filesystem monitoring
- Linux process enumeration
- Process search
- Controlled process termination using `SIGTERM`
- Overall health calculation: `HEALTHY`, `WARNING`, `CRITICAL`
- Health snapshot logging
- Modular C++17 structure
- Linux character-device driver source
- Make-based build and Git/GitHub workflow

## Technology Stack

| Area | Technology |
|---|---|
| OS | Linux / Ubuntu |
| Application | C++17 |
| Driver source | C |
| Compiler | GNU g++ |
| Build | GNU Make |
| Version control | Git |
| Repository | GitHub |
| Interface | Terminal / CLI |

## Architecture

```text
                    +----------------------+
                    |    SysGuard CLI      |
                    |       C++17          |
                    +----------+-----------+
                               |
                    Linux system interfaces
                               |
              +----------------+----------------+
              |                |                 |
            /proc             /sys          statvfs()
              |                |                 |
              +----------------+----------------+
                               |
                         Linux Kernel
                               |
                     CPU / Memory / FS /
                         Processes

Optional driver path:
SysGuard C++ -> /dev/sysguard -> Character Driver -> Linux Kernel
```

## C++ Modules

```text
SystemInfo
CPUMonitor
MemoryMonitor
DiskMonitor
ProcessMonitor
HealthMonitor
Logger
```

The application is separated into headers and implementation files to demonstrate modular C++ design.

## Linux/System Programming Concepts

- `/proc` virtual filesystem
- Linux process model and PIDs
- Linux signals (`SIGTERM`)
- `uname()`
- `statvfs()`
- File and stream operations
- User space vs kernel space
- Character devices
- Kernel modules
- Git-based development

## Build the Application

From the project root:

```bash
make
```

Run:

```bash
./sysguard
```

## Verified Run Environment

The application was actually built and tested in:

```text
OS            : Ubuntu 26.04.1 LTS
Kernel        : 6.18.40.1-microsoft-standard-WSL2
Architecture  : x86_64
CPU           : AMD Ryzen 7 6800H with Radeon Graphics
CPU Cores     : 16
```

### Verified Dashboard Result

```text
CPU Usage      : 0.0%
Load Average   : 0.1
Memory Usage   : 7.9%
Disk Usage     : 5.3%
Processes      : 26
System Health  : HEALTHY
```

### Verified Process Search

Searching for `bash` returned:

```text
PID 330  bash
PID 633  bash
Matches: 2
```

### Verified Logging

`sysguard.log` produced:

```text
CPU=0.00, MEMORY=7.91, DISK=5.26, STATUS=HEALTHY
```

## Menu

```text
1. System dashboard
2. System information
3. List processes
4. Search process
5. Terminate process
6. Save health snapshot to log
0. Exit
```

## Character Driver Component

The repository contains:

```text
driver/sysguard_driver.c
driver/Makefile
```

The driver uses the Linux misc-device framework and is designed to expose:

```text
/dev/sysguard
```

### WSL limitation observed during development

The project was developed in WSL2. The running kernel reported:

```text
6.18.40.1-microsoft-standard-WSL2
```

but the matching kernel development directory was not available:

```text
/lib/modules/6.18.40.1-microsoft-standard-WSL2/build
```

Therefore the driver **source is included and documented, but driver compilation/loading was not validated in this WSL environment**. The application itself was successfully built and executed.

For a native Linux machine with matching kernel headers, the driver can be built with:

```bash
cd driver
make
sudo insmod sysguard_driver.ko
cat /dev/sysguard
sudo rmmod sysguard_driver
```

## Testing

See:

- `tests/test_plan.md`
- `docs/STAGE5_TESTING.md`
- `docs/ACTUAL_TEST_RESULTS.md`

## Project Stages

- **Stage 1:** Project Introduction
- **Stage 2:** Requirements & Development Plan
- **Stage 3:** System Design & Architecture
- **Stage 4:** Initial Implementation & Prototype
- **Stage 5:** Testing, Integration & Improvement
- **Stage 6:** Final Implementation & Presentation

## Limitations

- Linux-specific
- CLI only
- Hardware sensors vary by system
- Per-process CPU/memory percentages are not included in this version
- Kernel-driver runtime validation is unavailable in the current WSL environment

## Future Enhancements

- ncurses-based real-time dashboard
- Per-process CPU and memory metrics
- Configurable health thresholds
- Historical CSV/report generation
- Temperature and fan monitoring
- Network statistics
- Extended driver `ioctl()` support

## GitHub Repository

**Repository:** https://github.com/sanishpanda3113-dev/SysGuard
