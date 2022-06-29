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
#include "../data_structures/ast.h"

#define BUFF_SIZE 16

void raise_mismatched_parentheses() {
    fprintf(stderr, "mismatched parentheses");
    exit(2);
}

void raise_missing_operand() {
    fprintf(stderr, "missing operand");
    exit(2);
}

void raise_missing_parameter() {
    fprintf(stderr, "missing parameter in function");
    exit(2);
}

void raise_missing_operator() {
    fprintf(stderr, "missing operator");
    exit(2);
}

void push_operator_node(Stack** output_ptr, Token* operator) {
    Node *right_child = st_pop(output_ptr), *left_child = NULL;
    if (!st_is_empty(*output_ptr))
        left_child = st_pop(output_ptr);
    else
        raise_missing_operand();
    Node *operator_node = init_node(operator, left_child, right_child);
    st_push(output_ptr, operator_node);
}

void push_function_node(Stack **output_ptr, Token *function) {
    Node *first_child;
    if (st_is_empty(*output_ptr))
        raise_missing_parameter();

    first_child = st_pop(output_ptr);
    int is_unary = !(strcmp(function->value, "max") == 0 || strcmp(function->value, "min") == 0 ||
                   strcmp(function->value, "gcd") == 0);
    if (is_unary) {
        Token *zero_operand = malloc(sizeof(Token));
        zero_operand->value = malloc(BUFF_SIZE);
        strcpy_s(zero_operand->value, BUFF_SIZE, "0");
        zero_operand->type = TOKEN_OPERAND;
        zero_operand->precedence = 0;

        Node *zero_node = init_node(zero_operand, NULL, NULL);
        st_push(output_ptr, init_node(function, first_child, zero_node));
    }
    else {
        if (st_is_empty(*output_ptr))
            raise_missing_parameter();

        Node *second_child = st_pop(output_ptr);
        st_push(output_ptr, init_node(function, second_child, first_child));
    }
}

void manage_operand(Stack **output_ptr, Token *operand) {
    Node* operand_node = init_node(operand, NULL, NULL);
    st_push(output_ptr, operand_node);
}

void manage_operator(Stack** operators_ptr, Stack** output_ptr, Token* operator) {
    if (!st_is_empty(*operators_ptr)) {
        Token* top_operator = st_peek(*operators_ptr);

        while (!st_is_empty(*operators_ptr) &&
               strcmp(top_operator->value, "(") != 0 && (top_operator->precedence > operator->precedence ||
                top_operator->precedence == operator->precedence && strcmp(operator->value, "^") != 0)) {
            st_pop(operators_ptr);

            push_operator_node(output_ptr, top_operator);

            if (!st_is_empty(*operators_ptr)) {
                top_operator = st_peek(*operators_ptr);
            }
        }

        //free(top_operator);
    }

    st_push(operators_ptr, operator);
}

void manage_comma(Stack** operators_ptr, Stack** output_ptr) {
    while (!st_is_empty(*operators_ptr) && ((Token*) st_peek(*operators_ptr))->value[0] != '(') {
        Token *top_operator = st_pop(operators_ptr);
        push_operator_node(output_ptr, top_operator);
    }
}

void manage_parentheses(Stack** operators_ptr, Stack** output_ptr, Token* parenthesis) {
    if (strcmp(parenthesis->value, "(") == 0)
        st_push(operators_ptr, parenthesis);
    else {
        /*if (!st_is_empty(*operators_ptr)) {
            Token* top_operator = st_peek(*operators_ptr);

            if (strcmp(top_operator->value, "(") != 0) {
                st_pop(operators_ptr);
                while (strcmp(top_operator->value, "(") != 0) {
                    if (st_is_empty(*operators_ptr))
                        raise_mismatched_parentheses();

                    push_operator_node(output_ptr, top_operator);

                    top_operator = st_pop(operators_ptr);
                }
            }
            else
                st_pop(operators_ptr);

            if (!st_is_empty(*operators_ptr) && ((Token*) st_peek(*operators_ptr))->type == TOKEN_FUNCTION)
                push_function_node(output_ptr, st_pop(operators_ptr));
            //free(top_operator);
        }
        else
            raise_mismatched_parentheses();*/
        manage_comma(operators_ptr, output_ptr);
        if (st_is_empty(*operators_ptr))
            raise_mismatched_parentheses();
        st_pop(operators_ptr);
        if (!st_is_empty(*operators_ptr) && ((Token*) st_peek(*operators_ptr))->type == TOKEN_FUNCTION)
            push_function_node(output_ptr, st_pop(operators_ptr));
    }
}

Node* parse(LinkedList* tokens) {
    //TODO modify parser so that it supports left associativity

    Stack *operators = init_stack(), *output = init_stack();
    while (tokens != NULL) {
        Token* token = tokens->value;
        if (token->type == TOKEN_OPERAND)
            manage_operand(&output, token);
        else if (token->type == TOKEN_FUNCTION)
            st_push(&operators, token);
        else if (token->type == TOKEN_COMMA)
            manage_comma(&operators, &output);
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
        else {
            push_operator_node(&output, top_operator);
        }
    }
    Node* result_operation = st_pop(&output);
    if (!st_is_empty(output))
        raise_missing_operator();
    return result_operation;
}