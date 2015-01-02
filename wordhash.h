#ifndef WORDHASH_H
#define WORDHASH_H

#define MAX_HASH_NUM 64
#define MAX_WORD_LEN 32
#define LENGTH_HASH 8
#define MIN_WORD_LEN 2

typedef struct combination_node {
    char combination[MAX_WORD_LEN];
    struct combination_node* next;
} combination_node;

typedef struct permutation_node {
    combination_node* combination_head;
    struct permutation_node* next;
} permutation_node;

void toUpper(char* word);

int hashLength(char* word);

int genWordHash(char* word);

void sortString(char* word, char* sorted);

#endif // WORDHASH_H
