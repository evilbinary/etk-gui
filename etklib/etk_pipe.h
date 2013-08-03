#ifndef _ETK_PIPE_H
#define _ETK_PIPE_H

#include "etk_type.h"

struct EtkPipe_t;
typedef struct EtkPipe_t EtkPipe;
struct EtkPipe_t{
	int read_fd;
	int write_fd;
};

EtkPipe* etk_pipe_create(void);
int   etk_pipe_read(EtkPipe* thiz, void* buff, u32 length);
int   etk_pipe_write(EtkPipe* thiz, const void* buff, u32 length);
int   etk_pipe_get_read_handle(EtkPipe* thiz);
int   etk_pipe_get_write_handle(EtkPipe* thiz);
void  etk_pipe_destroy(EtkPipe* thiz);
int   etk_pipe_check(EtkPipe* thiz);


#endif