# c11fetch installation
## Installing dependencies
c11fetch requires just a working C library, a C99/C11 compiler, meson and ninja.

### Arch Linux / Artix Linux / Parabola GNU/Linux-libre
```
pacman -S gcc meson ninja
```

### Devuan / Debian
```
apt install build-essential meson
```

### Gentoo
gcc, meson and ninja should be installed automatically.

### Android with Termux
```
apt install clang python ninja
pip3 install meson
```

### Alpine Linux
```
apk add build-base ninja meson
```

### OpenBSD
Requires an OpenBSD installation with installed compiler (comp-XX tarball) and:
```
pkg_add meson ninja
```

### macOS
Requires installed Xcode Command Line Tools and homebrew.
```
brew install meson ninja
```

## Installing c11fetch
To compile and install c11fetch:
```sh
meson build --buildtype=release --strip
meson install -C build
```

c11fetch can be executed by running following command:
```sh
c11fetch
```

### For android users: 
- specify meson prefix to your terminal's mini-chroot. For example: 
```
-Dprefix=/data/data/com.termux/files/usr
```
- if installation fails, remove '--strip' from meson flags.

### For macOS/Mac OS X users:
- if linker get errors about plugin stripping, add meson flag:
```
-Dstrip-plugins=false
```
and remove '--strip' flag from meson flags.

### For Haiku users
- If you use bash as default shell, you need to export SHELL variable. To do this just simply add line:
```sh
export SHELL
```
to
```
~/config/settings/profile
```

### External 'dl' library
If your system provides dlopen() and dlsym() via external 'dl' library, add to meson flags:
```
-Dlink-libdl=true
```