#include "ch.h"


void hexdump(BaseSequentialStream * bss, void *mem, unsigned int len);
char * rtrim(char * str, char trimchar);
void str2ip (char* str, uint8_t* ip);