#include "lexer/lexer.h"
#include "lexer/token.h"
#include "string_data.h"
#include "string_stream.h"
#include <ctype.h> // IWYU pragma: keep
#include <string.h>

const char *LEXER_KEYWORDS[] = 
{
	"define",
	NULL
};

bool isnumber(char c, bool *dot)
{
	if (c == '.')
	{
		if (dot == NULL)
			return true;
		else if (*dot)
			return false;
		else
		{
			*dot = true;
			return true;	
		}
	}
	else return isdigit(c);
}

bool iskeyword(char *x)
{
	const char **kw = LEXER_KEYWORDS;
	
	while (*kw != NULL)
	{
		if(strcmp(x, *kw) == 0)
			return true;
		kw++;
	}
	return false;
}

Token read_token(StringStream *is)
{
	READ_WHILE(isspace, is, NULL);

	Token tok = token_new(UNKNOWN, string_new(0), is->row, is->col);

	if(ss_eof(is))
	{
		tok.kind = END_OF_FILE;
		return tok;
	}
	char x = ss_peek(is);

	if (isdigit(x))
	{
		bool dot = false;
		while (isnumber(ss_peek(is), &dot))
			(void)string_push(&tok.value, ss_next(is));
		(void)string_squeeze(&tok.value);
		
		if (dot) tok.kind = FLOAT;
		else 	 tok.kind = INT;

		return tok;
	}

	if (isalpha(x))
	{
		READ_WHILE(isalnum, is, &tok.value);
		(void)string_squeeze(&tok.value);

		if (iskeyword(tok.value.p_data))
			 tok.kind = KEYWORD;
		else tok.kind = NAME;

		return tok;
	}

	(void)string_push(&tok.value, ss_next(is));
	(void)string_squeeze(&tok.value);
	tok.kind = UNKNOWN;
	return tok;
}