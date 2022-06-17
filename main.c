#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures/linked_list.h"
#include "Lexer/lexer.h"
#include "data_structures/ast.h"
#include "data_structures/stack.h"
#include "Parser/parser.h"
#include "tests.h"


int main() {
    test_parser();

    return 0;
}
