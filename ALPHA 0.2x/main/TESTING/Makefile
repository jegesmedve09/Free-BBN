EE_BIN = main.elf
EE_OBJS = main.o gfx.o audio.o pad.o utils.o video.o debug.o

EE_INCS += -I$(GSKIT)/include
EE_LDFLAGS += -L$(GSKIT)/lib
EE_LDFLAGS += -L$(PS2SDK)/ports/lib
EE_LDFLAGS += -L${PS2SDK}/ee/lib
EE_LDFLAGS += -Wl,-Map,main.map,-init=none,--defsym,_stack=0x01EFF000

EE_LIBS = -lgskit_toolkit -lgskit -lpatches -lkernel -lpng -lz -ldmakit -laudsrv -lpad -lmpeg -ldraw -lgraph -lpacket -ldma

EE_CFLAGS = -O2 -G0 -Wall 

all: $(EE_BIN)

#$(EE_BIN): $(EE_OBJS)
#	$(EE_CC) -o $@ $(EE_OBJS) $(EE_LDFLAGS) $(EE_LIBS)
clean:
	rm -f *.elf *.o *.a *.map

include $(PS2SDK)/samples/Makefile.pref
#include Makefile.eeglobal
include $(PS2SDK)/samples/Makefile.eeglobal
