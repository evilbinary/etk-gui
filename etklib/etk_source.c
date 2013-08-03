#include "etk_source.h"
#include "etk_global.h"

Ret etk_source_disable(EtkSource* thiz){
	thiz->disable++;

	return RET_OK;
}

Ret etk_source_enable(EtkSource* thiz){
	if(thiz->disable > 0)
	{
		thiz->disable--;
	}
	else
	{
		thiz->disable = 0;
	}

	return RET_OK;
}

int etk_source_get_fd(EtkSource* thiz){
	return thiz->get_fd(thiz);
}
int etk_source_check(EtkSource* thiz){
	return thiz->check(thiz);
}
Ret etk_source_dispatch(EtkSource* thiz){
	return thiz->dispatch(thiz);
}
void etk_source_destroy(EtkSource* thiz){
	thiz->destroy(thiz);
}
void etk_set_source_default(EtkSource* source){
	etkglobal.default_source=source;
}
EtkSource* etk_get_default_source(void){
	return etkglobal.default_source;
}

