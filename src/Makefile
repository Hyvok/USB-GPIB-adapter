PROJECT=gpib_adapter
ISP_PROGRAMMER=buspirate
ISP_FLAGS=-p m16u4 -P /dev/ttyUSB0
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-g -Os -Wall -mcall-prologues -mmcu=atmega16u4
SOURCES=main.c

all: $(PROJECT).hex

$(PROJECT).hex: $(PROJECT).out
	$(OBJCOPY) -j .text -O ihex $(PROJECT).out $(PROJECT).hex

$(PROJECT).out: $(SOURCES)
	$(CC) $(CFLAGS) -I./ -o $(PROJECT).out $(SOURCES)

program-usb:
	dfu-programmer erase
	dfu-programmer flash $(PROJECT).hex

program-isp:
	avrdude -c $(ISP_PROGRAMMER) $(ISP_FLAGS) -e
	avrdude -c $(ISP_PROGRAMMER) $(ISP_FLAGS) -U flash:w:$(PROJECT).hex

# Program fuses with avrdude, settings: 
# CKSEL = 0010, SUT = 10: Internal RC-oscillator, 6ck + 64ms start-up
# BOOTSZ = 10: Boot flash size 2048 words, start address $1800
# SPIEN = 0: SPI program downloading enabled
# JTAGEN = 0: JTAG interface enabled
# BODLEVEL = 000: Brown-out detection level VCC=4.3V
# HWB = 0: Hardware boot enable
fuses:
	avrdude -c buspirate -p m16u4 -P /dev/ttyUSB0 -U lfuse:w:0xe2:m \
			-U hfuse:w:0x98:m -U efuse:w:0xf0:m

clean:
	rm -f $(PROJECT).out
	rm -f $(PROJECT).hex
