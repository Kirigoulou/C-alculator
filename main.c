#include <stdio.h>
#include "linked_list.h"

int main() {
    LinkedList* list = init_list();
    add(&list, (void*) 5);
    add(&list, (void*)10);
    printf("%d\n", get_at(list, 0));
    printf("%d\n", get_at(list, 1));
    printf("%d\n", get_at(list, 2));

    return 0;
}
