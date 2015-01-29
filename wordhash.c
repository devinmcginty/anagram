#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./wordhash.h"

void toUpper(char* word) {
    int caseDiff = 'a' - 'A';
    int i;
    for (i = 0; i < strlen(word); i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            word[i] -= caseDiff;
        }
    }
}

int hashLength(char* word) {
    int len;
    len = (strlen(word) - MIN_WORD_LEN) % LENGTH_HASH;
    return len;
}

int genWordHash(char* word) {
    toUpper(word);
    unsigned int hashNum = 0;
    int alphaOffset = 'A' - 1,
        len = strlen(word),
        i;
    for (i = 0; i < len; i++) {
        if (word[i] >= 'A' && word[i] <= 'Z') {
            hashNum += word[i] - alphaOffset;
        }
    }
    return hashNum % MAX_HASH_NUM;
}

void sortString(char* word, char* sorted) {
    if (word) {
        char rstring[strlen(word)],
             ch;
        int position = 0,
            i;
        for (ch = 'A'; ch <= 'Z'; ch++ ) {
            for (i = 0; i < strlen(word); i++) {
                if (word[i] == ch) {
                    rstring[position] = ch;
                    position++;
                }
            }
        }
        rstring[position] = '\0';   // Terminating string
        strcpy(sorted, rstring);
    }
    else {
        strcpy(sorted, "");
    }
}

struct WordNode* createNode(char word[]) {
    WordNode* newNode = (struct WordNode*) malloc(sizeof(struct WordNode));
    if (newNode == NULL) {
        fprintf(stderr, "Aborting: malloc in createNode() returned NULL\n");
        exit(1);
    }
    strcpy(newNode->word, word);
    newNode->next = NULL;
    return newNode;
}

void insertWord(struct WordNode** head, char word[]) {
    struct WordNode* newNode = createNode(word);
    char currentWord[MAX_WORD_LEN];
    if (*head == NULL) {
        newNode->next = *head;
        *head = newNode;
    }
    else {
        if (strcmp((*head)->word, word) > 0) {
            newNode->next = *head;
            *head = newNode;
        }
        else {
            struct WordNode* current = *head;
            while (current->next != NULL &&
                   strcmp(current->next->word, word) <= 0) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }
}

void printAnagrams(struct WordNode* head, char word[]) {
    struct WordNode* current;
    current = head;
    char wordSorted[MAX_WORD_LEN],
         currentSorted[MAX_WORD_LEN];
    sortString(word, wordSorted);
    int comparison;
    while (current != NULL) {
        sortString(current->word, currentSorted);
        comparison = strcmp(currentSorted, wordSorted);
        if (!comparison) {
            printf("%s\n", current->word);
        }
        current = current->next;
    }
}

void printList(struct WordNode* head) {
    struct WordNode* current;
    current = head;
    while (current != NULL) {
        char sorted[MAX_WORD_LEN];
        sortString(current->word, sorted);
        printf("%s\n", current->word);
        current = current->next;
    }
}

void deleteList(struct WordNode* head) {
    struct WordNode* tempNode;
    while (tempNode != NULL) {
        tempNode = head->next;
        free(head);
        head = tempNode;
    }
    free(head);
    head = NULL;
}
