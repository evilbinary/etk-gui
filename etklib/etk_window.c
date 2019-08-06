#include "etk_window.h"
#include "etk_platform.h"
#include "etk_global.h"
#include "etk_wnd_manager.h"
#include "etk_key.h"

EtkWidget* etk_create_window(e32 x,e32 y,e32 width,e32 height,e32 type){
	EtkWidget *thiz=(EtkWidget*)ETK_MALLOC(sizeof(EtkWidget));
	EtkWindowClass *priv;
	thiz->subclass=ETK_MALLOC(sizeof(EtkWindowClass));

	etk_widget_init(thiz,x,y,width,height,type,0);
	thiz->event=etk_window_on_event;
	thiz->paint=etk_window_on_paint;

	priv=(EtkWindowClass*)thiz->subclass;
	priv->close_rect.x=4;
	priv->close_rect.y=4;
	priv->close_rect.width=15;
	priv->close_rect.height=14;
	priv->head_rect.x=3;
	priv->head_rect.y=3;
	priv->head_rect.width=width-7;
	priv->head_rect.height=20;
	priv->has_head=1;
	priv->data[0]=NULL;
	priv->data[1]=NULL;

	return thiz;
}
EtkWidget* etk_window_create(e32 x,e32 y,e32 width,e32 height,e32 type){
	EtkWidget *thiz=(EtkWidget*)ETK_MALLOC(sizeof(EtkWidget));
	EtkWindowClass *priv;
	thiz->subclass=ETK_MALLOC(sizeof(EtkWindowClass));
	priv=(EtkWindowClass*)thiz->subclass;
	priv->close_rect.x=6;
	priv->close_rect.y=6;
	priv->close_rect.width=15;
	priv->close_rect.height=20;
	priv->head_rect.x=3;
	priv->head_rect.y=3;
	priv->head_rect.width=width-7;
	priv->head_rect.height=25;
	priv->has_head=1;
	priv->data[0]=NULL;
	priv->data[1]=NULL;

	etk_widget_init(thiz,x,y,width,height,type,0);
	thiz->event=etk_window_on_event;
	thiz->paint=etk_window_on_paint;
	return thiz;
}

Bool etk_window_has_head(EtkWidget *thiz){
	EtkWindowClass *priv=(EtkWindowClass*)thiz->subclass;
	return priv->has_head;
}

Ret etk_window_on_paint_share_canvas_child(EtkWidget* thiz){
	EtkWindowClass *priv=(EtkWindowClass*)thiz->subclass;
	EtkWidget *child=(EtkWidget*)priv->data[0];
	while(child!=NULL){
		child->paint(child);
		child=child->next;
	}
    return RET_OK;
}
Ret etk_window_on_paint_head(EtkWidget* thiz){
	EtkColor color;
	EtkBitmap *h=NULL;
	EtkWindowClass *priv=(EtkWindowClass*)thiz->subclass;
	e32 j;
	EtkRect r=priv->close_rect;
	EtkRect t=priv->head_rect;
	etk_color_init(&color,0x333333,ETK_PIXEL_BGRA32);
	h=thiz->canvas->bitmap;
	for(j=t.y;j<t.height;j++){
		etk_bitmap_hline(h,t.x,j,t.width,color.color);
	}
	
	
	etk_bitmap_draw_line(h,r.x,r.y,r.x+r.width,r.y+r.height);
	etk_bitmap_draw_line(h,r.x,r.y+r.width,r.x+r.height,r.y);

	etk_bitmap_draw_rect(h,r.x-1,r.y-1,r.width+2,r.height+2,BLACK);
	etk_bitmap_draw_rect(h,r.x+1,r.y+1,r.width-2,r.height-2,GRAY);
	

	etk_bitmap_hline(h,r.x,r.y,r.width-1,WHITESMOKE);
	etk_bitmap_vline(h,r.x,r.y,r.height,WHITESMOKE);
	etk_bitmap_hline(h,r.x,r.y+r.height,r.width,GRAY);
	etk_bitmap_vline(h,r.x+r.width,r.y,r.height,GRAY);
	

	etk_canvas_hline(thiz->canvas,2,t.y+t.height-3,thiz->rect.width-5,GRAY);

	return RET_OK;
}
Ret etk_window_on_paint(EtkWidget* thiz){	

	//EtkWindowClass *priv=(EtkWindowClass*)thiz->subclass;
	if((thiz->type&ETK_WIDGET_WINDOW)){
		etk_window_on_paint_head(thiz);
		etk_canvas_draw_rect(thiz->canvas,0,0,thiz->rect.width-1,thiz->rect.height-1,BLACK);
		etk_canvas_draw_rect(thiz->canvas,2,2,thiz->rect.width-5,thiz->rect.height-5,GRAY);

		etk_canvas_hline(thiz->canvas,1,1,thiz->rect.width-3,WHITESMOKE);
		etk_canvas_vline(thiz->canvas,1,1,thiz->rect.height-3,WHITESMOKE);

		etk_canvas_hline(thiz->canvas,1,thiz->rect.height-2,thiz->rect.width-3,DIMGRAY);
		etk_canvas_vline(thiz->canvas,thiz->rect.width-2,1,thiz->rect.height-3,DIMGRAY);
	}
	

	etk_canvas_paint(thiz->display,thiz->canvas,&thiz->rect);
	etk_window_on_paint_share_canvas_child(thiz);
	return RET_OK;
}
Ret etk_window_on_event(EtkWidget* thiz, EtkEvent* event){
	EtkWindowClass *priv=(EtkWindowClass*)thiz->subclass;
	Ret ret;
	EtkEvent e;
	if(event==NULL)
		return RET_FAIL;
	//dbg_printf("==etk_window_on_event\n");
	switch(event->type){
	case ETK_EVENT_UPDATE:
		etk_widget_paint_all(thiz);
		//etk_window_update(thiz,&event->u.rect);
		break;
	case ETK_EVENT_MOVE_RESIZE:
		//dbg_printf("ETK_EVENT_MOVE_RESIZE\n");
		if(etk_widget_is_visible(thiz)){
			etk_wnd_manager_update(etk_default_wnd_manager());
		}
		break;
	case ETK_EVENT_SHOW:
		//printf("WINDOW ETK_EVENT_SHOW\n");
		etk_widget_paint(thiz);
		etk_event_init(&e, ETK_EVENT_SHOW);
		e.widget = thiz;
		etk_wnd_manager_dispatch_event(etk_default_wnd_manager(),&e);
		break;
	case ETK_EVENT_HIDE:
		
		etk_event_init(&e, ETK_EVENT_HIDE);
		e.widget = thiz;
		etk_wnd_manager_dispatch_event(etk_default_wnd_manager(), &e);
		break;
	
	case ETK_EVENT_MOUSE_DOWN:
	case ETK_EVENT_MOUSE_UP:
	case ETK_EVENT_MOUSE_MOVE:
	case ETK_EVENT_MOUSE_LONG_PRESS:{
			ret = etk_window_on_mouse_event(thiz,event);
			break;
		}
	case ETK_EVENT_KEY_DOWN:
	case ETK_EVENT_KEY_UP:
	case ETK_EVENT_KEY_LONG_PRESS:{
			ret = etk_window_on_key_event(thiz,event);
			break;
		}
	default:
		break;
	}
    return RET_OK;
}

Ret etk_window_on_key_event(EtkWidget* thiz, EtkEvent* event){
	//dbg_printf("--etk_window_on_key_event\n");
	//printf("key code:%x %d\n",event->u.key.code,event->u.key.code==ETK_KEY_SPACE);
    return RET_OK;
}
Ret etk_window_on_mouse_event(EtkWidget* thiz, EtkEvent* event){
	EtkWindowClass *priv=(EtkWindowClass*)thiz->subclass;
	
	if(event->type==ETK_EVENT_MOUSE_UP){
		EtkRect r;
		EtkWidget *w;
		r.width=1;
		r.height=1;
		r.x=event->u.mouse.x-thiz->rect.x;
		r.y=event->u.mouse.y-thiz->rect.y;
		r=etk_rect_intersect(priv->close_rect,r);
		if(r.width>0){	//check to close window on rect
			EtkEvent e;
			//printf("--etk_window_on_mouse_event\n");
			etk_event_init(&e, ETK_EVENT_WND_DESTROY);
			e.widget = thiz;
			etk_wnd_manager_dispatch_event(etk_default_wnd_manager(),&e);

		}
		r.width=2;
		r.height=2;
		r.x=event->u.mouse.x-thiz->rect.x;
		r.y=event->u.mouse.y-thiz->rect.y;
	
		w=(EtkWidget*)priv->data[0];
		while(w!=NULL){
			if(is_rect_cross(w->rect,r)){
				EtkEvent e;
				etk_event_init(&e,ETK_EVENT_MOUSE_UP);
				e.widget=w;
				etk_widget_event(w,&e);
			}
			w=w->next;
		}
		
	}else if(event->type==ETK_EVENT_MOUSE_DOWN){
		EtkRect r;
		EtkWidget *w;
		r.width=2;
		r.height=2;
		r.x=event->u.mouse.x-thiz->rect.x;
		r.y=event->u.mouse.y-thiz->rect.y;
	
		w=(EtkWidget*)priv->data[0];
		while(w!=NULL){
			if(is_rect_cross(w->rect,r)){
				EtkEvent e;
				etk_event_init(&e,ETK_EVENT_MOUSE_DOWN);
				e.widget=w;
				etk_widget_event(w,&e);
			}
			w=w->next;
		}
	}
    return RET_OK;
}
EtkRect etk_window_get_head_rect(EtkWidget* thiz){
	EtkWindowClass *priv=(EtkWindowClass*)thiz->subclass;
	return priv->head_rect;
}
EtkRect etk_window_get_close_rect(EtkWidget* thiz){
	EtkWindowClass *priv=(EtkWindowClass*)thiz->subclass;
	return priv->close_rect;
}

Ret etk_window_update(EtkWidget* thiz, EtkRect* rect){

	//thiz->display->update(thiz->display,thiz->canvas->bitmap,rect,thiz->canvas->region->rect.x,thiz->canvas->region->rect.y);
    return RET_OK;
}

void etk_window_append_child(EtkWidget* parent, EtkWidget* child){
	if(child->type&ETK_WIDGET_SHARE_PARENT_CAVANS){
		EtkWindowClass* priv=(EtkWindowClass*)parent->subclass;
		child->canvas=parent->canvas;
		if(priv->data[0]==NULL){
			priv->data[0]=child;
		}else{
			EtkWidget *w=(EtkWidget*)priv->data[0];
			etk_widget_append_next(w,child);
		}
	}else{
		etk_widget_append_child(parent,child);
	}
}
