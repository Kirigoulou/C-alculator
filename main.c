#include <stdio.h>
#include "linked_list.h"

int main() {
    LinkedList* list = init_list();
    /*for (int i = 5; i < 20; i++) {
        add(&list, (void *) i);
    }

    pretty_print(list, INT);
    printf("\n");

    replace_at(list, 15, (void*) 999);*/

    //add(&list, (void*) 5);
    pretty_print(list, INT);
    return 0;
}
