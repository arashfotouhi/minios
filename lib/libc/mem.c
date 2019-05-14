#include "mem.h"

void memory_copy (u8 *source, u8 *dest, u32 nbytes) 
{
    u32 i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}
