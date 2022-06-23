//
// Created by kirig on 14/06/2022.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../data_structures/linked_list.h"
#include "lexer.h"

#define BUFF_SIZE 16

int is_digit(char symbol) {
    return symbol >= 48 && symbol <= 57;
}

int is_number(char value[]) {
    for (int i = 0; i < strlen(value); i++)
        if (!is_digit(value[i]))
            return 0;
    return 1;
}

void add_token(LinkedList** tokens, char* value) {
    char* token_val = malloc(BUFF_SIZE * sizeof(char));
    strcpy(token_val, value);
    Token* token = malloc(sizeof(Token));
    token->value = malloc(sizeof value);
    token->value = token_val;
    if (is_number(value)) {
        token->precedence = 0;
        token->type = TOKEN_OPERAND;
    }
    else {
        char symbol = value[0];
        if (symbol == '(' || symbol == ')') {
            token->precedence = 4;
            token->type = TOKEN_SEPARATOR;
        }
        else {
            token->type = TOKEN_OPERATOR;
            if (symbol == '+' || symbol == '-')
                token->precedence = 1;
            else if (symbol == '*' || symbol == '/' || symbol == '%')
                token->precedence = 2;
            else if (symbol == '^')
                token->precedence = 3;
            else {
                fprintf(stderr, "unknown symbol '%s'", value);
                exit(2);
            }
        }
    }

    ll_add(tokens, token);
}

void add_plus_minus_token(LinkedList **tokens_ptr, int *plus_count, int *minus_count) {
    if (*minus_count == 0) {
        if (*plus_count > 0)
            add_token(tokens_ptr, "+");
    }
    else
        add_token(tokens_ptr, *minus_count % 2 == 0 ? "+" : "-");

    *plus_count = *minus_count = 0;
}

LinkedList* lex(char expr[]) {
    //TODO maybe illegal access to value of token during initialization
    LinkedList* tokens = init_list();
    size_t expr_size = strlen(expr);

    char number[BUFF_SIZE] = "";
    int plus_count = 0, minus_count = 0;
    for (int i = 0; i < expr_size; i++) {
        char symbol = expr[i];

        if (symbol == ' ')
            continue;
        else {
            if (symbol != '+' && symbol != '-')
                add_plus_minus_token(&tokens, &plus_count, &minus_count);

            if (is_digit(symbol))
                strncat(number, &symbol, 1);
            else {
                // arithmetical symbol other than + or minus
                if (strlen(number) != 0)
                    add_token(&tokens, number);
                memset(number, 0, sizeof(number));

                if (symbol == '-')
                    minus_count++;
                else if (symbol == '+')
                    plus_count++;
                else
                    add_token(&tokens, &symbol);
            }
        }
    }
    if (strlen(number) != 0)
        add_token(&tokens, number);

    return tokens;
}
