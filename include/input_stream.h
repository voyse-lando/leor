#pragma once
#ifndef INPUT_STREAM_H_
#define INPUT_STREAM_H_
#include <stdlib.h>

typedef struct InputStream
{
	char *p_buffer;
	size_t size;
}
InputStream;

extern InputStream input_stream_from_path(const char *path);
extern void input_stream_free(InputStream *is);

#endif // ! INPUT_STREAM_H_