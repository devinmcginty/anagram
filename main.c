// main.c
//
// Devin McGinty

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./wordhash.h"

// Dictionary file to read in
#define DICTIONARY_FILE "./words"
// Boolean constants
#define TRUE 1
#define FALSE 0

// Dynamically creates collection of hashed words
void hashWords(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM]);

// Clears collection of linked lists from memory.
void deleteWordData(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM]);

// Find and print all anagrams of a word
void findAnagrams(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM],
                  char word[]);

// Find and print all words given certain fixed characters
void findFixedWords(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM],
                   char word[]);

// Returns true if argument is a capital letter
int isLetter(char c);

int main(int argc, char const *argv[]) {
    const int MINIMUM_ARGUMENTS = 2;
    const char* CROSSWORD_flag = "-f";
    const char* INPUT_ERROR = "Insufficient input arguments given\n";
    if (argc < MINIMUM_ARGUMENTS) {
        fprintf(stderr, "%s\n", INPUT_ERROR);
        exit(1);
    }
    WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM] = {{NULL}};
    hashWords(wordData);
    char word[MAX_WORD_LEN];
    int i,
        crossword = FALSE;
    for (i = 1; i < argc; i++) {
        if (crossword) {
            // Crossword mode
            crossword = FALSE;
            strcpy(word, argv[i]);
            findFixedWords(wordData, word);
            printf("\n");
        }
        else if (strcmp(argv[i], CROSSWORD_flag) == 0) {
            // Activate crossword mode for next word
            crossword = TRUE;
        }
        else {
            // Anagram mode
            strcpy(word, argv[i]);
            findAnagrams(wordData, word);
            printf("\n");
        }
    }
    if (crossword) {
        fprintf(stderr, "%s\n", INPUT_ERROR);
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
        fprintf(stderr,
                "dictionary file %s not found.\n",
                DICTIONARY_FILE);
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
            }
            else {
                free(wordData[i][j]);
            }
        }
    }
}

void findAnagrams(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM],
                  char word[]) {
    int len, hash;
    len = hashLength(word);
    hash = genWordHash(word);
    printAnagrams(wordData[len][hash], word);
}

void findFixedWords(WordNode* wordData[LENGTH_HASH][MAX_HASH_NUM],
                   char word[]) {
    toUpper(word);
    int lenhash, i, c, length, match;
    lenhash = hashLength(word);
    length = strlen(word);
    WordNode* position = NULL;
    WordNode* matchList = NULL; // I am using a linked list to sort the output
    for (i = 0; i < MAX_HASH_NUM; i++) {
        for (position = wordData[lenhash][i];
             position != NULL;
             position = position->next) {
            match = TRUE;
            if (length != strlen(position->word)) {
                continue;
            }
            for (c = 0; c < length; c++) {
                if (!isLetter(word[c])) {
                    continue;
                }
                else if (word[c] != position->word[c]) {
                    match = FALSE;
                    break;
                }
            }
            if (match) {
                insertWord(&matchList, position->word);
            }
        }
    }
    printList(matchList);
}

int isLetter(char c) {
    return ('A' <= c && 'Z' >= c);
}
