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
    struct WordNode nodep;
    if (*head == NULL) {
        newNode->next = *head;
    }
}

void printList(struct WordNode* head) {

}

void deleteList(struct WordNode* head) {

}
