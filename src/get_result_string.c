#include "ssl_hash.h"

char		*get_result_string(unsigned char *result, int size)
{
	char *result_str = (char *)malloc(size * 2 + 1);
	for (int i = 0; i < size; i++)
	{
		char c = result[i] >> 4;
		result_str[i * 2] = (c < 0xa ? c + '0' : c + 'a' - 10);
		c = result[i] & 0xf;
		result_str[i * 2 + 1] = (c < 0xa ? c + '0' : c + 'a' - 10);
	}
	result_str[size * 2] = '\0';
	return (result_str);
}
