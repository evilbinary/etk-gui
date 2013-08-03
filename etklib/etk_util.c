#include "etk_util.h"
#include "etk_bitmap.h"
#include "etk_color.h"
#include "etk_platform.h"


void read_file_to_buffer(char* buffer,char* filename,int size){
	FILE* f=fopen(filename,"rb");
	int i;
	if(!f){
		printf("文件%s没找到.\n",filename);
		return ;
	}
	//printf("size:%d",size);
	fseek(f,0,SEEK_SET);
	fread(buffer,sizeof(char),size,f);
	fclose(f);
	if(strcmp("zmrom.bin",filename)==0){
		printf("zmrom.bin");
		f=fopen("tt.bin","wb");
		if(f==NULL){
			printf("文件ttbin没找到.\n");
	 
		}
		fwrite(buffer,sizeof(char),size,f);
		fclose(f);

	}
	
}



