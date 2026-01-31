# january / labs

## focus: transition and fundamentals

this month's main goal was to migrate from a high-level workflow to system development in c++, focusing on terminal tools and performance-driven logic.

## projects

- **01-simple-login-system**:
    - **topics**: `std::string`, `while (true)`, `control flow`, `g++ compilation`.
    - **goal**: create a gatekeeper with attempt limits and handling of infinite loops.

- **02-reverse-array**:
    - **topics**: `pointer arithmetic`, `in-place memory manipulation`, `vconverging pointers strategy`, `vvspatial complexity o(1)`, `g++ toolchain`.
    - **goal**: implement a high-performance array reversal algorithm by manipulating raw memory addresses directly, avoiding heap allocation or auxiliary buffers to simulate low-latency data processing.

- **03-asset-manager**:
    - **topics**: `c++ class-based design (encapsulation over structs)`, `filesystem persistence with flat-file .db`, `manual parsing and memory reconstruction`.
    - **goal**: build a basic financial asset management system that ensures data integrity through encapsulation, persists state locally using files, and reconstructs objects efficiently in memory using low-level c++ mechanisms.

- **04-sys-monitor**:
    - **topics**: `linux kernel introspection via /proc/meminfo`, `low-level c++ file i/o and string parsing`, `manual text tokenization with stringstream`, `performance-oriented compilation (-wall, -o3)`
    - **goal**: build a lightweight, system-wide linux memory monitor that reads kernel data directly from /proc, exposes it as a cli tool, and follows professional build, deploy, and automation practices used in real-world systems engineering.

## tools mastered

- **neovim**: basic navigation and insert/command modes.
- **tmux**: window management for compile/run cycle.
- **linux**: directory and permissions manipulation via terminal.
