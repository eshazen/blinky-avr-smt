# Firmware_v4

This is a C program designed to run on an ATTiny44/84 micro.
It displays a message of up to 127 characters in a 5x8 bitmap on a
column of 8 LEDs.  The character set includes [0-9 A-Z .!&?,].

A new message can be downloaded by pointing the board with two light
sensors at a Javascript applet which converts the text message to a
simplified Intel Hex format and transmits it as a binary code.  Two
squares on the monitor represent "clock" (strobe) and "data".

Each clock pulse causes two data bits to be sampled, the first on the
rising edge and the second on the falling edge.  The most-significant
bit of data is sent first, with 4 clock pulses per byte.

The hex record format is as follows:

`NNHHLLTTDD....CC`

Where:

`NN` is the record length.  0 is ignored, 01-0F are valid

`HH` and `LL` represent the starting address in EEPROM.

`TT` is the record type.  00 represents end-of-message

`CC` is an 8 bit checksum on the data




