#ifndef __TRIE_H__
#define __TRIE_H__

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>

#define MAX_LENGTH 50
#define MAX_SUGGETS 20

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define INDEX_TO_CHAR(i) ((int)i + (int)'a')

// Trie node
typedef struct Trie
{
    struct Trie *children[ALPHABET_SIZE];
    bool isEndOfWord; // true if the node represents end of a word
} TrieNode;

TrieNode *createNode();
void Trie_insert(TrieNode *root, const char *key);
bool Trie_search(TrieNode *root, const char *key);
bool isEmpty(TrieNode* root);
bool isEndOfWord(TrieNode* root);
void Trie_display(TrieNode* root, char *str, int level);
TrieNode* Trie_remove(TrieNode* root, char *key, int level);
int wordCount(TrieNode *root);
int Autocomplete(TrieNode* root, const char *query, char output[][MAX_LENGTH]);
void Trie_delete(TrieNode **root);

#endif