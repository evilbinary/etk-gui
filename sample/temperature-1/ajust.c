#include "ajust.h"
#include "etk_widget.h"
#include "etk_window.h"
#include "etk_platform.h"

typedef struct ajutst_t {
	int light_value;
	float tem_value;
	int light_intensity;
}Ajust;


EtkWidget * etk_ajust_create(e32 x,e32 y,e32 w,e32 h){
	EtkWindowClass *priv;
	Ajust *ajust;
	EtkWidget *thiz=etk_create_window(x,y,w,h,ETK_WIDGET_WINDOW);
	//thiz->paint=etk_ajust_paint;
	priv=(EtkWindowClass*)thiz->subclass;
	priv->data[1]=ETK_MALLOC(sizeof(Ajust));
	ajust=priv->data[1];
	ajust->light_intensity=0;
	ajust->light_value=0;
	ajust->tem_value=0.0;
	
	etk_widget_set_text(thiz,"Î¢¿Øµ÷½Ú");
}