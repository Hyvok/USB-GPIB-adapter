TARGET			=	GPIBAdapter
MCU          	= 	atmega16u4
ARCH         	=	AVR8
F_CPU        	=	8000000
# Not 100% sure if this is correct!
F_USB			=	$(F_CPU)
OPTIMIZATION 	=	s
ISP_PROGRAMMER	=	buspirate
ISP_FLAGS		=	-p m16u4 -P /dev/ttyUSB0
CC				=	avr-gcc
OBJCOPY			=	avr-objcopy
CC_FLAGS     	= 	-DUSE_LUFA_CONFIG_HEADER -IConfig/
CFLAGS			=	-g -Os -Wall -mcall-prologues -mmcu=atmega16u4 -std=c99 \
					-DF_CPU=$(F_CPU) -DF_USB=$(F_USB) $(CC_FLAGS)
SRC				=	$(TARGET).c Descriptors.c $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
LUFA_PATH    	= 	./lib/LUFA

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).o
	$(OBJCOPY) -j .text -O ihex $(TARGET).o $(TARGET).hex

$(TARGET).o: $(SRC)
	$(CC) $(CFLAGS) -I./ -o $(TARGET).o $(SRC)

program-usb:
	dfu-programmer erase
	dfu-programmer flash $(TARGET).hex

program-isp:
	avrdude -c $(ISP_PROGRAMMER) $(ISP_FLAGS) -e
	avrdude -c $(ISP_PROGRAMMER) $(ISP_FLAGS) -U flash:w:$(TARGET).hex

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
	rm -f $(TARGET).o
	rm -f $(TARGET).hex

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk
