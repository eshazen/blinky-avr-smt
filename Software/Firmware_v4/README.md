# Firmware_v4

This is a C program designed to run on an ATTiny44/84 micro.
It displays a message of up to 127 characters in a 5x8 bitmap on a
column of 8 LEDs.  The character set includes [0-9 A-Z .!&?,].

A new message can be downloaded by pointing the board with two light
sensors at a Javascript applet which converts the text message to a
simplified Intel Hex format and transmits it as a binary code.  Two
squares on the monitor represent "clock" (strobe) and "data".

## Build instructions

On Ubuntu Linux, install the packages `avr-libc`, `gcc-avr` and `avrdude`.
You also need gnu make (suggest to install `build-essential`).

(It is certainly possible to build and download the code on
other OS but I don't have documentation for that.  Google is your friend!)

On Linux:  edit `Makefile` to set `DUDEPORT` appropriately for your programmer.
Two common options are:
* `-c avrispv2 -P usb` for the official ISP V2 or clone
* `-c usbtiny -P usb` for a "USB Tiny" or clone

Type `make` to build:

    $ make
    avr-gcc -c -std=c99 -g -Os -mmcu=attiny84 -DF_CPU=1000000 main.c -o main.o
    avr-gcc -Wl,-Map=main.map,--cref -mmcu=attiny84 main.o -o main.elf
    avr-objcopy -j .text -j .data -O ihex main.elf main.hex
    avr-objdump -h -S main.elf > main.lst
    avr-size --common -d main.elf
       text    data     bss     dec     hex filename
       2708      10     171    2889     b49 main.elf

Connect the programming adapter to the 6 pin connector `J1`.
(You may have to install this yourself).

Type `make flash` to program the flash.

## Bugs

Messages longer than 15 characters currently aren't handled correctly
and corrupt the EEPROM.  

For now:  modify the programming code to not allow this

## Details

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




