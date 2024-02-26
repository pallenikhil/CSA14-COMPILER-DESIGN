#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Instruction {
    char result[10];
    char op;
    char operand1[10];
    char operand2[10];
} Instruction;

void optimizeCode(Instruction code[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(code[i].operand1, code[j].operand1) == 0 && 
                strcmp(code[i].operand2, code[j].operand2) == 0 &&
                code[i].op == code[j].op) {
                strcpy(code[j].result, code[i].result);
            }
        }
    }
}

int main() {
    Instruction code[] = {
        {"t1", '+', "a", "b"},
        {"t2", '-', "c", "d"},
        {"t3", '+', "a", "b"},
        {"t4", '*', "t1", "t2"},
        {"t5", '+', "t3", "t4"}
    };
    int n = sizeof(code) / sizeof(code[0]);

    printf("Before optimization:\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %s %c %s\n", code[i].result, code[i].operand1, code[i].op, code[i].operand2);
    }

    optimizeCode(code, n);

    printf("\nAfter optimization:\n");
    for (int i = 0; i < n; i++) {
        if (strcmp(code[i].result, "t") != 0) {
            printf("%s = %s %c %s\n", code[i].result, code[i].operand1, code[i].op, code[i].operand2);
        }
    }

    return 0;
}

