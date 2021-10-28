# SerialTFT
Arduino sketch for TFT display rendering using serial commands

# Current Command Set

```
us - Update screen

fs <color565> - fill screen with color
  
dr <x> <y> <width> <height> <color565> - draw rectangle
  
fr <x> <y> <width> <height> <color565> - draw filled rectangle

tf <font> - set text font (current fonts are "FFSB9", FFSB12", FFSB18", FFSB24")

tc <color565> - set text color
  
ta <alignment> - set text alingment ("t/m/b + l/c/r" - ie: "tc" for top center)

dt <x> <y> <text> - draw text
```
