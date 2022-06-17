//
// Created by kirig on 15/06/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "../data_structures/stack.h"
#include "../data_structures/linked_list.h"
#include "../Lexer/lexer.h"
#include "../data_structures/queue.h"

void raise_mismatched_parentheses() {
    fprintf(stderr, "mismatched parentheses");
    exit(2);
}

void manage_operator(Stack** operators_ptr, Queue** output_ptr, Token* operator) {
    if (!st_is_empty(*operators_ptr)) {
        //TODO too many is_empty tests
        Token* top_operator = st_peek(*operators_ptr);
        while (!st_is_empty(*operators_ptr) &&
               strcmp(top_operator->value, "(") != 0 && top_operator->precedence > operator->precedence) {
            st_pop(operators_ptr);
            qu_push(output_ptr, top_operator);
            if (!st_is_empty(*operators_ptr))
                top_operator = st_peek(*operators_ptr);
        }
    }
    st_push(operators_ptr, operator);
}

void manage_parentheses(Stack** operators_ptr, Queue** output_ptr, Token* parenthesis) {
    //TODO function do not pop opening parenthesis
    if (strcmp(parenthesis->value, "(") == 0)
        st_push(operators_ptr, parenthesis);
    else {
        if (!st_is_empty(*operators_ptr)) {
            Token* top_operator = st_peek(*operators_ptr);
            if (strcmp(top_operator->value, "(") != 0) {
                st_pop(operators_ptr);
                while (strcmp(top_operator->value, "(") != 0) {
                    if (st_is_empty(*operators_ptr))
                        raise_mismatched_parentheses();
                    qu_push(output_ptr, top_operator);
                    top_operator = st_pop(operators_ptr);
                }
            }
        }
        else
            raise_mismatched_parentheses();
    }
}

Queue* parse(LinkedList* tokens) {
    Stack *operators = init_stack();
    Queue *output = init_queue();
    while (tokens != NULL) {
        Token* token = tokens->value;
        if (token->type == TOKEN_OPERAND)
            qu_push(&output, (void*) token);
        else if (token->type == TOKEN_OPERATOR)
            manage_operator(&operators, &output, token);
        else
            manage_parentheses(&operators, &output, token);
        tokens = tokens->next;
    }
    while (!st_is_empty(operators)) {
        Token* top_operator = st_pop(&operators);
        if (strcmp(top_operator->value, "(") == 0)
            raise_mismatched_parentheses();
        else
            qu_push(&output, top_operator);
    }
    return output;
}