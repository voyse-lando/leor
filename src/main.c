#include <stdio.h>
#include "string_stream.h"
#include "helpers/repr.h"

int main(void)
{
	StringStream ss = ss_from_file_path("test.local.lr");

	char cs[3] = { 0 };
	while (!ss_eof(&ss))
	{
		repr_char(cs, ss_next(&ss));
		printf("`%s` : @ (%zu, %zu)\n", cs, ss.row, ss.col);
	}

	ss_free(&ss);
	return 0;
}