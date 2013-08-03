#ifndef ETK_DISPLAY_SDL_H
#define ETK_DISPLAY_SDL_H
#include "etk_bitmap.h"
#include "etk_display.h"
#include "etk_type.h"
#include <SDL/SDL.h>
#include "etk_rect.h"


Ret etk_display_sdl_update(EtkDisplay * display, EtkBitmap *bitmap, EtkRect *rect, e32 xoffset, e32 yoffset);
Ret etk_display_sdl_draw(u16 *bitmap,e32 length,e32 x,e32 y,e32 width,e32 height);

void etk_display_sdl_init();
void etk_display_sdl_destroy();

void draw_line(u16 x1, u16 y1, u16 x2, u16 y2);
void put_pixel(SDL_Surface *surface, int x, int y, u32 pixel);
void put_pixel16( SDL_Surface *surface, int x, int y, u16 pixel );
void put_pixel32( SDL_Surface *surface, int x, int y, u32 pixel );
u32 get_pixel32( SDL_Surface *surface, int x, int y );

void draw_dot_line( SDL_Surface *surface, int x, int y, u32 pixel );

void draw_hline(SDL_Surface *surface,int x,int y,int length,u32 color);
void draw_vline(SDL_Surface *surface,int x,int y,int length,u32 color);
void draw_rectangle(SDL_Surface *surface,int x,int y ,int width,int height,u32 color);
void draw_rectangle_rect(SDL_Surface *surface,EtkRect EtkRect,u32 color);
void fill_rectangle(SDL_Surface *surface,int x,int y ,int width,int height,u32 color);

void draw_pixel(e32 x,e32 y,u32 pixel);
void draw_rect(EtkRect rect,u32 color);
void draw_rects(EtkRect *rects,u32 color);
void fill_rects(EtkRect *rects);
void fill_rects_plus(EtkRect *rects, u32 color);
void add_rect(EtkRect *rects,EtkRect *rect);
void fill_rect_plus(EtkRect rect,u32 color);
void draw_region(EtkRegion *region,u32 color);

#endif
