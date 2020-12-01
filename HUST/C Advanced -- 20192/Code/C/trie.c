#include "trie.h"

// Returns new trie node (initialized to NULLs)
TrieNode *createNode()
{
    TrieNode *pNode = NULL;
    pNode = (TrieNode *)malloc(sizeof(TrieNode));

    if (pNode)
    {
        pNode->isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            pNode->children[i] = NULL;
    }
    return pNode;
}

// If not present, inserts key into trie 
// If the key is prefix of trie node, just marks leaf node 
void Trie_insert(TrieNode *root, const char *key)
{
    int length = strlen(key);
    int index;
    TrieNode *pCrawl = root; // Iter
    
    for (int level = 0; level < length; ++level)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = createNode();
        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else false
bool Trie_search(TrieNode *root, const char *key)
{
    int length = strlen(key);
    int index;
    TrieNode *pCrawl = root; // Iter

    for (int level = 0; level < length; ++level)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            return false;
        pCrawl = pCrawl->children[index];
    }

    // Last node can be NULL or not end of word
    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

// Returns true if root has no children, else false 
bool isEmpty(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true; 
}

// Check if current node is end of word or not
bool isEndOfWord(TrieNode* root)
{
    return root->isEndOfWord != false;
}

/* char str[20]; Trie_display(root, str, 0); */
// Display the content of Trie
void Trie_display(TrieNode* root, char *str, int level) 
{ 
    // If node is end of word, it indicates end
    // of string, so a null character is added
    // and string is displayed
    if (isEndOfWord(root))
    {
        str[level] = '\0';
        puts(str);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)  
    {
        // if NON NULL child is found 
        // add parent key to str and 
        // call the display function recursively 
        // for child node 
        if (root->children[i])  
        {
            str[level] = INDEX_TO_CHAR(i);
            Trie_display(root->children[i], str, level + 1); 
        } 
    } 
}

// Recursive function to delete a key from given Trie 
TrieNode* Trie_remove(TrieNode* root, char *key, int level) // level = 0
{ 
    // If tree is empty 
    if (!root) 
        return NULL; 
  
    // If last character of key is being processed 
    if (level == strlen(key))
    {
        // This node is no more end of word after 
        // removal of given key 
        if (root->isEndOfWord) 
            root->isEndOfWord = false; 
  
        // If given is not prefix of any other word 
        if (isEmpty(root)) { 
            free(root); 
            root = NULL; 
        }

        return root; 
    } 
  
    // If not last character, recur for the child 
    // obtained using ASCII value 
    int index = CHAR_TO_INDEX(key[level]);
    root->children[index] = Trie_remove(root->children[index], key, level + 1); 
  
    // If root does not have any child (its only child got  
    // deleted), and it is not end of another word. 
    if (isEmpty(root) && (root->isEndOfWord == false))
    { 
        free(root); 
        root = NULL; 
    }

    return root; 
}

// Count number of words
int wordCount(TrieNode *root) 
{ 
    int result = 0;

    // Leaf denotes end of a word 
    if (root->isEndOfWord) 
        result++; 
      
    for (int i = 0; i < ALPHABET_SIZE; i++)     
        if (root -> children[i]) 
            result += wordCount(root->children[i]); 
     
    return result;    
}

void suggestions(TrieNode* root, char *currPrefix, int *n, char output[][MAX_LENGTH])
{
    if (*n == MAX_SUGGETS)
        return;
    // found a string in Trie with the given prefix 
    if (root->isEndOfWord)
    {
        strcpy(output[*n], currPrefix);
        (*n)++;
    }

    // All children struct node pointers are NULL
    if (isEmpty(root))
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            // append current character to currPrefix string
            char ch = INDEX_TO_CHAR(i);
            strncat(currPrefix, &ch, 1);

            // recur over the rest
            suggestions(root->children[i], currPrefix, n, output);
            // remove last character
            currPrefix[strlen(currPrefix)-1] = '\0';
        }
    }
}

// Returns a list of suggestions
int Autocomplete(TrieNode* root, const char *query, char output[][MAX_LENGTH])
{
    TrieNode* pCrawl = root;

    // Check if prefix is present and find the
    // the node (of last level) with last character
    // of given string.
    int level;
    int length = strlen(query);
    for (level = 0; level < length; level++)
    {
        int index = CHAR_TO_INDEX(query[level]);

        // no string in the Trie has this prefix
        if (!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }

    // If prefix is present as a word.
    bool isWord = (pCrawl->isEndOfWord == true);
  
    // If prefix is last node of tree (has no children)
    bool isLast = isEmpty(pCrawl);

    // If prefix is present as a word, but
    // there is no subtree below the last
    // matching node.
    if (isWord && isLast)
    {
        strcpy(output[0], query);
        return 1;
    }

    // If there are are nodes below last
    // matching character.
    if (!isLast)
    {
        int n = 0;
        char prefix[50];
        strcpy(prefix, query);
        suggestions(pCrawl, prefix, &n, output);
        return n;
    }
}

void Trie_delete(TrieNode **root)
{
    if (*root == NULL)
    {
        printf("Root NULL\n");
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if ((*root)->children[i])
            Trie_delete(&(*root)->children[i]);
    }
    free(*root);
    *root = NULL;
}