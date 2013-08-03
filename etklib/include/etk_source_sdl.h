#ifndef _ETK_SOURCE_SDL_H
#define _ETK_SOURCE_SDL_H

#include "etk_source.h"
 
Ret etk_source_sdl_dispatch(EtkSource* thiz );
EtkSource *etk_source_sdl_create();
void etk_source_sdl_destroy(EtkSource* thiz);

int etk_source_sdl_get_fd(EtkSource* thiz);
int etk_source_sdl_check(EtkSource* thiz);

#endif