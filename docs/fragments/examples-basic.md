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
bongocat --watch-config --config ~/.config/bongocat.conf
```

## Toggle mode
Start or stop running instance

```bash
bongocat --toggle
```

## More
Custom config with hot-reload and custom `output_name`

```bash
bongocat --watch-config --output-name DP-2 --config ~/.config/bongocat.conf
```

## Config from stdin
Load multiple configs via pipe(`|`) and `stdin`

```bash
cat ~/.config/base.bongocat.conf ~/.config/devices.bongocat.conf | bongocat --config -
```

