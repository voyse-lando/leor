#pragma once
#ifndef LEXER_TOKEN_H_
#define LEXER_TOKEN_H_

#include "string_data.h"

typedef enum TokenKind
{
	NONE, UNKNOWN, END_OF_FILE,
	INT, FLOAT,
	NAME, KEYWORD,
	OPERATOR, PUNCTUATION
}
TokenKind;

typedef struct Token
{
	TokenKind kind;
	StringData value;
	size_t row, col;
}
Token;

extern Token token_new(TokenKind kind, StringData data, size_t row, size_t col);
extern void token_free(Token *tok);

extern const char *token_kind_to_string(TokenKind kind);

#endif // ! LEXER_TOKEN_H_