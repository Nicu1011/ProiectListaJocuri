#ifndef TIMP_H_
#define TIMP_H_


#define FORMAT_ORA "%02d_%02d_%02d"
#define FORMAT_DATA "%02d-%02d-%4d"

char* creaza_timestamp_data(const char* format);
char* creaza_timestamp_ora(const char* format);


#endif /* TIMP_H_ */
