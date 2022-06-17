//
// Created by kirig on 15/06/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"

Node* init_node(void* value, Node* left, Node* right) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->left = left;
    node->right = right;
    return node;
}

void infix_traversal(Node* root) {
    if (root != NULL) {
        infix_traversal(root->left);
        printf("%d\n", root->value);
        infix_traversal(root->right);
    }
}

void ast_to_postfix_rec(Queue** postfix_expr_ptr, Node* root) {
    if (root != NULL) {
        ast_to_postfix_rec(postfix_expr_ptr, root->left);
        ast_to_postfix_rec(postfix_expr_ptr, root->right);
        qu_push(postfix_expr_ptr, root->value);
    }
}

Queue* ast_to_postfix(Node* root) {
    Queue* postfix_expr = init_queue();
    ast_to_postfix_rec(&postfix_expr, root);
    return postfix_expr;
}