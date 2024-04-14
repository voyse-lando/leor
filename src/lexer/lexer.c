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
const char LEXER_OPERATORS[] = "+-*/%!&|<>=:" "\0";
const char LEXER_PUNCTUATION[] = "([{;,}])" "\0";

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

bool isoper(char c)
{
	for (const char *op = LEXER_OPERATORS; *op != '\0'; op++)
	{
		if (c == *op) return true;
	}
	return false;
}

bool ispunc(char c)
{
	for (const char *punc = LEXER_PUNCTUATION; *punc != '\0'; punc++)
	{
		if (c == *punc) return true;
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

	if (isoper(x))
	{
		READ_WHILE(isoper, is, &tok.value);
		(void)string_squeeze(&tok.value);

		tok.kind = OPERATOR;
		return tok;
	}

	if (ispunc(x))
	{
		(void)string_push(&tok.value, ss_next(is));
		(void)string_squeeze(&tok.value);

		tok.kind = PUNCTUATION;
		return tok;
	}

	(void)string_push(&tok.value, ss_next(is));
	(void)string_squeeze(&tok.value);
	tok.kind = UNKNOWN;
	return tok;
}