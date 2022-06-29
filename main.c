#include <stdio.h>
#include <string.h>
#include "data_structures/linked_list.h"
#include "Lexer/lexer.h"
#include "data_structures/ast.h"
#include "Parser/parser.h"

#define BUFF_SIZE 256

int main() {
    char expr[BUFF_SIZE] = "";
    fgets(expr, BUFF_SIZE-1, stdin);
    expr[strcspn(expr, "\n")] = '\0';

    LinkedList *tokens = lex(expr);
    Node *expr_node = parse(tokens);

    Queue *a = ast_to_postfix(expr_node);
    while (!qu_is_empty(a)) {
        Token *tok = qu_pop(&a);
        printf("%s ", tok->value);
    }

    int res = evaluate(expr_node);
    printf("\n%ld", res);

    return 0;
}
