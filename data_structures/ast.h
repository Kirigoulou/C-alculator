//
// Created by kirig on 15/06/2022.
//

#ifndef CALCULATOR_AST_H
#define CALCULATOR_AST_H

#include "queue.h"

typedef struct Node {
    struct Node* left;
    struct Node* right;
    void* value;
} Node;

Node* init_node(void* value, Node* left, Node* right);

void infix_traversal(Node* root);

Queue* ast_to_postfix(Node* root);

#endif //CALCULATOR_AST_H
