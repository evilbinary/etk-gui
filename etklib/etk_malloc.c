#include "etk_malloc.h"
#include "etk_platform.h"
#include "etk_type.h"

 

void etk_malloc_init(EtkMemoryManager *mem_manager,void * start_addr){
	mem_manager->has_init=1;
	mem_manager->memory_start=start_addr;	
	mem_manager->last_vailid_address=start_addr;
}
void *etk_malloc(EtkMemoryManager *mem_manager,e32 numbytes){
	void *current_location;
	EtkMemoryControlBlock *current_location_mcb;
	void *memrory_location;
	numbytes=numbytes+sizeof(EtkMemoryControlBlock);
	memrory_location=0;
	current_location=mem_manager->memory_start;
	while(current_location!=mem_manager->last_vailid_address){
		current_location_mcb=(EtkMemoryControlBlock*)current_location;
		if(current_location_mcb->is_availabel!=0){
			if(current_location_mcb->size>=numbytes){
				current_location_mcb->is_availabel=0;
				memrory_location=current_location;
				break;
			}
		}
		current_location=((e32*)current_location+current_location_mcb->size);
	}
	if(!memrory_location){
		memrory_location=mem_manager->last_vailid_address;
		mem_manager->last_vailid_address=(e32*)mem_manager->last_vailid_address+numbytes;
		current_location_mcb=(EtkMemoryControlBlock*)memrory_location;
		current_location_mcb->is_availabel=0;
		current_location_mcb->size=numbytes;
	}
	memrory_location=(e32*)memrory_location+sizeof(EtkMemoryControlBlock);
	return memrory_location;
}
void etk_free(EtkMemoryManager *mem_manager,void *firstbyte){
	EtkMemoryControlBlock *mcb;
	mcb=(EtkMemoryControlBlock*)((e32)firstbyte-sizeof(EtkMemoryControlBlock));
	mcb->is_availabel=1;
}

void test_mem(){
	EtkMemoryManager m;
	e32 *a[100];
	e32 *p=(e32 *)ETK_MALLOC(1024*1024);
	e32 i,s;
	printf("mem start addr:%x\n",p);
	etk_malloc_init(&m,p);
	
	for(i=0;i<100;i++){
		s=rand()%1024;
		a[i]=(e32*)etk_malloc(&m,s);
		printf("a[%d]:%x size:%d\n",i,a[i],s);
	}
	etk_free(&m,a[0]);
}