#ifndef EXTENDABLE_STRING
#define EXTENDABLE_STRING

#include "extendable_string.h"
#include <stdlib.h> 
#include <string.h> //memset

#include <stdio.h>

int extendable_string_size_create(extendable_string_t *str_struct, unsigned long long new_size){
	if (!str_struct){
		return 1;
	}
	str_struct->size = new_size;
	str_struct->index = 0;
	str_struct->array = (char*)malloc(str_struct->size*sizeof(char));
	if(!str_struct->array){
		return 1;
	}
	memset(str_struct->array, 0 , str_struct->size);
	return 0;
};

int extendable_string_create(extendable_string_t *str_struct){ //constructor;
	return extendable_string_size_create(str_struct, 32);
}

int extendable_string_extend(extendable_string_t *str_struct, long long new_size){
	char *temp;
	if (!(temp = (char *)malloc(new_size*sizeof(char)))){
		return 1;
	}
	memcpy(temp,str_struct->array, str_struct->index);
	//memset(temp[index+1], 0, (new_size - str_struct->size)*sizeof(char));
	str_struct->size = new_size;
	free(str_struct->array);
	str_struct->array = temp;
	return 0;
}

void extendable_string_delete(extendable_string_t *str_struct){ //destructor;
	free(str_struct->array);
	str_struct->size = 0;
	str_struct->index = 0;
}

int extendable_string_add_string(extendable_string_t *str_struct, const char *string){
	unsigned long long required_size = (strlen(string)+str_struct->index); 
	unsigned long long size = str_struct->size; 
	unsigned long long strlength = strlen(string);
	if ( required_size >= size) {
		if (!size){
			return 1;
		}
		do{
			unsigned long long last_size = size;
			size <<=2;
			if ((size<last_size)){
				printf("error\n");
		
				return 1;
			}
		}while (required_size >= size);
		if (extendable_string_extend(str_struct, size) == 1){
			return 1;
		}
		memset((void *)(str_struct->array+str_struct->index), 0, str_struct->size - str_struct->index);	
	}
	memcpy((void *)(str_struct->array+str_struct->index), string, strlength);
	str_struct->index+=strlength;	
};

const char *extendable_string_get_string(extendable_string_t *str_struct){
	return str_struct->array;
};

int extendable_string_get_element(extendable_string_t *str_struct, long long index, char *element){
	if (str_struct->index > index){
		*element = str_struct->array[index];
		return 0;
	}
	return 1;
}

#endif