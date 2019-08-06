#ifndef _ETK_UNIX_H
#define _ETK_UNIX_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
size_t etk_get_relative_time(void);
  
int etk_platform_init(int argc, char** argv);
void etk_platform_deinit(void);

#define etk_pipe_pair(fds)				pipe(fds)
#define etk_pipe_close(fd)				close(fd)
#define etk_pipe_recv(fd, buf, length)	read(fd, buf, length)
#define etk_pipe_send(fd, buf, length)	write(fd, buf, length)


#endif
