
Debian
====================
This directory contains files used to package sanityd/sanity-qt
for Debian-based Linux systems. If you compile sanityd/sanity-qt yourself, there are some useful files here.

## sanity: URI support ##


sanity-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install sanity-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your sanity-qt binary to `/usr/bin`
and the `../../share/pixmaps/sanity128.png` to `/usr/share/pixmaps`

sanity-qt.protocol (KDE)

