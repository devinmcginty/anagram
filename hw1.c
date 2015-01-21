#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./wordhash.h"

#define DICTIONARY_FILE "./words"
#define TRUE 1
#define FALSE 0

void hashWords(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM]);

void deleteWordData(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM]);

void makeAnagrams(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM],
                   char word[]);

int isNumber(char str[]);

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No input arguments given\n");
        exit(1);
    }
    WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM] = {{NULL}};
    hashWords(wordData);
    char word[MAX_WORD_LEN];
    if (argc == 2) {
        strcpy(word, argv[1]);
        int len, hash;
        len = hashLength(word);
        hash = genWordHash(word);
        printList(wordData[len][hash]);
        // makeAnagrams(wordData, word);
    }
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
    int len, hash;
    char word[MAX_WORD_LEN],
         *termPos;
    while(fgets(word, sizeof(word), dictFile) != NULL) {
        if((termPos = strchr(word, '\n')) != NULL) { *termPos = '\0';}
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

void makeAnagrams(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM],
                   char word[]) {
    int len, hash;
    len = hashLength(word);
    hash = genWordHash(word);
    printAnagrams(wordData[len][hash], word);
}

int isNumber(char str[]) {
    int i,
        len = strlen(str),
        ret = TRUE;
    for (i = 0; i < len; i++) {
        if (!isdigit(str[i])) {
            ret = FALSE;
            break;
        }
    }
    return ret;
}
