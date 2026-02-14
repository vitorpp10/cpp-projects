# february / labs

focus: systems programming and storage engines

this month shifted towards understanding how data is physically stored and retrieved from disk. moved away from high-level abstractions like std::fstream to work directly with linux system calls and memory layout.

## projects

### 01-minidb-kv

- topics: file descriptors (open/read/write), lseek & offsets, binary serialization, struct packing (__attribute__((packed))), in-memory indexing.
- goal: build a persistent key-value store from scratch that manages its own binary format. implements an append-only log structure for high-performance writes and maintains a ram-based hash index to map keys to physical disk offsets for o(1) retrieval. guarantees byte-level alignment and handles manual buffer management.

## tools mastered

- neovim: basic navigation and insert/command modes.
- tmux: window management for compile/run cycle.
- linux: directory permissions and manipulating raw file descriptors.
