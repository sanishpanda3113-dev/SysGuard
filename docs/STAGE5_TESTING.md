# Stage 5 – Testing, Integration & Improvement

## Testing Categories

### Unit-Level Checks
- CPU percentage calculation
- Memory percentage calculation
- Disk percentage calculation
- Health threshold calculation

### Integration Tests
- Application starts correctly.
- Monitoring modules work together.
- Logging receives current values.
- Process operations work with valid permissions.
- Driver can be built and loaded when kernel headers are available.

### System Tests
- Run on Linux.
- Test under normal CPU load.
- Test with high memory usage.
- Test with a nearly full test filesystem if available.
- Verify behavior with invalid PIDs.

## Reliability Improvements

- Check file opening operations.
- Handle zero/invalid denominators.
- Avoid terminating PID 1 or other protected system processes.
- Keep driver functionality minimal and read-only.

## Results

Record actual results from the Linux machine here before final submission.

| Test | Expected | Actual | Status |
|---|---|---|---|
| Build | Successful | Fill in | PASS/FAIL |
| Dashboard | Displays data | Fill in | PASS/FAIL |
| CPU | Percentage | Fill in | PASS/FAIL |
| Memory | Values | Fill in | PASS/FAIL |
| Disk | Values | Fill in | PASS/FAIL |
| Process list | PIDs/names | Fill in | PASS/FAIL |
| Search | Matching processes | Fill in | PASS/FAIL |
| Logging | File created | Fill in | PASS/FAIL |
| Driver | Device available | Fill in | PASS/FAIL |
