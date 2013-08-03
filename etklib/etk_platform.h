#ifndef _ETK_PLATFORM_H
#define _ETK_PLATFORM_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ETK_MALLOC(s)       malloc(s)
#define ETK_REALLOC(p, s)  realloc(p, s)
#define ETK_CALLOC(s)      calloc(1, s)
#define ETK_FREE(p)        if(p) {free(p); p = NULL;}

#define ETK_NEW(s)	(*s)malloc(sizeof(s))
#define ETK_DELETE(s)	

#define ETK_ZALLOC(s)      calloc(1, s)
#define ETK_ZFREE(p, size) if(p) {memset((p), 0x00, (size)); free(p); p = NULL;}
#define ETK_STRDUP(p)      p != NULL ? Etk_strdup(p) : NULL

#define dbg_printf(s)	printf(s)

#endif