#include "etk_source_default.h"
#include "etk_event.h"
#include "etk_pipe.h"
#include "etk_global.h"
#include "etk_sources_manager.h"
#include "etk_platform.h"

typedef struct PrivInfo_t
{
	EtkPipe* pipe;
	EtkOnEvent on_event;
	void* user_data;
}PrivInfo;

EtkSource* etk_default_source(void){
	return etkglobal.default_source;
}
EtkSource* etk_source_default_create(EtkOnEvent on_event, void* user_data){
	EtkSource* thiz = (EtkSource*)ETK_MALLOC(sizeof(EtkSource));
	if(thiz != NULL){
		PrivInfo* priv;
		thiz->priv=(PrivInfo*)ETK_MALLOC(sizeof(PrivInfo));
		priv=(PrivInfo*)thiz->priv;
		thiz->get_fd   = etk_source_default_get_fd;
		thiz->check    = etk_source_default_check;
		thiz->dispatch = etk_source_default_dispatch;
		thiz->destroy  = etk_source_default_destroy;
		thiz->next=NULL;
		thiz->prev=NULL;
		thiz->disable=0;

		thiz->ref = 1;
		priv->pipe = etk_pipe_create();
		priv->on_event  = on_event;
		priv->user_data = user_data;
	}
	return thiz;
}


int etk_source_default_get_fd(EtkSource* thiz){
	PrivInfo *priv=(PrivInfo*)thiz->priv;
	return etk_pipe_get_read_handle(priv->pipe);
}
int etk_source_default_check(EtkSource* thiz){
	PrivInfo *priv=(PrivInfo *)thiz->priv;
	return_val_if_fail(priv != NULL, -1);
	return etk_pipe_check(priv->pipe);
	//return -1;
}
Ret etk_source_default_dispatch(EtkSource* thiz){
	EtkEvent event;
	PrivInfo* priv=(PrivInfo*)thiz->priv;
	int ret;
	if(priv==NULL){
		return RET_NO_TARGET;
	}
	//dbg_printf("==etk_source_default_dispatch\n");
	ret=etk_pipe_read(priv->pipe, &event, sizeof(EtkEvent));
	switch(event.type){
		case ETK_EVENT_NOP:{
			break;
		}
		case ETK_EVENT_ADD_SOURCE:{
			etk_sources_manager_add(etk_default_sources_manager(), (EtkSource*)event.u.extra);
			break;
		}
		case ETK_EVENT_REMOVE_SOURCE:{
			etk_sources_manager_remove(etk_default_sources_manager(), (EtkSource*)event.u.extra);
			break;
		}
		default:{
			if(priv->on_event != NULL){
				//dbg_printf("etk_source_default_dispatch on event\n");
				priv->on_event(priv->user_data, &event);
			}
			break;
		}
	}

	return RET_OK;
}
void etk_source_default_destroy(EtkSource* thiz){

}

Ret etk_source_queue_event(EtkSource* thiz, EtkEvent* event){
	e32 ret;
	PrivInfo* priv=(PrivInfo*)thiz->priv;
	ret = etk_pipe_write(priv->pipe, event, sizeof(EtkEvent));
	return ret == sizeof(EtkEvent) ? RET_OK : RET_FAIL;
}
