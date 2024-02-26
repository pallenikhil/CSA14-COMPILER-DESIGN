#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}
void lexical_analyzer(char expression[]) {
    int length = strlen(expression);
    int i;
    printf("Operators found:\n");
    for (i = 0; i < length; i++) {
        if (is_operator(expression[i])) {
            printf("%c\n", expression[i]);
        }
    }
}
int main() {
    char expression[100];
    printf("Enter an arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);
    lexical_analyzer(expression);
    return 0;
}

