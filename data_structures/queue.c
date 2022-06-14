//
// Created by kirig on 14/06/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* init_queue() {
    return NULL;
}

int qu_is_empty(Queue* queue) {
    return queue == NULL;
}

void* qu_peek(Queue* queue) {
    if (qu_is_empty(queue)){
        fprintf(stderr, "cannot peek an empty queue");
        exit(1);
    }

    while (queue->next != NULL)
        queue = queue->next;

    return queue->value;
}

void qu_push(Queue** queue, void* elem) {
    Queue* new_head = (Queue*) malloc(sizeof(Queue*));
    new_head->next = *queue;
    new_head->value = elem;
    *queue = new_head;
}

void qu_pop(Queue** queue) {
    if (qu_is_empty(*queue)) {
        fprintf(stderr, "cannot pop an empty queue");
        exit(1);
    }

    while ((**queue).next != NULL)
        queue = (Queue**) &(**queue).next;

    *queue = NULL;
}