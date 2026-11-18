# DESCRIPTION

Shows an animated pet in a bar on wlr-layer-shell compositors. Pets include
the classic Bongo Cat, Digimon, Pokémon and more, depending on the binary.
The pet can react to key presses on every keyboard and to system state
(CPU usage, idle time, audio).

The program is lightweight, configurable and can be toggled on or off at
runtime. All sprites are embedded in the binary.

By default, the configuration is read from `$XDG_CONFIG_HOME/bongocat/bongocat.conf`,
`~/.config/bongocat/bongocat.conf` or `bongocat.conf` in the current directory.
You can override this with `--config`. Hot-reloading is supported with
`--watch-config`.
