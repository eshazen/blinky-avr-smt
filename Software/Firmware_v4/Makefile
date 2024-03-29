#
# makefile for BlinkyPovAvr code
#

MCU = attiny84

F_OSC = 1000000

CFLAGS = -std=c99 -g -Os -mmcu=$(MCU) -DF_CPU=$(F_OSC)

LDFLAGS = -Wl,-Map=$(<:.o=.map),--cref -mmcu=$(MCU)

DUDEPORT  = -c avrispv2 -P usb
# DUDEPORT  = -c usbtiny -P usb
DUDEMCU = t84
AVRDUDE  = avrdude $(DUDEPORT) -p $(DUDEMCU) -y -u 

objects = main.o

all: $(objects)  main.hex list

clean:
	rm -f *.o *~ *.hex *.elf *.map *.lst

flash: main.hex
	$(AVRDUDE) -U flash:w:$^:i

list:
	avr-objdump -h -S main.elf > main.lst
	avr-size --common -d main.elf

$(objects): %.o: %.c
	avr-gcc -c $(CFLAGS) $< -o $@

main.elf: main.o 
	avr-gcc $(LDFLAGS) main.o -o $@

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $< $@
