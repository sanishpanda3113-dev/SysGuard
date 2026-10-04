# Stage 4 – Initial Implementation & Prototype

## Implemented Components

- C++17 command-line interface
- System information module
- CPU monitoring
- Memory monitoring
- Disk monitoring
- Process enumeration
- Process search
- SIGTERM-based process termination
- Health status calculation
- Snapshot logging
- Linux character-device driver

## Implementation Approach

The application uses Linux-provided interfaces rather than external libraries. CPU and memory information are collected from `/proc`, disk capacity is collected with `statvfs()`, and process information is obtained from `/proc`.

The driver uses the Linux misc-device framework to expose `/dev/sysguard`.

## Prototype Demonstration

The initial prototype can demonstrate:

1. Building with `make`.
2. Launching `./sysguard`.
3. Displaying the dashboard.
4. Listing processes.
5. Searching for a process.
6. Writing a monitoring snapshot to `sysguard.log`.
7. Building/loading the optional driver.

## Progress Evidence

Add screenshots of:
- Terminal build
- SysGuard dashboard
- Process list
- Search result
- Log file
- Driver loaded and `/dev/sysguard`
