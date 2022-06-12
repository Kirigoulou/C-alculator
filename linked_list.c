//
// Created by kirig on 11/06/2022.
//
#import <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

LinkedList* init_list() {
    return NULL;
}

int is_empty(LinkedList* list) {
    return list->next == NULL;
}

int length(LinkedList* list) {
    int n = 0;
    while (list->next != NULL) {
        n++;
        list = list->next;
    }
    return n;
}

void* get_at(LinkedList* list, int index) {
    int i = 0;
    while (i++ < index) {
        if (list->next == NULL) {
            fprintf(stderr, "index out of range");
            exit(1);
        }

        list = list->next;
    }
    return list->value;
}

void replace_at(LinkedList* list, int index, void* value) {
    int i = 0;
    while (i++ < index) {
        if (list == NULL) {
            fprintf(stderr, "index out of range");
            exit(1);
        }

        list = list->next;
    }
    list->value = value;
}

void add(LinkedList** list, void* elem) {
    LinkedList* current = *list;
    while (*list  != NULL)
        list  = (LinkedList **) &(*list)->next;

    *list  = malloc(sizeof(LinkedList**));
    (*list)->next = NULL;
    (*list)->value = elem;
}

void remove_at(LinkedList* list, int index) {
    int i = 0;
    while (i++ < index-1) {
        if (list == NULL) {
            fprintf(stderr, "index out of range");
            exit(1);
        }

        list = list->next;
    }

    LinkedList* target = list->next;
    list->next = target->next;
    free(target);
}