//
// Created by kirig on 12/06/2022.
//

#ifndef CALCULATOR_TYPES_H
#define CALCULATOR_TYPES_H

typedef enum Type {
    INT,
    FLOAT,
    CHAR,
    STRING
} Type;

typedef enum TokenType {
    TOKEN_OPERAND,
    TOKEN_OPERATOR,
    TOKEN_SEPARATOR,
    TOKEN_FUNCTION,
    TOKEN_COMMA
} TokenType;

void print(void* elem, Type type);

#endif //CALCULATOR_TYPES_H
