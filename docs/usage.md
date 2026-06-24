
## Command Line

```bash
wpets-all [OPTIONS]

Options:
  -h, --help                Show this help message
  -v, --version             Show version information
  -c, --config              Specify config file (default: ~/.config/bongocat.conf)
  -w, --watch-config        Watch config file for changes and reload automatically
  -t, --toggle              Toggle bongocat on/off (start if not running, stop if running)
  -m, --monitor NAME        Force specific monitor output
      --random              Randomize animation_name at start up
      --strict              Only start up with a valid config and valid parameter
      --nr NR               Specify Nr. for PID file to avoid conflicting ruinning instances
      --ignore-running      Ignore current running instance (avoid PID file conflicts)
```

### Examples

```bash
# Basic usage (bongocat)
wpets

# Run immediately (bongocat)
wpets --watch-config

# Custom config with hot-reload (bongocat)
wpets --watch-config --config ~/.config/bongocat/bongocat.conf


# drop-in replacement for bongocat (bongocat)
wpets --watch-config --config ~/.config/bongocat/bongocat.conf

# pokemon sprites
wpets-pkmn --watch-config --config ~/.config/bongocat/pkmn.bongocat.conf
wpets-pkmn --watch-config --config ~/.config/bongocat/pmd.bongocat.conf

# most sprites available (Recommended)
wpets-all --watch-config --config ~/.config/bongocat/bongocat.conf
wpets-all --watch-config --config ~/.config/bongocat/digimon.bongocat.conf
wpets-all --watch-config --config ~/.config/bongocat/clippy.bongocat.conf
wpets-all --watch-config --config ~/.config/bongocat/neko.bongocat.conf
```

> `wpets` is the minimal binary. `wpets-all` bundles most sprites and is the recommended default. `wpets-ms-agent` and `wpets-pkmn` carry the larger sprite sheet variants.

See [examples/](examples) for more configs.

#### Hyprland

For [hyprland](https://hypr.land/) users, you can autostart `wpets` in your `hyprland.conf`:

```ini
# Auto start
exec-once = wpets-all --watch-config --config ~/.config/bongocat/screen1.bongocat.conf -m HDMI-A-1
exec-once = wpets-all --watch-config --config ~/.config/bongocat/screen2.bongocat.conf -m DP-1
exec-once = wpets-all --watch-config --config ~/.config/bongocat/screen3.bongocat.conf
exec-once = wpets-all --watch-config --config ~/.config/bongocat/screen4.bongocat.conf --random
```

> **Tip:** If waybar covers your pet, delay startup with `sleep 5 &&` - both run on the same layer and waybar may overlap.

<details>
<summary>More config examples</summary>

**Transparent bar, bottom-anchored, centered pet:**
```ini
overlay_position=bottom
overlay_opacity=0
cat_align=center
cat_height=80
```

**Pixel-perfect retro sprites (Digimon/Pokémon):**
```ini
enable_antialiasing=0
animation_name=Agumon
```

**Black Digimon sprite in dark-mode:**
```ini
enable_antialiasing=0
animation_name=dm20:Agumon
invert_color=1
```

**Random pet every session (great for variety):**
```ini
random=1
random_on_reload=1
```

**Pet that evolves while you use your PC:**
```ini
animation_name=Botamon
evolution=uptime
```
</details>
