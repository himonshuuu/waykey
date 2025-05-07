# waykey

[![License: GPL-3.0](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![GitHub stars](https://img.shields.io/github/stars/himonshuuu/waykey.svg)](https://github.com/himonshuuu/waykey/stargazers)
[![GitHub issues](https://img.shields.io/github/issues/himonshuuu/waykey.svg)](https://github.com/himonshuuu/waykey/issues)

A powerful Linux keyboard monitoring tool that captures and processes keyboard input events in real-time. waykey provides detailed keyboard state information through both a named pipe and a JSON state file, making it perfect for keyboard state visualization, gaming overlays, or custom keyboard monitoring applications.

## Features

- Real-time keyboard state monitoring
- Multiple output methods:
  - Named pipe for live event streaming
  - JSON state file for current keyboard state
- Automatic keyboard device detection
- Support for custom device selection
- Thread-safe state management
- Clean signal handling for graceful shutdown

## Requirements

- Linux system
- [libinput](https://wayland.freedesktop.org/libinput/doc/latest/) - For handling input devices
- [json-c](https://json-c.github.io/json-c/json-c-0.16/doc/html/index.html) - For JSON state management
- [pthread](https://man7.org/linux/man-pages/man7/pthreads.7.html) - For concurrent processing






# Installation



### AUR Package (Arch-based distributions)
comming soon... :D



## Building from Source

### Dependencies
```bash
# Arch/Manjaro
sudo pacman -S libinput json-c base-devel

# Debian/Ubuntu
sudo apt-get install libinput-dev libjson-c-dev build-essential

# Fedora/RHEL
sudo dnf install libinput-devel json-c-devel gcc make
```

```bash
git clone https://github.com/himonshuuu/waykey.git
cd waykey
make
sudo make install
```

## Usage

```bash
waykey [OPTIONS]

Options:
  -d, --device PATH    Input device path (optional)
  -p, --pipe PATH      Named pipe location (default: /tmp/waykey_pipe)
  -s, --state PATH     State file location (default: /tmp/waykey_state.json)
  -l, --list          List available keyboard devices and exit
  -h, --help          Show help message
```

### Examples

```bash
# Auto-detect keyboard and start monitoring
sudo waykey

# Monitor specific keyboard device
sudo waykey --device /dev/input/event3

# Use custom paths for pipe and state file
sudo waykey --pipe /tmp/custom_pipe --state /tmp/custom_state.json

# List available keyboard devices
sudo waykey --list
```

### Reading the Output

1. **Named Pipe Output**
   ```bash
   # In one terminal
   sudo waykey
   
   # In another terminal
   cat /tmp/waykey_pipe
   ```

2. **State File**

   ```bash
   # Monitor the state file
   watch -n 0.1 cat /tmp/waykey_state.json
   ```

## Integration with Waybar

1. **Install the waybar-waykey script** (if building from source):

```bash
# Download the script
curl -s "https://raw.githubusercontent.com/himonshuuu/waykey/main/extra/waybar.py" -o waybar.py
# Install it
sudo install -Dm755 waybar.py /usr/bin/waybar-waykey
# Clean up
rm waybar.py
```

2. **Install the systemd service file** (if building from source):
```bash
# Dowmload fhe service file
curl -s "https://raw.githubusercontent.com/himonshuuu/waykey/main/extra/waykey.service" -o waykey.service

# install it (root required)
sudo install -Dm644 waykey.service "/usr/lib/systemd/system/waykey.service"
# Cleanup
rm waykey.service
```


3. **Add to Waybar config** (`~/.config/waybar/config` or `~/.config/waybar/config.jsonc`):

```json
"custom/keypress": {
    "exec": "waybar-waykey",
    "return-type": "json",
    "interval": 0,
    "format": "{}",
    "tooltip": false
}
```

4. **Add styling to Waybar CSS** (`~/.config/waybar/style.css`):
```css
#custom-keypress {
    background-color: #4b4b4b;
    border-radius: 8px;
}
```
*You can checkout my dofiles :P*

5. **Start waykey service**:

```bash
sudo systemctl enable --now waykey.service
```

6. **Start the Systemd Service**

waykey comes with a systemd service (if installed from AUR) that can be enabled to run at system startup:

```bash
# Enable and start the service
sudo systemctl enable --now waykey.service

# Check service status
sudo systemctl status waykey.service
```
7. **Restart Waybar** to apply changes:

```bash
# If running Waybar directly
killall waybar && waybar &

# Or with your compositor's configuration
# (e.g., using Hyprland's dispatcher)
hyprctl dispatch exec "killall waybar && waybar &"
```

--- 

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests.

## License

This project is licensed under the [GPL-3.0](LICENSE) license.

## Acknowledgments

This project was inspired by [siduck/bubbly](https://github.com/siduck/bubbly). Thanks for the idea!