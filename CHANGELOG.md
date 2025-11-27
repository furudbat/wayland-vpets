# Changelog

All notable changes to this project will be documented in this file.

## [3.5.0] - 2025-11-26

### Added
- **Add NEW sprite sheets** - pmd (experimental)

### Fixed
- working (CPU) animation stuck
- fix dm sleep animation

## [3.4.0] - 2025-11-22

### Added
- Add running animation
  - animation speed-up when full CPU


## [3.3.1] - 2025-11-15

### Fixed
- randomize at start-up
- KDE (KWin) rendering (animation freeze)

## [3.3.0] - 2025-11-05

### Added
- **Custom Sprite Sheets** - load custom sprite sheet
  - [Examples](./examples)

### Fixed
- fix pre-loading pen/pen20

## [3.2.3] - 2025-10-30

### Added
- **Add NEW sprite sheet set** - misc
  - [neko](https://github.com/eliot-akira/neko?tab=readme-ov-file#readme)

## [3.2.2] - 2025-10-23

### Added
- **Add Missing Sprites** - add pen/pen20 dm versions
  - pen
  - pen20

### Improved
- refactor animation system - improve animations
  - smoother animation transitions

## [3.2.1] - 2025-10-11

### Fixed
- fix epoll draining
- fix TSAN warnings
- fix default config
- update man pages

## [3.2.0] - 2025-10-11

### Added
- **More Sprites** - add more MS Agents
  - Merlin
  - Rover
- **Movement** - Digimon can walk

### Fixed
- fix config watcher
- use urandom device for RNG seeding
- fix auto-detect resolution with multi-monitor setup

## [3.1.2] - 2025-09-05

### Fixed
- config file handling
- improve input devices check
- improve config watcher
- improve animation update poll

## [3.1.1] - 2025-08-30

### Fixed
- improve CPU usage animation

## [3.1.0] - 2025-08-28

### Added
- **CPU usage** - digimon react to CPU usage
- stdin config - pipe config via `stdin` with `--config -`
- Extend `find-devices` functionality
  - add `--by-id` option
  - add `--ignore-device` option
  - add `--include-mouse` option

### Fixed
- possible race condition and threading bugs

### Improved
- **add pngle** - alternative image loader; less RAM usage


## [3.0.1] - 2025-19-18

### Fixed
- read config with comments

## [3.0.0] - 2025-09-15

### Added
- **more Sprite** - add pkmn sprites
  - [menu sprites](https://archives.bulbagarden.net/wiki/Category:Animated_menu_sprites)


## [2.5.0] - 2025-09-12

_include changes from upstream_

### Added
- **more Sprite** - add custom colored dm sprites (optional)
- toggle bar visibility via signal (SIGUSR1)
- strict mode - only start up when valid config


## [2.4.0] - 2025-09-05

### Added
- `random` option - randomize animation_index at start (Digimon sprites)

### Improved
- **Lazy Loading** - load sprite sheets on demand


## [2.3.0] - 2025-08-30

### Added
- **more Sprite** - add more MS agents (optional)
  - [Links](https://www.spriters-resource.com/pc_computer/microsoftofficexp/asset/104490/)

### Improved
- make toggle more robust


## [2.2.0] - 2025-08-26

_include changes from 1.2.5 (upstream)_

### Added
- **More Sprites** - add more Digimon sprites (optional)
  - [dm](https://humulos.com/digimon/dm/)
  - [dm20](https://humulos.com/digimon/dm20/)
  - [dmx](https://humulos.com/digimon/dmx/)
  - [dmc](https://humulos.com/digimon/dmc/)


## [2.1.1] - 2025-08-25

### Added
- add CMakePresets

### Improved
- multi-threading locking
- fix sanitizer warnings and errors (UB, data races, deadlocks)
- update thread config via epoll

### Fixed
- fullscreen support for multi-monitor (hyprland)

## [2.1.0] - 2025-08-22

### Added
- **More Sprite** - add Clippy (MS Agent)

## [2.0.0] - 2025-08-22

### Moving to C++

_Moving towards C++_

* **reduce usage of pre-processor** - replace `#define` with `constexpr`
* use `ref&` instead of pointer
* use `nullptr` instead of `NULL`
* **Memory Management** - Simple Wrapper for malloc/free calls
  * move semantics
  * reduce manually clean up
* use of `enum class`
* brace initialization
* [add more asserts](https://github.com/tigerbeetle/tigerbeetle/blob/main/docs/TIGER_STYLE.md?trk=public_post_comment-text#safety)

_keep it as close as possible to the original, it's still C and Linux development with C libraries_


## [1.3.1] - 2025-08-08

_include changes from 1.2.4 (upstream)_

### Added
- **Overwrite config parameter** - Overwrite config setting with CLI Parameters
- BREAKING CHANGE: **Multiple processes** - Processes per screen possible (pid file per screen (`output_name`))
- **Reload Config with Signal** - Reload current config with `SIGURS2` signal

### Improved
- replace input fork with thread
- signal handling, use epoll
- CMake: add more compile options/feature-flags (`BONGOCAT_DISABLE_MEMORY_STATISTICS`, `BONGOCAT_LOG_LEVEL`)

### Fixed
- fix wayland memory leaks (toplevel)
- fix potential memory leaks


## [1.3.0] - 2025-08-06

### Added
- **More Sprite** - add Digimon sprite
  - New `animation_name` option 
  - Add minimal [dm - Version 1](https://humulos.com/digimon/dm/) Digimons
- **More buildsystem options** - add CMake
- **Sleep Mode** - new Options for Sleeping
  - New `enable_scheduled_sleep` option: pause animations and display the sleep frame
  - New `idle_sleep_timeout` option: user inactivity before entering sleep mode
- Invert Color - New `invert_color` option: Invert sprite sheet color
- Add KPM reaction - New `happy_kpm` option: Minimum keystrokes per minute (KPM) required to trigger the happy animation

### Improved
- BREAKING CHANGE: **C23** - use new C standard C23
- add Logger MACROs

### Fixed
- fix config reload crashes
- fix potential memory leaks
- code cleanup
- reduce globals variables, use context variables and structs

## [1.2.5] - 2025-08-26 (upstream)

### Added
- **Enhanced Configuration System** - New config variables for fine-tuning appearance and behavior
- **Sleep Mode** - Scheduled or idle-based sleep mode with customizable timing

### Fixed
- **Fixed Positioning** - Fine-tune position, defaults to center

### Improved
- **Default Values** - Refined default configuration values for better out-of-box experience

## [1.2.4] - 2025-08-08

### Added
- **Multi-Monitor Support** - Choose which monitor to display bongocat on using the `monitor` configuration option
- **Monitor Detection** - Automatic detection of available monitors with fallback to first monitor if specified monitor not found
- **XDG Output Protocol** - Proper Wayland protocol implementation for monitor identification

### Fixed
- **Memory Leaks** - Fixed memory leak in monitor configuration cleanup
- **Process Cleanup** - Resolved child process cleanup warnings during shutdown
- **Segmentation Fault** - Fixed crash during application exit related to Wayland resource cleanup

### Improved
- **Error Handling** - Better error messages when specified monitor is not found
- **Resource Management** - Improved cleanup order for Wayland resources
- **Logging** - Enhanced debug logging for monitor detection and selection

## [1.2.3] - 2025-08-02

### Added
- **Smart Fullscreen Detection** - Automatically hides overlay during fullscreen applications for a cleaner experience
- **Enhanced Artwork** - Custom-drawn bongocat image files by [@Shreyabardia](https://github.com/Shreyabardia)
- **Modular Architecture** - Reorganized codebase into logical modules for better maintainability

### Improved
- **Signal Handling** - Fixed duplicate log messages during shutdown
- **Code Organization** - Separated concerns into core, graphics, platform, config, and utils modules
- **Build System** - Updated to support new modular structure

## [1.2.2] - Previous Release

### Added
- Automatic screen detection for all sizes and orientations
- Enhanced performance optimizations

## [1.2.1] - Previous Release

### Added
- Configuration hot-reload system
- Dynamic device detection

## [1.2.0] - Previous Release

### Added
- Hot-reload configuration support
- Dynamic Bluetooth/USB keyboard detection
- Performance optimizations with adaptive monitoring
- Batch processing for improved efficiency

## [1.1.x] - Previous Releases

### Added
- Multi-device support
- Embedded assets
- Cross-platform compatibility (x86_64 and ARM64)
- Basic configuration
