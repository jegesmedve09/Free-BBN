#include <tamtypes.h>
#include <iopcontrol.h>
#include <kernel.h>          // for FlushCache
#include <sifrpc.h>          // for SifInitRpc, SifIopReset, etc.
#include <loadfile.h>        // load IRX

#include "shared_core.h"
#include "gfx.h"
#include "pad.h"
#include "elf_loader.h"

int main (void){


	SifInitRpc(0);
	while (!SifIopReset("", 0)) {};
	while (!SifIopSync()) {};
	SifInitRpc(0);


	gfx_init();
	pad_init();


	SharedCore *core = (SharedCore *)SHARED_CORE_ADDR;

	core->gsGlobal = gsGlobal;
	core->gfx_clear = gfx_clear;
	core->gfx_draw_line = gfx_draw_line;
	core->gfx_draw_square = gfx_draw_square;
	core->gfx_draw_text = gfx_draw_text;
	core->gfx_draw_triangle = gfx_draw_triangle;
	core->gfx_exec = gfx_exec;
	core->gfx_flip = gfx_flip;
	core->gfx_reset = gfx_reset;

	core->pad_get_joy_x = pad_get_joy_x;
	core->pad_get_joy_y = pad_get_joy_y;
	core->pad_get_buttons = pad_get_buttons;
	core->pad_get_pressed = pad_get_pressed;

	core->magic = CORE_MAGIC;

	FlushCache(0);
	FlushCache(2);

	char *argv[] = {"SPLASH", "--chained", NULL};
	int argc = 2;

	// Call your custom loader
	load_and_chain_elf("mc0:/MENU/SPLASH.ELF", argc, argv);
}
