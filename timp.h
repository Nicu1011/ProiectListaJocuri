#ifndef TIMP_H_
#define TIMP_H_


#include <stdio.h>
#include <time.h>

#define FORMAT_ORA "%02d_%02d_%02d"
#define FORMAT_DATA "%02d-%02d-%4d"

void creaza_timestamp_data(char* timestamp, size_t n, const char* format);
void creaza_timestamp_ora(char* timestamp, size_t n, const char* format);


#endif /* TIMP_H_ */
