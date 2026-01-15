#include <tamtypes.h>

int main(int argc, char **argv)
{
    asm volatile ("break");  // Intentional crash - PCSX2 will show "Break instruction"

    while(1) asm("nop");     // Should never reach
}
