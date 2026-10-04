# SysGuard Test Plan

## 1. Build Test
Command:
```bash
make
```
Expected: executable `sysguard` is created without compilation errors.

## 2. System Information Test
Open the application and select option 2.
Expected: Linux OS, kernel, architecture, hostname and CPU information are displayed.

## 3. CPU Test
Select the dashboard.
Expected: CPU utilization is displayed as a percentage.

## 4. Memory Test
Select the dashboard.
Expected: total and available RAM and memory utilization are displayed.

## 5. Disk Test
Select the dashboard.
Expected: root filesystem capacity and utilization are displayed.

## 6. Process Test
Select option 3.
Expected: Linux process PIDs, states and names are listed.

## 7. Search Test
Select option 4 and enter a known process name.
Expected: matching processes are displayed.

## 8. Process Termination Test
Use a harmless test process and select option 5.
Expected: SIGTERM is sent and the process exits if permissions allow it.

## 9. Logging Test
Select option 6.
Expected: `sysguard.log` is created/appended.

## 10. Driver Test
Build and load the kernel module:
```bash
cd driver
make
sudo insmod sysguard_driver.ko
cat /dev/sysguard
sudo rmmod sysguard_driver
```
Expected: driver message is returned.
