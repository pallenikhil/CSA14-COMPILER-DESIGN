#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Grammar rules
const char *productions[] = {
    "S -> E",
    "E -> E + T",
    "E -> T",
    "T -> T * F",
    "T -> F",
    "F -> ( E )",
    "F -> id"
};

// Parsing table (corrected)
char parsingTable[7][5][20] = {
    { "", "", "", "", "" },
    { "s1", "", "", "", "" },
    { "", "s2", "", "", "" },
    { "", "r2", "s3", "", "" },
    { "", "r4", "r4", "s5", "" },
    { "s6", "", "", "", "" },
    { "", "r7", "r7", "r7", "r7" },
};

bool slrParser(const char *input) {
    char stack[1000];
    int top = 0;
    int state = 0;

    stack[top] = '0';

    int index = 0;
    char symbol = input[index];

    while (true) {
        char action[20];
        strcpy(action, parsingTable[state][symbol - '0']);

        if (action[0] == '\0') {
            printf("Parsing error!\n");
            return false;
        }

        if (action[0] == 's') {
            stack[++top] = symbol;
            stack[++top] = action[1];
            state = action[1] - '0';
            symbol = input[++index];
        } else if (action[0] == 'r') {
            int production = action[1] - '0';
            int len = strlen(productions[production]);
            int popCount = len - 4;

            while (popCount--) {
                top -= 2;
            }

            int newState = stack[top] - '0';
            stack[++top] = productions[production][0];
            stack[++top] = parsingTable[newState][stack[top-1]-'0'][0];

            state = newState;
        } else if (action[0] == 'a') {
            printf("Parsing successful!\n");
            return true;
        }
    }
}

int main() {
    const char *input = "id+id*id";
    printf("Input: %s\n", input);
    if (slrParser(input)) {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }
    return 0;
}
