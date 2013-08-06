struct extendable_string{
	unsigned long long size;
	unsigned long long index; //new char index
	char *array;
};
typedef struct extendable_string extendable_string_t;

int extendable_string_create(extendable_string_t *str_struct); // constructor;
int extendable_string_size_create(extendable_string_t *str_struct, unsigned long long new_size); // constructor 1;
void extendable_string_delete(extendable_string_t *str_struct); //destructor;

int extendable_string_add_string(extendable_string_t *str_struct, const char *string);
const char *extendable_string_get_string(extendable_string_t *str_struct);
int extendable_string_get_element(extendable_string_t *str_struct, long long index, char *element);
