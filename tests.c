//
// Created by kirig on 17/06/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures/linked_list.h"
#include "Lexer/lexer.h"
#include "data_structures/ast.h"
#include "data_structures/stack.h"
#include "Parser/parser.h"
#include <time.h>

void test_lexer() {
    char a[] = "57 ^ 4 * (12 - 57735)";

    LinkedList* tokens = lex(a);
    while (tokens != NULL) {
        Token* token = tokens->value;
        printf("Value: %s | Precedence: %d | TYPE: %d\n", token->value, token->precedence, token->type);
        tokens = tokens->next;
    }
}

void test_parser() {
    char a[] = "57 ^ 4 + (2 - 5) * 5 - 33 * ( 12 + 1)";
    //char a[] = "57 + (4 * 78)";

    LinkedList *tokens = lex(a);
    Node *expr_tree = parse(tokens);

    Queue* postfix_expr = ast_to_postfix(expr_tree);
    while (!qu_is_empty(postfix_expr)) {
        Token *token = qu_pop(&postfix_expr);
        printf("%s ", token->value);
    }
}

void test_queue() {
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < 120) {
        Queue* st = init_queue();
        for (int i = 0; i < 20; i++) {
            //(void*) 0 is NULL
            qu_push(&st, (void*) i);
        }
        do {
            Queue* traversing = st;
            while (traversing != NULL) {
                printf("%d ", traversing->value);
                traversing = traversing->next;
            }
            int* val = qu_pop(&st);
            printf("| popped : %d", val);
            printf("\n");
        } while (!qu_is_empty(st));
    }
}

void test_stack() {
    time_t start_time = time(NULL);
    while (time(NULL) - start_time < 120) {
        Stack* st = init_stack();
        for (int i = 0; i < 20; i++) {
            //(void*) 0 is NULL
            st_push(&st, (void*) i);
        }
        do {
            Stack* traversing = st;
            while (traversing != NULL) {
                printf("%d ", traversing->value);
                traversing = traversing->next;
            }
            int* val = st_pop(&st);
            printf("| popped : %d", val);
            printf("\n");
        } while (!st_is_empty(st));
    }
}