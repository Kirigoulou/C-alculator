#include <stdio.h>
#include "data_structures/linked_list.h"
#include "data_structures/stack.h"

int main() {
    Stack* stack = init_stack();
    st_push(&stack, (void*) 10);
    st_push(&stack, (void*) 20);

    printf("%d", stack->value);

    return 0;
}
