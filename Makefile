EE_BIN = freebbn.elf
EE_OBJS = main.o sound.o gfx.o utils.o font.o settings.o pad.o splash.o menu.o cdvd.o filemgr.o

#poweroff_irx.c: $(PS2SDK)/iop/irx/poweroff.irx
#	bin2c $< $@ poweroff_irx

#poweroff_irx.o: poweroff_irx.c

# Force gsKit/dmaKit paths (overrides any missing auto stuff)
EE_INCS += -I$(GSKIT)/include
EE_LDFLAGS += -L$(GSKIT)/lib

# Modern libs
EE_LIBS = -lgskit -ldmakit -lpatches -lkernel -laudsrv -lpad -lelf-loader -lpoweroff -lcdvd
# Future-proof for your plans (uncomment as you add code/headers)
# EE_LIBS += -laudsrv          # sound
# EE_LIBS += -lcdvd            # CD/DVD reading
# EE_LIBS += -lfileXio         # file I/O (mc/hdd/host)
# EE_LIBS += -lps2ip -lps2netfs # networking basics

EE_CFLAGS = -O2 -G0 -Wall



all: $(EE_BIN)

clean:
	rm -f *.elf *.o *.a *.map

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
