#include "etk_main_loop.h"
#include "etk_platform.h"
#include "etk_event.h"
#include "etk_source_default.h"
#include "etk_global.h"




EtkMainLoop* etk_main_loop_create(EtkSourcesManager* sources_manager){
	EtkMainLoop *thiz=(EtkMainLoop*)ETK_MALLOC(sizeof(EtkMainLoop));
	if(thiz!=NULL){
		thiz->running=0;
		thiz->sources_manager=sources_manager;
		FD_ZERO(&thiz->fdset);
		memset(&thiz->fdset,0,sizeof(thiz->fdset));
	}
	return thiz;
}
Ret  etk_main_loop_run(EtkMainLoop* thiz){
	EtkSource *source;
	e32 fd=0;
	e32 mfd = 0;
	e32 ret = 0;
	struct timeval tv = {0};
	e32 wait_time = 3000;
	e32 source_wait_time = 0;

	thiz->running=1;
	printf("source nr:%d\n",thiz->sources_manager->source_nr);
	while(thiz->running){
		mfd = 0;
		wait_time = 3600*1000;
		FD_ZERO(&thiz->fdset);
		FD_ZERO(&thiz->err_fdset);

		for(source=thiz->sources_manager->sources;source!=NULL;source=source->next){
			if((fd = etk_source_get_fd(source)) >= 0){
				FD_SET(fd, &thiz->fdset);
				FD_SET(fd, &thiz->err_fdset);
				if(mfd < fd)	mfd = fd;
			}
			source_wait_time = etk_source_check(source);
			//printf("etk_source_check:%d\n",source_wait_time);
			if(source_wait_time >= 0 && source_wait_time < wait_time){
				wait_time = source_wait_time;
			}
			
		}
		
		tv.tv_sec = wait_time/1000; 
		tv.tv_usec = (wait_time%1000) * 1000;

		ret = select(mfd+1, &thiz->fdset, NULL, &thiz->err_fdset, &tv);
		for(source=thiz->sources_manager->sources;source!=NULL;source=source->next){
			if(source->disable > 0){
				etk_sources_manager_remove(thiz->sources_manager, source);
				dbg_printf("etk_sources_manager_remove11\n");
				continue;
			}
			if((fd=etk_source_get_fd(source))>0&&ret!=0){
				if(etk_source_dispatch(source) != RET_OK){
					etk_sources_manager_remove(thiz->sources_manager, source);
					dbg_printf("etk_sources_manager_remove22\n");
					//should be free source
				}
			}
			if((source_wait_time = etk_source_check(source)) == 0){
				//printf("source_xxxx_time:%d\n",source_wait_time);
				//dbg_printf("etk_source_check\n");
				if(etk_source_dispatch(source) != RET_OK){
					dbg_printf("etk_sources_manager_remove33\n");
					etk_sources_manager_remove(thiz->sources_manager, source);
					 
				}
				 
			}	
			
		}
		 
	}
}
EtkMainLoop* etk_default_main_loop(void){
	return etkglobal.main_loop;
}
Ret  etk_main_loop_quit(EtkMainLoop* thiz){
	EtkEvent event;
	etk_event_init(&event, ETK_EVENT_NOP);
	thiz->running = 0;
	return etk_source_queue_event(etk_default_source() , &event);
}
Ret  etk_main_loop_add_source(EtkMainLoop* thiz, EtkSource* source){
	EtkEvent event;
	etk_event_init(&event, ETK_EVENT_ADD_SOURCE);
	event.u.extra=source;
	etk_source_enable(source);
	return etk_source_queue_event(etk_default_source() , &event);
}
Ret  etk_main_loop_remove_source(EtkMainLoop* thiz, EtkSource* source){
	EtkEvent event;
	etk_event_init(&event, ETK_EVENT_REMOVE_SOURCE);
	event.u.extra=source;
	etk_source_enable(source);
	return etk_source_queue_event(etk_default_source() , &event);
}
void etk_main_loop_destroy(EtkMainLoop* thiz){
	if(thiz!=NULL){
		ETK_FREE(thiz);
	}
}