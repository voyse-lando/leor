#include <stdio.h>
#include "lexer/token.h"
#include "string_stream.h"
#include "lexer/lexer.h"

int main(void)
{
	StringStream ss = ss_from_file_path("test.local.lr");

	do
	{
		Token tok = read_token(&ss);
		printf("`%s` : %s @ (%zu, %zu)\n",
						tok.value.p_data,
						token_kind_to_string(tok.kind),
						tok.row, tok.col
			  );

		token_free(&tok);
	} while (!ss_eof(&ss));

	ss_free(&ss);
	return 0;
}