EE_BIN = splash.elf

# Source files in current folder + relative paths to shared objects
EE_OBJS = splash.o ../../gfx.o ../../font.o ../../elf_loader.o

EE_INCS += -I$(GSKIT)/include -I../../../  # Go up to find headers

EE_LDFLAGS += -L$(GSKIT)/lib #-specs=nosys.specs -Wl,--entry=0x00100000 -nostartfiles

EE_LIBS = -lgskit -ldmakit -lpatches -lkernel -lpad -lcdvd -lpoweroff

EE_CFLAGS = -O2 -G0 -Wall -fno-builtin

all: $(EE_BIN)

clean:
	rm -f *.elf *.o *.a *.map

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
