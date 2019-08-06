#ifndef _ETK_WIN32_H
#define _ETK_WIN32_H

#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <sys/stat.h>
#include <sys/types.h>


int   win32_socketpair(SOCKET socks[2]);

#define etk_pipe_pair(fds)				win32_socketpair(fds)
#define etk_pipe_close(fd)				closesocket(fd)
#define etk_pipe_recv(fd, buf, length)	recv(fd, buf, length, 0)
#define etk_pipe_send(fd, buf, length)	send(fd, buf, length, 0)

size_t etk_get_relative_time(void);
  
int etk_platform_init(int argc, char** argv);
void etk_platform_deinit(void);



#endif
