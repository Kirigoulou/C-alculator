//
// Created by kirig on 13/06/2022.
//

#ifndef CALCULATOR_STACK_H
#define CALCULATOR_STACK_H

#include "../types.h"

typedef struct Stack {
    void* next;
    void* value;
} Stack;

Stack* init_stack();

int st_is_empty(Stack* stack);

void* st_peek(Stack* stack);

void st_push(Stack** stack, void* elem);

void* st_pop(Stack** stack);

#endif //CALCULATOR_STACK_H
