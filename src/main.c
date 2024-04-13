#include <stdio.h>
#include "string_stream.h"

int main(void)
{
	StringStream ss = ss_from_file_path("test.local.lr");

	while (!ss_eof(&ss))
	{
		printf("%c : @ (%zu, %zu)\n", ss_next(&ss), ss.row, ss.col);
	}

	ss_free(&ss);
	return 0;
}