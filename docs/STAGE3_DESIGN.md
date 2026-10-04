# Stage 3 – System Design & Architecture

## High-Level Architecture

```text
+---------------------------+
|       SysGuard CLI        |
|        C++17              |
+------------+--------------+
             |
     Linux system interfaces
             |
   +---------+----------+
   |         |          |
 /proc     /sys     statvfs()
   |         |          |
   +---------+----------+
             |
        Linux Kernel
             |
   +---------+----------+
   |                    |
 CPU / Memory      Processes / FS

Optional driver:
C++ -> /dev/sysguard -> character driver -> kernel
```

## Major Components

### SystemInfo
Collects kernel, OS, architecture, hostname and uptime.

### CPUMonitor
Reads `/proc/stat`, `/proc/cpuinfo` and `/proc/loadavg`.

### MemoryMonitor
Reads `/proc/meminfo`.

### DiskMonitor
Uses `statvfs()` for filesystem capacity.

### ProcessMonitor
Enumerates numeric directories under `/proc` and reads process metadata.

### HealthMonitor
Applies simple thresholds to determine HEALTHY, WARNING or CRITICAL status.

### Driver
Exposes `/dev/sysguard` using the Linux misc-device interface.

## Data Structures

`CpuSnapshot` stores total and idle CPU counters.

`MemoryInfo` stores RAM and swap values.

`DiskInfo` stores filesystem capacity values.

`ProcessInfo` stores PID, process name and process state.

## Class/Module Diagram

```text
+----------------+
| CPUMonitor     |
+----------------+
| read_snapshot  |
| cpu_usage      |
+----------------+

+----------------+
| MemoryMonitor  |
+----------------+
| read_memory    |
| usage_percent  |
+----------------+

+----------------+
| ProcessMonitor |
+----------------+
| list           |
| search         |
| terminate      |
+----------------+

+----------------+
| DiskMonitor    |
+----------------+
| read_disk      |
| usage_percent  |
+----------------+

             |
             v
      +---------------+
      | HealthMonitor |
      +---------------+
      | health_status |
      +---------------+
```

## Sequence: Dashboard

```text
User -> SysGuard: Select Dashboard
SysGuard -> /proc: Read CPU
SysGuard -> /proc: Read memory
SysGuard -> statvfs: Read disk
SysGuard -> /proc: Count processes
SysGuard -> HealthMonitor: Evaluate values
HealthMonitor -> SysGuard: Status
SysGuard -> User: Display dashboard
```

## State Machine

```text
START
  |
  v
MENU
  |
  +--> COLLECT DATA --> DISPLAY
  |                       |
  |                       v
  |                     MENU
  |
  +--> PROCESS ACTION --> MENU
  |
  +--> LOG SNAPSHOT ----> MENU
  |
  +--> EXIT
```

## Git Strategy

- `main`: stable submission branch
- `feature/*`: individual feature development
- Commit after each meaningful module or documentation milestone.
