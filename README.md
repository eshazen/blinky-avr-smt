# blinky-avr-smt

![Overview Photo](Photos/overview.jpg)
![Blinky](http://edf.bu.edu/pov/taxi.jpg)

## Blinky POV soldering project

This is a soldering practice kit which displays a message in the air
on LEDs when waved back and forth.  

* Programming: https://ohm.bu.edu/~hazen/BlinkyPovAVR/prog/test_prog.html
  
## Ideas

The current board ("Rev 5") hardware/firmware is a bit troublesome.

To-do:

* Improve thermal relief on GND/VCC pads (fixed in 5.1?)
* Change SMT programming connector to TH (fixed in 5.1)
* Add pre-programmed message 
* Improve error-checking and display on download code
  (blink all LEDs on checksum error)
* Consider pre-programming the MCUs?
  (this would require an adapter socket)
  Ordered one on AliExpress 11/11.  Alleged delivery by end Nov.
