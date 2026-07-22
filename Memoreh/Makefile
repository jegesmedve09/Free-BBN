EE_BIN = init.elf
EE_OBJS = init.o

EE_INCS += -I$(GSKIT)/include
EE_LDFLAGS += -L$(GSKIT)/lib
EE_LDFLAGS += -L$(PS2SDK)/ports/lib

EE_LIBS = -lgskit_toolkit -lgskit -lpatches -lkernel -lpng -lz -ldmakit -laudsrv -lpad -lfileXio

EE_CFLAGS = -O2 -G0 -Wall

all: $(EE_BIN)

clean:
	rm -f *.elf *.o *.map *.bin loader_bin.c

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
