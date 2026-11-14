## Basic usage
Run with default config

```bash
bongocat
```

## Watch config (recommended)
With config hot-reload

```bash
bongocat --watch-config
```

## Configuration
Custom config with hot-reload

```bash
bongocat --watch-config --config ~/.config/bongocat/bongocat.conf
```

## Toggle mode
Start or stop running instance

```bash
bongocat --toggle
```
## Config from stdin
Load multiple configs via pipe(`|`) and `stdin`

```bash
cat ~/.config/bongocat/base.bongocat.conf ~/.config/bongocat/devices.bongocat.conf | bongocat --config -
```


## More

### Overwrite output
Custom config with hot-reload and custom `monitor`

```bash
bongocat --watch-config --output-name DP-2 --config ~/.config/bongocat/bongocat.conf
```

### PID Numbering
When having multiple PID instances ("instance already running" on the same screen), use `--nr` to avoid PID conflicts.

```bash
bongocat --watch-config --nr 1 --config ~/.config/bongocat/digimon1.bongocat.conf
bongocat --watch-config --nr 2 --config ~/.config/bongocat/digimon2.bongocat.conf
bongocat --watch-config --nr 3 --config ~/.config/bongocat/digimon3.bongocat.conf
```
