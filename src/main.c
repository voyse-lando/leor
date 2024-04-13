#include <stdio.h>
#include "input_stream.h"

int main(void)
{
	InputStream is = input_stream_from_path("test.local.lr");

	printf("%s : %zu\n", is.p_buffer, is.size);

	getchar();
	input_stream_free(&is);
	return 0;
}