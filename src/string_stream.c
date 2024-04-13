#include "string_stream.h"
#include "platform/io.h"
#include <stdio.h>

StringStream ss_from_file_path(const char *path)
{
	StringStream ss = { .p_buffer = NULL };

	ss.size = read_file(&(ss.p_buffer), path);
	ss.m_p_buffer_iterator = ss.p_buffer;
	ss.col = 1;
	ss.row = 1;

	return ss;
}

void ss_free(StringStream *ss)
{
	if (ss->p_buffer != NULL)
	{
		free(ss->p_buffer);
		ss->p_buffer = NULL;
	}
	ss->size = 0;
}

char ss_peek(StringStream *ss)
{
	if (ss_eof(ss))
		return 0;

	return *ss->m_p_buffer_iterator;
}

char ss_next(StringStream *ss)
{
	if (ss_eof(ss))
		return 0;
	char c = ss_peek(ss);
	ss->m_p_buffer_iterator++;

	if (c == '\n')
	{
		ss->row++;
		ss->col = 1;
	}
	else
		ss->col++;

	return c;
}

char ss_preview(StringStream *ss)
{
	char c = 0;
	ss->m_p_buffer_iterator++;
	if (!ss_eof(ss))
		c = *ss->m_p_buffer_iterator;

	ss->m_p_buffer_iterator--;
	return c;
}

bool ss_eof(StringStream *ss)
{
	return (size_t)ss->m_p_buffer_iterator >= (size_t)ss_end(ss);
}

const char *ss_begin(const StringStream *ss)
{
	return ss->p_buffer;
}
const char *ss_end(const StringStream *ss)
{
	return ss->p_buffer + ss->size;
}