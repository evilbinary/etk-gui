#include "etk_display.h"
#include "etk_type.h"
//#include "etk_display_sdl.h"
//#include "etk_global.h"
#include "etk_rect.h"

void etk_display_init(){
	
}

 Ret etk_display_update(EtkDisplay *thiz, EtkBitmap *bitmap, EtkRect *rect, e32 xoffset, e32 yoffset){
	thiz->update(thiz,bitmap,rect,xoffset,yoffset);
	return RET_OK;	
}
 EtkDisplay* etk_get_display(){
	 //return etkglobal.display;
}
