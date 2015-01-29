#ifndef WORDHASH_H
#define WORDHASH_H

// Words can hash between 0 and 63
#define MAX_HASH_NUM 64
// The size buffer for words
#define MAX_WORD_LEN 32
// Word lengths can hash from 0 to 7
#define LENGTH_HASH 8
// Words don't have less than 1 character
#define MIN_WORD_LEN 1

// Linked list node
typedef struct WordNode {
    char word[MAX_WORD_LEN];    // Word string
    struct WordNode* next;      // Pointer to next node
} WordNode;

// Capitalizes word in place
void toUpper(char* word);

// Returns the hash value of a word's length
// ([word length] - [minimum word length]) mod [maximum length hash value]
int hashLength(char* word);

// Returns the hash value of the characters in a word.
// Uses the sum of character values 'A' = 0, 'B' = 2, ..., 'Z' = 26
int genWordHash(char* word);

// Alphabetizes a word and places it in sorted
void sortString(char* word, char* sorted);

// Returns a WordNode struct with word data
struct WordNode* createNode(char word[]);

// Creates a WordNode out of word and inserts it in sorted order
void insertWord(struct WordNode** head, char word[]);

// Prints a linked list
void printList(struct WordNode* head);

// Prints all anagrams of word in linked list
void printAnagrams(struct WordNode* head, char word[]);

// Deletes a linked list
void deleteList(struct WordNode* head);

#endif // WORDHASH_H
