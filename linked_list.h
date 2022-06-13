//
// Created by kirig on 11/06/2022.
//

#ifndef CALCULATOR_LINKED_LIST_H
#define CALCULATOR_LINKED_LIST_H

#include "types.h"

typedef struct LinkedList {
    void* next;
    void* value;
} LinkedList;

LinkedList* init_list();

void pretty_print(LinkedList* list, Type type);

int is_empty(LinkedList* list);

int length(LinkedList* list);

void* get_at(LinkedList* list, int index);

void replace_at(LinkedList* list, int index, void* value);

void add(LinkedList** list, void* elem);

void pop(LinkedList** list);

void remove_at(LinkedList** list, int index);

#endif //CALCULATOR_LINKED_LIST_H
