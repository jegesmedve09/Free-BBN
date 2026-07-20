EE_BIN = main.elf
EE_OBJS = main.o

EE_INCS += -I$(GSKIT)/include
EE_LDFLAGS += -L$(GSKIT)/lib
EE_LDFLAGS += -L$(PS2SDK)/ports/lib
EE_LDFLAGS += -L${PS2SDK}/ee/lib
#EE_LDFLAGS += -T main.ld

EE_LIBS = -lcglue -lgskit_toolkit -lgskit -lpatches -lkernel -lpng -lz -ldmakit -laudsrv -lpad 

EE_CFLAGS = -O2 -G0 -Wall

all: $(EE_BIN)

#$(EE_BIN): $(EE_OBJS)
#	$(EE_CC) -o $@ $(EE_OBJS) $(EE_LDFLAGS) $(EE_LIBS)
clean:
	rm -f *.elf *.o *.a *.map

include $(PS2SDK)/samples/Makefile.pref
#include Makefile.eeglobal
include $(PS2SDK)/samples/Makefile.eeglobal
