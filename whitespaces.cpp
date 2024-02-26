#include <stdio.h>
int main() {
    char ch;
    int whitespaceCount = 0;
    int newlineCount = 0;
    printf("Enter text (Ctrl+D to end on Unix/Linux, Ctrl+Z on Windows):\n");
    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\t') {
            whitespaceCount++;
        } else if (ch == '\n') {
            newlineCount++;
        }
    }
    printf("Number of whitespaces: %d\n", whitespaceCount);
    printf("Number of newlines: %d\n", newlineCount);
    return 0;
}
