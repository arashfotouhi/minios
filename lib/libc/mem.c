#include "mem.h"

void memory_copy (u8 *source, u8 *dest, u32 nbytes) 
{
    u32 i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

u32 free_mem_addr = 0x10000;

u32 kmalloc(u32 size, int align, u32 *phys_addr)
{
	if (align == 1 && (free_mem_addr & 0xFFFFF000)) {
		free_mem_addr &= 0xFFFFF000;
		free_mem_addr += 0x1000;
	}

	if (phys_addr)
		*phys_addr = free_mem_addr;

	u32 ret = free_mem_addr;
	free_mem_addr += size;
	return ret;
}
