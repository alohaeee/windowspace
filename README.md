# windowspace
windowspace is non-tiling window manager for Windows inspired by aerospace for macOS.

## Installation
```
    scoop bucket add windowspace https://github.com/alohaeee/windowspace
    scoop install windowspace
```

## Documentation

use --help for latest commands.
```
Usage: windowspace [options] [--ipc [--pid <pid>] <command>]

Options:
  --help                         Show this help message
  --create-default-config        Create default config file
  --setup-auto-launch            Register program to start with Windows
  --setup_auto-launch_admin      Register program to start with Windows (admin)
  --remove-auto-launch           Remove program from Windows startup
  --ipc [--pid <pid>] <command>  Send IPC command

IPC Commands:
  workspace_focus (<char>)     Focus workspace by index
  workspace_move (<char>)      Move window to workspace by index
  workspace_back_and_forth     Focus between current and previous workspaces
  window_focus_next            Focus next window
  window_focus_prev            Focus previous window
  window_close                 Close window
  binding_layer_change (<int>) Change binding layer by index
  subprocess (<string>)        Run subprocess
  reload_config                Reload config file
```

windowspace.exe --create-default-config to create default config into `AppData/Roaming/WindowSpace/windowspace.toml` 

## Related projects
* [aerospace](https://github.com/nikitabobko/AeroSpace)
* [komorebi](https://github.com/LGUG2Z/komorebi)