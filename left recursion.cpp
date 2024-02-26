#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_RULES 10
#define MAX_SYMBOLS 10
struct ProductionRule {
    char nonTerminal;
    char symbols[MAX_SYMBOLS];
    int symbolCount;
};
bool isNonTerminal(char symbol) {
    return symbol >= 'A' && symbol <= 'Z';
}
void addRule(struct ProductionRule rules[MAX_RULES], int* ruleCount, char nonTerminal, char* symbols, int symbolCount) {
    struct ProductionRule newRule;
    newRule.nonTerminal = nonTerminal;
    newRule.symbolCount = symbolCount;
    for (int i = 0; i < symbolCount; i++) {
        newRule.symbols[i] = symbols[i];
    }
    rules[(*ruleCount)++] = newRule;
}
void eliminateLeftRecursion(struct ProductionRule rules[MAX_RULES], int ruleCount) {
    for (int i = 0; i < ruleCount; i++) {
        char nonTerminal = rules[i].nonTerminal;
        for (int j = 0; j < i; j++) {
            if (rules[j].nonTerminal == nonTerminal) {
                char newNonTerminal = nonTerminal + 1;
                rules[ruleCount].nonTerminal = newNonTerminal;
                rules[ruleCount].symbols[0] = '\0';
                rules[ruleCount].symbolCount = 0;
                
                for (int k = 0; k < rules[i].symbolCount; k++) {
                    if (rules[i].symbols[k] == nonTerminal) {
                        char newSymbols[MAX_SYMBOLS];
                        int newSymbolCount = 0;
                        for (int l = k + 1; l < rules[i].symbolCount; l++) {
                            newSymbols[newSymbolCount++] = rules[i].symbols[l];
                        }
                        newSymbols[newSymbolCount++] = newNonTerminal;
                        addRule(rules, &ruleCount, newNonTerminal, newSymbols, newSymbolCount);
                    } else {
                        rules[ruleCount].symbols[rules[ruleCount].symbolCount++] = rules[i].symbols[k];
                    }
                }
                rules[ruleCount].symbols[rules[ruleCount].symbolCount++] = newNonTerminal;
                char epsilon[] = {'\0'};
                addRule(rules, &ruleCount, newNonTerminal, epsilon, 1);
                rules[i].symbolCount = 0;
                for (int k = 0; k < rules[j].symbolCount; k++) {
                    rules[i].symbols[rules[i].symbolCount++] = rules[j].symbols[k];
                }
                rules[i].symbols[rules[i].symbolCount++] = newNonTerminal;
            }
        }
    }
}
void printGrammar(struct ProductionRule rules[MAX_RULES], int ruleCount) {
    printf("Grammar after eliminating left recursion:\n");
    for (int i = 0; i < ruleCount; i++) {
        printf("%c -> ", rules[i].nonTerminal);
        for (int j = 0; j < rules[i].symbolCount; j++) {
            printf("%c", rules[i].symbols[j]);
        }
        printf("\n");
    }
}

int main() {
    struct ProductionRule rules[MAX_RULES];
    int ruleCount = 0;
    addRule(rules, &ruleCount, 'A', "Aa", 2);
    addRule(rules, &ruleCount, 'A', "b", 1);
    addRule(rules, &ruleCount, 'A', "", 0);

    printf("Original Grammar:\n");
    printGrammar(rules, ruleCount);

    eliminateLeftRecursion(rules, ruleCount);

    printGrammar(rules, ruleCount);

    return 0;
}

