#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "timp.h"

/**
 * Creeaza un timestamp cu data curenta din calendar
 * @param format trebuie sa contina cel putin 3 specificatori de format
 * @return un string cu timestampul creat
 */
char* creaza_timestamp_data(const char* format)
{
	char* str_data = (char*)malloc(sizeof(char)*50);

	time_t timp = time(NULL);
	struct tm *timp_local = localtime(&timp);

	sprintf(str_data , format, timp_local->tm_mon + 1, timp_local->tm_mday, timp_local->tm_year + 1900);

	return str_data;
}
char* creaza_timestamp_ora(const char* format)
{
	char* str_ora = (char*)malloc(sizeof(char)*50);

	time_t timp = time(NULL);
	struct tm *timp_local = localtime(&timp);

	sprintf(str_ora , format, timp_local->tm_hour, timp_local->tm_min, timp_local->tm_sec);

	return str_ora;
}
