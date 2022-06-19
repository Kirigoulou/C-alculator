//
// Created by kirig on 14/06/2022.
//

#ifndef CALCULATOR_QUEUE_H
#define CALCULATOR_QUEUE_H

typedef struct Queue {
    void* next;
    void* value;
} Queue;

Queue* init_queue();

int qu_is_empty(Queue* queue);

void* qu_peek(Queue* queue);

void qu_push(Queue** queue, void* elem);

void* qu_pop(Queue** queue);

#endif //CALCULATOR_QUEUE_H
