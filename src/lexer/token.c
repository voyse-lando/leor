#include "lexer/token.h"
#include "string_data.h"

Token token_new(TokenKind kind, StringData data, size_t row, size_t col)
{
	Token tok = { kind, data, row, col };
	return tok;
}

void token_free(Token *tok)
{
	string_free(&tok->value);
	tok->kind = NONE;
	tok->row = 0;
	tok->col = 0;
}

#define TOKEN_KIND_TO_STRING_CASE(kind) \
case kind: \
	return #kind

const char *token_kind_to_string(TokenKind kind)
{
	switch (kind) {
	TOKEN_KIND_TO_STRING_CASE(NONE);
	TOKEN_KIND_TO_STRING_CASE(UNKNOWN);
	TOKEN_KIND_TO_STRING_CASE(END_OF_FILE);
	TOKEN_KIND_TO_STRING_CASE(INT);
	TOKEN_KIND_TO_STRING_CASE(FLOAT);
	TOKEN_KIND_TO_STRING_CASE(NAME);
	TOKEN_KIND_TO_STRING_CASE(KEYWORD);
	default:
		return "UNNAMED";
	}
}