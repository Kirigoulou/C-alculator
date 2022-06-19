//
// Created by kirig on 12/06/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

void print(void* elem, Type type){
    switch (type) {
        case INT:
            printf("%d", (int*) elem);
            break;
        case FLOAT:
            printf("%f", (float*) elem);
            break;
        case CHAR:
            printf("%c", (char*) elem);
            break;
        case STRING:
            printf("%s", elem);
            break;
        default:
            fprintf(stderr, "undefined type");
            exit(1);
    }
}
