#include "etk_event.h"

Ret etk_event_init(EtkEvent* event, EtkEventType type){
	if(event!=NULL){
		//memset(event, 0x00, sizeof(EtkEvent));
		event->type=type;
	}
	return RET_OK;
}