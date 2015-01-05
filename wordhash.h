#ifndef WORDHASH_H
#define WORDHASH_H

#define MAX_HASH_NUM 64
#define MAX_WORD_LEN 32
#define LENGTH_HASH 8
#define MIN_WORD_LEN 2

typedef struct WordNode {
    char word[MAX_WORD_LEN];
    struct WordNode* next;
} WordNode;

void toUpper(char* word);

int hashLength(char* word);

int genWordHash(char* word);

void sortString(char* word, char* sorted);

struct WordNode* createNode(char word[]);

void insertWord(struct WordNode** head, struct WordNode* newNode);

void printList(WordNode* head);

void deleteList(WordNode* head);

#endif // WORDHASH_H
