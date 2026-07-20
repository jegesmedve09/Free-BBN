EE_BIN  = loader.elf
EE_OBJS = crt0.o loader.o

EE_CC     = mips64r5900el-ps2-elf-gcc
EE_INCS   = -I$(PS2SDK)/ee/include -I$(PS2SDK)/common/include
EE_CFLAGS = -G0 -O2 -Wall -D_EE

EE_SYSROOT = /usr/local/ps2dev/ee/mips64r5900el-ps2-elf
EE_LIBDIR  = -L$(PS2SDK)/ee/lib -L$(EE_SYSROOT)/lib -Wl,-zmax-page-size=128

EE_LIBS = $(EE_LIBDIR) -nodefaultlibs \
          -Wl,--start-group \
              -lc -lcdvd -lcglue -lpthread -lpthreadglue -lkernel -lgcc \
          -Wl,--end-group

all: $(EE_BIN)
	@echo "Loader ready."
	mips64r5900el-ps2-elf-objcopy -O binary loader.elf loader.bin
	bin2c loader.bin loader_bin.c loader

crt0.o: crt0.s
	$(EE_CC) $(EE_CFLAGS) -c -o $@ $<

loader.o: loader.c
	$(EE_CC) $(EE_CFLAGS) $(EE_INCS) -c -o $@ $<

$(EE_BIN): $(EE_OBJS)
	$(EE_CC) -T loader.ld -nostartfiles -nostdlib \
	    -Wl,--no-warn-mismatch \
	    -Wl,-Map,loader.map \
	    -o $@ $(EE_OBJS) \
	    $(EE_LIBS)

clean:
	rm -f *.elf *.o *.map *.bin loader_bin.c

include $(PS2SDK)/samples/Makefile.pref
