#ifndef ETK_GLOBAL_H
#define ETK_GLOBAL_H

#include "etk_wnd_manager.h"
#include "etk_display.h"
#include "etk_source_default.h"
#include "etk_sources_manager.h"
#include "etk_main_loop.h"
#include "etk_font.h"
#include "etk_input_method_manager.h"
struct EtkGlobal_t;

typedef struct EtkGlobal_t EtkGlobal;
struct EtkGlobal_t{ 
	EtkFont *font;
	EtkDisplay *display;
	EtkWndManager *wndManager;
	EtkSource* default_source;
	EtkMainLoop* main_loop;
	EtkSourcesManager* sources_manager;
	EtkInputMethodManager *input_method_manager;
};

EtkGlobal etkglobal;


#endif