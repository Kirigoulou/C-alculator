#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures/linked_list.h"
#include "data_structures/stack.h"
#include "data_structures/queue.h"
#include "Lexer/lexer.h"

int main() {
    char a[] = "57 ^ 4 * (12 - 57735)";

    LinkedList* tokens = lex(a);
    while (tokens != NULL) {
        Token* token = tokens->value;
        printf("Value: %s | Precedence: %d | TYPE: %d\n", token->value, token->precedence, token->type);
        tokens = tokens->next;
    }

    return 0;
}
