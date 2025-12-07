# Contributing to Wayland V-Pets / Bongo Cat Overlay

First off, **thank you** for considering contributing! 🎉 Your help improves the project for everyone.
This guide will help you get started, whether you want to report issues, suggest features, or contribute code.

---

## Reporting Issues

If you encounter a bug or unexpected behavior:

1. Check if the issue has already been reported in [Issues](https://github.com/furudbat/wayland-vpets/issues).  
2. If not, open a new issue with:
   - **Title**: Short and descriptive  
   - **Description**: Steps to reproduce, expected vs. actual behavior  
   - **Environment**: OS, compositor, Wayland version, Bongo Cat version, input devices  
   - **Logs**: Any relevant debug output

> Please avoid sending private screenshots of proprietary content; only include relevant logs and minimal reproduction steps.

## Feature Requests

Feature requests are welcome! To submit a request:

1. Check if the feature has already been discussed in [Issues](https://github.com/furudbat/wayland-vpets/issues).  
2. Open a new issue and describe:
   - The problem the feature solves  
   - Expected behavior  
   - Any relevant screenshots or sketches  
   - Optional: Suggested implementation details  

---

## Getting Started

### Prerequisites

- Wayland compositor with layer shell support
- GCC or Clang (C++23/C23 support)
- wayland-client, wayland-protocols
- Make and CMake

### Building

```bash
git clone https://github.com/furudbat/wayland-vpets.git
cd wayland-vpets
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
````

> Legacy `make debug` is supported for old Bongo Cat workflows, or you can just use CMake.

### Running

```bash
./build/bongocat -c bongocat.conf -w
```

## Development Workflow

### Code Standards

Follow the project’s coding guidelines:

* **Language**: C23 / C++23
* **Memory Safety**: Use RAII and leak-free practices [see system_memory.h](include/utils/system_memory.h)
* **Threading**: Proper synchronization, stop threads before cleanup
* **Modern C++**: Prefer `constexpr`, `enum class`, `ref&`, `nullptr`, move semantics
* **Try to avoid STL & Minimal Templates, you can use C functions and Linux build-in functions**
* **Assets**: Embed large assets in separate TUs
* **Global State**: Avoid globals, pass context structs

_Run `make format` before committing_

### Key practices

* **Modern Compiler Features:** Requires C23/C++23 (`#embed`)
* **Thread Safety:** Thread-safe logging, mutexes, LockGuard, and atomic operations (`atomic_store/load`)
* **Memory & Resource Management:**
    * Prefer stack over heap; use heap only when required for mutexes or dynamic arrays
    * RAII for resources: Mutex, MMap, Buffers, FileDescriptors
    * Move semantics for cleanup reduction
* **Code Modernization:**
    * Use `ref&` instead of raw pointers (not-nullable)
    * Use `nullptr` instead of `NULL`
    * Replace `#define` with `constexpr` where possible
    * Use `enum class` and default/brace initialization
* **C++ Usage Restrictions:**
    * _Almost_ NO STL (only `<type_traits>` used)
        * Try to avoid using STL, keep core functions coherent with [upstream](https://github.com/saatvik333/wayland-bongocat)
        * Use Linux, Wayland and standard C libs
    * No classes except for RAII; apply **Rule of Five**
    * Minimal `template` usage
* **Asset Management:**
    * Embed large assets in separate translation units
    * Access via dedicated functions
* **Global State:**
    * Reduce globals, prefer context structs passed as parameters
* **Threading:**
    * Allocate memory upfront before starting threads
    * Prefer `create` functions with RVO instead of `init` with out-parameters
    * Stop all threads before releasing memory

### Making Changes

1. Fork the repository and create a branch for your feature or fix:
   ```bash
   git checkout -b feature/my-new-feature
   ```
2. Make your changes following the code standards.
3. Test your changes thoroughly, including multi-monitor and keyboard input scenarios (if you can).
4. Commit your changes with clear messages:

   ```bash
   git commit -m "feat: Add support for X feature"
   ```
5. Push your branch and open a Pull Request against `develop`.
6. Include a description of what your PR changes and any relevant screenshots or logs.

---

## Style Guidelines

* **Branch Naming**: `feature/xxx`, `bugfix/xxx`, `docs/xxx`
* **Commit Messages**: Use present tense, concise, and descriptive
* **Formatting**: try to Follow existing formatting and indentation
* **Documentation**: Update relevant README sections if needed
  * when adding new configuration, pls update [`bongocat.conf.example`](bongocat.conf.example)
  * when adding new program arguments update [`cli_show_help` in main](src/core/main.cpp)
    * update [man pages](docs/fragments/options.md)

### Commit Messages

Use conventional commits:

```
feat: add new feature
fix: resolve bug
docs: update documentation
refactor: improve code structure
```

## Code Structure

```
src/
├── core/       # Main application logic
├── config/     # Configuration parsing
├── graphics/   # Animation and rendering
├── platform/   # Wayland integration
└── utils/      # Error handling, memory
```


## Testing

```bash
# Run with debug logging
./build/bongocat -c bongocat.conf -w
# Build with Sanitizers (UBSAN,ASAN) enabled for checking for memory leaks
```

### Test Scripts

```bash
./scripts/test_bongocat.sh
```

There are also some test scripts, they are just for running, reloading and changing config for integration tests, meaning it's just for triggering the `asserts`.
Also test on your own and trust your eyes when testing four your rice :)

## Reporting Issues

When reporting bugs, please include:

- Your compositor (Sway, Hyprland, etc.)
- Config file contents
- Debug output (`enable_debug=1`)

## License

All contributions must comply with the project’s MIT License. By submitting code, you agree to license your contributions under MIT.

---

Thank you for helping make **Wayland Bongo Cat + V-Pets** a better, more delightful overlay! 💖

