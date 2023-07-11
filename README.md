# li-background
HTML background for wlroots based desktops and KDE

<video src="https://github.com/mi4code/li-background/assets/114027049/da056a4d-9e9d-4602-bfff-3ede21785c7a"></video>


## Compilation / Instalation:

Instal dependencies:
`sudo apt-get install libgtk-3-dev libwebkit2gtk-4.0-dev libgtk-layer-shell-dev`
(Debian)
`sudo pacman -S base-devel gtk3 webkit2gtk gtk-layer-shell`
(Arch)

Compile:
```
g++ -o li-background background.cc `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0 gtk-layer-shell-0`
```

Run:
`./li-background`

Options:
```
li-background
 (HTML background for wlroots based desktops)
 arguments:
  --display <number>
  --file </path/to/*.html>
  --help
```


## TODOs:
 - [ ] add settings UI
 - [ ] should be more connected with display output settings (one over all/one for one)
 - [x] file selection: cmd parameter / selected file / first `background*.html` in working directory / error message
 - [ ] add API to HTML (for calling cmd / obtaining system informations / ...) - can be just named pipe `li-background-pipe`
 - [ ] add more examples (video, scheduling, web resources, ...)
 - [ ] disable zoom, disable text selection, disable mouse actions (as settings options or in html ~ css `pointer-events: none;`)
 - [ ] performance optimalizations (stop rendering when desktop not shown, option to pre-render HTML to bitmap) 
 - [ ] fix hover bug when pointer leaves window
 
