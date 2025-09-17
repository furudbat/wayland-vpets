# Contributing to Wayland V-Pets / Bongo Cat Overlay

First off, **thank you** for considering contributing! 🎉 Your help improves the project for everyone.
This guide will help you get started, whether you want to report issues, suggest features, or contribute code.

---

## Table of Contents

1. [Reporting Issues](#reporting-issues)
2. [Feature Requests](#feature-requests)
3. [Development Setup](#development-setup)
4. [Code Standards](#code-standards)
5. [Submitting Pull Requests](#submitting-pull-requests)
6. [Style Guidelines](#style-guidelines)
7. [License](#license)

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

---

## Feature Requests

Feature requests are welcome! To submit a request:

1. Check if the feature has already been discussed in [Issues](https://github.com/furudbat/wayland-vpets/issues).  
2. Open a new issue and describe:
   - The problem the feature solves  
   - Expected behavior  
   - Any relevant screenshots or sketches  
   - Optional: Suggested implementation details  

---

## Development Setup

### Prerequisites

See [Building from Source](README.md#-building-from-source) for detailed instructions.

Quick start:

```bash
git clone https://github.com/furudbat/wayland-vpets.git
cd wayland-vpets
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
````

> Legacy `make debug` is supported for old Bongo Cat workflows, or you can just use CMake.

---

## Code Standards

Follow the project’s coding guidelines:

* **Language**: C23 / C++23
* **Memory Safety**: Use RAII and leak-free practices [see system_memory.h](include/utils/system_memory.h)
* **Threading**: Proper synchronization, stop threads before cleanup
* **Modern C++**: Prefer `constexpr`, `enum class`, `ref&`, `nullptr`, move semantics
* **Try to avoid STL & Minimal Templates, you can use C functions and Linux build-in functions**
* **Assets**: Embed large assets in separate TUs
* **Global State**: Avoid globals, pass context structs

For more details, see the [Code Standards section in README](README.md#code-standards).

---

## Submitting Pull Requests

1. Fork the repository and create a branch for your feature or fix:

   ```bash
   git checkout -b feature/my-new-feature
   ```
2. Make your changes following the code standards.
3. Test your changes thoroughly, including multi-monitor and keyboard input scenarios.
4. Commit your changes with clear messages:

   ```bash
   git commit -m "feat: Add support for X feature"
   ```
5. Push your branch and open a Pull Request against `main`.
6. Include a description of what your PR changes and any relevant screenshots or logs.

---

## Style Guidelines

* **Branch Naming**: `feature/xxx`, `bugfix/xxx`, `docs/xxx`
* **Commit Messages**: Use present tense, concise, and descriptive
* **Formatting**: try to Follow existing formatting and indentation, -- @TODO: add `.clang-format` and `.clang-tidy`
* **Documentation**: Update relevant README sections if needed
  * when adding new configuration, pls update [`bongocat.conf`](bongocat.conf)
  * when adding new program arguments update [`cli_show_help` in main](src/core/main.cpp)
    * update [man pages](docs/fragments/options.md)

---

## License

All contributions must comply with the project’s MIT License. By submitting code, you agree to license your contributions under MIT.

---

Thank you for helping make **Wayland Bongo Cat + V-Pets** a better, more delightful overlay! 💖

