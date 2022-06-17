//
// Created by kirig on 13/06/2022.
//
#include <stdio.h>
#include "stdlib.h"
#include "stack.h"

Stack* init_stack() {
    return NULL;
}

int st_is_empty(Stack* stack) {
    return stack == NULL;
}

void* st_peek(Stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, "cannot peek into an empty stack");
        exit(1);
    }

    return stack->value;
}

void st_push(Stack** stack, void* elem) {
    Stack* new_head = malloc(sizeof(Stack*));
    new_head->value = elem;
    new_head->next = *stack;
    *stack = new_head;
}

void* st_pop(Stack** stack) {
    if (*stack == NULL){
        fprintf(stderr, "cannot pop an empty stack");
        exit(1);
    }

    Stack* target = *stack;
    *stack = (**stack).next;
    return target;
}