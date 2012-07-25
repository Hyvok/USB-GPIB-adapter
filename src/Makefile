TARGET			=	GPIBAdapter
MCU          	= 	atmega16u4
ARCH         	=	AVR8
OPTIMIZATION 	=	s
F_CPU        	=	8000000
# Not 100% sure if this is correct!
F_USB			=	$(F_CPU)
ISP_PROGRAMMER	=	buspirate
ISP_FLAGS		=	-p m16u4 -P /dev/ttyUSB0
# Fuse flags for avrdude, settings: 
# CKSEL = 0010, SUT = 10: Internal RC-oscillator, 6ck + 64ms start-up
# BOOTSZ = 10: Boot flash size 2048 words, start address $1800
# SPIEN = 0: SPI program downloading enabled
# JTAGEN = 0: JTAG interface enabled
# BODLEVEL = 000: Brown-out detection level VCC=4.3V
# HWB = 0: Hardware boot enable
FUSES			= 	-U lfuse:w:0xe2:m -U hfuse:w:0x98:m -U efuse:w:0xf0:m
CC				=	avr-gcc
OBJCOPY			=	avr-objcopy
CPPFLAGS     	= 	-DUSE_LUFA_CONFIG_HEADER -Iconf/ -DF_CPU=$(F_CPU) -DF_USB=$(F_USB) -DUSB
CFLAGS			=	-g -O$(OPTIMIZATION) -Wall -mcall-prologues -mmcu=atmega16u4 -std=c99
#SRC			=	$(TARGET).c Descriptors.c $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
SRC				=	$(TARGET).c lib/GPIB.c lib/USART.c Descriptors.c $(LUFA_SRC_USB) $(LUFA_SRC_USBCLASS)
LUFA_PATH    	= 	./lib/LUFA

all:

program-usb:
	dfu-programmer erase
	dfu-programmer flash $(TARGET).hex

program-isp:
	avrdude -c $(ISP_PROGRAMMER) $(ISP_FLAGS) -e
	avrdude -c $(ISP_PROGRAMMER) $(ISP_FLAGS) -U flash:w:$(TARGET).hex

fuses:
	avrdude -c $(ISP_PROGRAMMER) $(ISP_FLAGS) $(FUSES)

clean:
	rm -f $(TARGET).o Descriptors.o
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
