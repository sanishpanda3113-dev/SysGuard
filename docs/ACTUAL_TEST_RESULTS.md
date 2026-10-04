# Actual Test Results

## Environment

- OS: Ubuntu 26.04.1 LTS
- Kernel: 6.18.40.1-microsoft-standard-WSL2
- Architecture: x86_64
- CPU: AMD Ryzen 7 6800H with Radeon Graphics
- CPU Cores reported: 16

## Test Results

| Test | Result |
|---|---|
| `make` build | PASS |
| Application launch | PASS |
| Dashboard | PASS |
| System information | PASS |
| Process listing | PASS |
| Process search (`bash`) | PASS |
| Health snapshot logging | PASS |
| Overall health calculation | PASS |
| Driver build/load in WSL2 | NOT VALIDATED – matching kernel build tree unavailable |

## Observed Values

### Dashboard

- CPU Usage: 0.0%
- Load Average: 0.1
- Memory Usage: 7.9%
- Disk Usage: 5.3%
- Total Processes: 26
- System Health: HEALTHY

### Process Search

Search query:

```text
bash
```

Matches:

```text
330  bash
633  bash
```

### Logging

Generated log entry:

```text
CPU=0.00, MEMORY=7.91, DISK=5.26, STATUS=HEALTHY
```

## Driver Environment Check

The running kernel was:

```text
6.18.40.1-microsoft-standard-WSL2
```

The required matching development tree was not present:

```text
/lib/modules/6.18.40.1-microsoft-standard-WSL2/build
```

This is recorded as an environment limitation rather than a software failure.
