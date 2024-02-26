#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
void generateThreeAddressCode(const char *expression);
int main() {
    char expression[100];
    printf("Enter an arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);
    if (expression[strlen(expression) - 1] == '\n')
        expression[strlen(expression) - 1] = '\0';
    generateThreeAddressCode(expression);
    return 0;
}

void generateThreeAddressCode(const char *expression) {
    char t = '0';
    char opStack[50], operandStack[50];
    int topOp = -1, topOperand = -1;
    char *token, *ptr;
    token = strtok((char *)expression, " ");
    while (token != NULL) {
        if (isdigit(*token)) {
            printf("t%c = %s\n", t++, token);
            operandStack[++topOperand] = t - 1;
        } else if (*token == '(') {
            opStack[++topOp] = *token;
        } else if (*token == ')') {
            while (opStack[topOp] != '(') {
                char op = opStack[topOp--];
                char operand2 = operandStack[topOperand--];
                char operand1 = operandStack[topOperand--];
                printf("t%c = %c %c %c\n", t++, operand1, op, operand2);
                operandStack[++topOperand] = t - 1;
            }
            topOp--; 
        } else {
            while (topOp != -1 && opStack[topOp] != '(' &&
                   ((*token == '*' || *token == '/') && (opStack[topOp] == '*' || opStack[topOp] == '/')) ||
                   ((*token == '+' || *token == '-') && (opStack[topOp] == '+' || opStack[topOp] == '-' ||
                                                        opStack[topOp] == '*' || opStack[topOp] == '/'))) {
                char op = opStack[topOp--];
                char operand2 = operandStack[topOperand--];
                char operand1 = operandStack[topOperand--];
                printf("t%c = %c %c %c\n", t++, operand1, op, operand2);
                operandStack[++topOperand] = t - 1;
            }
            opStack[++topOp] = *token;
        }
        token = strtok(NULL, " ");
    }
    while (topOp != -1) {
        char op = opStack[topOp--];
        char operand2 = operandStack[topOperand--];
        char operand1 = operandStack[topOperand--];
        printf("t%c = %c %c %c\n", t++, operand1, op, operand2);
        operandStack[++topOperand] = t - 1;
    }
    printf("Result: t%c\n", t - 1);
}

