#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct SymbolEntry {
    char name[50];
    int value;
    struct SymbolEntry *next;
} SymbolEntry;

SymbolEntry* createEntry(const char *name, int value) {
    SymbolEntry *newEntry = (SymbolEntry*)malloc(sizeof(SymbolEntry));
    if (newEntry != NULL) {
        strcpy(newEntry->name, name);
        newEntry->value = value;
        newEntry->next = NULL;
    }
    return newEntry;
}

void insertEntry(SymbolEntry **table, const char *name, int value) {
    SymbolEntry *newEntry = createEntry(name, value);
    if (newEntry != NULL) {
        newEntry->next = *table;
        *table = newEntry;
    }
}

SymbolEntry* searchEntry(SymbolEntry *table, const char *name) {
    SymbolEntry *current = table;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
void generateThreeAddressCode(const char *expression) {
}

int main() {
    SymbolEntry *symbolTable = NULL;

    insertEntry(&symbolTable, "x", 10);
    insertEntry(&symbolTable, "y", 20);
    insertEntry(&symbolTable, "z", 30);

    generateThreeAddressCode("x = y + z");

    return 0;
}

