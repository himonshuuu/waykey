# Maintainer: Himanshu Saikia <saikiahimangshu1256@gmail.com>

pkgname=waykey
pkgver=0.1.0
pkgrel=1
pkgdesc="A powerful Linux keyboard monitoring tool that captures and processes keyboard input events in real-time"
arch=('x86_64')
url="https://github.com/himonshuuu/waykey"
license=('GPL3')
depends=('libinput' 'json-c' 'systemd' 'libyaml')
makedepends=('make' 'gcc' 'git')
backup=('usr/lib/systemd/system/waykey.service')
source=("git+https://github.com/himonshuuu/${pkgname}.git")
sha256sums=('SKIP')

validpgpkeys=('189D1B9319C8061A777A89FFBF2647652B8D16C3') # Himanshu Saikia <saikiahimangshu1256@gmail.com>

pkgver() {
  cd "$pkgname"
  git describe --long --tags | sed 's/\([^-]*-\)g/r\1/;s/-/./g;s/^v//' || echo "0.1.0.$(git rev-list --count HEAD).g$(git rev-parse --short HEAD)"
}

build() {
    cd "$pkgname"
    make
}

package() {
    cd "$pkgname"
    make DESTDIR="$pkgdir" install
    
    curl -s "https://raw.githubusercontent.com/himonshuuu/waykey/main/extra/waybar.py" -o waybar.py
    install -Dm755 waybar.py "$pkgdir/usr/bin/waybar-waykey"
    rm waybar.py
    
    curl -s "https://raw.githubusercontent.com/himonshuuu/waykey/main/extra/waykey.service" -o waykey.service
    install -Dm644 waykey.service "$pkgdir/usr/lib/systemd/system/waykey.service"
    rm waykey.service


    install -Dm755 /dev/stdin "$pkgdir/usr/share/libalpm/scripts/$pkgname-setup.sh" << EOF
#!/bin/bash

# Detect keyboard devices
DEVICE_PATH=\$(/usr/bin/waykey --list | grep -v "Detected" | grep -E "^\[[0-9]+\]" | head -1 | sed -E 's/.*\((\/dev\/input\/event[0-9]+)\).*/\1/')

if [ -n "\$DEVICE_PATH" ]; then
    # Update systemd service file with detected device
    sed -i "s|^ExecStart=/usr/bin/waykey.*|ExecStart=/usr/bin/waykey -d \$DEVICE_PATH|" /usr/lib/systemd/system/waykey.service
    systemctl daemon-reload
    echo "Detected keyboard device: \$DEVICE_PATH"
    echo "To start and enable waykey service: sudo systemctl enable --now waykey.service"
else
    echo "No keyboard devices detected automatically."
    echo "Please run 'sudo waykey --list' to see available devices"
    echo "Then edit /usr/lib/systemd/system/waykey.service with your preferred device"
fi
EOF

    # Install pacman hook for post-install script
    install -Dm644 /dev/stdin "$pkgdir/usr/share/libalpm/hooks/$pkgname-setup.hook" << EOF
[Trigger]
Type = Package
Operation = Install
Operation = Upgrade
Target = waykey

[Action]
Description = Setting up waykey with detected keyboard...
When = PostTransaction
Exec = /usr/share/libalpm/scripts/$pkgname-setup.sh
EOF

    # Add Waybar integration documentation
    install -Dm644 /dev/stdin "$pkgdir/usr/share/doc/$pkgname/waybar-integration.md" << EOF
# Waybar Integration

To use waykey with Waybar, add this to your Waybar config:

\`\`\`json
"custom/keypress": {
    "exec": "waybar-waykey",
    "return-type": "json",
    "interval": 0,
    "format": "{}",
    "tooltip": false
}
\`\`\`

And add this to your CSS:

\`\`\`css
#custom-keypress {
    background-color: #4b4b4b;
    border-radius: 8px;
    box-shadow: 1px 1px 2px 1px rgba(0, 0, 0, 0.185);
    padding-left: 4px;
    padding-right: 4px;
    margin: 2px;
}
\`\`\`

After installing waykey, enable the service:

\`\`\`bash
sudo systemctl enable --now waykey.service
\`\`\`

If you need to use a different keyboard device, list available devices with:

\`\`\`bash
sudo waykey --list
\`\`\`

Then edit the service file with your preferred device:

\`\`\`bash
sudo nano /usr/lib/systemd/system/waykey.service
\`\`\`
EOF
}