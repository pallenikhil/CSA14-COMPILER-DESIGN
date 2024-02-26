#include <stdio.h>
#include <stdbool.h>
#include <string.h>
bool isSpace(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}
bool isAlpha(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
bool isValidSentence(const char *sentence) {
    int length = strlen(sentence);
    bool foundSpace = false;
    bool foundAlpha = false;
    bool foundVerb = false;
    bool foundSubject = false;
    bool foundObject = false;

    for (int i = 0; i < length; i++) {
        if (!isSpace(sentence[i]) && !isAlpha(sentence[i])) {
            return false;
        }
        if (isAlpha(sentence[i])) {
            foundAlpha = true;
            if (!foundSpace) {
                foundSubject = true;
            } else if (!foundVerb) {
                foundVerb = true;
            } else {
                foundObject = true;
            }
        }
        if (isSpace(sentence[i])) {
            foundSpace = true;
        }
    }
    return (foundAlpha && foundSubject && foundVerb && foundObject);
}
int main() {
    char sentence[100];
    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0';
    if (isValidSentence(sentence)) {
        printf("The sentence is valid according to the grammar.\n");
    } else {
        printf("The sentence is not valid according to the grammar.\n");
    }
    return 0;
}
