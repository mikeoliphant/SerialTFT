# SerialTFT
Arduino sketch for TFT display rendering using serial commands.

This is a sketch for using an arduino compatible micro-controller with a TFT screen as an external user interface controlled by sending simple graphics primitive commands over a serial connection.

It is currently set up to use the [TFT eSPI library](https://github.com/Bodmer/TFT_eSPI), but it should be easy to adapt. It has been tested using a [Seeed Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) device.

It makes use of the TFT eSPI Sprite class. This greatly accelerates rendering speed. More information here: http://blog.nostatic.org/2021/10/speeding-up-arduino-tft-tftespi-writes.html.

The Sprite-based rendering requires that the device have enough ram to use as a full-screen buffer. It would be simple to change the code to do direct rendering, though.

Because the Sprite-based rendering uses a temporary buffer, the "us" (update screen) command is required to render the buffer to the actual TFT. The idea is that you issue a series of rendering commands, and then do "us" to push what you have rendered to the display.

# Current Command Set

The current command set is limited to drawing rectangles and text. I plan to add additional functionality as I need it.

Commands muse be terminated with a newline ('\n') and should not exceed 255 characters.

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
