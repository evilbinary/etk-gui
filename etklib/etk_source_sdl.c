#include "etk_source_sdl.h"
#include "etk_display.h"
#include "etk_type.h"
#include "etk_platform.h"
#include "etk_display_sdl.h"
#include "etk_wnd_manager.h"
#include "etk.h"
#include "etk_key.h"

#define MAX 0xff

typedef struct _PrivInfo
{
	EtkEvent event;
}PrivInfo;

static int s_key_map[MAX] = {0};

static void etk_keymap_init(void){
	s_key_map[SDLK_ESCAPE%MAX] = ETK_KEY_ESC;
	s_key_map[SDLK_MINUS%MAX] = ETK_KEY_MINUS;
	s_key_map[SDLK_PLUS%MAX] = ETK_KEY_PLUS;
	s_key_map[SDLK_KP_MINUS%MAX] = ETK_KEY_MINUS;
	s_key_map[SDLK_KP_PLUS%MAX] = ETK_KEY_PLUS;
	s_key_map[SDLK_BACKSPACE%MAX] = ETK_KEY_SPACE;
	s_key_map[SDLK_EQUALS%MAX] = ETK_KEY_EQUAL;
	s_key_map[SDLK_KP_EQUALS%MAX] = ETK_KEY_EQUAL;
	s_key_map[SDLK_BACKSPACE%MAX] = ETK_KEY_BACKSPACE;
	s_key_map[SDLK_TAB%MAX] = ETK_KEY_TAB;
	s_key_map[SDLK_RETURN%MAX] = ETK_KEY_ENTER;
	s_key_map[SDLK_KP_ENTER%MAX] = ETK_KEY_ENTER;
	s_key_map[SDLK_LEFT%MAX] = ETK_KEY_LEFT;
	s_key_map[SDLK_RIGHT%MAX] = ETK_KEY_RIGHT;
	s_key_map[SDLK_DOWN%MAX] = ETK_KEY_DOWN;
	s_key_map[SDLK_DELETE%MAX] = ETK_KEY_DELETE;
	s_key_map[SDLK_UP%MAX] = ETK_KEY_UP;
	s_key_map[SDLK_INSERT%MAX]=ETK_KEY_INSERT;
	s_key_map[SDLK_LCTRL%MAX]=ETK_KEY_LEFTCTRL;
	s_key_map[SDLK_RCTRL%MAX]=ETK_KEY_RIGHTCTRL;
	s_key_map[SDLK_RSHIFT%MAX]=ETK_KEY_RIGHTSHIFT;
	s_key_map[SDLK_LSHIFT%MAX]=ETK_KEY_LEFTSHIFT;
}	
 



EtkSource *etk_source_sdl_create(){
	EtkSource *thiz=(EtkSource*)ETK_MALLOC(sizeof(EtkSource));
	thiz->priv=ETK_MALLOC(sizeof(PrivInfo));
	thiz->disable=0;
	thiz->get_fd=etk_source_sdl_get_fd;
	thiz->check=etk_source_sdl_check;
	thiz->dispatch=etk_source_sdl_dispatch;
	thiz->destroy=etk_source_sdl_destroy;
	//etk_keymap_init();
	etk_keymap_init();

	return thiz;
}
void etk_source_sdl_destroy(EtkSource* thiz){
	if(thiz != NULL){
		ETK_FREE(thiz->priv);
		ETK_FREE(thiz);
	}
}

int etk_source_sdl_get_fd(EtkSource* thiz){
	return -1;
}

int etk_source_sdl_check(EtkSource* thiz){
	return 0;
}




__inline Ret etk_source_sdl_dispatch(EtkSource* thiz ){
	SDL_Event event;
	PrivInfo *priv=(PrivInfo *)thiz->priv;
	EtkWidget *w;
	//while(1){
		if(!SDL_PollEvent( &event )){
			SDL_Delay(10);
			return RET_FAIL;
			//break;
		}
		//dbg_printf("event\n");
		priv->event.widget=NULL;
		switch(event.type){
		case SDL_KEYDOWN:{
			/*switch( event.key.keysym.sym ){
				case SDLK_t:
					w=etk_wnd_manager_get_grab_widget(etk_default_wnd_manager());
					draw_rects_minus(w->canvas->region->outputs,2,YELLOW);
					break;
				case SDLK_w:
					w=etk_wnd_manager_get_grab_widget(etk_default_wnd_manager());
					if(w!=NULL){
						draw_rect(w->rect,GREEN);
					}
					break;
				case SDLK_c:
					w=etk_wnd_manager_get_grab_widget(etk_default_wnd_manager());
					if(w!=NULL){
						if(w->chil!=NULL)
							fill_rect_plus(w->chil->rect,RED);
					}
					break;
				case SDLK_a:
					w=etk_wnd_manager_get_grab_widget(etk_default_wnd_manager());
					etk_default_wnd_manager_active(etk_default_wnd_manager(),w);
					break;
				case SDLK_e:
					w=etk_wnd_manager_get_grab_widget(etk_default_wnd_manager());
					draw_rects(w->canvas->region->outputs,RED);
					break;
				case SDLK_r:
					w=etk_wnd_manager_get_grab_widget(etk_default_wnd_manager());
					etk_default_wnd_manager_remove(etk_default_wnd_manager(),w);
					break;
				case SDLK_d:

					break;
				case SDLK_x:
					w=etk_wnd_manager_get_grab_widget(etk_default_wnd_manager());
					if(w!=NULL){
						if(w->next!=NULL)
							fill_rect_plus(w->next->rect,RED);
					}
					break;
			}*/
			
			etk_event_init(&priv->event,ETK_EVENT_KEY_DOWN);
			if(s_key_map[event.key.keysym.sym]==0){
				priv->event.u.key.code=event.key.keysym.sym;
			}else{
				priv->event.u.key.code=s_key_map[event.key.keysym.sym];
			}
			etk_wnd_manager_queue_event(etk_default_wnd_manager(), &priv->event);
			break;
		}
		case SDL_KEYUP:{
			etk_event_init(&priv->event,ETK_EVENT_KEY_UP);
			if(s_key_map[event.key.keysym.sym]==0){
				priv->event.u.key.code=event.key.keysym.sym;
			}else{
				priv->event.u.key.code=s_key_map[event.key.keysym.sym];
			}
			etk_wnd_manager_queue_event(etk_default_wnd_manager(), &priv->event);
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
			priv->event.type = ETK_EVENT_MOUSE_DOWN;
			priv->event.u.mouse.x = event.button.x;
			priv->event.u.mouse.y = event.button.y;
			etk_wnd_manager_queue_event(etk_default_wnd_manager(), &priv->event);
			//dbg_printf("sdl ETK_EVENT_MOUSE_DOWN\n");
			break;
		case SDL_MOUSEBUTTONUP:
			priv->event.type = ETK_EVENT_MOUSE_UP;
			priv->event.u.mouse.x = event.button.x;
			priv->event.u.mouse.y = event.button.y;
			etk_wnd_manager_queue_event(etk_default_wnd_manager(), &priv->event);
			//dbg_printf("ETK_EVENT_MOUSE_UP\n");
			break;
		case SDL_MOUSEMOTION:
			if(event.motion.state != SDL_PRESSED){
				break;
			}
			priv->event.type = ETK_EVENT_MOUSE_MOVE;
			priv->event.u.mouse.x = event.motion.x;
			priv->event.u.mouse.y = event.motion.y;
			etk_wnd_manager_queue_event(etk_default_wnd_manager(), &priv->event);
			////dbg_printf("ETK_EVENT_MOUSE_MOVE\n");
			break;
		case SDL_QUIT:
			etk_default_main_loop()->running=0;
			break;
		default:
			break;
		}
	//}
	//dbg_printf("break\n");
	return RET_OK;
}
