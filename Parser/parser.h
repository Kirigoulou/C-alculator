//
// Created by kirig on 15/06/2022.
//

#ifndef CALCULATOR_PARSER_H
#define CALCULATOR_PARSER_H

#include "../data_structures/linked_list.h"
#include "../data_structures/ast.h"
#include "../data_structures/stack.h"

Node* parse(LinkedList* tokens);

#endif //CALCULATOR_PARSER_H
