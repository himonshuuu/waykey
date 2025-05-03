# waykey 🎯

[![License: GPL-3.0](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Build Status](https://img.shields.io/github/actions/workflow/status/himonshuuu/waykey/build.yml?branch=main)](https://github.com/himonshuuu/waykey/actions)
[![GitHub stars](https://img.shields.io/github/stars/himonshuuu/waykey.svg)](https://github.com/himonshuuu/waykey/stargazers)
[![GitHub issues](https://img.shields.io/github/issues/himonshuuu/waykey.svg)](https://github.com/himonshuuu/waykey/issues)

A Linux tool that captures keyboard input events and gives you real-time state updates. Perfect for keystroke monitoring.


## Requirements

- Linux system
- [libinput](https://wayland.freedesktop.org/libinput/doc/latest/) - For handling input devices
- [json-c](https://json-c.github.io/json-c/json-c-0.16/doc/html/index.html) - For JSON magic
- [pthread](https://man7.org/linux/man-pages/man7/pthreads.7.html) - For smooth threading

## Installation

### Quick Start
```bash
# Arch/Manjaro
sudo pacman -S libinput json-c base-devel

# Debian/Ubuntu
sudo apt-get install libinput-dev libjson-c-dev build-essential

# Fedora/RHEL
sudo dnf install libinput-devel json-c-devel gcc make

# Build it!
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
  -h, --help          Show help
```

### Quick Examples

```bash
# Auto-detect and go
sudo waykey

# Pick your keyboard
sudo waykey --device /dev/input/event3

# Custom paths
sudo waykey --pipe /tmp/custom_pipe --state /tmp/custom_state.json
```

## 🤝 Contributing

Got ideas?:

1. Fork it
2. Create your branch: `git checkout -b cool-feature`
3. Commit changes: `git commit -m 'Add cool feature'`
4. Push it: `git push origin cool-feature`
5. Open a PR


> This project was inspired by [siduck/bubbly](https://github.com/siduck/bubbly)  Thanks for the idea! 

## 📝 License

Licensed under [GPL-3.0](LICENSE) - do awesome stuff with it!
