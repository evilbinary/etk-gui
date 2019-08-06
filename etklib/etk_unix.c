#include "etk_unix.h"
size_t etk_get_relative_time(void){
    struct timeval t_curr;
    gettimeofday(&t_curr,NULL);
    uint64_t inus = 1000*1000*t_curr.tv_sec + t_curr.tv_usec;
    return (size_t)(inus/1000);
}
int etk_platform_init(int argc, char** argv){
    return 0;
}
void etk_platform_deinit(void){
}
