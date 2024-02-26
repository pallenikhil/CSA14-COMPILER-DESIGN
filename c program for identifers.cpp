#include <stdio.h>
#include <ctype.h>

int main() {
    char input[1000];
    int charCount = 0, wordCount = 0, lineCount = 0;
    char prevChar = '\0';

    printf("Enter text (Press Ctrl+D to end):\n");

    while (fgets(input, sizeof(input), stdin) != NULL) {
        for (int i = 0; input[i] != '\0'; i++) {
            char currentChar = input[i];
            charCount++;

            // Check for a new word
            if (isspace(currentChar) && !isspace(prevChar)) {
                wordCount++;
            }

            // Check for a new line
            if (currentChar == '\n') {
                lineCount++;
            }

            prevChar = currentChar;
        }
    }

    // If the last character is not a newline, count it as one line
    if (prevChar != '\n') {
        lineCount++;
    }

    printf("Number of characters: %d\n", charCount);
    printf("Number of words: %d\n", wordCount);
    printf("Number of lines: %d\n", lineCount);

    return 0;
}

