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

int ll_is_empty(LinkedList* list);

int ll_length(LinkedList* list);

void* ll_get_at(LinkedList* list, int index);

void ll_replace_at(LinkedList* list, int index, void* value);

void ll_add(LinkedList** list, void* elem);

void ll_add_at(LinkedList** list, void* elem, int index);

void ll_pop(LinkedList** list);

void ll_remove_at(LinkedList** list, int index);

#endif //CALCULATOR_LINKED_LIST_H
