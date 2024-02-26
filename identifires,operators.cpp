#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool is_operator(char c) {return c == '+' || c == '-' || c == '*' || c == '/';}
bool is_valid_char(char c) {return isalnum(c) || c == '_';}

void analyze(char exp[]) {
    for (int i = 0; exp[i]; i++) {
        if (isspace(exp[i])) continue;
        if (exp[i] == '/' && exp[i + 1] == '/') while (exp[i] && exp[i++] != '\n');
        if (exp[i] == '/' && exp[i + 1] == '') while (!(exp[i] == '' && exp[i + 1] == '/') && exp[i]) i++;
        if (isalpha(exp[i]) || exp[i] == '_') {
            printf("Identifier: ");
            while (is_valid_char(exp[i])) printf("%c", exp[i++]);
            printf("\n");
        }
        if (isdigit(exp[i])) {
            printf("Constant: ");
            while (isdigit(exp[i])) printf("%c", exp[i++]);
            printf("\n");
        }
        if (is_operator(exp[i])) printf("Operator: %c\n", exp[i]);
    }
}

int main() {
    char exp[1000];
    printf("Enter expression: ");
    fgets(exp, sizeof(exp), stdin);
    analyze(exp);
    return 0;
}
