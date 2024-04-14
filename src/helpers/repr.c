#include "helpers/repr.h"

#define CASE_REPR_CHAR(cs, rt) \
case cs: \
	ret[1] = rt; \
	break

void repr_char(char ret[static 3], char c)
{
	ret[0] = '\\';
	ret[1] = '\0';
	ret[2] = '\0';

	switch (c)
	{
	CASE_REPR_CHAR('\0', '0');
	CASE_REPR_CHAR('\a', 'a');
	CASE_REPR_CHAR('\b', 'b');
	CASE_REPR_CHAR('\f', 'f');
	CASE_REPR_CHAR('\n', 'n');
	CASE_REPR_CHAR('\r', 'r');
	CASE_REPR_CHAR('\t', 't');
	CASE_REPR_CHAR('\v', 'v');
	default:
		ret[0] = c;
		break;
	}
}