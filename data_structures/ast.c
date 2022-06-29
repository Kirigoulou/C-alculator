//
// Created by kirig on 15/06/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "ast.h"
#include "../Lexer/lexer.h"

#define BUFF_SIZE 16

#pragma region arithmetical functions

long max(long a, long b) {
    return a >= b ? a : b;
}

long min(long a, long b) {
    return a <= b ? a : b;
}

long mysqrt(long a) {
    return (long) sqrt(a);
}

long facto(long a) {
    if (a < 0) {
        fprintf(stderr, "factorial of a negative number");
        exit(3);
    }

    long res = 1;
    while (a > 1)
        res *= a--;
    return res;
}

long is_prime(long a) {
    int div = 2;
    while (div * div < a && a % div != 0)
        div++;
    return div * div < a ? 0 : 1;
}

long fibo(int a) {
    if (a < 0) {
        fprintf(stderr, "fibonacci sequence of a negative number");
        exit(3);
    }
    if (a == 0)
        return 0;

    int x = 0, y = 1, cpt = 2;
    while (cpt++ <= a) {
        int tmp = x;
        x = y;
        y = y + tmp;
    }
    return y;
}

long gcd(int a, int b) {
    while (b != 0) {
        int tmp = a;
        a = b;
        b = a % b;
    }
    return a;
}

#pragma endregion

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

long compute_operator(char operator_symbol, long left_value, long right_value) {
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
    return res;
}

long compute_function(char name[], long left_value, long right_value) {
    if (strcmp(name, "max") == 0)
        return max(left_value, right_value);
    if (strcmp(name, "max") == 0)
        return max(left_value, right_value);
    if (strcmp(name, "sqrt") == 0)
        return mysqrt(left_value);
    if (strcmp(name, "facto") == 0)
        return facto(left_value);
    if (strcmp(name, "isprime") == 0)
        return is_prime(left_value);
    if (strcmp(name, "fibo") == 0)
        return fibo(left_value);

    return gcd(left_value, right_value);
}

void compute_node(Node** node) {
    Node *left = (**node).left, *right = (**node).right;
    Token *operator = (**node).value, *left_operand = left->value, *right_operand = right->value;

    long left_value = strtol(left_operand->value, NULL, 10),
        right_value = strtol(right_operand->value, NULL, 10);
    long res = 0;

    if (operator->type == TOKEN_OPERATOR) {
        char operator_symbol = (operator->value)[0];
        res = compute_operator(operator_symbol, left_value, right_value);
    }
    else
        res = compute_function(operator->value, left_value, right_value);

    snprintf(operator->value, sizeof operator->value, "%ld", res);

    free(left_operand->value);
    free(left_operand);
    free(right_operand->value);
    free(right_operand);
    free(left);
    free(right);
    
    (**node).left = NULL;
    (**node).right = NULL;
}

void evaluate_rec(Node* node) {
    if (node != NULL) {
        evaluate_rec(node->left);
        evaluate_rec(node->right);

        if (((Token*) node->value)->type == TOKEN_OPERATOR || ((Token*) node->value)->type == TOKEN_FUNCTION) {
            compute_node(&node);
        }
    }
}

long evaluate(Node* node) {
    evaluate_rec(node);
    return strtol(((Token*)node->value)->value, NULL, 10);
}