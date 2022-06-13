//
// Created by kirig on 11/06/2022.
//
#import <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "types.h"

LinkedList* init_list() {
    return NULL;
}

int is_empty(LinkedList* list) {
    return list == NULL;
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
    if (list == NULL) {
        fprintf(stderr, "index out of range");
        exit(1);
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

void pop(LinkedList** list) {
    if (*list == NULL) {
        fprintf(stderr, "cannot pop an empty list");
        exit(1);
    }

    while ((**list).next != NULL)
        list = (LinkedList **) &((**list).next);

    *list = NULL;
}

void remove_at(LinkedList** list, int index) {
    if (index == 0) {
        LinkedList* target = *list;
        *list = target->next;
        free(target);
        return;
    }

    int i = 0;
    while (i++ < index-1) {
        if (*list == NULL) {
            fprintf(stderr, "index out of range");
            exit(1);
        }

        list = (LinkedList **) &((**list).next);
    }
    if ((**list).next == NULL) {
        fprintf(stderr, "index out of range");
        exit(1);
    }

    LinkedList* target = (**list).next;
    (**list).next = target->next;
    free(target);
}

void pretty_print(LinkedList* list, Type type) {
    if (list == NULL)
        return;

    print(list->value, type);

    list = list->next;
    if (list == NULL)
        return;

    printf(" |");
    while (list->next != NULL) {
        printf(" ");
        print(list->value, type);
        printf(" |");
        list = list->next;
    }
    printf(" ");
    print(list->value, type);
}