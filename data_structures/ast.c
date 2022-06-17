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