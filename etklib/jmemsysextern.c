#include "jpeglib.h"
#include "etk_platform.h"

void * jpeg_get_small JPP((j_common_ptr cinfo, size_t sizeofobject)){
	return ETK_MALLOC(sizeofobject);
}
void jpeg_free_small JPP((j_common_ptr cinfo, void * object, size_t sizeofobject)){
	ETK_FREE(object);
}

long jpeg_mem_init JPP((j_common_ptr cinfo)){

	return 0;
}
void jpeg_mem_term JPP((j_common_ptr cinfo)){

}