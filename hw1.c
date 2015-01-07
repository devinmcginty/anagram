#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./wordhash.h"

#define DICTIONARY_FILE "./words"

void hashWords(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM]);

void deleteWordData(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM]);

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No input arguments given\n");
        exit(1);
    }
    WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM] = {{NULL}};
    hashWords(wordData);

    deleteWordData(wordData);
    exit(0);
}

void hashWords(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM]) {
    // Open File
    char fmode[] = "r";
    FILE* dictFile = fopen(DICTIONARY_FILE, fmode);
    if (dictFile == NULL) {
        fclose(dictFile);
        fprintf(stderr, "word file %s not found.\n", DICTIONARY_FILE);
        exit(1);
    }
    // Hash words
    int len,
        hash;
    char word[MAX_WORD_LEN];
    while(fgets(word, sizeof(word), dictFile) != NULL) {
        len = hashLength(word);
        hash = genWordHash(word);
        insertWord(&wordData[len][hash], word);
    }
    fclose(dictFile);
}

void deleteWordData(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM]) {
    int i, j;
    for (i = 0; i < (LENGTH_HASH); i++) {
        for (j = 0; j < MAX_HASH_NUM; j++) {
            if (wordData[i][j] != NULL) {
                deleteList(wordData[i][j]);
            } else {
                free(wordData[i][j]);
            }
        }
    }
}
