#include <iostream>
#include "Trie.h"
using namespace std;

const int ALPHABET_SIZE = 1000;     //should be change to 10, but same result

// trie node 
struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];

    // isEndOfWord is true if the node represents 
    // end of a word 
    bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs) 
struct TrieNode* getNode(void)
{
    struct TrieNode* pNode = new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void Trie_insert(struct TrieNode* root, string key)
{
    struct TrieNode* pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - '0';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf 
    pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else 
// false 
bool Trie_search(struct TrieNode* root, string key)
{
    struct TrieNode* pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - '0';
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}