#pragma once
#ifndef LEXER_LEXER_H_
#define LEXER_LEXER_H_

#include "lexer/token.h"
#include "string_stream.h"

#define READ_WHILE(predicate, input, out) \
while (predicate(ss_peek(input))) \
	(void)string_push(out, ss_next(input))

extern const char *LEXER_KEYWORDS[];

extern bool isnumber(char c, bool *dot);
extern bool iskeyword(char *x);

extern Token read_token(StringStream *is);

#endif // ! LEXER_LEXER_H_