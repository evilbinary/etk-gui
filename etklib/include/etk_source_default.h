#ifndef _ETK_SOURCE_DEFAULT_H
#define _ETK_SOURCE_DEFAULT_H

#include "etk_source.h"
#include "etk_type.h"
#include "etk_event.h"

EtkSource* etk_source_default_create(EtkOnEvent on_event, void* user_data);

int etk_source_default_get_fd(EtkSource* thiz);
int etk_source_default_check(EtkSource* thiz);
Ret etk_source_default_dispatch(EtkSource* thiz);
void etk_source_default_destroy(EtkSource* thiz);

EtkSource* etk_default_source(void);
Ret etk_source_queue_event(EtkSource* thiz, EtkEvent* event);


#endif