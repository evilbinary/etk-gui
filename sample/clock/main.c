#include "etk.h"
#include "etk_type.h"
#include "etk_rect.h"
#include "etk_window.h"
#include "etk_widget.h"
#include "etk_wnd_manager.h"
#include "etk_image_bmp_decoder.h"
#include "etk_image_jpeg_decoder.h"

#include "sinclock.h"

int main(int argc, char* argv[]){
	EtkWndManager *manager;
	EtkBitmap *b;
	EtkRect t;
	EtkWidget* desktop;
	EtkWidget* hellowin;
	EtkImageDecoder *bmp_decoder;
	
	//初始化所有etk 环境
	etk_init(argc, argv);

	//取得窗口管理
	manager=etk_get_wnd_manager();
	//创建图片 jpeg解码 ,也可以用bmp 但是函数需要改成 etk_image_jpeg_decoder_create();
	bmp_decoder=etk_image_bmp_decoder_create();

	//创建桌面

	desktop=etk_create_window(0,0,639,479,ETK_WIDGET_DESKTOP|ETK_WIDGET_NO_BITMAP);
	b=bmp_decoder->decode(bmp_decoder,"bg.bmp");
	t.x=0;t.y=0;
	t.width=b->w;
	t.height=b->h;
	etk_canvas_set_bitmap(desktop->canvas,b);
	
	//创建窗口
	hellowin=etk_create_window(100,200,300,200,ETK_WIDGET_WINDOW);
	
	//绘制字符 hello world 到窗口画布上去
	etk_canvas_draw_string(hellowin->canvas,100,100,"hello,world.");
	

	//添加时钟
	etk_app_clock(50, 50, 400, 400);
	etk_app_clock(100, 100, 300, 300);
	etk_app_clock(150, 150, 200, 200);

	//显示所有窗口
	etk_widget_show_all(desktop);

	//运行etk
	etk_run();
	//退出etk
	etk_exit();

	return 0;
}
