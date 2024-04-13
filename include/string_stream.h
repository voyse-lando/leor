#pragma once
#ifndef INPUT_STREAM_H_
#define INPUT_STREAM_H_
#include <stdlib.h>
#include <stdbool.h>

typedef struct StringStream
{
	char *p_buffer;
	size_t size;

	const char *m_p_buffer_iterator;
	size_t row, col;
}
StringStream;

extern StringStream ss_from_file_path(const char *path);
extern void ss_free(StringStream *ss);

extern char ss_peek(StringStream *ss);
extern char ss_next(StringStream *ss);
extern char ss_preview(StringStream *ss);
extern bool ss_eof(StringStream *ss);
extern const char *ss_begin(const StringStream *ss);
extern const char *ss_end(const StringStream *ss);

#endif // ! INPUT_STREAM_H_