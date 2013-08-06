#ifndef SYNCH_PRINTF
#define SYNCH_PRINTF
#include <pthread.h>
#include <stdio.h>
#include <stdarg.h>

static pthread_mutex_t print_mutex;

void init_synch_printing(){
	pthread_mutex_init(&print_mutex, NULL);
}

int synch_printf (const char *format, ...)
{
   va_list arg;
   int done;

   va_start (arg, format);
   
   pthread_mutex_lock(&print_mutex);
   done = vfprintf (stdout, format, arg);
   pthread_mutex_unlock(&print_mutex);
   va_end (arg);
   return done;
}
#endif