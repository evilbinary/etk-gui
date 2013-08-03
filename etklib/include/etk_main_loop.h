#ifndef _ETK_MAIN_LOOP_H
#define _ETK_MAIN_LOOP_H

#include "etk_sources_manager.h"
#include "etk_platform.h"
#include "etk_win32.h"

struct EtkMainLoop_t;
typedef struct EtkMainLoop_t EtkMainLoop;

struct EtkMainLoop_t
{
	int running;
	fd_set fdset;
	fd_set err_fdset;
	EtkSourcesManager* sources_manager;
};

EtkMainLoop* etk_main_loop_create(EtkSourcesManager* sources_manager);
Ret  etk_main_loop_run(EtkMainLoop* thiz);
Ret  etk_main_loop_quit(EtkMainLoop* thiz);
Ret  etk_main_loop_add_source(EtkMainLoop* thiz, EtkSource* source);
Ret  etk_main_loop_remove_source(EtkMainLoop* thiz, EtkSource* source);
void etk_main_loop_destroy(EtkMainLoop* thiz);

EtkMainLoop* etk_default_main_loop(void);

#endif