# cpp-systems-lab

this repository documents my journey in low-latency systems engineering. the focus is transitioning from high-level abstractions to understanding how c++ code interacts directly with hardware, including the cpu, memory, disk, and linux kernel.

## tools & environment

* **neovim**: basic navigation, insert/command modes for terminal-based editing.
* **tmux**: window and session management for an efficient compile/run cycle.
* **linux**: manipulating raw file descriptors, directory permissions, and kernel interfaces (/proc).

## repository structure

* **`fundamentals/`** — focus: transition to system development in c++, terminal tools, and performance-driven logic.
  * `login-system/`: creates a gatekeeper with attempt limits and handling of infinite loops.
  * `reverse-array/`: implements a high-performance array reversal algorithm by manipulating raw memory addresses directly, avoiding heap allocation (o(1) spatial complexity).
  * `asset-manager/`: builds a financial asset management system using c++ class-based encapsulation, persisting state locally via flat-file .db, and manually reconstructing objects in memory.
  * `sys-monitor/`: a lightweight linux memory monitor that reads kernel data directly from /proc/meminfo, exposing it as a cli tool using professional build practices (-wall, -o3).

* **`storage/`** — focus: understanding how data is physically stored and retrieved from disk.
  * ***coming soon: log-structured storage engine***

* **`system-io/`** — focus: in-depth exploration of linux syscalls and filesystem behavior, bypassing standard c++ streams.
  * `sequential-vs-random-write/`: benchmarks the latency penalty of lseek by comparing sequential append operations versus random in-place updates.
  * `block-size-throughput/`: analyzes the impact of buffer size (4kb vs 1mb) on i/o throughput and syscall overhead.
  * `fsync-latency/`: investigates the cost of durability by measuring the performance gap between volatile page cache writes and hardware synchronized writes (fsync).
  * `mmap-editor/`: demonstrates memory-mapped file manipulation by creating a file, mapping it into ram with mmap(), writing data directly, and syncing changes back to disk.
  * `fd-stream/`: uses raw posix system calls (open, read, write, close) and file descriptors to read a file and output to stdout.

* **`processes/`** — focus: inter-process communication, scheduling, and process lifecycle.
  * `fork-generator/`: explores basic process management by creating multiple child processes with fork(), while the parent monitors and collects termination status using waitpid() in non-blocking mode.
  * `fork-exec-shell/`: implements a minimal interactive shell loop that parses user input, forks a child process, and replaces its memory image using execvp.
  * `pipe-latency/`: measures ipc latency using two unidirectional pipes between a parent and child, performing a high-frequency ping-pong of single-byte messages to time round-trip duration.

* **`memory/`** — focus: memory allocation, heap management, raw pointers, and execution faults.
  * `custom-malloc/`: implements a minimal userspace heap allocator using sbrk() to request memory from the kernel, tracking blocks with a linked list of headers for first-fit recycling.
  * `pointer-arithmetic/`: demonstrates manual heap allocation using new/delete[], utilizing raw pointers to reverse an array in-place.
  * `leaks/`: simulates a memory leak by overriding a pointer before freeing its block, creating unreachable memory (detected via valgrind).
  * `double-free/`: causes a runtime abort and core dump by calling delete twice on the same pointer, corrupting the internal cache of the memory allocator.
  * `dangling-pointer/`: triggers an invalid write error by attempting to assign a value to a memory address that has already been released back to the heap.
  * `null-deref/`: intentionally passes a null pointer to a function that dereferences it, generating a segmentation fault for gdb stack trace analysis.
  * `pagemap/`: translates a virtual memory address to its corresponding physical address by reading /proc/self/pagemap, illustrating page frame calculation.
  * `manual-reallocation/`: illustrates dynamic array mechanics by allocating a larger heap block, copying old data, and safely freeing previous memory to prevent internal fragmentation.

* **`experiments/`** — focus: unstructured sandbox for testing new concepts.
  * `scratch/`: temporary files and quick syntax checks.
  * `quick-tests/`: mini-benchmarks for specific functions.
  * `one-off/`: isolated single-file scripts that do not fit a larger module.

## how to run

each project folder contains self-contained experiments. standard compilation follows this format:

```
g++ -wall -wextra -o3 folder-name/main.cpp -o app_name
./app_name
```
