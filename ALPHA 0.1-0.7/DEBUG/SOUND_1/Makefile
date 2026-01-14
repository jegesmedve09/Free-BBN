EE_BIN = sound_1_debug.elf
EE_OBJS = main.o

# Force gsKit/dmaKit paths (overrides any missing auto stuff)
EE_INCS += -I$(GSKIT)/include
EE_LDFLAGS += -L$(GSKIT)/lib

# Modern libs
EE_LIBS = -lgskit -ldmakit -lpatches -lkernel -laudsrv

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
