#ifndef _ETK_MALLOC_H
#define _ETK_MALLOC_H
#include "etk_type.h"

struct etk_mem_manager_t;
typedef struct etk_mem_manager_t EtkMemoryManager;
struct etk_mem_control_block_t;
typedef struct etk_mem_control_block_t EtkMemoryControlBlock;

struct etk_mem_manager_t{
	e32 has_init;
	void *memory_start;
	void *last_vailid_address;
};
struct etk_mem_control_block_t{
	e32 is_availabel;
	e32 size;
};

void *etk_malloc(EtkMemoryManager *mem_manager,e32 numbytes);
void etk_free(EtkMemoryManager *mem_manager,void *firstbyte);
void etk_malloc_init(EtkMemoryManager *mem_manager,void * start_addr);

#endif