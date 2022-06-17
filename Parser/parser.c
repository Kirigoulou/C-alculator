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

void raise_mismatched_parentheses() {
    fprintf(stderr, "mismatched parentheses");
    exit(2);
}

void manage_operand(Stack** output_ptr, Token* operand) {
    Node* operand_node = init_node(operand, NULL, NULL);
    st_push(output_ptr, operand_node);
}

void manage_operator(Stack** operators_ptr, Stack** output_ptr, Token* operator) {
    if (!st_is_empty(*operators_ptr)) {
        Token* top_operator = st_peek(*operators_ptr);

        while (!st_is_empty(*operators_ptr) &&
               strcmp(top_operator->value, "(") != 0 && top_operator->precedence >= operator->precedence) {
            st_pop(operators_ptr);

            Node *right_child = st_pop(output_ptr), *left_child = st_pop(output_ptr);
            Node *operator_node = init_node(top_operator, left_child, right_child);
            st_push(output_ptr, operator_node);

            if (!st_is_empty(*operators_ptr)) {
                top_operator = st_peek(*operators_ptr);
            }
        }

        //free(top_operator);
    }

    st_push(operators_ptr, operator);
}

void manage_parentheses(Stack** operators_ptr, Stack** output_ptr, Token* parenthesis) {
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


                    Node *right_child = st_pop(output_ptr), *left_child = st_pop(output_ptr);
                    Node *operator_node = init_node(top_operator, left_child, right_child);
                    st_push(output_ptr, operator_node);

                    top_operator = st_pop(operators_ptr);
                }
            }

            //free(top_operator);
        }
        else
            raise_mismatched_parentheses();
    }
}

Stack* parse(LinkedList* tokens) {
    //TODO modify parser so that it supports left associativity

    Stack *operators = init_stack(), *output = init_stack();
    while (tokens != NULL) {
        Token* token = tokens->value;
        if (token->type == TOKEN_OPERAND)
            manage_operand(&output, token);
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

            Node *right_child = st_pop(&output), *left_child = st_pop(&output);
            Node *operator_node = init_node(top_operator, left_child, right_child);
            st_push(&output, operator_node);
        }
    }
    return output->value;
}