#include <stdio.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 10

struct ProductionRule {
    char nonTerminal;
    char symbols[MAX_SYMBOLS];
    int symbolCount;
};

void addRule(struct ProductionRule rules[MAX_RULES], int* ruleCount, char nonTerminal, char* symbols, int symbolCount) {
    struct ProductionRule newRule = {nonTerminal, {0}, symbolCount};
    memcpy(newRule.symbols, symbols, symbolCount);
    rules[(*ruleCount)++] = newRule;
}

void eliminateLeftFactoring(struct ProductionRule rules[MAX_RULES], int* ruleCount) {
    for (int i = 0; i < *ruleCount; i++) {
        char nonTerminal = rules[i].nonTerminal;
        int prefixLen = 0;
        for (int j = i + 1; j < *ruleCount; j++)
            if (rules[j].nonTerminal == nonTerminal)
                for (int k = 0; rules[i].symbols[k] && rules[i].symbols[k] == rules[j].symbols[k]; k++)
                    if (k > prefixLen) prefixLen = k;

        if (prefixLen > 0) {
            char newNonTerminal = nonTerminal + 1, newSymbols[MAX_SYMBOLS];
            memcpy(newSymbols, rules[i].symbols, prefixLen);
            for (int k = 0; k < *ruleCount; k++)
                if (rules[k].nonTerminal == nonTerminal) memmove(rules[k].symbols, &rules[k].symbols[prefixLen], MAX_SYMBOLS - prefixLen), rules[k].symbolCount -= prefixLen;
            addRule(rules, ruleCount, nonTerminal, newSymbols, prefixLen);
            for (int k = i; k < *ruleCount; k++) if (rules[k].nonTerminal == nonTerminal) addRule(rules, ruleCount, newNonTerminal, rules[k].symbols, rules[k].symbolCount);
        }
    }
}

void printGrammar(struct ProductionRule rules[MAX_RULES], int ruleCount) {
    printf("Grammar after eliminating left factoring:\n");
    for (int i = 0; i < ruleCount; i++) {
        printf("%c -> ", rules[i].nonTerminal);
        for (int j = 0; j < rules[i].symbolCount; j++) printf("%c", rules[i].symbols[j]);
        printf("\n");
    }
}

int main() {
    struct ProductionRule rules[MAX_RULES];
    int ruleCount = 0;
    // Example Grammar: A -> ab | ac | abc | ad
    addRule(rules, &ruleCount, 'A', "ab", 2);
    addRule(rules, &ruleCount, 'A', "ac", 2);
    addRule(rules, &ruleCount, 'A', "abc", 3);
    addRule(rules, &ruleCount, 'A', "ad", 2);
    printf("Original Grammar:\n");
    printGrammar(rules, ruleCount);
    eliminateLeftFactoring(rules, &ruleCount);
    printGrammar(rules, ruleCount);
    return 0;
}

