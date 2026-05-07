EE_BIN = freebbn.elf
EE_OBJS = main.o font.o gfx.o utils.o pad.o

EE_INCS += -I$(GSKIT)/include
EE_LDFLAGS += -L$(GSKIT)/lib 

EE_LIBS = -lgskit -ldmakit -lpatches -lkernel -lpad -lcdvd -lpoweroff

EE_CFLAGS = -O2 -G0 -Wall -fno-builtin

all: $(EE_BIN)

clean:
	rm -f *.elf *.o *.a *.map

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
