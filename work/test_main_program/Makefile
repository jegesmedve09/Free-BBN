EE_BIN = main.elf
EE_OBJS = main.o

EE_INCS += -I$(GSKIT)/include
EE_LDFLAGS += -L$(GSKIT)/lib

EE_LIBS = -lgskit -ldmakit -lpatches -lkernel -lpoweroff -lpad -laudsrv -lcdvd

EE_CFLAGS = -O2 -G0 -Wall

all: $(EE_BIN)
	mv main.elf main.fbnx

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
