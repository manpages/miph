#include "extendable_string.h"
#include <stdio.h>

int main(){
	extendable_string_t a;
	char c;
	unsigned long address;
	unsigned long long i = 5;
	extendable_string_size_create(&a, 2);
	printf("string state: \"%s\", size: %llu, index: %llu\n", extendable_string_get_string(&a), a.size, a.index);
	extendable_string_add_string(&a,"Abc");
	printf("string state: \"%s\", size: %llu, index: %llu\n", extendable_string_get_string(&a), a.size, a.index);
	extendable_string_add_string(&a,"Abc");
	printf("string state: \"%s\", size: %llu, index: %llu\n", extendable_string_get_string(&a), a.size, a.index);
	if (extendable_string_get_element(&a, i, &c)){
		printf("error\n");
	}else{
		address = (unsigned long)(&c);
		printf("element on %llu is \'%c\'\n",i, c);
	}
	return 0;
} 