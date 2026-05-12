#include "timp.h"

void creaza_timestamp_data(char* timestamp, size_t n, const char* format)
{
	time_t timp = time(NULL);
	struct tm *timp_local = localtime(&timp);

	snprintf(timestamp, n, format,
			timp_local->tm_mday,
			timp_local->tm_mon + 1,
			timp_local->tm_year + 1900);
}
void creaza_timestamp_ora(char* timestamp, size_t n, const char* format)
{
	time_t timp = time(NULL);
	struct tm *timp_local = localtime(&timp);

	snprintf(timestamp, n, format,
				timp_local->tm_hour,
				timp_local->tm_min,
				timp_local->tm_sec);
}
