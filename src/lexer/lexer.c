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

		READ_WHILE_COND(isnumber(ss_peek(is), &dot), is, &tok.value);
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

#define ESC_SEQ_CASE(ec, sq) \
case ec: \
	string_push(&tok.value, sq); \
	break

	if (x == '\'' || x == '\"')
	{
		(void)ss_next(is);

		char z;
		bool esc = false;
		while (!ss_eof(is) && (z = ss_next(is)) != x)
		{
			if (esc)
			{
				esc = false;
				switch (z) {
				ESC_SEQ_CASE('0', '\0');
				ESC_SEQ_CASE('a', '\a');
				ESC_SEQ_CASE('b', '\b');
				ESC_SEQ_CASE('f', '\f');
				ESC_SEQ_CASE('n', '\n');
				ESC_SEQ_CASE('t', '\t');
				ESC_SEQ_CASE('v', '\v');
				default:
					string_push(&tok.value, z);
				}
			}
			else if (z == '\\')
				esc = true;
			else if (z == x)
				break;
			else
				string_push(&tok.value, z);
		}

		string_squeeze(&tok.value);
		tok.kind = (x == '\'') ? CHAR : STRING;
		
		return tok;
	}

#undef ESC_SEQ_CASE

	(void)string_push(&tok.value, ss_next(is));
	(void)string_squeeze(&tok.value);
	tok.kind = UNKNOWN;
	return tok;
}