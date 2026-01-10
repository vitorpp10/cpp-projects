# 01-simple-login-system

## Overview

This is the first lab focused on control flow logic and string manipulation in C++. The goal was to build a "gatekeeper" system that validates credentials and manages error states with a strict attempt limit.

## Technical Implementation

- **String handling**: Used the `<string>` library to manage character sequences. Unlike the primitive `char` type (which supports only one byte), `std::string` allows efficient comparison of full sequences, which is crucial for validating the password "streetfighter".

- **Infinite loop architecture**: The main structure uses a `while (true)` loop. This approach allows full control over the program's lifecycle internally, breaking the loop only when security conditions (success or lockout) are met.

- **State tracking**: Implemented an `int` variable (`count`) to act as a failure counter. On each negative iteration, the state increments (`count += 1`), triggering a security mechanism when `count == 3`.

- **Flow control**:
  - `break`: Ends execution immediately after success or attempt overflow.
  - `continue`: Restarts the data capture cycle while the security limit has not been reached.

- **Performance note**: Used `\n` instead of `std::endl` to avoid unnecessary buffer flushes, ensuring faster and more efficient terminal output.

## Compilation

To compile and run this lab via terminal (Linux):
```bash
g++ 01-simple-login.cpp -o login_system && ./login_system
