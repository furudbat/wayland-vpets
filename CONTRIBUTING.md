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

> Legacy `make debug` is supported for old Bongo Cat dev workflows.

`make debug` provides a quick debug build.
You can inspect the old workflow in the old [`Makefile`](Makefile.old).  
_**Note:** The binary name in AUR is `wpets`, but during development and `make install` it is still `bongocat`._

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

#### Moving to C++

This project is migrated to C++ while retaining a C-style foundation for performance, Wayland compatibility and mosty compatible with [upstream](https://github.com/saatvik333/wayland-bongocat).  
The codebase remains largely C under the hood, using Linux + Wayland libraries, while gradually adopting modern C++ practices for safety and maintainability.

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


- `assets/` - Sprite sheets and media
- `src/` - Core application logic and platform-specific code
- `include/` - Headers
- `scripts/` - Utilities and codegen
- `lib/` - External libraries

```
wayland-vpets/
├── assets/             # sprite sheets and media resources
├── Dockerfiles/        # Container build definitions
├── examples/           # Example configurations
├── include/            # Header files (same structure as src/)
├── lib/                # External libraries (image loader)
├── nix/                # NixOS integration
├── protocols/          # Generated Wayland protocols
├── scripts/            # Codegen and utility scripts
└── src/                # Source code
├──── config/           # Configuration system implementation
├──── core/             # Core application logic (main)
├──── embedded_assets/  # Embedded assets
├──── graphics/         # Rendering and graphics implementation
├──── image_loader/     # Assets loading implementations
├──── platform/         # Platform-specific code (input and wayland)
└──── utils/            # General utilities
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

<details>
<summary>Copyright</summary>

This project is **free**, **non-commercial** and not associated with these entities.
Pokémon are owned by Nintendo, Creatures Inc. and GAME FREAK Inc.
Digimon and all related characters, and associated images are owned by Bandai Co., Ltd, Akiyoshi Hongo, and Toei Animation Co., Ltd.
Clippy and other MS Agents are owed by Microsoft.
See [COPYRIGHT](assets/COPYRIGHT.md) for more details.
</details>

---

Thank you for helping make **Wayland Bongo Cat + V-Pets** a better, more delightful overlay! 💖

