EE_BIN = freebbn.elf
EE_OBJS = main.o gfx.o utils.o font.o pad.o info.o background.o menu.o cdvd.o irx.o sound.o\
          \
          SUBMENU/ABOUT/about.o \
          \
          SUBMENU/CHANNELS/channels.o \
          SUBMENU/CHANNELS/GAMESCHANNEL/gameschannel.o \
          \
          SUBMENU/CHANNELS/GAMESCHANNEL/RUNDISC/rundisc.o\
          SUBMENU/CHANNELS/UTILITIES/utilities.o \
          \
          SUBMENU/SYSTEMSETTINGS/systemsettings.o \
          SUBMENU/SYSTEMSETTINGS/SYSTEMINFO/systeminfo.o \
          SUBMENU/SYSTEMSETTINGS/DATEANDTIME/dateandtime.o \
          \
          SUBMENU/NETWORKSETTINGS/networksettings.o \
          \
          SUBMENU/SAVEMANAGER/savemanager.o \

#poweroff_irx.c: $(PS2SDK)/iop/irx/poweroff.irx
#	bin2c $< $@ poweroff_irx

#poweroff_irx.o: poweroff_irx.c

# Force gsKit/dmaKit paths (overrides any missing auto stuff)
EE_INCS += -I$(GSKIT)/include
EE_LDFLAGS += -L$(GSKIT)/lib

# Modern libs
EE_LIBS = -lgskit -ldmakit -lpatches -lkernel -lpoweroff -lpad -laudsrv -lcdvd
# Future-proof for your plans (uncomment as you add code/headers)
# EE_LIBS += -laudsrv          # sound
# EE_LIBS += -lcdvd            # CD/DVD reading
# EE_LIBS += -lfileXio         # file I/O (mc/hdd/host)
# EE_LIBS += -lps2ip -lps2netfs # networking basics

EE_CFLAGS = -O2 -G0 -Wall



all: $(EE_BIN)

clean:
	rm -f *.elf *.o *.a *.map
	rm -f SUBMENU/ABOUT/*.elf SUBMENU/ABOUT/*.o SUBMENU/ABOUT/*.a SUBMENU/ABOUT/*.map
	rm -f SUBMENU/SYSTEMSETTINGS/*.elf SUBMENU/SYSTEMSETTINGS/*.o SUBMENU/SYSTEMSETTINGS/*.a SUBMENU/SYSTEMSETTINGS/*.map
	rm -f SUBMENU/SYSTEMSETTINGS/SYSTEMINFO/*.elf SUBMENU/SYSTEMSETTINGS/SYSTEMINFO/*.o SUBMENU/SYSTEMSETTINGS/SYSTEMINFO/*.a SUBMENU/SYSTEMSETTINGS/SYSTEMINFO/*.map

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
