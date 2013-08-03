#ifndef _SINCLOCK_H
#define _SINCLOCK_H
#include "etk.h"
#include "etk_type.h"
#include "etk_rect.h"
#include "etk_window.h"
#include "etk_widget.h"
#include "etk_wnd_manager.h"
#include "etk_image_bmp_decoder.h"
#include "etk_image_jpeg_decoder.h"
#include "etk_source_timer.h"


static Ret etk_clock_event(EtkWidget* thiz, EtkEvent* event);
static Ret etk_clock_draw(EtkWidget* thiz, unsigned char h, unsigned char m, unsigned char s);
Ret etk_clock_update_time_listener(void *data);
EtkWidget* etk_app_clock();

EtkWidget* etk_app_clock(e32 x,e32 y,e32 width,e32 height);

















#endif
