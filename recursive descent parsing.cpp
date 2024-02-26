#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
double expression();
double term();
double factor();
void error();
char *input;
void error() {
    fprintf(stderr, "Syntax error\n");
    exit(1);
}
double number() {
    double result = 0;
    while (isdigit(*input)) {
        result = result * 10 + (*input - '0');
        input++;
    }
    return result;
}
double factor() {
    if (*input == '(') {
        input++;
        double result = expression();
        if (*input == ')')
            input++;
        else
            error();
        return result;
    } else if (isdigit(*input)) {
        return number();
    } else {
        error();
        return 0; 
    }
}
double term() {
    double result = factor();
    while (input =='/' || *input == '/') {
        if (input == '') {
            input++;
            result *= factor();
        } else {
            input++;
            double denominator = factor();
            if (denominator == 0)
                error();
            result /= denominator;
        }
    }
    return result;
}
double expression() {
    double result = term();
    while (*input == '+' || *input == '-') {
        if (*input == '+') {
            input++;
            result += term();
        } else {
            input++;
            result -= term();
        }
    }
    return result;
}

int main() {
    char buffer[100];
    printf("Enter an arithmetic expression: ");
    fgets(buffer, sizeof(buffer), stdin);
    input = buffer;
    double result = expression();
    printf("Result: %lf\n", result);

    return 0;
}
