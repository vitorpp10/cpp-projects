# march / labs

**focus:** os internals and process management

this month's main goal was to dive deep into linux mechanisms, focusing on advanced process management, system architecture, and terminal lifecycle using low-level system calls.

## projects

### 01 - mini-shell
* **topics:** process creation (`fork`), binary execution (`execve`), zombie process handling (`waitpid`), built-in commands (`chdir`), memory leak prevention.
* **goal:** engineer a functional linux terminal emulator (repl) capable of executing external binaries, managing background execution state (`&`), and preventing resource leaks.

## tools mastered

* **valgrind:** strict memory leak detection and memory error profiling.
* **linux api:** direct kernel interaction using raw posix system calls.
* **g++ toolchain:** compiling with strict flags for performance and memory checking.
