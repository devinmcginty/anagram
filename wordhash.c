#include <string.h>
#include <stdlib.h>
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
    return (strlen(word) - (1 + MIN_WORD_LEN)) % LENGTH_HASH;
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

struct WordNode* createNode(char word[]) {
    WordNode* newNode = (struct WordNode*) malloc(sizeof(struct WordNode));
    strcpy(newNode->word, word);
    newNode->next = NULL;
    return newNode;
}

void insertWord(struct WordNode** head, struct WordNode* newNode) {
    if (*head == NULL) {
        newNode->next = *head;
        *head = newNode;
    }
    else {
        struct WordNode* current = *head;
        while (strcmp(current->next->word, newNode->word) < 0 &&
               current->next != NULL) {
            // printf("Scanning %s\n", current->word);
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void printList(struct WordNode* head) {
    struct WordNode* current;
    current = head;
    while (current != NULL) {
        printf("%s\n", current->word);
        current = current->next;
    }
    // printf("Leaving printList\n");
}

void deleteList(struct WordNode* head) {
    struct WordNode* tempNode;
    while (tempNode != NULL) {
        tempNode = head->next;
        // printf("Freeing %s\n", head->word);
        free(head);
        head = tempNode;
    }
    free(tempNode);
    // printf("Freeing %s\n", head->word);
}
