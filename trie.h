#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <cstdint>
#include <list>
using std::list;
using std::string;

const int ALPHABET_SIZE = 32;
int to_baudot(char c);

struct TrieNode
{
    string word;
    TrieNode *children[26] = {NULL};
};
struct Trie
{
        void add_word(const std::string &word);
        TrieNode root_node;
};
struct Match
{
    string word;
    uint64_t index; 
    Match(const string &init_word, uint64_t init_index) : word(init_word), index(init_index) {}
};
int match_sequence(const string &sequence, uint64_t sequence_start_index, list<Match> matches, list<TrieNode> &partial_matches, Trie &trie);
#endif