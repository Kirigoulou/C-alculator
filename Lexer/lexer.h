//
// Created by kirig on 14/06/2022.
//

#ifndef CALCULATOR_LEXER_H
#define CALCULATOR_LEXER_H

#include "../types.h"
#include "../data_structures/linked_list.h"

typedef struct Token {
    char* value;
    int precedence;
    TokenType type;
} Token;

LinkedList* lex(char expr[]);

#endif //CALCULATOR_LEXER_H
