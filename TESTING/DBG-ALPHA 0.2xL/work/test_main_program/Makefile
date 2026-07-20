EE_BIN = main.elf
EE_OBJS = main.o

EE_INCS += -I$(GSKIT)/include
EE_LDFLAGS += -L$(GSKIT)/lib
EE_LDFLAGS += -L$(PS2SDK)/ports/lib
EE_LDFLAGS += -Wl,--defsym,_stack=0x01EFF000
EXTRA_LDFLAGS=+= -Wl,-Map,main.map

EE_LIBS = -lgskit -lpatches -lkernel -ldmakit -lpoweroff -lpad -laudsrv -lcdvd

EE_CFLAGS = -O2 -G0 -Wall

all: $(EE_BIN)

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
