# Section 5.3 - Example 5.3 Solving Blackjack (Monte Carlo Control)

## Requirements
Large static arrays (as used in previous examples) were causing stack smashing.
Switched to dynamically allocated arrays via `libvolk`.

Install on Ubuntu derivates: `sudo apt install libvolk2-bin libvolk2-dev`

Install on Arch: `sudo pacman -S libvolk`

## Run
Run `./build.sh && ./main`
