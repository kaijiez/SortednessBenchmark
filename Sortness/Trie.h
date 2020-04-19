
#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED

struct TrieNode* getNode(void);

void Trie_insert(struct TrieNode* root, std::string key);

bool Trie_search(struct TrieNode* root, std::string key);

#endif //TRIE_H_INCLUDED