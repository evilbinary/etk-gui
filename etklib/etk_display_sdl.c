#include "etk_display_sdl.h"
#include "etk_type.h"


#include <SDL.h>
#include "etk_rect.h"

SDL_Surface * screen;
#ifdef SDL2
SDL_Window* gWindow = NULL;
SDL_Renderer* renderer;
#endif

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define R(color) (color>>16)
#define G(color) ((color>>8)&0xff)
#define B(color) (color&0xff)

void etk_display_sdl_init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	#ifdef SDL
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,32,SDL_SWSURFACE );	//SDL_NOFRAME|
	SDL_WM_SetCaption("Etk gui", NULL );
	#endif
	#ifdef SDL2
		//Create window
        gWindow = SDL_CreateWindow( "Etk gui", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            screen = SDL_GetWindowSurface( gWindow );
			renderer = SDL_CreateRenderer(gWindow, -1, 0);
        }
	#endif
	//SDL_FillRect(screen,NULL,WHITE);
	put_pixel32(screen, 10, 10, 0xffff);
	//draw_hline(screen,10,10,100,RED);
	//draw_hline(screen,10,12,100,BLUE);
	//draw_vline(screen,10,10,100,BLACK);
	/*draw_rectangel_rect(screen,win,BLACK);
	 draw_rectangel_rect(screen,r0,BLUE);
	 EtkRect rr=rect_intersect(win,r0);
	 if(is_rect_cross(win,r0)){
	 fill_rectangel(screen,rr.x,rr.y,rr.width,rr.height,RED);
	 }*/
	//draw_rectangel(screen,50,50,600,20,BLACK);
	//draw_rectangel(screen,50,70,100,80,GREEN);
	//fill_rectangel(screen,50,50,100,20,GREEN);
	//fill_rectangel(screen,50,70,100,80,RED);
	//draw_rectangel_rect(screen,r0,BLUE);
	//sub_rect(&win,r0);
#ifdef SDL
	SDL_Flip(screen);
#endif
#ifdef SDL2
	SDL_RenderPresent(renderer);
#endif
}

void etk_display_sdl_destroy() {
	SDL_FreeSurface(screen);
	SDL_Quit();
}


Ret etk_display_sdl_update(EtkDisplay * display, EtkBitmap *bitmap, EtkRect *rect, e32 xoffset, e32 yoffset) {
	e32 i, j;
	e32 x, y;
	u32 *p32;
	u16 *p16;
	EtkRect inter,rect0;
	if(bitmap->bitperpixel==16) {
		u16 *lp=NULL;
		p16 = (u16*) bitmap->bits;
		rect0.x=rect->x;
		rect0.y=rect->y;
		rect0.width=bitmap->w;
		rect0.height=bitmap->h;
		inter=etk_rect_intersect(rect0,*rect);
		
		for(j=yoffset,y=inter.y;y<(inter.y+inter.height);y++,j++){
			lp=(u16 *)(0xa1000000)+y*display->width;
			if(y<0||y>(display->height-1))
				continue;
			for(i=xoffset,x=inter.x;x<(inter.x+inter.width);x++,i++){
				//lcd_dot(x,y, p16[i + j * bitmap->w]);
				if(x<0||x>(display->width-1))
					continue;
				lp[x]=p16[i + j * bitmap->w];
			}
		}
			
	}else if(bitmap->bitperpixel==32){
		u32 *lp=NULL;
		p32 = (u32*) bitmap->bits;
		rect0.x=rect->x;
		rect0.y=rect->y;
		rect0.width=bitmap->w;
		rect0.height=bitmap->h;
		inter=etk_rect_intersect(rect0,*rect);
		
		for(j=yoffset,y=inter.y;y<(inter.y+inter.height);y++,j++){
			lp=(u32 *)(screen->pixels)+y*display->width;
			if(y<0||y>(display->height-1))
				continue;
			for(i=xoffset,x=inter.x;x<(inter.x+inter.width);x++,i++){
				//lcd_dot(x,y, p16[i + j * bitmap->w]);
				if(x<0||x>(display->width-1))
					continue;
				lp[x]=p32[i + j * bitmap->w];
			}
		}

	}
	//SDL_Delay(200);
#ifdef SDL
	SDL_Flip(screen);
#endif
#ifdef SDL2
	SDL_RenderPresent(renderer);
#endif
}


u32 getpixel(SDL_Surface *surface, e32 x, e32 y){
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void draw_line(u16 x1, u16 y1, u16 x2, u16 y2) {
	int t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, row, col;
	int color=rand()%0xffffff;
	delta_x = x2 - x1; //�����������
	delta_y = y2 - y1;
	row = x1;
	col = y1;
	if (delta_x > 0) {
		incx = 1; //���õ�������
	} else if (delta_x == 0) {
		incx = 0;//��ֱ��
	} else {
		incx = -1;
		delta_x = -delta_x;
	}
	if (delta_y > 0) {
		incy = 1;
	} else if (delta_y == 0) {
		incy = 0;//ˮƽ��
	} else {
		incy = -1;
		delta_y = -delta_y;
	}
	if (delta_x > delta_y) {
		distance = delta_x; //ѡȡ�����������
	} else {
		distance = delta_y;
	}

	for (t = 0; t <= distance + 1; t++) { //�������
		put_pixel(screen, row, col, color);//����
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance) {
			xerr -= distance;
			row += incx;
		}
		if (yerr > distance) {
			yerr -= distance;
			col += incy;
		}
	}

}

__inline void put_pixel(SDL_Surface *surface, int x, int y, u32 pixel) {
	/*if (x < 0 || y < 0 || x > (SCREEN_WIDTH - 1) || y > (SCREEN_HEIGHT - 1))
	 return;*/
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;
	if (surface->h <= y || surface->w <= x||x<0||y<0)
		return;
	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *) p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		} else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *) p = pixel;
		break;
	}
}

void put_pixel16(SDL_Surface *surface, int x, int y, u16 pixel) {
	//Convert the pixels to 32 bit
	u16 *pixels = (u16 *) surface->pixels;
	//Set the pixel
	if (surface->h <= y || surface->w <= x)
		return;
	pixels[(y * surface->w) + x] = pixel;
}
void put_pixel32(SDL_Surface *surface, int x, int y, u32 pixel) {

	//Convert the pixels to 32 bit
	u32 *pixels = (u32 *) surface->pixels;
	//Set the pixel
	if (surface->h <= y || surface->w <= x||x<0||y<0)
		return;
	pixels[(y * surface->w) + x] = pixel;
}
void draw_dot_line(SDL_Surface *surface, int x, int y, u32 pixel) {
	if (x % 2 == 0 || y % 2 == 0)
		put_pixel(surface, x, y, pixel);
}
u32 get_pixel32(SDL_Surface *surface, int x, int y) {
	//Convert the pixels to 32 bit
	u32 *pixels = (u32 *) surface->pixels;
	//Get the requested pixel
	return pixels[(y * surface->w) + x];
}

void draw_hline(SDL_Surface *surface, int x, int y, int length, u32 color) {
	int z = x + length;
	for (; x <= z; x++) {
		put_pixel(surface, x, y, color);
	}
}
void draw_vline(SDL_Surface *surface, int x, int y, int length, u32 color) {
	int z = y + length;
	for (; y <= z; y++) {
		put_pixel(surface, x, y, color);
	}
}
void draw_rectangle(SDL_Surface *surface, int x, int y, int width, int height, u32 color) {
	draw_hline(surface, x, y, width, color);
	//SDL_Flip(screen);
	draw_hline(surface, x, y + height, width, color);
	//SDL_Flip(screen);
	draw_vline(surface, x, y, height, color);
	//SDL_Flip(screen);
	draw_vline(surface, x + width, y, height, color);
	//SDL_Flip(screen);
}
void draw_dot_rectangle(SDL_Surface *surface, int x, int y, int width, int height, u32 color) {
	draw_dot_line(surface, x, y, color);
}

void draw_rectangle_rect(SDL_Surface *surface, EtkRect rect, u32 color) {
	draw_rectangle(surface, rect.x, rect.y, rect.width, rect.height, color);
}
void fill_rectangle(SDL_Surface *surface, int x, int y, int width, int height, u32 color) {
	int z = y + height;
	for (; y <= z; y++) {
		draw_hline(surface, x, y, width, color);
	}
}

void draw_pixel(e32 x,e32 y,u32 pixel){
	put_pixel(screen,x,y,pixel);
}
void draw_rect(EtkRect rect, u32 color) {
	draw_rectangle_rect(screen, rect, color);
#ifdef SDL
	SDL_Flip(screen);
#endif
#ifdef SDL2
	SDL_RenderPresent(renderer);
#endif
}

void draw_rects_minus(EtkRect *rects,e32 m, u32 color) {
	EtkRect *p = rects;
	EtkRect *t;
	int i = 0;
	while (p != NULL) {
		EtkRect t;
		t.height=p->height-m-m;
		t.width=p->width-m-m;
		t.x=p->x+m;
		t.y=p->y+m;
		draw_rectangle_rect(screen,t, color);
		p = p->next;

	}

	#ifdef SDL
	SDL_Flip(screen);
#endif
#ifdef SDL2
	SDL_RenderPresent(renderer);
#endif
}
void draw_rects(EtkRect *rects, u32 color) {
	EtkRect *p = rects;
	EtkRect *t;
	int i = 0;
	while (p != NULL) {
		draw_rectangle_rect(screen, *p, color);
		t = p;
		p = p->next;

	}
	//draw_rectangel_rect(screen,*t,YELLOW);
#ifdef SDL
	SDL_Flip(screen);
#endif
#ifdef SDL2
	SDL_RenderPresent(renderer);
#endif
}
void fill_rects(EtkRect *rects) {
	EtkRect *p = rects;
	int i = 0;
	while (p != NULL) {
		fill_rectangle(screen, p->x, p->y, p->width, p->height, i);
		i += 0xff;
		p = p->next;

	}
}
void fill_rects_plus(EtkRect *rects, u32 color) {
	EtkRect *p = rects;
	while (p != NULL) {
			fill_rect_plus(*p, color);
		p = p->next;
	}
}
void fill_rect_plus(EtkRect rect, u32 color) {
	EtkRect *p = &rect;
	if (p == NULL)
		return;
	fill_rectangle(screen, p->x + 1, p->y + 1, p->width - 2, p->height - 2, color);
#ifdef SDL
	SDL_Flip(screen);
#endif
#ifdef SDL2
	SDL_RenderPresent(renderer);
#endif
	//SDL_Delay(100);
	//fill_rectangle(screen, p->x + 1, p->y + 1, p->width - 2, p->height - 2, GRAY);
	//SDL_Flip(screen);

}

void draw_region(EtkRegion *region, u32 color) {
	//if (region->iscover == 0) {
	//	draw_rects(region->rects, color);
	//} else {
	//	fill_rect_plus(region->rect, BLACK);
	//}
}
