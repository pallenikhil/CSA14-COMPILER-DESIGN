#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
bool isValidIdentifier(const char *identifier) {
    if (!isalpha(identifier[0]) && identifier[0] != '_')
        return false;
    for (int i = 1; i < strlen(identifier); i++) {
        if (!isalnum(identifier[i]) && identifier[i] != '_')
            return false;
    }
    return true;
}

int main() {
    char identifier[50];
    printf("Enter an identifier: ");
    scanf("%s", identifier);
    if (isValidIdentifier(identifier))
        printf("Valid identifier!\n");
    else
        printf("Invalid identifier!\n");
    return 0;
}

