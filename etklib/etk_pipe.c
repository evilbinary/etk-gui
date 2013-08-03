#include "etk_pipe.h"
#include "etk_platform.h"
#include "etk_win32.h"


EtkPipe* etk_pipe_create(void){
	int pipes[2] = {0};
	EtkPipe* thiz = (EtkPipe*)ETK_MALLOC(sizeof(EtkPipe));
	if(thiz != NULL){
		etk_pipe_pair(pipes);
		thiz->read_fd  = pipes[0];
		thiz->write_fd = pipes[1];
	}
	return thiz;
}
int etk_pipe_read(EtkPipe* thiz, void* buff, u32 length){
	//dbg_printf("etk_pipe_read\n");
	return etk_pipe_recv(thiz->read_fd, (e8*)buff, length);
}
int etk_pipe_write(EtkPipe* thiz, const void* buff, u32 length){
	//dbg_printf("etk_pipe_write\n");
	return etk_pipe_send(thiz->write_fd, (e8*)buff, length);
}
int etk_pipe_get_read_handle(EtkPipe* thiz){
	return thiz != NULL ? thiz->read_fd : -1;
}
int   etk_pipe_get_write_handle(EtkPipe* thiz){
	return thiz != NULL ? thiz->write_fd : -1;
}
void etk_pipe_destroy(EtkPipe* thiz){
	if(thiz != NULL){
		etk_pipe_close(thiz->read_fd);
		etk_pipe_close(thiz->write_fd);
		ETK_ZFREE(thiz, sizeof(*thiz));
	}
}
int etk_pipe_check(EtkPipe* thiz){
	return -1;
}