#include "etk_type.h"
#include "etk_rect.h"
#include "etk_display_sdl.h"
#include "etk_platform.h"
#include "etk_window.h"
#include "etk_source_sdl.h"
#include "etk.h"
#include "etk_wnd_manager.h"
#include "etk_util.h"
#include "etk_stack.h"
#include "etk_button.h"
#include "etk_image_jpeg_decoder.h"
#include "etk_image_bmp_decoder.h"
#include "etk_menu.h"
#include "etk_menu_item.h"
#include "mine.h"


int etk_main(int argc,char* argv[]);

Ret button0_listener(void* user_data, void* obj);
Ret menu0_listener(void *data,void *obj);
Ret menu0_item0_listener(void *data,void *obj);
Ret menu0_item1_listener(void *data,void *obj);
Ret menu0_item2_listener(void *data,void *obj);

Ret menu1_listener(void *data,void *obj);
Ret menu1_item0_listener(void *data,void *obj);
Ret menu1_item1_listener(void *data,void *obj);

int etk_main(int argc,char* argv[]){
 EtkWndManager *manager;
	EtkWidget* desktop;
	EtkWidget* status;
	EtkWidget* wins[20];
	EtkWidget* button;
	EtkWidget* menu[3];
	EtkWidget* menu_item[10];
	EtkWidget* pic;
	EtkImageDecoder *jpeg_decoder,*bmp_decoder;
	EtkBitmap *b;
	EtkRect t;
	e32 posx=0;
	e32 posy=0;
	e32 i;
	//取得窗口管理
	manager=etk_get_wnd_manager();
	//创建图片解码
	jpeg_decoder=etk_image_jpeg_decoder_create();
	bmp_decoder=etk_image_bmp_decoder_create();
	
	//创建桌面
	/*desktop=(EtkWidget*)etk_create_window(0,0,640,480,ETK_WIDGET_DESKTOP);
	etk_default_wnd_manager_set_desktop(manager,desktop);*/
	desktop=etk_create_window(0,0,639,479,ETK_WIDGET_DESKTOP|ETK_WIDGET_NO_BITMAP);
	b=bmp_decoder->decode(bmp_decoder,"bg.bmp");
	t.x=0;t.y=0;
	t.width=b->w;
	t.height=b->h;
	etk_canvas_set_bitmap(desktop->canvas,b);
	/*
	//创建状态栏
	status=(EtkWidget*)etk_create_window(0,0,640,40,ETK_WIDGET_CHILD);
	etk_widget_append_child(desktop,status);
	
	//创建菜单 0
	menu[0]=(EtkWidget*)etk_create_menu(status,0,00,80,40);
	etk_widget_set_text(menu[0],"Menu");
	etk_button_set_clicked_listener(menu[0],menu0_listener,menu[0]);
	//创建子菜单
	menu_item[0]=(EtkWidget*)etk_create_menu_item(menu[0],menu[0]->rect.x,menu[0]->rect.height,menu[0]->rect.width,20);
	etk_widget_set_text(menu_item[0],"Open");
	etk_menu_item_set_clicked_listener(menu_item[0],menu0_item0_listener,menu_item[0]);

	menu_item[1]=(EtkWidget*)etk_create_menu_item(menu[0],menu[0]->rect.x,menu[0]->rect.height+20,menu[0]->rect.width,20);
	etk_widget_set_text(menu_item[1],"Save");
	etk_menu_item_set_clicked_listener(menu_item[1],menu0_item1_listener,menu_item[1]);

	menu_item[2]=(EtkWidget*)etk_create_menu_item(menu[0],menu[0]->rect.x,menu[0]->rect.height+20*2,menu[0]->rect.width,20);
	etk_widget_set_text(menu_item[2],"Exit");
	etk_menu_item_set_clicked_listener(menu_item[2],menu0_item2_listener,menu_item[2]);
	
	//创建菜单 1
	menu[1]=(EtkWidget*)etk_create_menu(status,90,0,80,40);
	etk_widget_set_text(menu[1],"Setting");
	etk_button_set_clicked_listener(menu[1],menu1_listener,menu[1]);
	
	//创建子菜单
	menu_item[3]=(EtkWidget*)etk_create_menu_item(menu[1],menu[1]->rect.x,menu[1]->rect.height,menu[1]->rect.width,20);
	etk_widget_set_text(menu_item[3],"Open F");
	etk_menu_item_set_clicked_listener(menu_item[3],menu0_item0_listener,menu_item[3]);

	menu_item[4]=(EtkWidget*)etk_create_menu_item(menu[1],menu[1]->rect.x,menu[1]->rect.height+20,menu[1]->rect.width,20);
	etk_widget_set_text(menu_item[4],"Save F");
	etk_menu_item_set_clicked_listener(menu_item[4],menu0_item1_listener,menu_item[4]);

	menu_item[5]=(EtkWidget*)etk_create_menu_item(menu[1],menu[1]->rect.x,menu[1]->rect.height+20*2,menu[1]->rect.width,20);
	etk_widget_set_text(menu_item[5],"Exit F");
	etk_menu_item_set_clicked_listener(menu_item[5],menu0_item2_listener,menu_item[5]);
	 
	 
	//创建按钮
	button=(EtkWidget*)etk_create_button(desktop,300,100,80,40);
	etk_widget_set_text(button,"add win");
	etk_button_set_clicked_listener(button,button0_listener,button);
	
	//创建jpeg 图片
	b=jpeg_decoder->decode(jpeg_decoder,"flower.jpg");
	t.x=0;t.y=0;
	t.width=b->w;
	t.height=b->h;
	pic=(EtkWidget*)etk_create_window(50,250,b->w,b->h,ETK_WIDGET_WINDOW);
	etk_canvas_draw_bitmap(pic->canvas,b,&t,&t,0x00);
	etk_canvas_draw_string(pic->canvas,50,50,"picture");
	
	//创建bmp 图片
	b=bmp_decoder->decode(bmp_decoder,"ee.bmp");
	t.x=0;t.y=0;
	t.width=b->w;
	t.height=b->h;
	wins[0]=etk_create_window(50,250,b->w,b->h,ETK_WIDGET_WINDOW);
	etk_canvas_draw_bitmap(wins[0]->canvas,b,&t,&t,0x00);
	etk_canvas_draw_string(wins[0]->canvas,10,20,"Etk gui by EvilBinary");

	b=jpeg_decoder->decode(jpeg_decoder,"alan.jpg");
	t.x=0;t.y=0;
	t.width=b->w;
	t.height=b->h;
	pic=(EtkWidget*)etk_create_window(50,250,b->w,b->h,ETK_WIDGET_CHILD|ETK_WIDGET_WINDOW);
	etk_canvas_draw_bitmap(pic->canvas,b,&t,&t,0x00);
	etk_widget_append_child(desktop,pic);
	 
	for(i=0;i<2;i++){
		posx=rand()%240;
		posy=rand()%280;
		wins[i]=(EtkWidget*)etk_create_window(posx,posy,rand()%100+230,rand()%100+150,ETK_WIDGET_CHILD|ETK_WIDGET_WINDOW);
		etk_widget_append_child(desktop,wins[i]);


	}*/

	//创建扫雷游戏
	etk_game_mine(10, 30, 8, 8, 10);
	etk_game_mine(160, 30, 10, 10, 14);
	etk_game_mine(340, 30, 16, 16, 20);

	//显示所有窗口
	etk_widget_show_all(desktop);
}


int main( int argc, char* argv[] ){ 
	etk_init(argc, argv);
	etk_main(argc,argv);
	etk_run();
	etk_exit();

	return 0;    
}


Ret button0_listener(void* user_data, void* obj){
	EtkBitmap *b=NULL; 
	EtkRect t;
	EtkWidget *pic;
	EtkImageDecoder* decoder=etk_image_jpeg_decoder_create();
	printf("click button1 dtat:%d obj:%d\n",user_data,obj);
	//b=decoder->decode(decoder,"12.jpg");
	
	if(b!=NULL){
		t.x=0;t.y=0;
		t.width=b->w;
		t.height=b->h;
	}else{
		t.x=rand()%600;t.y=rand()%400;
		t.width=100;
		t.height=100;

	}
	pic=(EtkWidget*)etk_create_window(t.x,t.y,t.width,t.height,ETK_WIDGET_WINDOW);
	//etk_canvas_draw_bitmap(pic->canvas,b,&t,&t,0x00);
	//etk_canvas_draw_string(pic->canvas,50,50,"picture");
	//etk_bitmap_destroy(b);
	//etk_image_jpeg_decoder_destroy(decoder);
	
	//etk_widget_paint(pic);
	etk_widget_show(pic,1);
}

Ret menu0_listener(void *data,void *obj){
	EtkWidget *m=(EtkWidget*)obj;
	printf("menu0_listener click\n");
	
}
Ret menu0_item0_listener(void *data,void *obj){
	printf("menu0_item0_listener click\n");
}
Ret menu0_item1_listener(void *data,void *obj){
	printf("menu0_item1_listener click\n");
}
Ret menu0_item2_listener(void *data,void *obj){
	printf("menu0_item2_listener click\n");
}

Ret menu1_listener(void *data,void *obj){
	printf("menu1_listener click\n");
}
Ret menu1_item0_listener(void *data,void *obj){
	printf("menu1_item0_listener click\n");
}
Ret menu1_item1_listener(void *data,void *obj){
	printf("menu1_item1_listener click\n");
}

