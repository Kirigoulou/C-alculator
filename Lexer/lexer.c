//
// Created by kirig on 14/06/2022.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../data_structures/linked_list.h"
#include "lexer.h"

#define BUFF_SIZE 16

void raise_unexpected_comma() {
    fprintf(stderr, "unexpected comma");
    exit(2);
}

void raise_undefined_function() {
    fprintf(stderr, "undefined function");
    exit(2);
}

int is_digit(char symbol) {
    return symbol >= 48 && symbol <= 57;
}

int is_lowercase_letter(char symbol) {
    return symbol >= 'a' && symbol <= 'z';
}

int is_number(char value[]) {
    for (int i = 0; i < strlen(value); i++)
        if (!is_digit(value[i]))
            return 0;
    return 1;
}

void add_function(LinkedList **tokens, char *name) {
    if (strcmp(name, "max") != 0 && strcmp(name, "min") != 0 && strcmp(name, "sqrt") != 0 && strcmp(name, "facto") != 0
    && strcmp(name, "isprime") != 0 && strcmp(name, "fibo") != 0 && strcmp(name, "gcd") != 0)
        raise_undefined_function();

    char* token_val = malloc(BUFF_SIZE);
    strcpy(token_val, name);
    Token* token = malloc(sizeof(Token));
    token->value = malloc(sizeof name);
    token->value = token_val;
    token->precedence = 5;
    token->type = TOKEN_FUNCTION;

    ll_add(tokens, token);
}

void add_token(LinkedList **tokens, char *value) {
    char* token_val = malloc(BUFF_SIZE);
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
        if (symbol == '(') {
            if (!ll_is_empty(*tokens)) {
                Token *last_token = ll_last(*tokens);
                if (last_token->type == TOKEN_OPERAND || last_token->value[0] == ')')
                    add_token(tokens, "*");
            }
            token->precedence = 4;
            token->type = TOKEN_SEPARATOR;
        }
        else if (symbol == ')') {
            token->precedence = 4;
            token->type = TOKEN_SEPARATOR;
        }
        else if (symbol == ',') {
            token->precedence = 0;
            token->type = TOKEN_COMMA;
        }
        else {
            token->type = TOKEN_OPERATOR;
            if (symbol == '-' || symbol == '+') {
                if (ll_is_empty(*tokens) || ((Token*) ll_last(*tokens))->value[0] == '(') {
                    add_token(tokens, "0");
                    token->precedence = 4;
                }
                else
                    token->precedence = 1;
            }
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

LinkedList* check_commas_rec(LinkedList *tokens_ptr, Token *token_function) {
    int max_commas = (strcmp(token_function->value, "max") == 0 || strcmp(token_function->value, "min") == 0 ||
                       strcmp(token_function->value, "gcd") == 0);
    int nb_commas = 0;
    char function_name[BUFF_SIZE];
    strcpy_s(function_name, BUFF_SIZE, token_function->value);

    tokens_ptr = (LinkedList *) ((*tokens_ptr).next);
    Token *token = (*tokens_ptr).value;
    while (tokens_ptr != NULL && token->value[0] != ')') {
        if (token->value[0] == ',') {
            nb_commas++;
            if (nb_commas > max_commas)
                raise_unexpected_comma();
        }
        else if (token->type == TOKEN_FUNCTION)
            tokens_ptr = check_commas_rec(tokens_ptr, token);

        tokens_ptr = (LinkedList *) ((*tokens_ptr).next);
        if (tokens_ptr != NULL)
            token = (*tokens_ptr).value;


    }
    return tokens_ptr;
}

void check_commas(LinkedList *tokens) {
    while (tokens != NULL) {
        Token *token = tokens->value;
        if (token->type == TOKEN_FUNCTION)
            tokens = check_commas_rec(tokens, token);
        if (tokens != NULL)
            tokens = tokens->next;
    }
}

LinkedList* lex(char expr[]) {
    //TODO maybe illegal access to value of token during initialization
    LinkedList* tokens = init_list();
    size_t expr_size = strlen(expr);

    char number[BUFF_SIZE] = "", name[BUFF_SIZE] = "";
    int plus_count = 0, minus_count = 0;
    for (int i = 0; i < expr_size; i++) {
        char symbol = expr[i];

        if (symbol == ' ') {
            if (strlen(number) != 0)
                add_token(&tokens, number);
            memset(number, 0, sizeof(number));
            if (strlen(name) != 0)
                add_function(&tokens, name);
            memset(name, 0, sizeof(number));
            continue;
        }
        else {
            if (symbol != '+' && symbol != '-')
                add_plus_minus_token(&tokens, &plus_count, &minus_count);

            if (is_lowercase_letter(symbol)) {
                char letter[2] = "";
                letter[0] = symbol;
                strcat_s(name, BUFF_SIZE, letter);
            }
            else {
                if (strlen(name) != 0)
                    add_function(&tokens, name);
                memset(name, 0, sizeof(number));

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
    }
    if (strlen(number) != 0)
        add_token(&tokens, number);

    check_commas(tokens);

    return tokens;
}
