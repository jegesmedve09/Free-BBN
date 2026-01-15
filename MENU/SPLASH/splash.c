#include <tamtypes.h>
#include "../../gfx.h"

int main(int argc, char **argv)
{
    gfx_flip();
    gfx_clear(GS_SETREG_RGBAQ(0x60,0x60,0xFF, 0x00, 0x00));
    gfx_exec();
}
