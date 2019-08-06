#include "etk_app.h"
#include "etk_wnd_manager.h"
#include "etk_image_bmp_decoder.h"
#include "etk_image_jpeg_decoder.h"
#include "ekt_input_method_pinyin.h"
#include "etk_window.h"
#include "etk_button.h"
#include "etk.h"
#include "etk_wnd_manager.h"
#include "etk_util.h"
#include "etk_stack.h"
#include "etk_button.h"
#include "etk_image_jpeg_decoder.h"
#include "etk_menu.h"
#include "etk_menu_item.h"
#include "etk_entry.h"
#include "etk_input_method_manager.h"
#include "ekt_input_method_pinyin.h"
#include "etk_display_sdl.h"
#include "etk_rect.h"
#include "etk_type.h"
#include "etk_source_timer.h"
#include "etk_sources_manager.h"





int etk_app_main( int argc, char* argv[] ){
	EtkWndManager *manager;
	EtkWidget* desktop;
	EtkWidget* status;
	EtkWidget* wins[20];
	EtkWidget* buttons[20];
	EtkWidget* menu[3];
	EtkWidget* menu_item[10];
	EtkWidget* pic;
	EtkImageDecoder *jpeg_decoder,*bmp_decoder;
	EtkBitmap *b;
	EtkRect t;
	e32 i;
	e32 xsize,ysize,xspan,yspan,startx,starty,x,y;

	e8 button_name[20][10]={"Clock","Vedio","Temp","Note","Shut","Help","Mine","Block","Photo"};

	//ȡ�ô��ڹ���
	manager=etk_get_wnd_manager();
	//����ͼƬ����
	jpeg_decoder=etk_image_jpeg_decoder_create();
	bmp_decoder=etk_image_bmp_decoder_create();

	//��������
	/*desktop=(EtkWidget*)etk_create_window(0,0,640,480,ETK_WIDGET_DESKTOP);
	etk_default_wnd_manager_set_desktop(manager,desktop);*/
	desktop=etk_create_window(0,0,639,479,ETK_WIDGET_DESKTOP|ETK_WIDGET_NO_BITMAP);
	b=bmp_decoder->decode(bmp_decoder,"./bg.bmp");
	t.x=0;t.y=0;
	t.width=b->w;
	t.height=b->h;
	etk_canvas_set_bitmap(desktop->canvas,b);


	//����״̬��
	status=(EtkWidget*)etk_create_window(0,0,640,30,ETK_WIDGET_CHILD);
	etk_widget_append_child(desktop,status);

	//�����˵� 0
	menu[0]=(EtkWidget*)etk_create_menu(status,0,00,80,30);
	etk_widget_set_text(menu[0],"菜单");
	etk_button_set_clicked_listener(menu[0],menu0_listener,menu[0]);
	//�����Ӳ˵�
	menu_item[0]=(EtkWidget*)etk_create_menu_item(menu[0],menu[0]->rect.x,menu[0]->rect.height,menu[0]->rect.width,20);
	etk_widget_set_text(menu_item[0],"Open");
	etk_menu_item_set_clicked_listener(menu_item[0],menu0_item0_listener,menu_item[0]);

	menu_item[1]=(EtkWidget*)etk_create_menu_item(menu[0],menu[0]->rect.x,menu[0]->rect.height+20,menu[0]->rect.width,20);
	etk_widget_set_text(menu_item[1],"Save");
	etk_menu_item_set_clicked_listener(menu_item[1],menu0_item1_listener,menu_item[1]);

	menu_item[2]=(EtkWidget*)etk_create_menu_item(menu[0],menu[0]->rect.x,menu[0]->rect.height+20*2,menu[0]->rect.width,20);
	etk_widget_set_text(menu_item[2],"Exit");
	etk_menu_item_set_clicked_listener(menu_item[2],menu0_item2_listener,menu_item[2]);

	//�����˵� 1
	menu[1]=(EtkWidget*)etk_create_menu(status,80,0,80,30);
	etk_widget_set_text(menu[1],"Setting");
	etk_button_set_clicked_listener(menu[1],menu1_listener,menu[1]);

	//�����Ӳ˵�
	menu_item[3]=(EtkWidget*)etk_create_menu_item(menu[1],menu[1]->rect.x,menu[1]->rect.height,menu[1]->rect.width,20);
	etk_widget_set_text(menu_item[3],"Open F");
	etk_menu_item_set_clicked_listener(menu_item[3],menu0_item0_listener,menu_item[3]);

	menu_item[4]=(EtkWidget*)etk_create_menu_item(menu[1],menu[1]->rect.x,menu[1]->rect.height+20,menu[1]->rect.width,20);
	etk_widget_set_text(menu_item[4],"Save F");
	etk_menu_item_set_clicked_listener(menu_item[4],menu0_item1_listener,menu_item[4]);

	menu_item[5]=(EtkWidget*)etk_create_menu_item(menu[1],menu[1]->rect.x,menu[1]->rect.height+20*2,menu[1]->rect.width,20);
	etk_widget_set_text(menu_item[5],"Exit F");
	etk_menu_item_set_clicked_listener(menu_item[5],menu0_item2_listener,menu_item[5]);


	//������ť
	startx=10;starty=430;xsize=52;ysize=40;xspan=5;yspan=5;
	x=startx;y=starty;
	for(i=0;i<9;i++){
		buttons[i]=etk_button_create_ex(x,y,xsize,ysize,ETK_WIDGET_CHILD|ETK_WIDGET_SHARE_PARENT_CAVANS);
		etk_window_append_child(desktop,buttons[i]);
		etk_widget_set_text(buttons[i],button_name[i]);
		etk_button_set_clicked_listener(buttons[i],button0_listener,buttons[i]);
		x=x+xsize+xspan;
		if((i+1)%10==0){
			y=y+ysize+yspan;
			x=startx;
		}
	}
	i=0;
	etk_button_set_clicked_listener(buttons[i],button0_listener,buttons[i]);i++;
	etk_button_set_clicked_listener(buttons[i],button1_listener,buttons[i]);i++;
	etk_button_set_clicked_listener(buttons[i],button2_listener,buttons[i]);i++;
	etk_button_set_clicked_listener(buttons[i],button3_listener,buttons[i]);i++;
	etk_button_set_clicked_listener(buttons[i],button4_listener,buttons[i]);i++;
	etk_button_set_clicked_listener(buttons[i],button5_listener,buttons[i]);i++;
	etk_button_set_clicked_listener(buttons[i],button6_listener,buttons[i]);i++;
	etk_button_set_clicked_listener(buttons[i],button7_listener,buttons[i]);i++;
	etk_button_set_clicked_listener(buttons[i],button8_listener,buttons[i]);i++;

	{
		EtkSource *timer;
		wins[0]=etk_create_window(20,20,200,150,ETK_WIDGET_WINDOW);
		timer=etk_source_timer_create(100,timer2_listener,wins[0]);
		etk_sources_manager_add(etk_default_sources_manager(),timer);
		etk_canvas_draw_char(wins[0]->canvas,50,50,'3');
		etk_canvas_draw_string(wins[0]->canvas,50,80,"哈哈");
	}
	//��ʾ���д���
	etk_widget_show_all(desktop);

	return 0;
}

Ret win_update_time_listener(void *data){
	time_t now = time(0);
	char buf[20];
	struct tm* t = localtime(&now);
	EtkRect r;
	EtkWidget *timewin=(EtkWidget*)data;
	sprintf(buf,"%d:%d:%d",t->tm_hour,t->tm_min,t->tm_sec);
	r.x=timewin->rect.width>>2;
	r.y=timewin->rect.height>>2;
	r.width=100;
	r.height=20;
	//etk_canvas_draw_rect(timewin->canvas,r.x,r.y,r.width,r.height,RED);
	etk_canvas_fill_rect(timewin->canvas,r.x,r.y,r.width,r.height,WHITE);
	etk_canvas_draw_string(timewin->canvas,r.x,r.y,buf);
	r.x+=timewin->rect.x;
	r.y+=timewin->rect.y;
	etk_default_wnd_manager_update_rect(etk_default_wnd_manager(),&r);

	return RET_OK;
}

Ret button0_listener(void* user_data, void* obj){
	EtkBitmap *b=NULL;
	EtkRect t,d;
	EtkWidget *timewin;
	printf("click button1 dtat:%d obj:%d\n",user_data,obj);
	if(b!=NULL){
		t.x=0;t.y=0;
		t.width=b->w;
		t.height=b->h;
	}else{
		t.x=100;t.y=100;
		t.width=240;
		t.height=140;

	}
	timewin=etk_create_window(rand()%200,rand()%200,t.width,t.height,ETK_WIDGET_WINDOW);
	etk_widget_show(timewin,1);
	{
		EtkSource *timer;
		timer=etk_source_timer_create(1000,win_update_time_listener,timewin);
		etk_sources_manager_add(etk_default_sources_manager(),timer);
	}
	return RET_OK;
}
Ret button1_listener(void* user_data, void* obj){
	EtkBitmap *b=NULL;
	EtkRect t,d;
	EtkWidget *pic;
	EtkImageDecoder* decoder=etk_image_jpeg_decoder_create();
	printf("click button1 dtat:%d obj:%d\n",user_data,obj);
	b=decoder->decode(decoder,"flower.jpg");
	if(b!=NULL){
		t.x=0;t.y=0;
		t.width=b->w;
		t.height=b->h;
	}else{
		t.x=100;t.y=100;
		t.width=240;
		t.height=140;

	}
	pic=etk_create_window(rand()%200,rand()%200,t.width,t.height,ETK_WIDGET_WINDOW);
	etk_canvas_draw_bitmap(pic->canvas,b,&t,&t,0x00);
	etk_bitmap_destroy(b);
	etk_image_jpeg_decoder_destroy(decoder);
	etk_widget_paint(pic);
	etk_widget_show(pic,1);
	return RET_OK;
}
Ret button2_listener(void* user_data, void* obj){
	return RET_OK;
}
Ret button3_listener(void* user_data, void* obj){
	return RET_OK;
}
Ret button4_listener(void* user_data, void* obj){
	return RET_OK;
}
Ret button5_listener(void* user_data, void* obj){
	EtkWidget* win;
	win=etk_create_window(rand()%200,rand()%200,140,60,ETK_WIDGET_WINDOW);
	etk_canvas_draw_string(win->canvas,6,30,"About etk gui");
	etk_widget_show(win,1);
	return RET_OK;
}
Ret button6_listener(void* user_data, void* obj){

	return RET_OK;
}

Ret win_update_block_listener(void *data){
	time_t now = time(0);
	char buf[20];
	struct tm* t = localtime(&now);
	EtkRect r;
	EtkWidget *win=(EtkWidget*)data;
	sprintf(buf,"%d:%d:%d",t->tm_hour,t->tm_min,t->tm_sec);
	r.x=win->rect.width>>2;
	r.y=win->rect.height>>2;
	r.width=100;
	r.height=20;
	//etk_canvas_draw_rect(timewin->canvas,r.x,r.y,r.width,r.height,RED);
	etk_canvas_fill_rect(win->canvas,r.x,r.y,r.width,r.height,WHITE);
	etk_canvas_draw_string(win->canvas,r.x,r.y,buf);
	r.x+=win->rect.x;
	r.y+=win->rect.y;
	etk_default_wnd_manager_update_rect(etk_default_wnd_manager(),&r);

	return RET_OK;
}


Ret button7_listener(void* user_data, void* obj){
	/*EtkWidget *block=etk_game_block(40, 30);
	etk_widget_show_all(block);
	{
		EtkSource *timer;
		timer=etk_source_timer_create(1000,win_update_block_listener,block);
		etk_sources_manager_add(etk_default_sources_manager(),timer);
	}*/
	return RET_OK;
}
Ret button8_listener(void* user_data, void* obj){
	EtkBitmap *b=NULL;
	EtkRect t,d;
	EtkWidget *pic;
	EtkImageDecoder* decoder=etk_image_jpeg_decoder_create();
	printf("click button1 dtat:%d obj:%d\n",user_data,obj);
	b=decoder->decode(decoder,"eee1.jpg");
	if(b!=NULL){
		t.x=0;t.y=0;
		t.width=b->w;
		t.height=b->h;
	}else{
		t.x=100;t.y=100;
		t.width=240;
		t.height=140;

	}
	pic=etk_create_window(rand()%200,rand()%200,t.width,t.height,ETK_WIDGET_WINDOW);
	etk_canvas_draw_bitmap(pic->canvas,b,&t,&t,0x00);
	etk_canvas_draw_string(pic->canvas,50,50,"picture");
	etk_bitmap_destroy(b);
	etk_image_jpeg_decoder_destroy(decoder);
	etk_widget_paint(pic);
	etk_widget_show(pic,1);
	return RET_OK;
}


Ret menu0_listener(void *data,void *obj){
	e32 i,j,count;
	e32 k;
	EtkWidget *m;
	e32 imax=30;
	e32 jmax=40;
	count=0xa1a1;
	for(k=0;k<0;k++){
		m=etk_create_window(20,20,600,450,ETK_WIDGET_WINDOW);
		for(i=0;i<imax;i++){
			for(j=0;j<jmax;j++){
				etk_canvas_draw_char(m->canvas,j*16,i*16+20,count);
				count++;
			}
		}
		etk_widget_show(m,1);
	}
	return RET_OK;

}
Ret menu0_item0_listener(void *data,void *obj){


	printf("menu0_item0_listener click\n");
	return RET_OK;
}
Ret menu0_item1_listener(void *data,void *obj){
	printf("menu0_item1_listener click\n");

	return RET_OK;
}
Ret menu0_item2_listener(void *data,void *obj){
	printf("menu0_item2_listener click\n");

	return RET_OK;
}

Ret menu1_listener(void *data,void *obj){
	printf("menu1_listener click\n");

	return RET_OK;
}
Ret menu1_item0_listener(void *data,void *obj){
	printf("menu1_item0_listener click\n");

	return RET_OK;
}
Ret menu1_item1_listener(void *data,void *obj){
	printf("menu1_item1_listener click\n");

	return RET_OK;
}
e32 length;
Ret timer0_listener(void *data){
	EtkWidget* wii;
	EtkEvent e;
	EtkPoint p;
	EtkBitmap *b;
	EtkColor c;
	if(data==NULL){
		return RET_OK;
	}
	wii=(EtkWidget*)data;
	p.y=wii->rect.y;
	p.x=wii->rect.x+1;

	//p.y=w->rect.y+1;
	//printf("mov==%d,%d\n",wii->rect.x,wii->rect.y);

	etk_event_init(&e,ETK_EVENT_MOVE);
	e.u.extra=&p;
	e.widget=wii;
	etk_wnd_manager_default_dispatch_event(etk_default_wnd_manager(),&e);
	return RET_OK;
}
Ret timer1_listener(void *data){
	EtkWidget* wii;
	EtkRect r;

	if(data==NULL){
		return RET_OK;
	}
	wii=(EtkWidget*)data;
	r.x=10;
	r.y=length--*1+wii->rect.height-10;
	r.width=20;
	r.height=length*1+wii->rect.height-10;
	if(r.y<(10)){
		printf(">\n");
		return RET_REMOVE;

	}
	etk_canvas_fill_rect(wii->canvas,r.x,r.y,r.width,r.height,0xbcbcae);

	r.x+=wii->rect.x;
	r.y+=wii->rect.y;
	//etk_default_wnd_manager_update_rect(etk_default_wnd_manager(),&r);
	return RET_OK;
}
e32 posx,posy,f1,f2;

Ret timer2_listener(void *data){
	EtkWidget* wii;
	EtkEvent e;
	if(data==NULL){
		return RET_OK;
	}
		wii=(EtkWidget*)data;
	if(f1==0){
		f1=1;f2=1;
		posx=rand()%100;
		posy=50+rand()%100;
	}
	if(posx+100>wii->rect.width){
		f1=-1;
	}
	if(posy+20>wii->rect.height){
		f2=-1;
	}
	if(posx<5){
		f1=1;
	}if(posy<22){
		f2=1;
	}
	wii=(EtkWidget*)data;
	etk_canvas_fill_rect(wii->canvas,posx-1,posy,5,16,WHITE);
	etk_canvas_draw_string(wii->canvas,posx+=f1*1,posy+=1*f2,"hello,world!");
	etk_default_wnd_manager_update_rect(etk_default_wnd_manager(),&wii->rect);

	return RET_OK;
}
