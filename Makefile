# ------------------------------------------------------------
# PS2 Homebrew Makefile - Multi-ELF chained system
# ------------------------------------------------------------
EE_BIN_INIT     = INIT.ELF
EE_BIN_SPLASH   = MENU/SPLASH.ELF

# Common objects for INIT (full core + loader)
EE_OBJS_INIT    = main.o gfx.o pad.o font.o utils.o settings.o cdvd.o elf_loader.o

# Objects for SPLASH (only menu logic + loader)
EE_OBJS_SPLASH  = MENU/splash.o elf_loader.o

# gsKit/dmaKit paths
EE_INCS += -I$(GSKIT)/include
EE_LDFLAGS += -L$(GSKIT)/lib

# ------------------------------------------------------------
# Libraries
# ------------------------------------------------------------
EE_LIBS_INIT = -lgskit -ldmakit -lpatches -lkernel -laudsrv -lpad -lpoweroff -lcdvd

# Minimal for menus (no gfx/pad/font duplication)
EE_LIBS_MENU = -lkernel -lpad -lelf-loader

# ------------------------------------------------------------
# Flags
# ------------------------------------------------------------
EE_CFLAGS   = -O2 -G0 -Wall -fno-builtin
EE_LDFLAGS += -s

# ------------------------------------------------------------
# Rules
# ------------------------------------------------------------
all: $(EE_BIN_INIT) $(EE_BIN_SPLASH)

# INIT.ELF - bootstrap with full core
$(EE_BIN_INIT): $(EE_OBJS_INIT)
	$(EE_CC) -o $@ $^ $(EE_LDFLAGS) $(EE_LIBS_INIT)

# SPLASH.ELF - first chained screen (no core code linked)
$(EE_BIN_SPLASH): $(EE_OBJS_SPLASH)
	$(EE_CC) -o $@ $^ $(EE_LDFLAGS) $(EE_LIBS_MENU)

# Generic compilation rule
%.o: %.c
	$(EE_CC) $(EE_CFLAGS) $(EE_INCS) -c $< -o $@

clean:
	rm -f *.elf *.o *.a *.map MENU/*.elf MENU/*.o

include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
