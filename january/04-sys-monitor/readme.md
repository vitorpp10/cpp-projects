# 04-sys-monitor

low-level linux memory monitor built with c++, makefile automation, and bash-based deployment.

this project focuses on direct interaction with the linux kernel via the `/proc` virtual filesystem, combined with professional build, deploy, and automation practices commonly used in real-world systems engineering and devops workflows.

---

## overview

the goal of this project is to create a lightweight system monitoring tool that reads memory information directly from the linux kernel and exposes it via a command-line executable available system-wide.

key characteristics:

* reads kernel memory metrics from `/proc/meminfo`
* parses raw kernel text using low-level c++ constructs
* uses a makefile for reproducible builds and compiler control
* deploys the binary into `/usr/local/bin`
* designed to be automated via `cron`

---

## project structure

```
04-sys-monitor.cpp   # core c++ source code
makefile             # build automation and compilation rules
deploy.sh            # automated build + system-wide deploy script
```

---

## core concepts used

* linux kernel introspection (`/proc` filesystem)
* low-level file i/o with `std::ifstream`
* string parsing with `std::string` and `std::stringstream`
* manual text tokenization
* compiler optimization and warning control
* unix permissions and binary deployment
* shell scripting and automation

---

## c++ implementation details

### kernel interaction via `/proc`

linux exposes real-time kernel data through the virtual filesystem `/proc`. the file `/proc/meminfo` contains detailed memory statistics updated by the kernel itself.

the program opens this file directly:

* no system calls to external tools (`free`, `awk`, etc.)
* no shell execution
* pure kernel-backed data access

this ensures:

* minimal overhead
* maximum reliability
* deterministic behavior

### file reading logic

* `std::ifstream` is used to open `/proc/meminfo` in read-only mode
* the file is read line-by-line using `std::getline`
* each line is scanned using `std::string::find`

example logic:

* search for lines containing `memtotal`
* (future extension: also parse `memfree`)

### string parsing strategy

once the target line is found, the program uses `std::stringstream` to split the raw kernel text into structured tokens.

typical `/proc/meminfo` line format:

```
memtotal:       16384256 kB
```

tokenized into:

* name   → `memtotal:`
* value  → `16384256`
* unit   → `kB`

this approach avoids fragile manual indexing and allows safe, readable extraction of numeric values.

### output

the parsed values are reformatted and printed to stdout, allowing the program to be:

* used interactively in a terminal
* redirected to log files
* consumed by cron jobs

---

## makefile design

the makefile provides a professional, reproducible build pipeline.

### variables

* `cxx = g++` → explicitly selects the compiler
* `flags = -wall -o3` → enables strict warnings and maximum optimization
* `target = sys_monitor` → defines the output binary name

### compilation flags

* `-wall`

  * enables extensive compiler diagnostics
  * helps detect undefined behavior and logical errors early

* `-o3`

  * aggressive optimization level
  * focuses on execution speed and instruction-level optimization
  * commonly used in performance-critical and hft-style workloads

### targets

* `all`

  * default entry point (equivalent to `main` in c++)
  * builds the final executable

* `clean`

  * removes generated binaries
  * ensures clean rebuilds and avoids stale artifacts

---

## deploy script (bash)

the `deploy.sh` script automates the full build and installation process.

### responsibilities

* cleans previous builds
* recompiles the project using `make`
* installs the binary system-wide
* sets correct execution permissions

### system-level deployment

the binary is moved to:

```
/usr/local/bin/sys_monitor
```

this location:

* is included in the default `$path`
* is intended for locally installed system tools
* avoids conflicts with distribution-managed binaries

### permissions

`chmod +x` ensures the binary is executable by the system.

`sudo` is required because the script modifies protected system directories.

---

## summary

this project demonstrates:

* real kernel-level data access
* low-level c++ systems programming
* professional build tooling
* unix deployment standards
* automation-ready design

it is intentionally minimal, explicit, and close to the operating system — exactly how real system tools are built.
