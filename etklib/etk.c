#include "etk.h"
#include "etk_global.h"
#include "etk_wnd_manager.h"
#include "etk_platform.h"
#include "etk_display.h"
#include "etk_display_sdl.h"
#include "etk_main_loop.h"
#include "etk_source_sdl.h"
#include "etk_win32.h"



void etk_init_all(){
	//source manager init
	etkglobal.sources_manager=etk_sources_manager_create();
	
	//main loop init
	etkglobal.main_loop=etk_main_loop_create(etk_default_sources_manager());
	//win manager init
	etkglobal.wndManager=etk_default_wnd_manager_create(etkglobal.main_loop);

	//content to the platform
	//font init
	etkglobal.font=etk_font_default_create("zmrom.bin");
	//display init
	etk_display_init();
	etk_display_sdl_init();
	etkglobal.display=(EtkDisplay*)ETK_MALLOC(sizeof(EtkDisplay));
	etkglobal.display->update=etk_display_sdl_update;	//should be change if not supports sdl
	etkglobal.display->format=ETK_PIXEL_RGB565;
	etkglobal.display->height=480;
	etkglobal.display->width=640;
	//source init
	etk_sources_manager_add(etk_default_sources_manager(),  etk_source_sdl_create());

	//input method manager init
	etkglobal.input_method_manager=etk_input_method_manager_create();

}
Ret etk_init(int argc,char* argv[]){
	etk_platform_init(argc,argv);
	etk_init_all();
	return RET_OK;
}

Ret etk_run(void){
	Ret ret = etk_main_loop_run(etk_default_main_loop());

	return ret;
}
int etk_exit(){
	etk_display_sdl_destroy();	//maybe change to
	etk_platform_deinit();
	etk_default_main_loop()->running=0;
}