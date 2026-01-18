#include <tamtypes.h>
#include <kernel.h>

#include "../../gfx.h"
#include "../../utils.h"
#include "../../background.h"

int channels_show(void)
{
	while (1)
	{
		update_lava_background();
		gfx_flip();
		gfx_exec();
	}
}
