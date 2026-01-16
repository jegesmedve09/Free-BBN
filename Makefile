# === Your existing Makefile ===
EE_BIN = freebbn.elf
EE_OBJS = main.o font.o gfx.o utils.o \
          ps2atad_irx.o ps2hdd_irx.o ps2fs_irx.o \
          usbd_irx.o usbhdfsd_irx.o   # add more if needed

EE_INCS += -I$(GSKIT)/include
EE_LDFLAGS += -L$(GSKIT)/lib
EE_LIBS = -lgskit -ldmakit -lpatches -lkernel -lmc -lhdd -lpoweroff

EE_CFLAGS = -O2 -G0 -Wall -fno-builtin

# === bin2c rules - use the correct path ===
BIN2C = /usr/local/ps2dev/ps2sdk/bin/bin2c

ps2atad_irx.c: $(PS2SDK)/iop/irx/ps2atad.irx
	$(BIN2C) $< $@ ps2atad_irx

ps2hdd_irx.c: $(PS2SDK)/iop/irx/ps2hdd.irx
	$(BIN2C) $< $@ ps2hdd_irx

ps2fs_irx.c: $(PS2SDK)/iop/irx/ps2fs.irx
	$(BIN2C) $< $@ ps2fs_irx

usbd_irx.c: $(PS2SDK)/iop/irx/usbd.irx
	$(BIN2C) $< $@ usbd_irx

usbhdfsd_irx.c: $(PS2SDK)/iop/irx/usbhdfsd.irx
	$(BIN2C) $< $@ usbhdfsd_irx

# Optional: if you have dev9.irx or atad.irx variants
# dev9_irx.c: $(PS2SDK)/iop/irx/dev9.irx
# 	$(BIN2C) $< $@ dev9_irx

all: $(EE_BIN)

clean:
	rm -f *.elf *.o *.a *.map *_irx.c

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
