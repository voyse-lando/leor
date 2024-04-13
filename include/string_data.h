#pragma once
#ifndef STRING_DATA_H_
#define STRING_DATA_H_

#include <stdlib.h>

#define STRING_DATA_MAX_SIZE 256

typedef struct StringData
{
	size_t m_p_data_size;
	char *p_data;
}
StringData;

extern StringData string_new(size_t reserve);
extern void string_free(StringData *sd);

extern int string_squeeze(StringData *sd);

#endif // ! STRING_DATA_H_