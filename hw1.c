#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./wordhash.h"

#define DICTIONARY_FILE "./words"

struct WordNode* hashWords(WordNode wordData[LENGTH_HASH][MAX_HASH_NUM]);

int main(int argc, char const *argv[]) {
    WordNode wordData[LENGTH_HASH][MAX_HASH_NUM];
    int i, j;

    hashWords(wordData);

    // for (i = 0; i < (LENGTH_HASH); i++) {
    //     for (j = 0; j < MAX_HASH_NUM; j++) {
    //         printf("%d %d %s %s\n", i, j, wordData[i][j].combination, wordData[i][j].word);
    //     }
    // }

    // if (argc >= 2) {
    //     char word[63];
    //     strcpy(word, argv[1]);
    //     toUpper(word);
    //     printf("%s\t%d\n", word, genWordHash(word));
    //     char sorted[strlen(word)];
    //     sortString(word, sorted);
    //     printf("%s\n", sorted);
    //     if (strcmp(sorted, word) == 0) {
    //         printf("Alphabetical\n");
    //     } else {
    //         printf("Not alphabetical\n");
    //     }
    // } else {
    //     int test[50] = {0},
    //         i;
    //     for (i = 0; i < 50; i++) {
    //         printf("%d\n", test[i]);
    //     }
    // }
    return 0;
}

struct WordNode* hashWords(WordNode wordData[LENGTH_HASH][MAX_HASH_NUM]) {
    // Open File
    char fmode[] = "r";
    FILE* dictFile = fopen(DICTIONARY_FILE, fmode);
    if (dictFile == NULL) {
        fclose(dictFile);
        fprintf(stderr, "Word file %s not found.\n", DICTIONARY_FILE);
        exit(1);
    }
    // Hash words
    int len,
        hash;
    char word[MAX_WORD_LEN];
    WordNode* newNode;
    while(fgets(word, sizeof(word), dictFile) != NULL) {
        len = hashLength(word);
        hash = genWordHash(word);
        createNode(word);
        // strcpy(wordData[len][hash].word, word);
    }
    fclose(dictFile);
}
