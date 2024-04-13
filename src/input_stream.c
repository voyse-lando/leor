#include "input_stream.h"
#include "platform/io.h"
#include <stdio.h>

InputStream input_stream_from_path(const char *path)
{
	InputStream is = { .p_buffer = NULL };

	is.size = read_file(&(is.p_buffer), path);

	return is;
}

void input_stream_free(InputStream *is)
{
	if (is->p_buffer != NULL)
	{
		free(is->p_buffer);
		is->p_buffer = NULL;
	}
	is->size = 0;
}