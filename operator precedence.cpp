#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

double evaluateExpression(const char *expression);

double calculate(double num1, double num2, char op);

int main() {
    char expression[100];
    
    printf("Enter an arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);

    // Remove newline character if present
    if (expression[strlen(expression) - 1] == '\n') {
        expression[strlen(expression) - 1] = '\0';
    }

    double result = evaluateExpression(expression);
    printf("Result: %.2f\n", result);

    return 0;
}

double evaluateExpression(const char *expression) {
    double operandStack[50];
    char operatorStack[50];
    int operandTop = -1, operatorTop = -1;
    char *token, *ptr;

    token = strtok((char *)expression, " ");
    while (token != NULL) {
        if (isdigit(*token)) {
            operandStack[++operandTop] = strtod(token, &ptr);
        } else if (*token == '(') {
            operatorStack[++operatorTop] = *token;
        } else if (*token == ')') {
            while (operatorStack[operatorTop] != '(') {
                double operand2 = operandStack[operandTop--];
                double operand1 = operandStack[operandTop--];
                char op = operatorStack[operatorTop--];
                operandStack[++operandTop] = calculate(operand1, operand2, op);
            }
            operatorTop--; // Discard '('
        } else {
            while (operatorTop != -1 && operatorStack[operatorTop] != '(' &&
                   ((*token == '*' || *token == '/') && (operatorStack[operatorTop] == '*' || operatorStack[operatorTop] == '/')) ||
                   ((*token == '+' || *token == '-') && (operatorStack[operatorTop] == '+' || operatorStack[operatorTop] == '-' ||
                                                        operatorStack[operatorTop] == '*' || operatorStack[operatorTop] == '/'))) {
                double operand2 = operandStack[operandTop--];
                double operand1 = operandStack[operandTop--];
                char op = operatorStack[operatorTop--];
                operandStack[++operandTop] = calculate(operand1, operand2, op);
            }
            operatorStack[++operatorTop] = *token;
        }
        token = strtok(NULL, " ");
    }

    while (operatorTop != -1) {
        double operand2 = operandStack[operandTop--];
        double operand1 = operandStack[operandTop--];
        char op = operatorStack[operatorTop--];
        operandStack[++operandTop] = calculate(operand1, operand2, op);
    }

    return operandStack[operandTop];
}

double calculate(double num1, double num2, char op) {
    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            return num1 / num2;
        case '^':
            return pow(num1, num2);
        default:
            printf("Invalid operator\n");
            exit(EXIT_FAILURE);
    }
}

