//
// Created by kirig on 15/06/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ast.h"
#include "../Lexer/lexer.h"

#define BUFF_SIZE 16

void raise_dividebyzero() {
    fprintf(stderr, "can not divide by 0");
    exit(2);
}

Node* init_node(void* value, Node* left, Node* right) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->left = left;
    node->right = right;
    return node;
}

void infix_traversal(Node* node) {
    if (node != NULL) {
        infix_traversal(node->left);
        printf("%d\n", node->value);
        infix_traversal(node->right);
    }
}

void ast_to_postfix_rec(Queue** postfix_expr_ptr, Node* node) {
    if (node != NULL) {
        ast_to_postfix_rec(postfix_expr_ptr, node->left);
        ast_to_postfix_rec(postfix_expr_ptr, node->right);
        qu_push(postfix_expr_ptr, node->value);
    }
}

Queue* ast_to_postfix(Node* root) {
    Queue* postfix_expr = init_queue();
    ast_to_postfix_rec(&postfix_expr, root);
    return postfix_expr;
}

void compute_node(Node** node) {
    Node *left = (**node).left, *right = (**node).right;
    Token *operator = (**node).value, *left_operand = left->value, *right_operand = right->value;

    char operator_symbol = (operator->value)[0];
    long left_value = strtol(left_operand->value, NULL, 10),
        right_value = strtol(right_operand->value, NULL, 10);
    long res = 0;
    switch (operator_symbol) {
        case '+':
            res = left_value + right_value;
            break;
        case '-':
            res = left_value - right_value;
            break;
        case '*':
            res = left_value * right_value;
            break;
        case '/':
            if (right_value == 0)
                raise_dividebyzero();
            res = left_value / right_value;
            break;
        case '^':
            res = pow(left_value, right_value);
            break;
        case '%':
            if (right_value == 0)
                raise_dividebyzero();
            res = left_value % right_value;
            break;
        default:
            break;
    }

    snprintf(operator->value, sizeof operator->value, "%d", res);
    free(left);
    free(right);
    (**node).left = NULL;
    (**node).right = NULL;
}

void evaluate_rec(Node* node) {
    if (node != NULL) {
        evaluate_rec(node->left);
        evaluate_rec(node->right);

        if (((Token*) node->value)->type == TOKEN_OPERATOR) {
            compute_node(&node);
        }
    }
}

long evaluate(Node* node) {
    evaluate_rec(node);
    return strtol(((Token*)node->value)->value, NULL, 10);
}